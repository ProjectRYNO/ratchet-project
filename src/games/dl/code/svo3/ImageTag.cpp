#include "TagUtils.h"
#include "CPage.h"
#include "CInputContextBase.h"
#include "CAudioContextBase.h"
#include "CDrawContextBase.h"
#include "CMemoryContextBase.h"
#include "Navigation.h"
#include "string.h"
#include "TagUtils.h"
#include "SVOString.h"
#include "ImageTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_ImageTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern char *svoImageTypeStrings[];

extern "C" {
extern char svoImageTagName[];
extern char gTagNotSetStr[];

}
extern "C" {
extern char *svoImageTypeStrings[];
}
extern char svoImageTagSource[];
extern char svoImageTagAudioClass[];
extern const SVTagVtablePrefix svoImageTagVtable;
CAudioContextBaseState *GetAudioContext(void);
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
void decodeEntityText(char *);
extern char svoImageTagAttrType[];
extern char svoImageTagAttrId[];
extern char svoImageTagAttrWidth[];
extern char svoImageTagAttrHeight[];
extern char svoImageTagAttrX[];
extern char svoImageTagAttrY[];
extern char svoImageTagAttrHref[];
void DefaultInit___dupe10(ImageTagState *);
int getImageTypeAttrib(ImageTagState *, iks *, char *, unsigned int *);
#define SECTION(name) __attribute__((section(".svo_ImageTag_" #name)))

SECTION(FreeResources___dupe18) void FreeResources___dupe18(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe11(SVTag *tag);
extern "C" SECTION(IsSelectable___dupe11) long IsSelectable___dupe11(SVTag *tag)
{
    return (tag->m_bSelectable != 0) & ((unsigned int)tag != 0xFFFFFF44u);
}

}

extern "C" SECTION(_ImageTag) void _ImageTag(ImageTagState *self, unsigned int flags)
{
    SVTag *tag = &self->base;
    tag->vtable = &svoImageTagVtable;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoImageTagSource, 0x33);
    draw->vtable->DestroyImage(draw, self->m_iID);
    if (self->ImageBuf) {
        svFreeSafe(tag->m_contexts->memoryContext, self->ImageBuf);
        self->ImageBuf = 0;
    }
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(DefaultInit___dupe10) void DefaultInit___dupe10(ImageTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoImageTagName, 64);
    tag->m_align = 1;
    tag->m_displayLength = 0;
    memset(tag->m_link, 0, 128);
    tag->m_imageType = 1;
    tag->base.m_fillColor = 0xFFFFFFFF;
    tag->base.m_lineColor = 0xFF000000;
    tag->base.m_tagClass = gTagNotSetStr;
    tag->Height = 0;
    tag->m_iID = 0;
    tag->ImageBuf = 0;
    tag->Width = 0;
}

extern "C" SECTION(Draw___dupe14) void Draw___dupe14(ImageTagState *self)
{
    if (!self->ImageBuf) return;
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoImageTagSource, 0x9F);
    int selected = tag->vtable->IsSelected(tag) != 0;
    // Retail forwards v0 twice, not the separate u0 field.
    draw->vtable->DrawImage(draw, tag->m_tagid, self->ImageBuf, self->PosX, self->PosY, self->Width, self->Height, self->v0, self->v0, selected, 255);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ImageTag", getImageTypeAttrib);

extern "C" SECTION(HandleInput___dupe41) int HandleInput___dupe41(ImageTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoImageTagSource, 0x6f);
    if (!input) __SVO_Assert_Handler(svoImageTagSource, 0x70);
    if (!page) __SVO_Assert_Handler(svoImageTagSource, 0x71);
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE) && !tag->vtable->IgnoreInput(tag) && tag->vtable->IsSelected(tag) && page->m_state == 0) {
        if ((unsigned int)self + 0xBC == 0) __SVO_Assert_Handler(svoImageTagSource, 0x7b);
        if (self->m_link[0]) {
            followLink(page, self->m_link, 0);
            CAudioContextBaseState *audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoImageTagAudioClass);
            return 0;
        }
    }
    if (tag->vtable->IsSelected(tag)) {
        for (int action = 0; action < 4; ++action) {
            if (HasActionOccurred(input, 0x11, (PadAction)action)) {
                CDrawContextBase *draw = tag->m_contexts->drawContext;
                if (!draw) __SVO_Assert_Handler(svoImageTagSource, 0x8e);
                return Navigate(tag, input, draw, tag->m_xml, page) == 0;
            }
        }
    }
    return 1;
}

extern "C" SECTION(ImageTag) void ImageTag(ImageTagState *self, iks *xml, CAllContextData *contexts)
{
    SVTag *tag = &self->base;
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoImageTagVtable;
    DefaultInit___dupe10(self);
    getImageTypeAttrib(self, tag->m_xml, svoImageTagAttrType, &self->m_imageType);
    int id;
    char *link;
    getIntAttrib(xml, svoImageTagAttrId, &id);
    getIntAttrib(xml, svoImageTagAttrWidth, &self->Width);
    getIntAttrib(xml, svoImageTagAttrHeight, &self->Height);
    getIntAttrib(xml, svoImageTagAttrX, &self->PosX);
    getIntAttrib(xml, svoImageTagAttrY, &self->PosY);
    getStringAttrib(xml, svoImageTagAttrHref, &link);
    if (link) {
        for (int i = 0; i < 128; ++i) self->m_link[i] = link[i];
    }
    else self->m_link[0] = 0;
    self->m_iID = id;
    tag->m_tagid = id;
    if (self->m_link[0]) {
        tag->m_bSelectable = 1;
        decodeEntityText(self->m_link);
    } else tag->m_bSelectable = 0;
}

extern "C" SECTION(InitImage___dupe2) void InitImage___dupe2(ImageTagState *self, char *data, size_t size)
{
    SVTag *tag = &self->base;
    if (!data) __SVO_Assert_Handler(svoImageTagSource, 0xEE);
    self->ImageBuf = (char *)svAllocSafe(tag->m_contexts->memoryContext, (unsigned int)size, 4, 0xEF, svoImageTagSource);
    if (!self->ImageBuf) __SVO_Assert_Handler(svoImageTagSource, 0xF0);
    memcpy(self->ImageBuf, data, size);
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoImageTagSource, 0xF4);
    draw->vtable->InitImage(draw, tag->m_tagid, self->ImageBuf, self->PosX, self->PosY, self->Width, self->Height, self->v0, self->v0);
}
