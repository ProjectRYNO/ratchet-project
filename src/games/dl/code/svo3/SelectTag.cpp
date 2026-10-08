#include "string.h"
#include "SVOString.h"
#include "SelectTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_SelectTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

extern "C" {

SVTagModuleState *getInstance___dupe17(void);
extern char svoSelectTagFormNameAttribute[];
void AddSelectElement(FormTag *form, SelectTagState *tag);


extern "C" {
extern char *svoSelectEmptyOption;
}
extern "C" {
extern char svoSelectTagName[];
extern char gTagNotSetStr[];

}
#define SECTION(name) __attribute__((section(".svo_SelectTag_" #name)))

SECTION(FreeResources___dupe15) void FreeResources___dupe15(SVTag *tag)
{
    FreeContexts(tag);
}

long IsSelectable___dupe10(SelectTagState *tag);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", IsSelectable___dupe10);

SECTION(GetValue) char *GetValue(SelectTagState *tag)
{
    return tag->m_values[tag->m_currOptionIdx];
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", _SelectTag);

extern "C" SECTION(advanceCurrOption) void advanceCurrOption(SelectTagState *tag, int direction)
{
    tag->m_currOptionIdx = (tag->m_currOptionIdx + tag->m_numOptions + direction) % tag->m_numOptions;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", changeCurOptionToNextLetterInAlphabet);

extern "C" SECTION(DefaultInit___dupe9) void DefaultInit___dupe9(SelectTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoSelectTagName, 64);
    tag->m_fontSize = 14;
    tag->m_align = 1;
    tag->base.m_lineColor = 0xFFFFFFFF;
    tag->base.m_fillColor = 0xFF0000FF;
    tag->m_highlightLineColor = 0xFF00FF00;
    tag->m_highlightFillColor = 0xFFFFFF00;
    tag->m_bRequiredForSubmit = 0;
    tag->m_displayLength = 0;
    tag->m_text = 0;
    tag->m_parentForm = 0;
    tag->m_enableGroupSelection = 0;
    tag->m_textColor = 0xFFFFFFFF;
    tag->m_highlightTextColor = 0xFF00FF00;
    tag->m_numOptions = 0;
    tag->m_currOptionIdx = 0;
    tag->m_options = 0;
    tag->m_values = 0;
    tag->m_bSubmitAsEncryped = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", Draw___dupe13);

extern "C" SECTION(FindParentForm) FormTag *FindParentForm(SelectTagState *tag, iks *parent, SVTag **tagList)
{
    SVTagModuleState *module = getInstance___dupe17();
    while (!module->vtable->IsMyTag(module, parent)) {
        parent = iks_parent(parent);
        if (!parent) return 0;
    }
    char *formName = iks_find_attrib(parent, svoSelectTagFormNameAttribute);
    for (int i = 0; i < 256; ++i) {
        SVTag *candidate = tagList[i];
        if (candidate) {
            char *name = candidate->vtable->GetTagName(candidate);
            if (!strcmp(name, formName)) return (FormTag *)tagList[i];
        }
    }
    return 0;
}

extern "C" SECTION(getCurrOptionStrPtr) char *getCurrOptionStrPtr(SelectTagState *tag)
{
    if (tag->m_numOptions > 0) return iks_cdata(iks_child(tag->m_options[tag->m_currOptionIdx]));
    return svoSelectEmptyOption;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", HandleInput___dupe40);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", populateSelectOptions);

extern "C" SECTION(RegisterWithForm) void RegisterWithForm(SelectTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm(tag, parent, tagList);
    if (tag->m_parentForm) AddSelectElement(tag->m_parentForm, tag);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SelectTag", SelectTag);
