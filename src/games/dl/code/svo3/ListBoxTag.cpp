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

extern "C" {
extern char svoListBoxTagSource[];
}
extern "C" {
extern const SVTagVtablePrefix svoListBoxTagVtable;
void FreeResources___dupe48(ListBoxTagState *tag);
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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", calculateScrollBarPercentage);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", changeSelectedItem);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", DefaultInit___dupe22);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", deleteItem);

extern "C" SECTION(deselectItem) void deselectItem(ListBoxTagState *tag, int index)
{
    if (tag->m_maxNumItems > 100) __SVO_Assert_Handler(svoListBoxTagSource, 0x16d);
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x16e);
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoListBoxTagSource, 0x16f);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoListBoxTagSource, 0x170);
    tag->m_selectedIndex = -1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", Draw___dupe25);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", FreeResources___dupe48);

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

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", HandleInput___dupe53);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", initListboxItem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", isIndexSelected);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/ListBoxTag", ListBoxTag);

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
