#include "common.h"
#include "iksemel.h"
#include <string.h>

iks *IKS_SECTION(iks_new_within) iks_new_within(const char *name, ikstack *s)
{
    iks *x;

    x = iks_stack_alloc(s, sizeof(iks));
    if (!x) return 0;
    memset(x, 0, sizeof(iks));
    x->type = IKS_TAG;
    x->stack = s;
    if (name) {
        x->name = iks_stack_strdup(s, name, 0);
        if (!x->name) return 0;
    }
    return x;
}

iks *IKS_SECTION(iks_insert) iks_insert(iks *x, const char *name)
{
    iks *y;

    if (!x) return 0;
    y = iks_new_within(name, x->stack);
    if (!y) return 0;
    y->parent = x;
    if (!x->children) x->children = y;
    if (x->last_child) {
        x->last_child->next = y;
        y->prev = x->last_child;
    }
    x->last_child = y;
    return y;
}

iks *IKS_SECTION(iks_insert_cdata) iks_insert_cdata(iks *x, const char *data, unsigned int len)
{
    iks *y;

    if (!x || !data) return 0;
    if (len == 0) len = strlen(data);
    y = x->last_child;
    if (y && y->type == IKS_CDATA) {
        y->cdata = iks_stack_strecat(x->stack, y->cdata, y->cdata_size, data, len);
        y->cdata_size += len;
    } else {
        y = iks_insert(x, 0);
        if (!y) return 0;
        y->type = IKS_CDATA;
        y->cdata = iks_stack_alloc(x->stack, len + 1);
        if (!y->cdata) return 0;
        memcpy(y->cdata, data, len);
        y->cdata[len] = '\0';
        y->cdata_size = len;
    }
    return y;
}

iks *IKS_SECTION(iks_insert_attrib) iks_insert_attrib(iks *x, const char *name, const char *value)
{
    iks *y;
    unsigned int len;

    if (!x) return 0;
    y = x->attributes;
    while (y) {
        if (strcmp(name, y->name) == 0) break;
        y = y->next;
    }
    if (0 == y) {
        y = iks_new_within(name, x->stack);
        if (!y) return 0;
        y->parent = x;
        if (!x->attributes) x->attributes = y;
        if (x->last_attribute) {
            x->last_attribute->next = y;
            y->prev = x->last_attribute;
        }
        x->last_attribute = y;
    }
    if (value) {
        len = strlen(value);
        y->type = IKS_ATTRIBUTE;
        y->cdata = iks_stack_alloc(x->stack, len + 1);
        if (!y->cdata) return 0;
        memcpy(y->cdata, value, len);
        y->cdata[len] = '\0';
        y->cdata_size = len;
    } else {
        if (y->next) y->next->prev = y->prev;
        if (y->prev) y->prev->next = y->next;
        if (x->attributes == y) x->attributes = y->next;
        if (x->last_attribute == y) x->last_attribute = y->prev;
    }
    return y;
}

void IKS_SECTION(iks_delete) iks_delete(iks *x)
{
    if (x) iks_stack_delete(x->stack);
}

iks *IKS_SECTION(iks_next) iks_next(iks *node)
{
    return node ? node->next : 0;
}

iks *IKS_SECTION(iks_next_tag) iks_next_tag(iks *x)
{
    if (x) {
        while (1) {
            x = x->next;
            if (0 == x) break;
            if (IKS_TAG == x->type) return x;
        }
    }
    return 0;
}

iks *IKS_SECTION(iks_parent) iks_parent(iks *node)
{
    return node ? node->parent : 0;
}

iks *IKS_SECTION(iks_child) iks_child(iks *node)
{
    return node ? node->children : 0;
}

iks *IKS_SECTION(iks_find) iks_find(iks *x, const char *name)
{
    iks *y;

    if (!x) return 0;
    y = x->children;
    while (y) {
        if (y->name && strcmp(y->name, name) == 0) return y;
        y = y->next;
    }
    return 0;
}

char *IKS_SECTION(iks_find_cdata) iks_find_cdata(iks *x, const char *name)
{
    iks *y;

    y = iks_find(x, name);
    if (!y) return 0;
    y = y->children;
    if (!y) return 0;
    return y->cdata;
}

char *IKS_SECTION(iks_find_attrib) iks_find_attrib(iks *x, const char *name)
{
    iks *y;

    if (!x) return 0;
    y = x->attributes;
    while (y) {
        if (y->name && strcmp(y->name, name) == 0) return y->cdata;
        y = y->next;
    }
    return 0;
}

int IKS_SECTION(iks_type) iks_type(iks *node)
{
    return node ? node->type : 0;
}

char *IKS_SECTION(iks_name) iks_name(iks *node)
{
    return node ? node->name : 0;
}

char *IKS_SECTION(iks_cdata) iks_cdata(iks *node)
{
    return node ? node->cdata : 0;
}

int IKS_SECTION(iks_has_children) iks_has_children(iks *x)
{
    if (x && x->children) return 1;
    return 0;
}

extern const char iksEntityAmp[];
extern const char iksEntityApos[];
extern const char iksEntityQuot[];
extern const char iksEntityLt[];
extern const char iksEntityGt[];

unsigned int IKS_SECTION(escape_size) escape_size(char *src, unsigned int len)
{
    unsigned int sz;
    char c;
    unsigned int i;

    sz = 0;
    for (i = 0; i < len; i++) {
        c = src[i];
        switch (c) {
            case '&': sz += 4; break;
            case '\'': sz += 5; break;
            case '"': sz += 5; break;
            case '<': sz += 3; break;
            case '>': sz += 3; break;
            default: sz++; break;
        }
    }
    return sz;
}

char *IKS_SECTION(my_strcat) my_strcat(char *dest, char *src, unsigned int len)
{
    if (0 == len) len = strlen(src);
    memcpy(dest, src, len);
    return dest + len;
}

char *IKS_SECTION(escape) escape(char *dest, char *src, unsigned int len)
{
    char c;
    unsigned int i;
    unsigned int j = 0;

    for (i = 0; i < len; i++) {
        c = src[i];
        if ('&' == c || '<' == c || '>' == c || '\'' == c || '"' == c) {
            if (i - j > 0) dest = my_strcat(dest, src + j, i - j);
            j = i + 1;
            switch (c) {
                case '&': dest = my_strcat(dest, (char *)iksEntityAmp, 5); break;
                case '\'': dest = my_strcat(dest, (char *)iksEntityApos, 6); break;
                case '"': dest = my_strcat(dest, (char *)iksEntityQuot, 6); break;
                case '<': dest = my_strcat(dest, (char *)iksEntityLt, 4); break;
                case '>': dest = my_strcat(dest, (char *)iksEntityGt, 4); break;
            }
        }
    }
    if (i - j > 0) dest = my_strcat(dest, src + j, i - j);
    return dest;
}
