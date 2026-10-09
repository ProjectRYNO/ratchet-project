#include "TagUtils.h"
#include "CPage.h"
#include "CInputContextBase.h"
#include "CAudioContextBase.h"
#include "CDrawContextBase.h"
#include "CMemoryContextBase.h"
#include "Navigation.h"
#include "string.h"
#include "SVOString.h"
#include "StaticImageTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_StaticImageTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern char svoStaticImageTagName[];
extern char gTagNotSetStr[];
extern char svoStaticImageUnsetName[];


extern char svoStaticImageTagSource[];
extern char svoStaticImageTagAudioClass[];
extern const SVTagVtablePrefix svoStaticImageTagVtable;
CAudioContextBaseState *GetAudioContext(void);
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
void decodeEntityText(char *);
extern char svoStaticImageTagAttrIndex[];
extern char svoStaticImageTagAttrWidth[];
extern char svoStaticImageTagAttrHeight[];
extern char svoStaticImageTagAttrX[];
extern char svoStaticImageTagAttrY[];
extern char svoStaticImageTagAttrHref[];
extern char svoStaticImageTagAttrName[];
char *DefaultInit___dupe11(StaticImageTagState *);
#define SECTION(name) __attribute__((section(".svo_StaticImageTag_" #name)))

SECTION(FreeResources___dupe20) void FreeResources___dupe20(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe12(SVTag *tag);
extern "C" SECTION(IsSelectable___dupe12) long IsSelectable___dupe12(SVTag *tag)
{
    return (tag->m_bSelectable != 0) & ((unsigned int)tag != 0xFFFFFF4Cu);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/StaticImageTag", DefaultInit___dupe11);

extern "C" SECTION(Draw___dupe15) void Draw___dupe15(StaticImageTagState *self)
{
    SVTag *tag = &self->base;
    CDrawContextBase *draw = tag->m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoStaticImageTagSource, 0x87);
    int selected = tag->vtable->IsSelected(tag) != 0;
    draw->vtable->DrawStaticImage(draw, tag->m_tagid, self->m_imageName, self->m_index, self->m_imageX, self->m_imageY, self->m_imageWidth, self->m_imageHeight, self->u0, self->v0, selected, 255);
}

extern "C" SECTION(HandleInput___dupe42) int HandleInput___dupe42(StaticImageTagState *self, CPage *page)
{
    SVTag *tag = &self->base;
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoStaticImageTagSource, 0x5a);
    if (!input) __SVO_Assert_Handler(svoStaticImageTagSource, 0x5b);
    if (!page) __SVO_Assert_Handler(svoStaticImageTagSource, 0x5c);
    if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE) && !tag->vtable->IgnoreInput(tag) && tag->vtable->IsSelected(tag) && page->m_state == 0) {
        if ((unsigned int)self + 0xB4 == 0) __SVO_Assert_Handler(svoStaticImageTagSource, 0x63);
        if (self->m_link[0]) {
            followLink(page, self->m_link, 0);
            CAudioContextBaseState *audio = GetAudioContext();
            ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoStaticImageTagAudioClass);
            return 0;
        }
    }
    if (tag->vtable->IsSelected(tag)) {
        for (int action = 0; action < 4; ++action) {
            if (HasActionOccurred(input, 0x11, (PadAction)action)) {
                CDrawContextBase *draw = tag->m_contexts->drawContext;
                if (!draw) __SVO_Assert_Handler(svoStaticImageTagSource, 0x77);
                return Navigate(tag, input, draw, tag->m_xml, page) == 0;
            }
        }
    }
    return 1;
}

extern "C" SECTION(StaticImageTag) void StaticImageTag(StaticImageTagState *self, iks *xml, CAllContextData *contexts)
{
    SVTag *tag = &self->base;
    SVTagConstruct(tag, xml, contexts);
    tag->vtable = &svoStaticImageTagVtable;
    DefaultInit___dupe11(self);
    int index;
    char *link;
    getIntAttrib(xml, svoStaticImageTagAttrIndex, &index);
    getIntAttrib(xml, svoStaticImageTagAttrWidth, &self->m_imageWidth);
    getIntAttrib(xml, svoStaticImageTagAttrHeight, &self->m_imageHeight);
    getIntAttrib(xml, svoStaticImageTagAttrX, &self->m_imageX);
    getIntAttrib(xml, svoStaticImageTagAttrY, &self->m_imageY);
    getStringAttrib(xml, svoStaticImageTagAttrHref, &link);
    char *name = iks_find_attrib(tag->m_xml, svoStaticImageTagAttrName);
    if (!name) __SVO_Assert_Handler(svoStaticImageTagSource, 0x3D);
    svstrncpy(self->m_imageName, name, 32);
    memcpy(self->m_link, link, 128);
    if (!strlen(self->m_imageName)) __SVO_Assert_Handler(svoStaticImageTagSource, 0x41);
    self->m_index = index;
    if ((unsigned int)self + 0xB4 && strlen(self->m_link)) {
        tag->m_bSelectable = 1;
        decodeEntityText(self->m_link);
    } else tag->m_bSelectable = 0;
}
