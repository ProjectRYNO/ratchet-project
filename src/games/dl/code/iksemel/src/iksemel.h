#ifndef IKSEMEL_H
#define IKSEMEL_H

#include "iks.h"

#define IKS_SECTION(name) __attribute__((section(".iks_" #name)))

// Keep the remaining assembly at its retail address alongside compiled slots.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .iks_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

// Retail chunk header, verified against iks_stack_new/alloc/strecat; data follows at 0x14.
typedef struct ikstack_struct { // 0x18
    /* 0x00 */ unsigned int len;
    /* 0x04 */ unsigned int used;
    /* 0x08 */ int pad_0;
    /* 0x0C */ unsigned int last;
    /* 0x10 */ struct ikstack_struct *next;
    /* 0x14 */ char data[4];
} ikstack;

typedef int iksTagHook(void *user_data, char *name, char **atts, int type);
typedef int iksCDataHook(void *user_data, char *data, unsigned int len);
typedef void iksDeleteHook(void *user_data);

// Retail parser, verified against iks_sax_extend/parse/parser_reset/AllocateMoreAttrs.
// token_pos is the buffer offset iks_parse keeps while a tag is still open.
typedef struct iksparser_struct { // 0x64
    /* 0x00 */ ikstack *s;
    /* 0x04 */ void *user_data;
    /* 0x08 */ iksTagHook *tagHook;
    /* 0x0C */ iksCDataHook *cdataHook;
    /* 0x10 */ iksDeleteHook *deleteHook;
    /* 0x14 */ char *stack;
    /* 0x18 */ unsigned int stack_max;
    /* 0x1C */ unsigned int stack_pos;
    /* 0x20 */ int context;
    /* 0x24 */ int oldcontext;
    /* 0x28 */ int tag_open;
    /* 0x2C */ unsigned int token_pos;
    /* 0x30 */ int tagtype;
    /* 0x34 */ unsigned int attmax;
    /* 0x38 */ unsigned int attcur;
    /* 0x3C */ int attflag;
    /* 0x40 */ char **atts;
    /* 0x44 */ int valflag;
    /* 0x48 */ unsigned int entpos;
    /* 0x4C */ char entity[8];
    /* 0x54 */ unsigned int nr_bytes;
    /* 0x58 */ unsigned int nr_lines;
    /* 0x5C */ int uni_max;
    /* 0x60 */ int uni_len;
} iksparser;

enum { IKS_OK = 0, IKS_NOMEM = 1, IKS_BADXML = 2, IKS_HOOK = 3 };
enum { IKS_OPEN = 0, IKS_CLOSE = 1, IKS_SINGLE = 2 };

#ifdef __cplusplus
extern "C" {
#endif

extern void *(*my_malloc_func)(unsigned int size);
extern void (*my_free_func)(void *ptr);

ikstack *iks_stack_new(unsigned int chunk_size);
void *iks_stack_alloc(ikstack *s, unsigned int size);
char *iks_stack_strdup(ikstack *s, const char *src, unsigned int len);
char *iks_stack_strecat(ikstack *s, char *old, unsigned int old_len, const char *src, unsigned int src_len);
void iks_stack_delete(ikstack *s);

iks *iks_new_within(const char *name, ikstack *s);
iks *iks_insert(iks *x, const char *name);
iks *iks_insert_cdata(iks *x, const char *data, unsigned int len);
iks *iks_insert_attrib(iks *x, const char *name, const char *value);
void iks_delete(iks *x);
iks *iks_find(iks *x, const char *name);
char *iks_find_cdata(iks *x, const char *name);
char *iks_find_attrib(iks *x, const char *name);

iksparser *iks_sax_extend(ikstack *s, void *user_data, iksTagHook *tagHook, iksCDataHook *cdataHook, iksDeleteHook *deleteHook);
unsigned int iks_nr_bytes(iksparser *prs);
unsigned int iks_nr_lines(iksparser *prs);
int iks_parse(iksparser *prs, const char *data, unsigned int len, int finish);
void iks_parser_reset(iksparser *prs);
void iks_parser_delete(iksparser *prs);
iksparser *iks_dom_new(iks **iksptr);

void iks_set_malloc_func(void *(*func)(unsigned int size));
void iks_set_free_func(void (*func)(void *ptr));
char *iks_escape(ikstack *s, char *src, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif
