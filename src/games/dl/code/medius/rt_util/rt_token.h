#ifndef RT_TOKEN_H
#define RT_TOKEN_H

#define RT_TOKEN_RESULT_ERROR 56001
#define RT_TOKEN_RESULT_INVALID_PARAM 56002
#define RT_TOKEN_RESULT_NOT_ENOUGH_SPACE 56003
#define RT_TOKEN_MEM_ALLOC 56004
#define RT_TOKEN_ALREADY_INIT 56005
#define RT_TOKEN_RESULT_NOT_IMPLEMENTED 56006
#define RT_TOKEN_RESULT_OTHER_OWNED 56007

// Owner ID of an unowned token; also the first invalid token ID.
#define RT_TOKEN_NO_OWNER 0xFFFF

typedef unsigned int RT_TOKEN_ID;

// Names and layouts from the retail ELF debug information.
typedef struct { // 0x4
    /* 0x0 */ unsigned short ownerID;
    /* 0x2 */ unsigned short state;
} RT_TOKEN_DATA;

typedef struct { // 0xC
    /* 0x0 */ unsigned int num_tokens;
    /* 0x4 */ unsigned int max_tokens;
    /* 0x8 */ RT_TOKEN_DATA *p_token_info_array;
} RT_TOKEN_SYSTEM_INFO;

#ifdef __cplusplus
extern "C" {
#endif

int rt_token_start(RT_TOKEN_SYSTEM_INFO **pTokenSystem);
void rt_token_shutdown(RT_TOKEN_SYSTEM_INFO **pTokenSystem);
int rt_token_is_valid(RT_TOKEN_ID tokenID);
void rt_token_free_owner(unsigned int OwnerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
void rt_token_check_ownership(RT_TOKEN_ID tokenID, unsigned int *pTokenOwnerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
int rt_token_grant_ownership(RT_TOKEN_ID tokenID, unsigned int *pClientID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
int rt_token_release_ownership(RT_TOKEN_ID tokenID, unsigned int ClientID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
int rt_token_update_ownership(RT_TOKEN_ID tokenID, unsigned int ownerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
int rt_token_create_table(unsigned int tokenCount, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
int rt_token_expand_table(unsigned int tokenCount, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
void rt_token_destroy_table(RT_TOKEN_SYSTEM_INFO *pTokenSystem);
void rt_token_add_ownership(RT_TOKEN_ID tokenID, unsigned int ownerID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
void rt_token_remove_ownership(RT_TOKEN_ID tokenID, RT_TOKEN_SYSTEM_INFO *pTokenSystem);
int rt_token_build_token_msg(unsigned char *p_buffer, unsigned int max_buffer_len, unsigned int *pMsgLen,
                             unsigned char MsgType, unsigned short TokenID, unsigned int OwnerID);

#ifdef __cplusplus
}
#endif

#endif
