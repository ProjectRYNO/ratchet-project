#include "TextEditableTag.h"
extern "C" char svoTextEditableSource[];
#define SECTION(name) __attribute__((section(".svo_TextEditableTag_" #name)))
#include "common.h"

extern "C" SECTION(DefaultHandleInput) long DefaultHandleInput(SVTag *tag, CPage *page)
{
    CInputContextBaseState *input = tag->m_contexts->inputContext;
    if (!tag->m_xml) __SVO_Assert_Handler(svoTextEditableSource, 10);
    if (!input) __SVO_Assert_Handler(svoTextEditableSource, 11);
    if (!page) __SVO_Assert_Handler(svoTextEditableSource, 12);
    if (tag->m_isDefTextEntry)
        ((const TextEditableTagVtablePrefix *)tag->vtable)->HandleTextEntry(tag, input);
    if (tag->m_isDefTextScroll) {
        int action = HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_UP);
        if (!action) action = HasActionOccurred(input, 0x11, SV_ACTION_SCROLL_DOWN);
        if (action) ((const TextEditableTagVtablePrefix *)tag->vtable)->ScrollText(tag, (signed char)action);
    }
    return 1;
}
