#include "CDrawContextBase.h"

#include "CInputContextBase.h"
#include "CPage.h"
#include "SVBrowser.h"
#include "TagUtils.h"
#include "TagUtils.h"
#include "HttpUtils.h"
#include "CAudioContextBase.h"
#include "SVOString.h"
#include "SVTag.h"
#include "CMemoryContextBase.h"
#include "string.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_ListBoxTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "ListBoxTag.h"

extern "C" {

extern char svoListBoxTagSource[];

extern "C" {
extern const SVTagVtablePrefix svoListBoxTagVtable;
void FreeResources___dupe48(ListBoxTagState *tag);
}
extern "C" {
extern char svoListBoxTagName[];
extern unsigned int svoNextTagId;
}
extern "C" {

}
extern "C" {
extern char svoListBoxMoveClass[];
extern char svoListBoxItemName[];
extern char svoListBoxHrefAttribute[];
extern char svoListBoxClassAttribute[];
extern char svoListBoxDefaultItemClass[];
extern char svoListBoxNameAttribute[];
extern char svoListBoxLinkOptionAttribute[];
CAudioContextBaseState *GetAudioContext();
void initListboxItem(ListBoxTagState *, ListBoxItem *);
}
extern "C" {
void SignalPluginEvent(SVBrowserPrefix *, int, void *);
void DefaultInit___dupe22(ListBoxTagState *);
void populateListboxItems(ListBoxTagState *);
}
extern "C" {
extern char svoListBoxFontSizeAttribute[];
extern char svoListBoxDisplayLengthAttribute[];
extern char svoListBoxAlignAttribute[];
extern char svoListBoxFillColorAttribute[];
extern char svoListBoxLineColorAttribute[];
extern char svoListBoxDefaultColorAttribute[];
extern char svoListBoxHighlightColorAttribute[];
extern char svoListBoxMaxItemsAttribute[];
extern char svoListBoxMaxVisibleItemsAttribute[];
extern char svoListBoxPopulatedAttribute[];
extern char svoListBoxLineSpacingAttribute[];
extern char svoListBoxButtonHeightAttribute[];
}
extern "C" {
float calculateScrollBarPercentage(ListBoxTagState *);
void TrimToFitDisplaySize(CDrawContextBase *, char *, float, int);
}
#define SECTION(name) __attribute__((section(".svo_ListBoxTag_" #name)))

SECTION(SetExternalDrawFunction) void SetExternalDrawFunction(ListBoxTagState *tag, int turnOffDraw)
{
    tag->m_turnOffDraw = turnOffDraw;
}

}

extern "C" SECTION(_ListBoxTag) void _ListBoxTag(SVTag *tag, unsigned long flags)
{
    tag->vtable = &svoListBoxTagVtable;
    FreeResources___dupe48((ListBoxTagState *)tag);
    tag->vtable = &svoTagVtable;
    if (flags & 1) SVTagDelete(tag);
}

extern "C" SECTION(addItem) long addItem(ListBoxTagState *tag, char *itemName)
{
    if (!itemName) __SVO_Assert_Handler(svoListBoxTagSource, 0x253);
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x254);
    if (tag->m_numItems >= tag->m_maxNumItems) return 0;
    ListBoxItem *item = (ListBoxItem *)svAllocSafe(tag->base.m_contexts->memoryContext,
        sizeof(ListBoxItem), 0, 0x258, svoListBoxTagSource);
    int index = tag->m_numItems;
    item->displayStr = itemName;
    tag->m_numItems = index + 1;
    tag->m_items[index] = item;
    return 1;
}

extern "C" SECTION(calculateScrollBarPercentage) float calculateScrollBarPercentage(ListBoxTagState *tag)
{
    int count = tag->m_numItems;
    if (tag->m_maxVisibleItems < count) count = tag->m_maxVisibleItems;
    if (tag->m_topVisibleIndex < 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x2C5);
    float fraction = 0.0f;
    if (tag->m_topVisibleIndex > 0) fraction = (float)tag->m_topVisibleIndex / (float)count;
    return fraction;
}

extern "C" SECTION(changeSelectedItem) void changeSelectedItem(ListBoxTagState *tag, int direction)
{
    if (!tag->m_numItems) return;
    int old = tag->m_selectedIndex;
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x1c3);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x1c4);
    int selected = tag->m_selectedIndex;
    int top = tag->m_topVisibleIndex;
    if (direction == -1) {
        if (selected == -1) tag->m_selectedIndex = tag->m_numItems - 1;
        else {
            int count = tag->m_numItems;
            int next = (selected - 1 + count) % count;
            tag->m_selectedIndex = next;
            if (next < top) tag->m_topVisibleIndex = next;
            else if (next >= top + tag->m_maxVisibleItems) tag->m_topVisibleIndex = top + count - tag->m_maxVisibleItems;
        }
    } else if (direction == 1) {
        if (selected == -1) tag->m_selectedIndex = 0;
        else {
            int count = tag->m_numItems;
            int next = (selected + 1 + count) % count;
            tag->m_selectedIndex = next;
            if (next < top) tag->m_topVisibleIndex = next;
            else if (next >= top + tag->m_maxVisibleItems) tag->m_topVisibleIndex = top + 1;
        }
    }
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x1ef);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x1f0);
    if (old != tag->m_selectedIndex) {
        CAudioContextBaseState *audio = GetAudioContext();
        ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 5, svoListBoxMoveClass);
    }
}

extern "C" SECTION(clearItems) void clearItems(ListBoxTagState *tag)
{
    memset(tag->m_items, 0, sizeof(tag->m_items));
    tag->m_maxNumItems = 0;
    tag->m_bPopulatedByPage = 0;
    tag->m_maxVisibleItems = 0;
    tag->m_numItems = 0;
    tag->m_selectedIndex = 0;
    tag->m_topVisibleIndex = 0;
}

extern "C" SECTION(countItems) long countItems(ListBoxTagState *tag)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x163);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x164);
    if (tag->m_numItems < 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x165);
    return tag->m_numItems;
}

extern "C" SECTION(DefaultInit___dupe22) void DefaultInit___dupe22(ListBoxTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoListBoxTagName, 64);
    const ListBoxTagVtablePrefix *vtable = (const ListBoxTagVtablePrefix *)tag->base.vtable;
    tag->m_fontSize = 14;
    tag->m_align = 1;
    tag->base.m_fillColor = 0xFFFFFFFF;
    tag->base.m_lineColor = 0xFF00FF00;
    tag->m_defaultItemColor = 0xFF000000;
    tag->m_selectedItemColor = 0xFFFFFF00;
    tag->m_buttonHeight = 20.0f;
    tag->m_lineSpacing = 20.0f;
    tag->m_displayLength = 0.0f;
    tag->m_turnOffDraw = 0;
    tag->m_selectFocusAreaMode = 0;
    tag->m_scrollBarPercentage = 0.0f;
    tag->m_maxNumItems = 0;
    tag->m_maxVisibleItems = 0;
    vtable->clearItems(tag);
}

extern "C" SECTION(deleteItem) long deleteItem(ListBoxTagState *tag, int index)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x273);
    int count = tag->m_numItems;
    if (index >= count || !tag->m_items[index]) return 0;
    for (; index < count - 1; ++index) tag->m_items[index] = tag->m_items[index + 1];
    count = tag->m_numItems;
    tag->m_numItems = count - 1;
    // Retail clears the old count index, not the last occupied index.
    tag->m_items[count] = 0;
    return 1;
}

extern "C" SECTION(deselectItem) void deselectItem(ListBoxTagState *tag, int index)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x16d);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x16e);
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x16f);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x170);
    tag->m_selectedIndex = -1;
}

extern "C" SECTION(Draw___dupe25) void Draw___dupe25(ListBoxTagState *tag)
{
    if (!tag->m_bPopulatedByPage || tag->m_turnOffDraw) return;
    CDrawContextBase *draw = tag->base.m_contexts->drawContext;
    if (!draw) __SVO_Assert_Handler(svoListBoxTagSource, 0x111);
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoListBoxTagSource, 0x112);
    int selected = ((const ListBoxTagVtablePrefix *)tag->base.vtable)->getSelectedIndex(tag);
    int count = tag->m_numItems;
    if (tag->m_maxVisibleItems < count) count = tag->m_maxVisibleItems;
    tag->m_scrollBarPercentage = calculateScrollBarPercentage(tag);
    float fraction = (float)count / (float)((const ListBoxTagVtablePrefix *)tag->base.vtable)->countItems(tag);
    long active = tag->base.vtable->IsSelected(&tag->base);
    draw->vtable->DrawListBox(draw, tag->base.m_tagid, tag->base.m_x, tag->base.m_y,
        tag->base.m_z, tag->base.m_width, tag->base.m_height, tag->base.m_lineColor,
        tag->base.m_fillColor, tag->m_scrollBarPercentage, fraction, active, tag->base.m_tagClass);
    float y = tag->base.m_y;
    ListBoxItem **item = tag->m_items + tag->m_topVisibleIndex;
    for (int i = tag->m_topVisibleIndex; i < tag->m_topVisibleIndex + count; ++i, ++item) {
        strlen((*item)->displayStr);
        float x = tag->base.m_x + 10.0f;
        unsigned int color = i == selected ? tag->m_selectedItemColor : tag->m_defaultItemColor;
        if (tag->m_displayLength > 0.0f) TrimToFitDisplaySize(draw, (*item)->displayStr, tag->m_displayLength, tag->m_fontSize);
        float height = tag->m_buttonHeight;
        int length = strlen((*item)->displayStr);
        draw->vtable->DrawButton(draw, (*item)->tagid, x, y, 100000.0f, tag->base.m_width,
            height, 0xFF000000, 0xFF0000FF, color, i == selected, (*item)->displayStr,
            length, tag->m_fontSize, tag->m_align, (*item)->tagClass, 0);
        y = tag->base.m_y + tag->m_lineSpacing * (float)(i - tag->m_topVisibleIndex + 1);
    }
}

extern "C" SECTION(FreeResources___dupe48) void FreeResources___dupe48(ListBoxTagState *tag)
{
    if (tag->m_pTimer) _SVChronograph(tag->m_pTimer, 3);
    for (int i = 0; i < tag->m_maxNumItems; ++i) {
        ListBoxItem *item = tag->m_items[i];
        if (item) svFreeSafe(tag->base.m_contexts->memoryContext, item);
    }
}

extern "C" SECTION(getItem) ListBoxItem * getItem(ListBoxTagState *tag, int index)
{
    if (!tag->m_numItems) return 0;
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x180);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x181);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x182);
    if (!tag->m_items[index]) __SVO_Assert_Handler(svoListBoxTagSource, 0x183);
    return tag->m_items[index];
}

extern "C" SECTION(getNumVisibleRows) long getNumVisibleRows(ListBoxTagState *tag)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x2aa);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x2ab);
    if (tag->m_maxVisibleItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x2ac);
    return tag->m_maxVisibleItems;
}

extern "C" SECTION(getSelectedIndex) long getSelectedIndex(ListBoxTagState *tag)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x287);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x288);
    if (tag->m_selectedIndex >= tag->m_numItems && tag->m_numItems != 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x289);
    return tag->m_selectedIndex;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", getSelectedItem);

extern "C" SECTION(getTopVisibleIndex) long getTopVisibleIndex(ListBoxTagState *tag)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x29a);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x29b);
    if (tag->m_maxVisibleItems < tag->m_numItems) {
    if (tag->m_topVisibleIndex > tag->m_numItems - tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x29e);
    } else {
    if (tag->m_topVisibleIndex >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x2a2);
    }
    return tag->m_topVisibleIndex;
}

extern "C" SECTION(HandleInput___dupe53) int HandleInput___dupe53(ListBoxTagState *tag, CPage *page)
{
    CInputContextBaseState *input = tag->base.m_contexts->inputContext;
    if (!tag->base.m_xml) __SVO_Assert_Handler(svoListBoxTagSource, 0x95);
    if (!input) __SVO_Assert_Handler(svoListBoxTagSource, 0x96);
    if (!page) __SVO_Assert_Handler(svoListBoxTagSource, 0x97);
    if (!tag->m_selectFocusAreaMode && tag->base.vtable->IsSelected(&tag->base)) {
        if (tag->m_bPopulatedByPage) {
            if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
                if (page->m_state) return 0;
                int selected = ((const ListBoxTagVtablePrefix *)tag->base.vtable)->getSelectedIndex(tag);
                ListBoxItem *item = tag->m_items[selected];
                if (!item->h_ref) return 0;
                followLink(page, item->h_ref, item->linkOption);
                CAudioContextBaseState *audio = GetAudioContext();
                ((const CAudioContextVtablePrefix *)audio->vtable)->Play(audio, 1, svoListBoxMoveClass);
                return 0;
            }
        } else if (HasActionOccurred(input, 0x11, SV_ACTION_ACTIVATE)) {
            SignalPluginEvent(GetInstance(), 0, tag);
        }
        int direction;
        if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_UP)) direction = -1;
        else if (HasActionOccurred(input, 0x11, SV_ACTION_NAV_DOWN)) direction = 1;
        else {
            HasActionOccurred(input, 0x11, SV_ACTION_LEAVE_FOCUS_GROUP);
            return 1;
        }
        ((const ListBoxTagVtablePrefix *)tag->base.vtable)->changeSelectedItem(tag, direction);
    }
    return 1;
}

extern "C" SECTION(initListboxItem) void initListboxItem(ListBoxTagState *tag, ListBoxItem *item)
{
    unsigned int id = svoNextTagId;
    item->displayStr = 0;
    item->h_ref = 0;
    item->linkOption = 0;
    item->tagClass = 0;
    item->name = 0;
    item->info = 0;
    svoNextTagId = id + 1;
    item->tagid = id;
}

extern "C" SECTION(isIndexSelected) int isIndexSelected(ListBoxTagState *tag, int index)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x290);
    if (tag->m_maxNumItems < tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x291);
    if (index >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x292);
    if (!tag->m_items[index]) __SVO_Assert_Handler(svoListBoxTagSource, 0x293);
    return index == tag->m_selectedIndex;
}

extern "C" SECTION(ListBoxTag) void ListBoxTag(ListBoxTagState *tag, iks *xml, CAllContextData *contexts)
{
    SVTagConstruct(&tag->base, xml, contexts);
    tag->base.vtable = &svoListBoxTagVtable;
    DefaultInit___dupe22(tag);
    getIntAttrib(tag->base.m_xml, svoListBoxFontSizeAttribute, &tag->m_fontSize);
    getFloatAttrib(tag->base.m_xml, svoListBoxDisplayLengthAttribute, &tag->m_displayLength);
    getAlignAttrib(tag->base.m_xml, svoListBoxAlignAttribute, &tag->m_align);
    getColorAttrib(tag->base.m_xml, svoListBoxFillColorAttribute, &tag->base.m_fillColor);
    getColorAttrib(tag->base.m_xml, svoListBoxLineColorAttribute, &tag->base.m_lineColor);
    getColorAttrib(tag->base.m_xml, svoListBoxDefaultColorAttribute, &tag->m_defaultItemColor);
    getColorAttrib(tag->base.m_xml, svoListBoxHighlightColorAttribute, &tag->m_selectedItemColor);
    getIntAttrib(tag->base.m_xml, svoListBoxMaxItemsAttribute, &tag->m_maxNumItems);
    if (tag->m_maxNumItems < 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x50);
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x51);
    getIntAttrib(tag->base.m_xml, svoListBoxMaxVisibleItemsAttribute, &tag->m_maxVisibleItems);
    if (tag->m_maxVisibleItems < 0) __SVO_Assert_Handler(svoListBoxTagSource, 0x53);
    getIntAttrib(tag->base.m_xml, svoListBoxPopulatedAttribute, &tag->m_bPopulatedByPage);
    getStringAttrib(tag->base.m_xml, svoListBoxClassAttribute, &tag->base.m_tagClass);
    if (tag->m_bPopulatedByPage) populateListboxItems(tag);
    else SignalPluginEvent(GetInstance(), 12, tag);
    getFloatAttrib(tag->base.m_xml, svoListBoxLineSpacingAttribute, &tag->m_lineSpacing);
    getFloatAttrib(tag->base.m_xml, svoListBoxButtonHeightAttribute, &tag->m_buttonHeight);
    SVChronographState *timer = (SVChronographState *)SVChronographNew(0x10);
    SVChronograph(timer, 0);
    tag->m_pTimer = timer;
    Start___dupe3(timer);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", populateListboxItems);

extern "C" SECTION(replaceItem) long replaceItem(ListBoxTagState *tag, ListBoxItem *item, int index)
{
    if (!tag->m_numItems) return 0;
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x1a0);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x1a1);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x1a2);
    if (!tag->m_items[index]) __SVO_Assert_Handler(svoListBoxTagSource, 0x1a4);
    if (!item) __SVO_Assert_Handler(svoListBoxTagSource, 0x1a5);
    tag->m_items[index] = item;
    return 1;
}

extern "C" SECTION(selectIndex) long selectIndex(ListBoxTagState *tag, int index)
{
    if (!tag->m_numItems) return 0;
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x1b3);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x1b4);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x1b5);
    tag->m_selectedIndex = index;
    return 1;
}
