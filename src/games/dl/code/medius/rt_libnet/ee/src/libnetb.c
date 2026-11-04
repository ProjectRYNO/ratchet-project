#include "common.h"

#define MEDIUS_LIBNETB_SECTION(name) __attribute__((section(".medius_libnetb_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_libnetb_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef int RT_4BYTE;
typedef unsigned int RT_U4BYTE;
typedef void *CID_B;

typedef struct { void *pData; RT_U4BYTE nSize; } RT_DATA_INFO;
typedef struct { RT_DATA_INFO aData[8]; RT_U4BYTE nTotalSize; RT_4BYTE nLength; } RT_DATA_VECTOR;

typedef struct { RT_4BYTE msg_type; RT_4BYTE cid_ee; RT_4BYTE result; } CID_STATE_UPDATE;
typedef struct { RT_4BYTE msg_type; RT_4BYTE cid_ee; RT_4BYTE count; } CID_SYNC;
typedef struct {
    RT_4BYTE msg_type; RT_4BYTE cid_ee; RT_4BYTE code; RT_4BYTE data_len; RT_4BYTE ret;
    void *p0; void *p1; RT_4BYTE s0; RT_4BYTE s1;
} CID_CONTROL;
typedef struct CID_DATA {
    RT_4BYTE msg_type; RT_4BYTE cid_ee; RT_4BYTE count; RT_4BYTE addr_count; RT_4BYTE result; RT_4BYTE flags;
    void *p0; void *p1; RT_4BYTE s0; RT_4BYTE s1; RT_4BYTE n_recvd; struct CID_DATA *next;
} CID_DATA;
typedef struct CID {
    RT_4BYTE msg_type; RT_4BYTE last_flags; RT_4BYTE result; RT_4BYTE b_opened; RT_4BYTE cid_ee; RT_4BYTE cid_iop;
    RT_4BYTE type; RT_4BYTE local_port; RT_4BYTE remote_port; RT_4BYTE remote_ip; RT_4BYTE b_sync_recv;
    RT_4BYTE b_sync_outstanding; RT_4BYTE sync_count; void *p_sync_buf; CID_DATA *msg_head; struct CID *next;
} CID;

// head of the libnetb socket (CID) linked list
extern CID *mediusLibnetbCidList;

void *memset(void *, int, unsigned int);
int init_vblock_trans(void *msg, int size, RT_DATA_VECTOR *vec);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetCreate);

int MEDIUS_LIBNETB_SECTION(sceBInetOpen) sceBInetOpen(void *cd, unsigned int *buf, CID_B cid_b, int ms)
{
    CID_STATE_UPDATE msg;
    RT_DATA_VECTOR vec;
    vec.nLength = 0;
    vec.nTotalSize = 0;
    memset(&msg, 0, sizeof(msg));
    msg.msg_type = 2;
    msg.cid_ee = ((CID *)cid_b)->cid_ee;
    return init_vblock_trans(&msg, sizeof(msg), &vec);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetClose);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetRecv);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetRecvFrom);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetRecvEcho);

int MEDIUS_LIBNETB_SECTION(sceBInetSend) sceBInetSend(void *cd, unsigned int *buf, CID_B cid_b, void *ptr, int count, int *pflags, int ms)
{
    CID_DATA msg;
    RT_DATA_VECTOR vec;
    *pflags = 0;
    vec.nLength = 0;
    vec.nTotalSize = 0;
    vec.aData[vec.nLength].pData = ptr;
    vec.aData[vec.nLength].nSize = count;
    vec.nTotalSize += count;
    vec.nLength++;
    memset(&msg, 0, sizeof(msg));
    msg.msg_type = 9;
    msg.cid_ee = ((CID *)cid_b)->cid_ee;
    msg.count = count;
    msg.flags = *pflags;
    if (init_vblock_trans(&msg, sizeof(msg), &vec) != 0)
        count = 0;
    return count;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetSendTo);

int MEDIUS_LIBNETB_SECTION(sceBInetVSend) sceBInetVSend(void *cd, unsigned int *buf, CID_B cid_b, RT_DATA_VECTOR *p_vector, int *pflags, int ms)
{
    CID_DATA msg;
    RT_U4BYTE n;
    *pflags = 0;
    memset(&msg, 0, sizeof(msg));
    msg.msg_type = 9;
    msg.cid_ee = ((CID *)cid_b)->cid_ee;
    msg.count = p_vector->nTotalSize;
    msg.flags = *pflags;
    return init_vblock_trans(&msg, sizeof(msg), p_vector) ? 0 : p_vector->nTotalSize;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetVSendTo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetSendEcho);

int MEDIUS_LIBNETB_SECTION(sceBInetControl) sceBInetControl(void *cd, unsigned int *buf, CID_B cid_b, int code, void *ptr, int len)
{
    CID_CONTROL msg;
    RT_DATA_VECTOR vec;
    memset(&msg, 0, sizeof(msg));
    msg.msg_type = 13;
    msg.cid_ee = ((CID *)cid_b)->cid_ee;
    msg.code = code;
    msg.data_len = len;
    vec.nLength = 0;
    vec.nTotalSize = 0;
    vec.aData[vec.nLength].pData = ptr;
    vec.aData[vec.nLength].nSize = len;
    vec.nTotalSize += len;
    vec.nLength++;
    return init_vblock_trans(&msg, sizeof(msg), &vec);
}

int MEDIUS_LIBNETB_SECTION(sceBInetGetAvailBytesToRead) sceBInetGetAvailBytesToRead(CID_B cid_b, int *pflags)
{
    CID *cid = (CID *)cid_b;
    CID_DATA *d;
    int n = 0;
    *pflags = 0;
    if (cid->msg_head) {
        d = (CID_DATA *)cid->msg_head->p0;
        n = d->count;
        if (n == 0)
            *pflags = d->flags;
    }
    return n;
}

int MEDIUS_LIBNETB_SECTION(sceBInetDisplayLibnetbState) sceBInetDisplayLibnetbState(void)
{
    return 0;
}

int MEDIUS_LIBNETB_SECTION(sceBInetIsOpened) sceBInetIsOpened(CID_B cid_b, int *pbOpened)
{
    CID *cid = (CID *)cid_b;
    *pbOpened = cid->b_opened;
    return cid->result;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBInetUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBLibnetInitialize);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", sceBLibnetTerminate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", init_vblock_trans);

int MEDIUS_LIBNETB_SECTION(process_create_block) process_create_block(CID *p_cid)
{
    CID *p = mediusLibnetbCidList;
    while (p) {
        if (p->cid_ee == p_cid->cid_ee) {
            p->cid_iop = p_cid->cid_iop;
            p->result = p_cid->result;
            p = 0;
        } else {
            p = p->next;
        }
    }
    return 0;
}

int MEDIUS_LIBNETB_SECTION(process_open_response) process_open_response(CID_STATE_UPDATE *p_up)
{
    CID *p = mediusLibnetbCidList;
    while (p) {
        if (p->cid_ee == p_up->cid_ee) {
            int r = p_up->result;
            p->result = r;
            if (r == 0)
                p->b_opened = 1;
            p = 0;
        } else {
            p = p->next;
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", process_data_block);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/rt_libnet/ee/src/libnetb", process_control_block);

int MEDIUS_LIBNETB_SECTION(process_sync_block) process_sync_block(CID_SYNC *p_sync)
{
    CID *p = mediusLibnetbCidList;
    while (p) {
        if (p->cid_ee == p_sync->cid_ee) {
            p->b_sync_outstanding = 0;
            p = 0;
        } else {
            p = p->next;
        }
    }
    return 0;
}
