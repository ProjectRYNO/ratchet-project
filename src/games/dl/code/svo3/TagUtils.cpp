#include "string.h"
#include "TagUtils.h"
#include "common.h"
// Keep unreplaced assembly in its original function slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_TagUtils_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "SVTag.h"
#include "CPage.h"
#include "SVTagModuleList.h"
#include "SVOString.h"
#include "CMemoryContextBase.h"
#include <string.h>
#include <stdlib.h>

extern "C" {
int strcasecmp(const char *, const char *);
CMemoryContextBaseState *GetMemoryContext(void);
void TagUtilsDelete(void *memory) __asm__("operator.delete___dupe5");
unsigned long SvoAtofBits(char *text) __asm__("atof");
float dptofp(unsigned long bits);
extern char svoTagUtilsSource[];
extern char svoTagTrue[];
extern char svoTagFalse[];
extern char svoTagCenter[];
extern char svoTagLeft[];
extern char svoTagRight[];
extern char *svoTagLinkOptions[9];
SVTagModuleState *getInstance___dupe2(void);
SVTagModuleState *getInstance___dupe4(void);
SVTagModuleState *getInstance___dupe7(void);
SVTagModuleState *getInstance___dupe5(void);
SVTagModuleState *getInstance___dupe8(void);
SVTagModuleState *getInstance___dupe9(void);
SVTagModuleState *getInstance___dupe20(void);
SVTagModuleState *getInstance___dupe12(void);
SVTagModuleState *getInstance___dupe13(void);
SVTagModuleState *getInstance___dupe14(void);
SVTagModuleState *getInstance___dupe15(void);
SVTagModuleState *getInstance___dupe16(void);
SVTagModuleState *getInstance___dupe18(void);
SVTagModuleState *getInstance___dupe22(void);
SVTagModuleState *getInstance___dupe17(void);
SVTagModuleState *getInstance___dupe26(void);
SVTagModuleState *getInstance___dupe19(void);
SVTagModuleState *getInstance___dupe21(void);
SVTagModuleState *getInstance___dupe23(void);
SVTagModuleState *getInstance___dupe24(void);
SVTagModuleState *getInstance___dupe25(void);
SVTagModuleState *getInstance___dupe27(void);
SVTagModuleState *getInstance___dupe10(void);
SVTagModuleState *getInstance___dupe11(void);
SVTagModuleState *getInstance___dupe28(void);
SVTagModuleState *getInstance___dupe29(void);
SVTagModuleState *getInstance___dupe6(void);
SVTagModuleState *getInstance___dupe30(void);
SVTagModuleState *getInstance___dupe31(void);

extern "C" {
extern char *svoTagLinkOptions[];
}
extern "C" {

}
#define SECTION(name) __attribute__((section(".svo_TagUtils_" #name)))

SECTION(operator.delete___dupe5) void TagUtilsDelete(void *memory)
{
    svFreeSafe(GetMemoryContext(), memory);
}

SECTION(RegisterCommonTagModules) void RegisterCommonTagModules(void)
{
    SVTagModuleListState *list = getInstance___dupe3();
    AddTagModule(list, getInstance___dupe2());
    AddTagModule(list, getInstance___dupe4());
    AddTagModule(list, getInstance___dupe7());
    AddTagModule(list, getInstance___dupe5());
    AddTagModule(list, getInstance___dupe8());
    AddTagModule(list, getInstance___dupe9());
    AddTagModule(list, getInstance___dupe20());
    AddTagModule(list, getInstance___dupe12());
    AddTagModule(list, getInstance___dupe13());
    AddTagModule(list, getInstance___dupe14());
    AddTagModule(list, getInstance___dupe15());
    AddTagModule(list, getInstance___dupe16());
    AddTagModule(list, getInstance___dupe18());
    AddTagModule(list, getInstance___dupe22());
    AddTagModule(list, getInstance___dupe17());
    AddTagModule(list, getInstance___dupe26());
    AddTagModule(list, getInstance___dupe19());
    AddTagModule(list, getInstance___dupe21());
    AddTagModule(list, getInstance___dupe23());
    AddTagModule(list, getInstance___dupe24());
    AddTagModule(list, getInstance___dupe25());
    AddTagModule(list, getInstance___dupe27());
    AddTagModule(list, getInstance___dupe10());
    AddTagModule(list, getInstance___dupe11());
    AddTagModule(list, getInstance___dupe28());
    AddTagModule(list, getInstance___dupe29());
    AddTagModule(list, getInstance___dupe6());
    AddTagModule(list, getInstance___dupe30());
    AddTagModule(list, getInstance___dupe31());
}

SECTION(getIntAttrib) long getIntAttrib(iks *xml, char *name, int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text || !svisdigit((signed char)*text)) return 0;
    *value = atoi(text);
    return 1;
}

SECTION(getBoolAttrib) long getBoolAttrib(iks *xml, char *name, int *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    if (!strcasecmp(text, svoTagTrue)) *value = 1;
    else if (!strcasecmp(text, svoTagFalse)) *value = 0;
    // An unrecognized but present attribute still succeeds without a store.
    return 1;
}

SECTION(getFloatAttrib) long getFloatAttrib(iks *xml, char *name, float *value)
{
    char *text = iks_find_attrib(xml, name);
    if (!text || !svisdigit((signed char)*text)) return 0;
    // Retail atof returns IEEE double bits in v0, then dptofp returns f0.
    *value = dptofp(SvoAtofBits(text));
    return 1;
}

SECTION(getAlignAttrib) long getAlignAttrib(iks *xml, char *name, int *align)
{
    char *text = iks_find_attrib(xml, name);
    if (!text) return 0;
    if (!strcasecmp(text, svoTagCenter)) *align = 1;
    else if (!strcasecmp(text, svoTagLeft)) *align = 0;
    else if (!strcasecmp(text, svoTagRight)) *align = 2;
    else {
        __SVO_Assert_Handler(svoTagUtilsSource, 0xCD);
        return 0;
    }
    return 1;
}

SECTION(getColorAttrib) long getColorAttrib(iks *xml, char *name, unsigned int *color)
{
    char *text = iks_find_attrib(xml, name);
    if (text) {
        if (*text == '#' && svisxdigit((signed char)text[1])) {
            *color = strtol(text + 1, 0, 16);
            return 1;
        }
        __SVO_Assert_Handler(svoTagUtilsSource, 0xF1);
    }
    return 0;
}

long getLinkOptionAttrib(iks *xml, char *name, unsigned int *option);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TagUtils", getLinkOptionAttrib);

SECTION(getStringAttrib) long getStringAttrib(iks *xml, char *name, char **value)
{
    char *text = iks_find_attrib(xml, name);
    if (text) *value = text;
    return text != 0;
}

SECTION(getTagByName) SVTag *getTagByName(char *name, CPage *page)
{
    SVTag **tags = page->m_pFrontDisplayBuffer->tagList;
    int count = 0;
    while (*tags && count < 256) {
        SVTag *tag = *tags++;
        if (!strcasecmp(tag->vtable->GetTagName(tag), name)) return tag;
        ++count;
    }
    return 0;
}

iks *getChildIksStruct(iks *xml, char *name);
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/TagUtils", getChildIksStruct);

SECTION(getChildIksStructList) int getChildIksStructList(iks *xml, char *name, iks **list, int size)
{
    if (!xml) __SVO_Assert_Handler(svoTagUtilsSource, 0x161);
    if (!list) __SVO_Assert_Handler(svoTagUtilsSource, 0x162);
    if (size <= 0) __SVO_Assert_Handler(svoTagUtilsSource, 0x163);
    memset(list, 0, (unsigned int)size * 4);
    int count = 0;
    if (iks_has_children(xml)) {
        for (iks *child = iks_child(xml); child; child = iks_next(child)) {
            if (iks_name(child) && !strncmp(name, iks_name(child), 256)) {
                if (count < size) list[count] = child;
                ++count;
            }
        }
        if (count > size) {
            __SVO_Assert_Handler(svoTagUtilsSource, 0x186);
            count = size;
        }
    }
    return count;
}

}
