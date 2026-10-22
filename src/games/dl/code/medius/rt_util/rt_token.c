#include "common.h"
#include "rt_token.h"

#define MEDIUS_TOKEN_SECTION(name) __attribute__((section(".medius_token_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_token_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#define RT_INVALID_PARAM 2

extern void *memset(void *pointer, int value, unsigned int size);
extern void *memcpy(void *destination, const void *source, unsigned int size);
extern int rt_msg_set_u2byte(unsigned char *buffer, unsigned short value);
extern int rt_memory_allocate_init_zero(void **pointer, unsigned long size);
extern int rt_memory_free(void **pointer);

int MEDIUS_TOKEN_SECTION(rt_token_start) rt_token_start(RT_TOKEN_SYSTEM_INFO **pTokenSystem)
{
    if (!*pTokenSystem) {
        if (rt_memory_allocate_init_zero((void **)pTokenSystem, sizeof(RT_TOKEN_SYSTEM_INFO))) return RT_TOKEN_MEM_ALLOC;
        memset(*pTokenSystem, 0, sizeof(RT_TOKEN_SYSTEM_INFO));
        return 0;
    }
    return RT_TOKEN_ALREADY_INIT;
}

void MEDIUS_TOKEN_SECTION(rt_token_shutdown) rt_token_shutdown(RT_TOKEN_SYSTEM_INFO **pTokenSystem)
{
    if (*pTokenSystem) {
        rt_token_destroy_table(*pTokenSystem);
        rt_memory_free((void **)pTokenSystem);
        *pTokenSystem = 0;
    }
}

int MEDIUS_TOKEN_SECTION(rt_token_is_valid) rt_token_is_valid(RT_TOKEN_ID tokenID)
{
    if (tokenID >= RT_TOKEN_NO_OWNER) return 0;
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", func_01EABFE0);

void MEDIUS_TOKEN_SECTION(rt_token_free_owner) rt_token_free_owner(unsigned int OwnerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem)
{
    RT_TOKEN_ID tokenID;

    if (!pTokenSystem) rt_token_start(&pTokenSystem);
    if (OwnerID == RT_TOKEN_NO_OWNER) return;
    if (!pTokenSystem->num_tokens) return;
    for (tokenID = 0; tokenID < pTokenSystem->max_tokens; tokenID++) {
        if (pTokenSystem->p_token_info_array[tokenID].ownerID == OwnerID)
            rt_token_remove_ownership(tokenID, pTokenSystem);
    }
}

void MEDIUS_TOKEN_SECTION(rt_token_check_ownership) rt_token_check_ownership(RT_TOKEN_ID tokenID, unsigned int *pTokenOwnerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem)
{
    if (!pTokenSystem) rt_token_start(&pTokenSystem);
    if (!pTokenSystem->num_tokens || tokenID >= pTokenSystem->max_tokens
        || pTokenSystem->p_token_info_array[tokenID].ownerID == RT_TOKEN_NO_OWNER) {
        *pTokenOwnerID = RT_TOKEN_NO_OWNER;
    } else {
        *pTokenOwnerID = pTokenSystem->p_token_info_array[tokenID].ownerID;
    }
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_grant_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_release_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_update_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_list_check_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_list_grant_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_list_release_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_list_update_ownership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_create_table);

int MEDIUS_TOKEN_SECTION(rt_token_expand_table) rt_token_expand_table(unsigned int tokenCount, RT_TOKEN_SYSTEM_INFO *pTokenSystem)
{
    void *pOld;
    int size;

    if (!pTokenSystem) return RT_TOKEN_RESULT_INVALID_PARAM;
    if (rt_memory_allocate_init_zero(&pOld, pTokenSystem->max_tokens * sizeof(RT_TOKEN_DATA))) return RT_TOKEN_MEM_ALLOC;
    size = pTokenSystem->max_tokens * sizeof(RT_TOKEN_DATA);
    memcpy(pOld, pTokenSystem->p_token_info_array, size);
    rt_memory_free((void **)&pTokenSystem->p_token_info_array);
    if (rt_token_create_table(tokenCount, pTokenSystem)) return RT_TOKEN_MEM_ALLOC;
    memcpy(pTokenSystem->p_token_info_array, pOld, size);
    rt_memory_free(&pOld);
    return 0;
}

void MEDIUS_TOKEN_SECTION(rt_token_destroy_table) rt_token_destroy_table(RT_TOKEN_SYSTEM_INFO *pTokenSystem)
{
    if (!pTokenSystem) return;
    if (pTokenSystem->p_token_info_array) rt_memory_free((void **)&pTokenSystem->p_token_info_array);
    pTokenSystem->p_token_info_array = 0;
    pTokenSystem->max_tokens = 0;
    pTokenSystem->num_tokens = 0;
}

void MEDIUS_TOKEN_SECTION(rt_token_add_ownership) rt_token_add_ownership(RT_TOKEN_ID tokenID, unsigned int ownerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem)
{
    if (!pTokenSystem) return;
    if (!pTokenSystem->max_tokens) return;
    if (!pTokenSystem->p_token_info_array) return;
    pTokenSystem->p_token_info_array[tokenID].ownerID = ownerID;
    pTokenSystem->num_tokens++;
}

void MEDIUS_TOKEN_SECTION(rt_token_remove_ownership) rt_token_remove_ownership(RT_TOKEN_ID tokenID, RT_TOKEN_SYSTEM_INFO *pTokenSystem)
{
    // Indexed in place on purpose: a local RT_TOKEN_DATA pointer (&array[tokenID] or
    // array + tokenID) makes 2.96 emit the address addu with its operands swapped.
    if (pTokenSystem->p_token_info_array[tokenID].ownerID == RT_TOKEN_NO_OWNER) return;
    pTokenSystem->p_token_info_array[tokenID].state = 0;
    pTokenSystem->p_token_info_array[tokenID].ownerID = RT_TOKEN_NO_OWNER;
    pTokenSystem->num_tokens--;
    if (!pTokenSystem->num_tokens) rt_token_destroy_table(pTokenSystem);
}

int MEDIUS_TOKEN_SECTION(rt_token_build_token_msg) rt_token_build_token_msg(unsigned char *p_buffer, unsigned int max_buffer_len, unsigned int *pMsgLen,
                             unsigned char MsgType, unsigned short TokenID, unsigned int OwnerID)
{
    unsigned char msg[512];
    unsigned char *p = msg;
    unsigned int len;

    if (!((unsigned char)(MsgType - 1) < 3 || MsgType == 7 || MsgType == 8 || MsgType == 10 || MsgType == 9))
        return RT_INVALID_PARAM;
    *p++ = MsgType;
    rt_msg_set_u2byte(p, TokenID);
    p += 2;
    len = 3;
    if (MsgType == 7) {
        rt_msg_set_u2byte(p, OwnerID);
        len = 5;
    }
    if (len > max_buffer_len || !p_buffer) return RT_INVALID_PARAM;
    memcpy(p_buffer, msg, len);
    *pMsgLen = len;
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", rt_token_build_token_list_msg);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_util/rt_token", func_01EACE98);
