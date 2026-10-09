#include "SVTagModule.h"
#include "ImageTag.h"
#include "CPage.h"
#include "DownloadBinary.h"
#include "CDrawContextBase.h"
#include "TagUtils.h"
#include "string.h"
extern "C" {
extern char svoImageTagModuleSource[];
extern char svoImageModuleIDAttribute[];
extern char svoImageModuleWidthAttribute[];
extern char svoImageModuleHeightAttribute[];
extern char svoImageModuleSourceAttribute[];
extern char svoImageModuleEmptyString[];
extern char svoImageModuleDownloadAttribute[];
extern char svoImageModulePreValue[];
extern char svoImageModuleTagType[];
const void *DownloadBinary(DownloadBinaryState *);
void _DownloadBinary(DownloadBinaryState *, int);
void SetDimensions___dupe2(DownloadBinaryState *, unsigned short, unsigned short);
void SetPath(DownloadBinaryState *, char *);
void SetDownloadCallback(DownloadBinaryState *, DownloadCallback);
void SetID___dupe2(DownloadBinaryState *, int);
int GetID(DownloadBinaryState *);
unsigned short GetWidth(DownloadBinaryState *);
unsigned short GetHeight(DownloadBinaryState *);
void PopInTransitArray(CPage *, DownloadBinaryState *);
void PushPostTransitionArray(CPage *, DownloadBinaryState *, DownloadBinaryState **);
char *GetTagTypeName(SVTag *);
void InitImage___dupe2(ImageTagState *, char *, int);
CDrawContextBase *GetDrawContext();
}
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_ImageTagModule_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTagModule.h"
#include <string.h>

extern "C" {
extern SVTagModuleState *svoImageTagModuleInstance;
extern const SVTagModuleVtablePrefix svoImageTagModuleVtable;
extern char svoImageTagModuleSource[];
extern char svoImageTagModuleName[];
void ImageTag(void *memory, iks *xml, CAllContextData *contexts);

#define SECTION(name) __attribute__((section(".svo_ImageTagModule_" #name)))

SECTION(IsMyTag___dupe8) int IsMyTag___dupe8(SVTagModuleState *module, iks *xml)
{
    if (iks_type(xml) != IKS_TAG) __SVO_Assert_Handler(svoImageTagModuleSource, 0x1A);
    return strcmp(iks_name(xml), svoImageTagModuleName) == 0;
}

SECTION(BuildTag___dupe9) void BuildTag___dupe9(SVTagModuleState *module, iks *xml, SVTag **outTag, SVTag **tagList, CAllContextData *contexts)
{
    if (!xml || !tagList) __SVO_Assert_Handler(svoImageTagModuleSource, 0x20);
    void *memory = SVTagNew(0x170);
    ImageTag(memory, xml, contexts);
    *outTag = (SVTag *)memory;
}

SECTION(getInstance___dupe10) SVTagModuleState *getInstance___dupe10(void)
{
    if (!svoImageTagModuleInstance) {
        SVTagModuleState *module = (SVTagModuleState *)SVTagModuleNew(4);
        module->vtable = &svoImageTagModuleVtable;
        svoImageTagModuleInstance = module;
    }
    return svoImageTagModuleInstance;
}

SECTION(FreeResources___dupe17) void FreeResources___dupe17(SVTagModuleState *module)
{
    if (svoImageTagModuleInstance) {
        svoImageTagModuleInstance->vtable->destroy(svoImageTagModuleInstance, 3);
        svoImageTagModuleInstance = 0;
    }
}

}

extern "C" SECTION(processImageCB) void processImageCB(unsigned int status, char *buffer, int length, void *user, int swapBuffers)
{
    if (!buffer) __SVO_Assert_Handler(svoImageTagModuleSource, 0x6A);
    ImageTagState *image = 0;
    DownloadBinaryState download;
    DownloadBinary(&download);
    CPage *page = (CPage *)user;
    PopInTransitArray(page, &download);
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    for (int i = 0; i < 256; ++i) {
        image = (ImageTagState *)tags[i];
        if (!strcmp(GetTagTypeName(&image->base), svoImageModuleTagType)) {
            int id = image->m_iID;
            if (id == GetID(&download)) break;
        }
    }
    if (!image) __SVO_Assert_Handler(svoImageTagModuleSource, 0x7D);
    InitImage___dupe2(image, buffer, length);
    if (status != 200) __SVO_Assert_Handler(svoImageTagModuleSource, 0x87);
    CDrawContextBase *draw = GetDrawContext();
    int id = GetID(&download);
    unsigned short width = GetWidth(&download);
    unsigned short height = GetHeight(&download);
    draw->vtable->StoreDownloadedImage(draw, id, buffer, width, height);
    _DownloadBinary(&download, 2);
}

extern "C" SECTION(ScanTags___dupe4) void ScanTags___dupe4(SVTagModuleState *module, iks *xml, SVTag **tags, CAllContextData *contexts, SVTagScanResult *actions)
{
    char *mode = 0;
    char *source = 0;
    int width = 0;
    int height = 0;
    int id;
    DownloadBinaryState *queued;
    DownloadBinaryState download;
    DownloadBinary(&download);
    memset(&download, 0, sizeof(download));
    getIntAttrib(xml, svoImageModuleIDAttribute, &id);
    getIntAttrib(xml, svoImageModuleWidthAttribute, &width);
    getIntAttrib(xml, svoImageModuleHeightAttribute, &height);
    getStringAttrib(xml, svoImageModuleSourceAttribute, &source);
    if (strcmp(source, svoImageModuleEmptyString)) {
        getStringAttrib(xml, svoImageModuleDownloadAttribute, &mode);
        SetDimensions___dupe2(&download, width, height);
        SetPath(&download, source);
        SetDownloadCallback(&download, processImageCB);
        SetID___dupe2(&download, id);
        PushPostTransitionArray(contexts->pMain, &download, &queued);
        int action = strcmp(svoImageModulePreValue, mode) == 0 ? 1 : 2;
        actions->download = queued;
        actions->action = action;
    }
    _DownloadBinary(&download, 2);
}
