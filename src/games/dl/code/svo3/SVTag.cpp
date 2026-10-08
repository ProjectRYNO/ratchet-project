#include "CMemoryContextBase.h"
#include "SVTagModule.h"
extern "C" {
CMemoryContextBaseState *GetMemoryContext(void);
extern char svoTagSource[];
void * SVTagoperator_new___dupe8(unsigned int size) __asm__("operator.new___dupe8");

}
#define SECTION(name) __attribute__((section(".svo_tag_" #name)))
#include "common.h"
// Keep unreplaced assembly in its original function slots.

// Retain the allocator and XML constructor at their original addresses.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_tag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"
#include "CInputContextBase.h"
#include "SVBrowser.h"
#include <string.h>

extern "C" {
extern char svoTagSource[];
extern char gTagNotSetStr[];
extern char svoTagNavUpAttribute[];
extern char svoTagNavDownAttribute[];
extern char svoTagNavLeftAttribute[];
extern char svoTagNavRightAttribute[];
CMemoryContextBaseState *GetMemoryContext(void);
void SignalPluginEvent(SVBrowserPrefix *browser, int event, SVTag *tag);
#define TAG_SECTION(name) __attribute__((section(".svo_tag_" #name)))

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVTag", operator.new___dupe8);

TAG_SECTION(operator.delete___dupe7) void SVTagDelete(SVTag *tag)
{
    FreeContexts(tag);
    CMemoryContextBaseState *memory = GetMemoryContext();
    svFreeSafe(memory, tag);
}

TAG_SECTION(DefaultInit___dupe3) void DefaultInit___dupe3(SVTag *tag)
{
    memset(tag->m_tagTypeName, 0, 64);
    tag->m_fillColor = 0xFFFF0000;
    tag->m_tagClass = gTagNotSetStr;
    tag->m_bSelectable = 1;
    tag->m_xml = 0;
    tag->m_tagid = 0;
    tag->m_bSelected = 0;
    tag->m_x = 0;
    tag->m_y = 0;
    tag->m_z = 0;
    tag->m_width = 0;
    tag->m_height = 0;
    tag->m_info = 0;
    tag->m_name = 0;
    tag->m_toolTip = 0;
    tag->m_toolTipTagName = 0;
    tag->m_bIgnoreInput = 0;
    tag->m_bOptional = 0;
    tag->vtable->SetVisible(tag, 1);
    reset___dupe2(&tag->m_navInfo);
    tag->m_isDefTextEntry = 0;
    tag->m_bNeverSelectable = 0;
    tag->m_isDefTextScroll = 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/SVTag", SVTag);

TAG_SECTION(SetSelectedState) void SetSelectedState(SVTag *tag, int selected)
{
    int value = selected != 0;
    if (!tag->vtable->IsSelectable(tag) || tag->m_bNeverSelectable) value = 0;
    tag->m_bSelected = value;
}

TAG_SECTION(SetSelectable) void SetSelectable(SVTag *tag, int selectable)
{
    tag->m_bSelectable = tag->m_bNeverSelectable ? 0 : selectable != 0;
}

TAG_SECTION(GetDimensions) void GetDimensions(SVTag *tag, float *x, float *y, float *width, float *height)
{
    *x = tag->m_x;
    *y = tag->m_y;
    *width = tag->m_width;
    *height = tag->m_height;
}

TAG_SECTION(SetDimensions) void SetDimensions(SVTag *tag, float x, float y, float width, float height)
{
    tag->m_height = height;
    tag->m_x = x;
    tag->m_y = y;
    tag->m_width = width;
}

TAG_SECTION(GetQueryParams) void GetQueryParams(SVTag *tag, char **name, char **value)
{
    *name = 0;
    *value = 0;
}

TAG_SECTION(SetContexts) void SetContexts(SVTag *tag, CAllContextData *contexts)
{
    CMemoryContextBaseState *memory = GetMemoryContext();
    tag->m_contexts = (CAllContextData *)svAllocSafe(memory, 0x18, 0, 0xE0, svoTagSource);
    *tag->m_contexts = *contexts;
}

TAG_SECTION(FreeContexts) void FreeContexts(SVTag *tag)
{
    if (!tag->m_contexts) __SVO_Assert_Handler(svoTagSource, 0xE7);
    CMemoryContextBaseState *memory = GetMemoryContext();
    svFreeSafe(memory, tag->m_contexts);
}

TAG_SECTION(HandleInputForPluginEvents) void HandleInputForPluginEvents(SVTag *tag)
{
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!input) __SVO_Assert_Handler(svoTagSource, 0xF7);
    SVBrowserPrefix *browser = GetInstance();
    if (tag->vtable->IsSelected(tag)) {
        SignalPluginEvent(browser, 8, tag);
        if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE))
            SignalPluginEvent(browser, 0, tag);
    }
}

TAG_SECTION(SetVisible) void SetVisible(SVTag *tag, int visible)
{
    tag->m_bIsVisible = visible;
}

TAG_SECTION(GetVisible) int GetVisible(SVTag *tag)
{
    return tag->m_bIsVisible;
}

TAG_SECTION(GetNavInfo) CNavInfoState *GetNavInfo(SVTag *tag)
{
    return &tag->m_navInfo;
}

TAG_SECTION(GetTagTypeName) char *GetTagTypeName(SVTag *tag)
{
    if (!strlen(tag->m_tagTypeName)) __SVO_Assert_Handler(svoTagSource, 0x12E);
    return tag->m_tagTypeName;
}

TAG_SECTION(GetNavigationAttributes) void GetNavigationAttributes(SVTag *tag, CNavInfoState *navigation, iks *xml)
{
    navigation->up = iks_find_attrib(xml, svoTagNavUpAttribute);
    navigation->down = iks_find_attrib(xml, svoTagNavDownAttribute);
    navigation->left = iks_find_attrib(xml, svoTagNavLeftAttribute);
    navigation->right = iks_find_attrib(xml, svoTagNavRightAttribute);
}
}
