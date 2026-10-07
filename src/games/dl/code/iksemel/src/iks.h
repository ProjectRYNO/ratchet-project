#ifndef IKS_H
#define IKS_H

// Retail EE node layout, verified against iks_new_within/insert/insert_attrib.
typedef struct iks_struct { // 0x30
    /* 0x00 */ struct iks_struct *next;
    /* 0x04 */ struct iks_struct *prev;
    /* 0x08 */ struct iks_struct *children;
    /* 0x0C */ struct iks_struct *last_child;
    /* 0x10 */ struct iks_struct *attributes;
    /* 0x14 */ struct iks_struct *last_attribute;
    /* 0x18 */ struct iks_struct *parent;
    /* 0x1C */ int type;
    /* 0x20 */ struct ikstack_struct *stack;
    /* 0x24 */ char *name;
    /* 0x28 */ char *cdata;
    /* 0x2C */ unsigned int cdata_size;
} iks;

enum { IKS_NONE = 0, IKS_TAG = 1, IKS_ATTRIBUTE = 2, IKS_CDATA = 3 };

#ifdef __cplusplus
extern "C" {
#endif

iks *iks_next(iks *node);
iks *iks_parent(iks *node);
iks *iks_child(iks *node);
int iks_type(iks *node);
char *iks_name(iks *node);
char *iks_cdata(iks *node);
iks *iks_next_tag(iks *node);
int iks_has_children(iks *node);

#ifdef __cplusplus
}
#endif

#endif
