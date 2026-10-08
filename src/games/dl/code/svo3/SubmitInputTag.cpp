#include "string.h"
#include "SubmitInputTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SubmitInputTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {

extern "C" {
SVTagModuleState *getInstance___dupe17(void);
extern char svoSubmitInputTagFormNameAttribute[];
void AddSubmitElement(FormTag *form, SubmitInputTagState *tag);
extern char svoSubmitInputTagSource[];

}
#define SECTION(name) __attribute__((section(".svo_SubmitInputTag_" #name)))

SECTION(IsSelectable___dupe14) long IsSelectable___dupe14(void *self)
{
    return 1;
}

SECTION(FreeResources___dupe32) void FreeResources___dupe32(SVTag *tag)
{
    FreeContexts(tag);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", DefaultInit___dupe16);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", Draw___dupe22);

extern "C" SECTION(FindParentForm___dupe5) FormTag *FindParentForm___dupe5(SubmitInputTagState *tag, iks *parent, SVTag **tagList)
{
    if (!parent) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xA9);
    if (!tagList) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xAA);
    SVTagModuleState *module = getInstance___dupe17();
    if (!module->vtable->IsMyTag(module, parent)) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xB2);
    char *formName = iks_find_attrib(parent, svoSubmitInputTagFormNameAttribute);
    if (!formName) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xB8);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!name) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xBF);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", HandleInput___dupe48);

extern "C" SECTION(RegisterWithForm___dupe5) void RegisterWithForm___dupe5(SubmitInputTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm___dupe5(tag, parent, tagList);
    if (!tag->m_parentForm) __SVO_Assert_Handler(svoSubmitInputTagSource, 0xD1);
    AddSubmitElement(tag->m_parentForm, tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SubmitInputTag", SubmitInputTag);
