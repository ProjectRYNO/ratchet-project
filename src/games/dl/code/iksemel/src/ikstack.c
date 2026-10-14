#include "common.h"
#include "iksemel.h"
#include <string.h>

// Rounds up to the next multiple of 8, adding a full 8 when already aligned.
#define ALIGN8(x) ((x) + (8 - ((x) & 7)))

ikstack *IKS_SECTION(find_space) find_space(ikstack *s, unsigned int size)
{
    unsigned int csize;

    csize = s->len;
    while (1) {
        if (s->len - s->used >= size) return s;
        if (!s->next) break;
        s = s->next;
    }
    if (size < csize) size = csize;
    s->next = iks_stack_new(size);
    return s->next;
}

ikstack *IKS_SECTION(iks_stack_new) iks_stack_new(unsigned int chunk_size)
{
    ikstack *s;

    if (chunk_size < 0x20) chunk_size = 0x20;
    chunk_size = ALIGN8(chunk_size);
    s = my_malloc_func(sizeof(ikstack) + chunk_size);
    if (!s) return 0;
    s->len = chunk_size;
    s->used = 0;
    s->pad_0 = -1;
    s->last = -1;
    s->next = 0;
    return s;
}

void *IKS_SECTION(iks_stack_alloc) iks_stack_alloc(ikstack *s, unsigned int size)
{
    ikstack *c;
    void *mem;

    if (size < 8) size = 8;
    size = ALIGN8(size);
    c = find_space(s, size);
    if (!c) return 0;
    mem = c->data + c->used;
    c->last = c->used;
    c->used += size;
    return mem;
}

char *IKS_SECTION(iks_stack_strdup) iks_stack_strdup(ikstack *s, const char *src, unsigned int len)
{
    char *dest;

    if (!src) return 0;
    if (0 == len) len = strlen(src);
    dest = iks_stack_alloc(s, len + 1);
    if (!dest) return 0;
    memcpy(dest, src, len);
    dest[len] = '\0';
    return dest;
}

char *IKS_SECTION(iks_stack_strecat) iks_stack_strecat(ikstack *s, char *old, unsigned int old_len, const char *src, unsigned int src_len)
{
    char *ret;
    ikstack *c;

    if (!old_len) old_len = strlen(old);
    if (!src_len) src_len = strlen(src);
    for (c = s; c; c = c->next) {
        if (c->data + c->last == old) break;
    }
    if (!c) {
        ret = iks_stack_alloc(s, old_len + src_len + 1);
        memcpy(ret, old, old_len);
        memcpy(ret + old_len, src, src_len);
        ret[old_len + src_len] = '\0';
        return ret;
    }
    if (src_len < c->len - c->used) {
        ret = c->data + c->last;
        memcpy(ret + old_len, src, src_len);
        c->used += src_len;
        c->data[c->used] = '\0';
    } else {
        c = find_space(s, ALIGN8(old_len + src_len + 1));
        if (!c) return 0;
        c->last = c->used;
        ret = c->data + c->used;
        memcpy(ret, old, old_len);
        c->used += old_len;
        memcpy(c->data + c->used, src, src_len);
        c->used += src_len;
        c->data[c->used] = '\0';
        c->used++;
    }
    c->used = ALIGN8(c->used);
    return ret;
}

void IKS_SECTION(iks_stack_delete) iks_stack_delete(ikstack *s)
{
    ikstack *tmp;

    while (s) {
        tmp = s->next;
        my_free_func(s);
        s = tmp;
    }
}
