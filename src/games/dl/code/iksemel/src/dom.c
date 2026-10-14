#include "common.h"
#include "iksemel.h"
#include <stdio.h>

struct dom_data { // 0x0C
    /* 0x00 */ iks **iksptr;
    /* 0x04 */ iks *current;
    /* 0x08 */ unsigned int chunk_size;
};

extern const char iksDomErrorBlankLines[];
extern const char iksDomErrorBorder[];
extern const char iksDomErrorParsing[];
extern const char iksDomErrorTwoTags[];
extern const char iksDomErrorRootLevel[];
extern const char iksDomErrorNotAllowed[];

int IKS_SECTION(tagHook) tagHook(struct dom_data *data, char *name, char **atts, int type)
{
    iks *x;
    int i;

    if (*data->iksptr) {
        printf(iksDomErrorBlankLines);
        printf(iksDomErrorBorder);
        printf(iksDomErrorBorder);
        printf(iksDomErrorParsing);
        printf(iksDomErrorTwoTags);
        printf(iksDomErrorRootLevel);
        printf(iksDomErrorNotAllowed);
        printf(iksDomErrorBorder);
        printf(iksDomErrorBorder);
        printf(iksDomErrorBlankLines);
        return IKS_BADXML;
    }
    if (IKS_OPEN == type || IKS_SINGLE == type) {
        if (data->current) {
            x = iks_insert(data->current, name);
        } else {
            ikstack *s;
            s = iks_stack_new(data->chunk_size);
            x = iks_new_within(name, s);
        }
        if (atts) {
            i = 0;
            while (atts[i]) {
                iks_insert_attrib(x, atts[i], atts[i + 1]);
                i += 2;
            }
        }
        data->current = x;
    }
    if (IKS_CLOSE == type || IKS_SINGLE == type) {
        x = iks_parent(data->current);
        if (x) {
            data->current = x;
        } else {
            *data->iksptr = data->current;
            data->current = 0;
        }
    }
    return IKS_OK;
}

int IKS_SECTION(cdataHook) cdataHook(struct dom_data *data, char *cdata, unsigned int len)
{
    if (data->current) iks_insert_cdata(data->current, cdata, len);
    return IKS_OK;
}

void IKS_SECTION(deleteHook) deleteHook(struct dom_data *data)
{
    if (data->current) iks_delete(data->current);
    data->current = 0;
}

iksparser *IKS_SECTION(iks_dom_new) iks_dom_new(iks **iksptr)
{
    ikstack *s;
    struct dom_data *data;

    *iksptr = 0;
    s = iks_stack_new(0x100);
    if (!s) return 0;
    data = iks_stack_alloc(s, sizeof(struct dom_data));
    data->iksptr = iksptr;
    data->current = 0;
    data->chunk_size = 0x1000;
    return iks_sax_extend(s, data, (iksTagHook *)tagHook, (iksCDataHook *)cdataHook, (iksDeleteHook *)deleteHook);
}
