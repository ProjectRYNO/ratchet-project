#include "SelectTag.h"
#include "CMemoryContextBase.h"
#include "CInputContextBase.h"
#include "CDrawContextBase.h"
#include "TagUtils.h"
#include "HttpUtils.h"
#include "string.h"
extern "C" {
extern const SVTagVtablePrefix svoSelectTagVtable;
extern unsigned char svoCharacterTypes[];
extern int svoSelectNextDirection;
extern int svoSelectPreviousDirection;
extern char svoSelectTagSource[];
extern char svoSelectOptionName[];
extern char svoSelectValueAttribute[];
extern char svoSelectSelectedAttribute[];
CMemoryContextBaseState *GetMemoryContext();
void advanceCurrOption(SelectTagState *, int);
char *getCurrOptionStrPtr(SelectTagState *);
int Navigate(SVTag *, CInputContextBaseState *, CDrawContextBase *, iks *, CPage *);
int TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
void DefaultInit___dupe9(SelectTagState *);
void RegisterWithForm(SelectTagState *, iks *, SVTag **);
}
extern "C" {
extern char svoSelectFontSizeAttribute[];
extern char svoSelectDisplayLengthAttribute[];
extern char svoSelectAlignAttribute[];
extern char svoSelectHighlightColorAttribute[];
extern char svoSelectFontColorAttribute[];
extern char svoSelectTextColorAttribute[];
extern char svoSelectHighlightTextColorAttribute[];
extern char svoSelectFillColorAttribute[];
extern char svoSelectHighlightFillColorAttribute[];
extern char svoSelectLineColorAttribute[];
extern char svoSelectHighlightLineColorAttribute[];
extern char svoSelectEnableGroupSelectionAttribute[];
extern char svoSelectSelectableAttribute[];
extern char svoSelectClassAttribute[];
extern char svoSelectSubmitAsEncryptedAttribute[];
extern char svoSelectRequiredForPostAttribute[];
}
extern "C" {
void changeCurOptionToNextLetterInAlphabet(SelectTagState *, int);
int populateSelectOptions(SelectTagState *, iks *);
}

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

int IsSelectable___dupe10(SelectTagState *tag);
extern "C" SECTION(IsSelectable___dupe10) int IsSelectable___dupe10(SelectTagState *tag)
{
    if (!tag->base.m_bSelectable) return 0;
    return tag->m_numOptions > 0;
}

SECTION(GetValue) char *GetValue(SelectTagState *tag)
{
    return tag->m_values[tag->m_currOptionIdx];
}

}

extern "C" SECTION(_SelectTag) void _SelectTag(SelectTagState *tag, unsigned int flags)
{
    tag->base.vtable = &svoSelectTagVtable;
    if (tag->m_options) {
        CMemoryContextBaseState *memory = GetMemoryContext();
        svFreeSafe(memory, tag->m_options);
        tag->m_options = 0;
    }
    if (tag->m_values) {
        CMemoryContextBaseState *memory = GetMemoryContext();
        svFreeSafe(memory, tag->m_values);
        tag->m_values = 0;
    }
    tag->base.vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(&tag->base);
}

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

extern "C" SECTION(HandleInput___dupe40) int HandleInput___dupe40(SelectTagState *tag, CPage *page)
{
    SVTag *base = &tag->base;
    CInputContextBaseState *input = base->m_contexts->inputContext;
    if (!base->vtable->IsSelected(base)) return 1;
    if (HasActionOccurred(input, 0x11, SV_ACTION_SELECT_NEXT_ITEM)) {
        advanceCurrOption(tag, svoSelectNextDirection);
        return 0;
    }
    if (HasActionOccurred(input, 0x11, SV_ACTION_SELECT_PREV_ITEM)) {
        advanceCurrOption(tag, svoSelectPreviousDirection);
        return 0;
    }
    int direction;
    if (HasActionOccurred(input, 0x11, SV_ACTION_SELECT_PREV_GROUP)) direction = svoSelectPreviousDirection;
    else if (HasActionOccurred(input, 0x11, SV_ACTION_SELECT_NEXT_GROUP)) direction = svoSelectNextDirection;
    else {
        if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_LEFT) || HasActionOccurred(input, 0x11, SV_ACTION_NAV_RIGHT))
            return Navigate(base, input, base->m_contexts->drawContext, base->m_xml, page) == 0;
        return 1;
    }
    if (tag->m_enableGroupSelection) {
        changeCurOptionToNextLetterInAlphabet(tag, direction);
        return 0;
    }
    return 1;
}

extern "C" SECTION(populateSelectOptions) int populateSelectOptions(SelectTagState *tag, iks *xml)
{
    int count = 0;
    for (iks *node = iks_child(xml); node; node = iks_next(node)) {
        char *name = iks_name(node);
        if (name && !strcmp(name, svoSelectOptionName)) ++count;
    }
    tag->m_numOptions = count;
    if (count <= 0) return 0;
    tag->m_options = (iks **)svAllocSafe(GetMemoryContext(), tag->m_numOptions << 2, 0, 0x10F, svoSelectTagSource);
    tag->m_values = (char **)svAllocSafe(GetMemoryContext(), tag->m_numOptions << 2, 0, 0x110, svoSelectTagSource);
    if (!tag->m_options || !tag->m_values) return 0;
    memset(tag->m_options, 0, tag->m_numOptions << 2);
    memset(tag->m_values, 0, tag->m_numOptions << 2);
    count = 0;
    for (iks *node = iks_child(xml); node; node = iks_next(node)) {
        char *name = iks_name(node);
        if (name && !strcmp(name, svoSelectOptionName)) {
            tag->m_options[count] = node;
            tag->m_values[count] = iks_find_attrib(node, svoSelectValueAttribute);
            int selected = 0;
            getBoolAttrib(node, svoSelectSelectedAttribute, &selected);
            if (selected) tag->m_currOptionIdx = count;
            ++count;
        }
    }
    return count > 0;
}

extern "C" SECTION(RegisterWithForm) void RegisterWithForm(SelectTagState *tag, iks *parent, SVTag **tagList)
{
    tag->m_parentForm = FindParentForm(tag, parent, tagList);
    if (tag->m_parentForm) AddSelectElement(tag->m_parentForm, tag);
}

extern "C" SECTION(SelectTag) void SelectTag(SelectTagState *tag, iks *xml, SVTag **tagList, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoSelectTagVtable;
    DefaultInit___dupe9(tag);
    getIntAttrib(tag->base.m_xml, svoSelectFontSizeAttribute, &tag->m_fontSize);
    getFloatAttrib(tag->base.m_xml, svoSelectDisplayLengthAttribute, &tag->m_displayLength);
    getAlignAttrib(tag->base.m_xml, svoSelectAlignAttribute, &tag->m_align);
    getColorAttrib(tag->base.m_xml, svoSelectHighlightColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoSelectFontColorAttribute, &tag->base.m_lineColor);
    getColorAttrib(tag->base.m_xml, svoSelectTextColorAttribute, &tag->m_textColor);
    getColorAttrib(tag->base.m_xml, svoSelectHighlightTextColorAttribute, &tag->m_highlightTextColor);
    getColorAttrib(tag->base.m_xml, svoSelectFillColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoSelectHighlightFillColorAttribute, &tag->m_highlightFillColor);
    getColorAttrib(tag->base.m_xml, svoSelectLineColorAttribute, &tag->base.m_lineColor);
    getColorAttrib(tag->base.m_xml, svoSelectHighlightLineColorAttribute, &tag->m_highlightLineColor);
    getBoolAttrib(tag->base.m_xml, svoSelectEnableGroupSelectionAttribute, &tag->m_enableGroupSelection);
    if (!getBoolAttrib(tag->base.m_xml, svoSelectSelectableAttribute, &tag->base.m_bSelectable)) tag->base.m_bSelectable = 1;
    getStringAttrib(tag->base.m_xml, svoSelectClassAttribute, &tag->base.m_tagClass);
    populateSelectOptions(tag, xml);
    if (!getBoolAttrib(tag->base.m_xml, svoSelectSubmitAsEncryptedAttribute, &tag->m_bSubmitAsEncryped)) tag->m_bSubmitAsEncryped = 0;
    if (!getBoolAttrib(tag->base.m_xml, svoSelectRequiredForPostAttribute, &tag->m_bRequiredForSubmit)) tag->m_bRequiredForSubmit = 0;
    RegisterWithForm(tag, iks_parent(tag->base.m_xml), tagList);
}
