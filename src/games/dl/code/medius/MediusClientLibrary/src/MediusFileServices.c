#include "common.h"
#include "MediusRequests.h"

#define MEDIUS_FILES_SECTION(name) __attribute__((section(".medius_files_" #name)))

// Retained assembly and compiled functions keep their original retail slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .medius_files_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

MediusErrorCode MEDIUS_FILES_SECTION(MediusFileCreate) MediusFileCreate(MediusFileCreateRequest *MyFileCreateRequest, MediusFileTypeCreateCallback MyFileCreateCallback,void *pUserData)
{
    MyFileCreateRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[101] = MyFileCreateCallback;
    gUserArguments[101] = pUserData;
    if (MediusSendMessage(1, 0xa5, 0x1d8, MyFileCreateRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusFileServices", MediusFileUpload);

MediusErrorCode MEDIUS_FILES_SECTION(MediusFileClose) MediusFileClose(MediusFileCloseRequest *MyFileCloseRequest, MediusFileTypeCloseCallback MyFileCloseCallback,void *pUserData)
{
    MyFileCloseRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[103] = MyFileCloseCallback;
    gUserArguments[103] = pUserData;
    if (MediusSendMessage(1, 0xaa, 0xc4, MyFileCloseRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

MediusErrorCode MEDIUS_FILES_SECTION(MediusFileDownload) MediusFileDownload(MediusFileDownloadRequest *MyFileDownloadRequest, MediusFileTypeDownloadCallback MyFileDownloadCallback,void *pUserData)
{
    MyFileDownloadRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[104] = MyFileDownloadCallback;
    gUserArguments[104] = pUserData;
    if (MediusSendMessage(1, 0xac, 0xc4, MyFileDownloadRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusFileServices", func_01EDB288);

MediusErrorCode MEDIUS_FILES_SECTION(MediusFileDelete) MediusFileDelete(MediusFileDeleteRequest *MyFileDeleteRequest, MediusFileTypeDeleteCallback MyFileDeleteCallback,void *pUserData)
{
    MyFileDeleteRequest->MessageID[0x14] = 0;
    if (GlobalInitFlag != 1) return MediusErrorNotInitialized;
    if (!(ghMyConnection != 0)) return MediusErrorNotConnected;
    gMediusFunctionPointers[106] = MyFileDeleteCallback;
    gUserArguments[106] = pUserData;
    if (MediusSendMessage(1, 0xb0, 0xc4, MyFileDeleteRequest) != 0) return MediusErrorSendingMessage;
    return MediusErrorNone;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusFileServices", func_01EDB308);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusFileServices", MediusFileListFiles);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/medius/MediusClientLibrary/src/MediusFileServices", MediusFileInitAttributes);
