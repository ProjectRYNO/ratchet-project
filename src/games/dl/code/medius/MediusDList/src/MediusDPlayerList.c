#include "common.h"
#include "../../rt_util/rt_pack.h"

#define MEDIUS_DPLIST_SECTION(name) __attribute__((section(".medius_dplist_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_dplist_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef struct MediusDMetaType MediusDMetaType;

// Player list meta type, created on first use.
extern MediusDMetaType *mediusDPlayerListMetaType;
// Field definitions of the player list meta type.
extern char mediusDPlayerListFields[];
typedef struct {
    MediusDMetaType *(*create)(int, void *, int);
    void (*destroy)(MediusDMetaType *);
} MediusDMetaTypeInterface;
extern const MediusDMetaTypeInterface MediusDMetaType_I;

MediusDMetaType *MEDIUS_DPLIST_SECTION(GetMediusDPlayerListMetaType) GetMediusDPlayerListMetaType(void)
{
    if (!mediusDPlayerListMetaType)
        mediusDPlayerListMetaType = MediusDMetaType_I.create(0, mediusDPlayerListFields, 0x2C);
    return mediusDPlayerListMetaType;
}

void MEDIUS_DPLIST_SECTION(DestroyPlayerListMetaType) DestroyPlayerListMetaType(void)
{
    if (mediusDPlayerListMetaType) {
        MediusDMetaType_I.destroy(mediusDPlayerListMetaType);
        mediusDPlayerListMetaType = 0;
    }
}

int MEDIUS_DPLIST_SECTION(rt_pack_u4byte) rt_pack_u4byte(int mode, RT_PACK_BUFFER *buffer, void *value)
{
    return rt_pack_anything(mode, buffer, value, 4);
}

int MEDIUS_DPLIST_SECTION(rt_pack_4byte) rt_pack_4byte(int mode, RT_PACK_BUFFER *buffer, void *value)
{
    return rt_pack_anything(mode, buffer, value, 4);
}

int MEDIUS_DPLIST_SECTION(rt_pack_u1byte) rt_pack_u1byte(int mode, RT_PACK_BUFFER *buffer, unsigned char *value)
{
    return rt_pack_1byte(mode, buffer, (char *)value);
}
