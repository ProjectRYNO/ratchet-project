#include "SVOString.h"
#include "CMemoryContextBase.h"
#include "string.h"
#include "GenericListBoxTag.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_GenericListBoxTag_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"

extern "C" {
extern char svoGenericListBoxTagSource[];

extern "C" {
extern char svoGenericListBoxTagSource[];
}
extern "C" {
extern char svoGenericListBoxTagName[];
}
extern "C" {

}
#define SECTION(name) __attribute__((section(".svo_GenericListBoxTag_" #name)))

SECTION(FreeResources___dupe56) void FreeResources___dupe56(SVTag *tag)
{
    __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x70);
}

}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", _GenericListBoxTag);

extern "C" SECTION(addHandle) long addHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    if (tag->m_numItems >= tag->m_maxNumItems) return 0;
    if (!handle) {
        __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x1A4);
        return 0;
    }
    const GenericListBoxTagVtablePrefix *vtable = (const GenericListBoxTagVtablePrefix *)tag->base.vtable;
    if (vtable->getIndexOfHandle(tag, handle) != -1)
        __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x1AB);
    tag->m_handles[tag->m_numItems] = handle;
    ++tag->m_numItems;
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", changeSelectedItem___dupe2);

extern "C" SECTION(clearList) void clearList(GenericListBoxTagState *tag)
{
    if (tag->m_handles) memset(tag->m_handles, 0, tag->m_maxNumItems * 4);
    tag->m_topVisibleIndex = 0;
    tag->m_numItems = 0;
    tag->m_selectedIndex = 0;
}

extern "C" SECTION(DefaultInit___dupe23) void DefaultInit___dupe23(GenericListBoxTagState *tag)
{
    svstrncpy(tag->base.m_tagTypeName, svoGenericListBoxTagName, 64);
    const GenericListBoxTagVtablePrefix *vtable = (const GenericListBoxTagVtablePrefix *)tag->base.vtable;
    tag->base.m_lineColor = 0xFF00FF00;
    tag->m_highlightFillColor = 0xFF808080;
    tag->m_highlightLineColor = 0xFFFFFFFF;
    tag->base.m_fillColor = 0xFFFFFFFF;
    tag->m_handles = 0;
    tag->m_turnOffDraw = 0;
    tag->m_entryTagIDs = 0;
    vtable->clearList(tag);
}

extern "C" SECTION(deleteHandle) long deleteHandle(GenericListBoxTagState *tag, svo_listbox_handle handle)
{
    const GenericListBoxTagVtablePrefix *vtable = (const GenericListBoxTagVtablePrefix *)tag->base.vtable;
    long index = vtable->getIndexOfHandle(tag, handle);
    if (index == -1) return 0;
    if (index >= tag->m_numItems) {
        __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x1D6);
        return 0;
    }
    for (int i = index; i < tag->m_numItems - 1; ++i) {
        tag->m_handles[i] = tag->m_handles[i + 1];
        if (tag->m_selectedIndex == i + 1) tag->m_selectedIndex = i;
    }
    if (index < tag->m_topVisibleIndex + tag->m_maxVisibleItems && tag->m_topVisibleIndex > 0)
        --tag->m_topVisibleIndex;
    --tag->m_numItems;
    tag->m_handles[tag->m_numItems] = 0;
    return 1;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", Draw___dupe26);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", GenericListBoxTag);

extern "C" SECTION(getHandleByIndex) long getHandleByIndex(GenericListBoxTagState *tag, int index)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x219);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x21a);
    if (!tag->m_handles[index]) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x21b);
    return (int)tag->m_handles[index];
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", getIndexOfHandle);

extern "C" SECTION(getNumVisibleRows___dupe2) long getNumVisibleRows___dupe2(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x211);
    if (tag->m_maxVisibleItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x212);
    return tag->m_maxVisibleItems;
}

extern "C" SECTION(getSelectedHandle) long getSelectedHandle(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x223);
    if (tag->m_selectedIndex < tag->m_topVisibleIndex) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x224);
    if (tag->m_selectedIndex >= tag->m_topVisibleIndex + tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x225);
    return (int)tag->m_handles[tag->m_selectedIndex];
}

extern "C" SECTION(getSelectedIndex___dupe2) long getSelectedIndex___dupe2(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x190);
    if (tag->m_selectedIndex >= tag->m_numItems && tag->m_numItems != 0) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x191);
    return tag->m_selectedIndex;
}

extern "C" SECTION(getTopVisibleIndex___dupe2) long getTopVisibleIndex___dupe2(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x202);
    if (tag->m_maxVisibleItems < tag->m_numItems) {
    if (tag->m_topVisibleIndex > tag->m_numItems - tag->m_maxVisibleItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x205);
    } else {
    if (tag->m_topVisibleIndex >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x209);
    }
    return tag->m_topVisibleIndex;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/GenericListBoxTag", HandleInput___dupe54);

extern "C" SECTION(selectIndex___dupe2) long selectIndex___dupe2(GenericListBoxTagState *tag, int index)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x137);
    if (index < 0 || index >= tag->m_numItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x138);
    tag->m_selectedIndex = index;
    return 1;
}

extern "C" SECTION(size) long size(GenericListBoxTagState *tag)
{
    if (tag->m_numItems > tag->m_maxNumItems) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x113);
    if (tag->m_numItems < 0) __SVO_Assert_Handler(svoGenericListBoxTagSource, 0x114);
    return tag->m_numItems;
}
