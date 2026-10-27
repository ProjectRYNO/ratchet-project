#ifndef MEDIUS_SEQUENCE_H
#define MEDIUS_SEQUENCE_H

// Stream-media audio (CSequence) and video (CVSequence) reorder buffers.
// Names and layouts from the retail ELF debug information.
#define SEQ_BLOCKS 64

typedef enum { THRESHOLD_LOW = 1 } THRESHOLD;
typedef enum { ExtraNetStreamMediaAudioType = 0xFFFFFF } NetStreamMediaAudioType;

typedef struct { // 0x100
    /* 0x00 */ unsigned int nSequence;
    /* 0x04 */ unsigned int nSize;
    /* 0x08 */ unsigned char data[248];
} SEQBLOCK;

typedef struct { // 0x4010
    /* 0x00 */ THRESHOLD m_eThreshold;
    /* 0x04 */ NetStreamMediaAudioType m_eMedia;
    /* 0x08 */ unsigned int m_iNext;
    /* 0x0C */ unsigned int m_nBlockCount;
    /* 0x10 */ SEQBLOCK m_Blocks[SEQ_BLOCKS];
} CSequence;

typedef struct { // 0x200
    /* 0x00 */ unsigned int nSequence;
    /* 0x04 */ unsigned int nSize;
    /* 0x08 */ unsigned char data[504];
} VSEQBLOCK;

typedef struct { // 0x800C
    /* 0x00 */ unsigned int m_iNext;
    /* 0x04 */ unsigned int m_iLast;
    /* 0x08 */ unsigned int m_nBlockCount;
    /* 0x0C */ VSEQBLOCK m_Blocks[SEQ_BLOCKS];
} CVSequence;

#ifdef __cplusplus
extern "C" {
#endif

CSequence *CreateSequence(void);
void DestroySequence(CSequence *pSequence);
void InitSequence(CSequence *pSequence);
CVSequence *CreateVSequence(void);
void DestroyVSequence(CVSequence *pSequence);

#ifdef __cplusplus
}
#endif

#endif
