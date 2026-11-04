#include "common.h"

#define MEDIUS_CODEC_SECTION(name) __attribute__((section(".medius_codec_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_codec_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

typedef int RT_4BYTE;
typedef short RT_2BYTE;
typedef unsigned char RT_U1BYTE;
typedef void *CODEC_HANDLE;
typedef int NetStreamMediaAudioType;
typedef int CODEC_MODE;
typedef void (*CODEC_INIT_FUNC)(CODEC_HANDLE);
typedef void (*CODEC_DESTROY_FUNC)(CODEC_HANDLE);
typedef RT_4BYTE (*ENCODE_FRAME_FUNC)(CODEC_HANDLE, RT_2BYTE *, RT_U1BYTE *);
typedef RT_4BYTE (*DECODE_FRAME_FUNC)(CODEC_HANDLE, RT_U1BYTE *, RT_2BYTE *);

// Layout from the retail ELF debug information.
typedef struct { // 0xA1C
    /* 0x000 */ NetStreamMediaAudioType eMedia;
    /* 0x004 */ CODEC_MODE eMode;
    /* 0x008 */ RT_4BYTE nBytesPerFrame;
    /* 0x00C */ RT_4BYTE nBytesEncodedFrame;
    /* 0x010 */ RT_4BYTE nEncodeBytesPerUpdate;
    /* 0x014 */ RT_4BYTE nDecodeBytesPerUpdate;
    /* 0x018 */ RT_4BYTE nEncodeBytesLast;
    /* 0x01C */ RT_4BYTE nDecodeBytesLast;
    /* 0x020 */ CODEC_INIT_FUNC initFunc;
    /* 0x024 */ CODEC_DESTROY_FUNC destroyFunc;
    /* 0x028 */ ENCODE_FRAME_FUNC encodeFunc;
    /* 0x02C */ DECODE_FRAME_FUNC decodeFunc;
    /* 0x030 */ RT_4BYTE m_RawSizeBytes;
    /* 0x034 */ RT_4BYTE m_EncodedBytes;
    /* 0x038 */ CODEC_HANDLE hCodec;
    /* 0x03C */ RT_U1BYTE m_Encoded[480];
    /* 0x21C */ RT_U1BYTE m_RawBuff[2048];
} CODEC;

// Handle counter handed out by the stub codec.
extern int mediusStubCodecHandle;
extern int rt_memory_free(void **pointer);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/codec", CreateCodec);

void MEDIUS_CODEC_SECTION(DestroyCodec) DestroyCodec(CODEC *pCodec)
{
    if (pCodec) {
        if (pCodec->destroyFunc) pCodec->destroyFunc(pCodec->hCodec);
        rt_memory_free((void **)&pCodec);
    }
}

RT_4BYTE MEDIUS_CODEC_SECTION(InitCodec) InitCodec(CODEC *pCodec)
{
    RT_4BYTE result;

    if (!pCodec || !pCodec->hCodec) {
        result = -1;
    } else {
        if (pCodec->initFunc) pCodec->initFunc(pCodec->hCodec);
        pCodec->m_RawSizeBytes = 0;
        result = 0;
        pCodec->m_EncodedBytes = 0;
    }
    return result;
}

NetStreamMediaAudioType MEDIUS_CODEC_SECTION(GetCodecType) GetCodecType(CODEC *pCodec)
{
    return pCodec->eMedia;
}

RT_4BYTE MEDIUS_CODEC_SECTION(GetEncodedFrameSize) GetEncodedFrameSize(CODEC *pCodec)
{
    return pCodec->nBytesEncodedFrame;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/codec", EncodeData);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/StreamMedia/src/codec", DecodeData);

CODEC_HANDLE MEDIUS_CODEC_SECTION(stubCreate) stubCreate(void)
{
    return (CODEC_HANDLE)++mediusStubCodecHandle;
}

void MEDIUS_CODEC_SECTION(stubDestroy) stubDestroy(CODEC_HANDLE hCodec)
{
}

void MEDIUS_CODEC_SECTION(stubInit) stubInit(CODEC_HANDLE hCodec)
{
}

RT_4BYTE MEDIUS_CODEC_SECTION(stubEncode) stubEncode(CODEC_HANDLE hCodec, RT_2BYTE *pIn, RT_U1BYTE *pOut)
{
    return 0;
}

RT_4BYTE MEDIUS_CODEC_SECTION(stubDecode) stubDecode(CODEC_HANDLE hCodec, RT_U1BYTE *pIn, RT_2BYTE *pOut)
{
    return 0;
}
