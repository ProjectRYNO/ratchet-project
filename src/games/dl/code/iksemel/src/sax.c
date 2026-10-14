#include "common.h"
#include "iksemel.h"
#include <string.h>

enum {
    C_CDATA = 0, C_TAG_START, C_TAG, C_TAG_END, C_ATTRIBUTE, C_ATTRIBUTE_1, C_ATTRIBUTE_2,
    C_VALUE, C_VALUE_APOS, C_VALUE_QUOT, C_WHITESPACE, C_ENTITY, C_COMMENT, C_COMMENT_1,
    C_COMMENT_2, C_COMMENT_3, C_MARKUP, C_MARKUP_1, C_SECT, C_SECT_CDATA, C_SECT_CDATA_1,
    C_SECT_CDATA_2, C_SECT_CDATA_3, C_SECT_CDATA_4, C_SECT_CDATA_C, C_SECT_CDATA_E,
    C_SECT_CDATA_E2, C_PI
};

extern const char iksEntityNameAmp[];
extern const char iksEntityNameQuot[];
extern const char iksEntityNameApos[];
extern const char iksEntityNameLt[];
extern const char iksEntityNameGt[];
extern const char iksCDataBracket[];
extern const char iksCDataBrackets[];

int sax_core(iksparser *prs, char *buf, int len);

iksparser *IKS_SECTION(iks_sax_extend) iks_sax_extend(ikstack *s, void *user_data, iksTagHook *tagHook, iksCDataHook *cdataHook, iksDeleteHook *deleteHook)
{
    iksparser *prs;

    prs = iks_stack_alloc(s, sizeof(iksparser));
    if (!prs) return 0;
    memset(prs, 0, sizeof(iksparser));
    prs->s = s;
    prs->user_data = user_data;
    prs->tagHook = tagHook;
    prs->cdataHook = cdataHook;
    prs->deleteHook = deleteHook;
    return prs;
}

unsigned int IKS_SECTION(iks_nr_bytes) iks_nr_bytes(iksparser *prs)
{
    return prs->nr_bytes;
}

unsigned int IKS_SECTION(iks_nr_lines) iks_nr_lines(iksparser *prs)
{
    return prs->nr_lines;
}

int IKS_SECTION(AllocateMoreAttrs) AllocateMoreAttrs(iksparser *prs)
{
    char **tmp;

    if (prs->attcur < prs->attmax * 2) return IKS_OK;
    prs->attmax += 12;
    tmp = my_malloc_func(sizeof(char *) * 2 * prs->attmax);
    if (!tmp) return IKS_NOMEM;
    memset(tmp, 0, sizeof(char *) * 2 * prs->attmax);
    memcpy(tmp, prs->atts, sizeof(char *) * prs->attcur);
    my_free_func(prs->atts);
    prs->atts = tmp;
    return IKS_OK;
}

int IKS_SECTION(sax_core) sax_core(iksparser *prs, char *buf, int len)
{
    int err;
    int pos = 0, old = 0, re;
    unsigned char c;

    while (pos < len) {
        re = 0;
        c = buf[pos];
        if (0 == c || 0xFE == c || 0xFF == c) return IKS_BADXML;
        if (prs->uni_max) {
            if ((c & 0xC0) != 0x80) return IKS_BADXML;
            prs->uni_len++;
            if (prs->uni_len == prs->uni_max) prs->uni_max = 0;
            goto cont;
        } else {
            if (c & 0x80) {
                unsigned char mask;
                if ((c & 0x60) == 0x40) {
                    prs->uni_max = 2;
                    mask = 0x1F;
                } else if ((c & 0x70) == 0x60) {
                    prs->uni_max = 3;
                    mask = 0x0F;
                } else if ((c & 0x78) == 0x70) {
                    prs->uni_max = 4;
                    mask = 0x07;
                } else if ((c & 0x7C) == 0x78) {
                    prs->uni_max = 5;
                    mask = 0x03;
                } else if ((c & 0x7E) == 0x7C) {
                    prs->uni_max = 6;
                    mask = 0x01;
                } else {
                    return IKS_BADXML;
                }
                if ((c & mask) == 0) return IKS_BADXML;
                prs->uni_len = 1;
                goto cont;
            }
        }

        switch (prs->context) {
            case C_CDATA:
                if ('&' == c) {
                    buf[pos] = '\0';
                    if (old < pos && prs->cdataHook) {
                        err = prs->cdataHook(prs->user_data, &buf[old], pos - old);
                        if (IKS_OK != err) return err;
                    }
                    prs->entpos = 0;
                    prs->context = C_ENTITY;
                    break;
                }
                if ('<' == c) {
                    if (old < pos && prs->cdataHook) {
                        err = prs->cdataHook(prs->user_data, &buf[old], pos - old);
                        if (IKS_OK != err) return err;
                    }
                    prs->tag_open = 1;
                    prs->context = C_TAG_START;
                    prs->token_pos = buf - prs->stack + pos;
                }
                break;

            case C_TAG_START:
                prs->context = C_TAG;
                if ('/' == c) {
                    prs->tagtype = IKS_CLOSE;
                    prs->token_pos++;
                    break;
                }
                if ('?' == c) {
                    prs->context = C_PI;
                    break;
                }
                if ('!' == c) {
                    prs->context = C_MARKUP;
                    break;
                }
                prs->tagtype = IKS_OPEN;
                break;

            case C_TAG:
                if (' ' == c || '\t' == c || '\r' == c || '\n' == c) {
                    buf[pos] = '\0';
                    if (IKS_CLOSE == prs->tagtype)
                        prs->oldcontext = C_TAG_END;
                    else
                        prs->oldcontext = C_ATTRIBUTE;
                    prs->context = C_WHITESPACE;
                    break;
                }
                if ('/' == c) {
                    if (IKS_CLOSE == prs->tagtype) return IKS_BADXML;
                    buf[pos] = '\0';
                    prs->tagtype = IKS_SINGLE;
                    prs->context = C_TAG_END;
                    break;
                }
                if ('>' == c) {
                    prs->context = C_TAG_END;
                    re = 1;
                }
                break;

            case C_TAG_END:
                if (c != '>') return IKS_BADXML;
                buf[pos] = '\0';
                if (prs->tagHook) {
                    char **tmp;
                    if (prs->attcur == 0) tmp = 0; else tmp = prs->atts;
                    err = prs->tagHook(prs->user_data, prs->stack + prs->token_pos + 1, tmp, prs->tagtype);
                    if (IKS_OK != err) return err;
                }
                prs->attcur = 0;
                old = pos + 1;
                prs->attflag = 0;
                prs->tag_open = 0;
                prs->context = C_CDATA;
                break;

            case C_ATTRIBUTE:
                if ('/' == c) {
                    prs->tagtype = IKS_SINGLE;
                    prs->context = C_TAG_END;
                    break;
                }
                if ('>' == c) {
                    prs->context = C_TAG_END;
                    re = 1;
                    break;
                }
                if (!prs->atts) {
                    prs->attmax = 12;
                    prs->atts = my_malloc_func(sizeof(char *) * 2 * 12);
                    if (!prs->atts) return IKS_NOMEM;
                    memset(prs->atts, 0, sizeof(char *) * 2 * 12);
                    prs->attcur = 0;
                } else {
                    if (AllocateMoreAttrs(prs)) return IKS_NOMEM;
                }
                prs->attflag = 1;
                prs->context = C_ATTRIBUTE_1;
                prs->atts[prs->attcur] = &buf[pos];
                break;

            case C_ATTRIBUTE_1:
                if ('=' == c) {
                    buf[pos] = '\0';
                    prs->context = C_VALUE;
                }
                break;

            case C_ATTRIBUTE_2:
                if ('/' == c) {
                    prs->tagtype = IKS_SINGLE;
                    if (AllocateMoreAttrs(prs)) return IKS_NOMEM;
                    prs->atts[prs->attcur] = 0;
                    prs->context = C_TAG_END;
                    break;
                }
                if ('>' != c) {
                    prs->context = C_ATTRIBUTE;
                    re = 1;
                    break;
                }
                if (AllocateMoreAttrs(prs)) return IKS_NOMEM;
                prs->atts[prs->attcur] = 0;
                prs->context = C_TAG_END;
                re = 1;
                break;

            case C_VALUE:
                prs->atts[prs->attcur + 1] = &buf[pos + 1];
                if ('\'' == c) {
                    prs->context = C_VALUE_APOS;
                    break;
                }
                if ('"' == c) {
                    prs->context = C_VALUE_QUOT;
                    break;
                }
                return IKS_BADXML;

            case C_VALUE_APOS:
                if ('\'' == c) {
                    buf[pos] = '\0';
                    prs->oldcontext = C_ATTRIBUTE_2;
                    prs->context = C_WHITESPACE;
                    prs->attcur += 2;
                }
                break;

            case C_VALUE_QUOT:
                if ('"' == c) {
                    buf[pos] = '\0';
                    prs->oldcontext = C_ATTRIBUTE_2;
                    prs->context = C_WHITESPACE;
                    prs->attcur += 2;
                }
                break;

            case C_WHITESPACE:
                if (' ' != c && '\t' != c && '\r' != c && '\n' != c) {
                    prs->context = prs->oldcontext;
                    re = 1;
                }
                break;

            case C_ENTITY:
                if (';' == c) {
                    char t = '?';
                    prs->entity[prs->entpos] = '\0';
                    if (strcmp(prs->entity, iksEntityNameAmp) == 0)
                        t = '&';
                    else if (strcmp(prs->entity, iksEntityNameQuot) == 0)
                        t = '"';
                    else if (strcmp(prs->entity, iksEntityNameApos) == 0)
                        t = '\'';
                    else if (strcmp(prs->entity, iksEntityNameLt) == 0)
                        t = '<';
                    else if (strcmp(prs->entity, iksEntityNameGt) == 0)
                        t = '>';
                    buf[pos] = t;
                    old = pos;
                    prs->context = C_CDATA;
                } else {
                    prs->entity[prs->entpos++] = buf[pos];
                    if (prs->entpos > 7) return IKS_BADXML;
                }
                break;

            case C_COMMENT:
                if ('-' != c) return IKS_BADXML;
                prs->context = C_COMMENT_1;
                break;

            case C_COMMENT_1:
                if ('-' == c) prs->context = C_COMMENT_2;
                break;

            case C_COMMENT_2:
                if ('-' == c)
                    prs->context = C_COMMENT_3;
                else
                    prs->context = C_COMMENT_1;
                break;

            case C_COMMENT_3:
                if ('>' != c) return IKS_BADXML;
                prs->context = C_CDATA;
                old = pos + 1;
                break;

            case C_MARKUP:
                prs->tag_open = 0;
                if ('[' == c) {
                    prs->context = C_SECT;
                    break;
                }
                if ('-' == c) {
                    prs->context = C_COMMENT;
                    break;
                }
                prs->context = C_MARKUP_1;

            case C_MARKUP_1:
                if ('>' == c) {
                    prs->context = C_CDATA;
                    old = pos + 1;
                }
                break;

            case C_SECT:
                if ('C' == c) {
                    prs->context = C_SECT_CDATA;
                    break;
                }
                return IKS_BADXML;

            case C_SECT_CDATA:
                if ('D' != c) return IKS_BADXML;
                prs->context = C_SECT_CDATA_1;
                break;

            case C_SECT_CDATA_1:
                if ('A' != c) return IKS_BADXML;
                prs->context = C_SECT_CDATA_2;
                break;

            case C_SECT_CDATA_2:
                if ('T' != c) return IKS_BADXML;
                prs->context = C_SECT_CDATA_3;
                break;

            case C_SECT_CDATA_3:
                if ('A' != c) return IKS_BADXML;
                prs->context = C_SECT_CDATA_4;
                break;

            case C_SECT_CDATA_4:
                if ('[' != c) return IKS_BADXML;
                old = pos + 1;
                prs->context = C_SECT_CDATA_C;
                break;

            case C_SECT_CDATA_C:
                if (']' == c) {
                    prs->context = C_SECT_CDATA_E;
                    if (prs->cdataHook && old < pos) {
                        err = prs->cdataHook(prs->user_data, &buf[old], pos - old);
                        if (IKS_OK != err) return err;
                    }
                }
                break;

            case C_SECT_CDATA_E:
                if (']' == c) {
                    prs->context = C_SECT_CDATA_E2;
                } else {
                    if (prs->cdataHook) {
                        err = prs->cdataHook(prs->user_data, (char *)iksCDataBracket, 1);
                        if (IKS_OK != err) return err;
                    }
                    old = pos;
                    prs->context = C_SECT_CDATA_C;
                }
                break;

            case C_SECT_CDATA_E2:
                if ('>' == c) {
                    prs->context = C_CDATA;
                    old = pos + 1;
                } else {
                    if (prs->cdataHook) {
                        err = prs->cdataHook(prs->user_data, (char *)iksCDataBrackets, 2);
                        if (IKS_OK != err) return err;
                    }
                    old = pos;
                    prs->context = C_SECT_CDATA_C;
                }
                break;

            case C_PI:
                prs->tag_open = 0;
                old = pos + 1;
                if ('>' == c) prs->context = C_CDATA;
                break;
        }
cont:
        if (0 == re) {
            pos++;
            prs->nr_bytes++;
            if ('\n' == c) prs->nr_lines++;
        }
    }
    err = IKS_OK;
    if (prs->cdataHook && (prs->context == C_CDATA || prs->context == C_SECT_CDATA_C) && old < pos)
        err = prs->cdataHook(prs->user_data, &buf[old], pos - old);
    return err;
}

int IKS_SECTION(iks_parse) iks_parse(iksparser *prs, const char *data, unsigned int len, int finish)
{
    char *buf;
    unsigned int keep;
    int need;
    int diff;
    unsigned int i;

    if (!data) return IKS_OK;
    if (len == 0) len = strlen(data);
    if (prs->stack) {
        diff = 0;
        if (prs->tag_open) {
            keep = prs->stack_pos - prs->token_pos;
            if (prs->token_pos) {
                memmove(prs->stack, prs->stack + prs->token_pos, keep);
                prs->stack_pos -= prs->token_pos;
                diff = -prs->token_pos;
                prs->token_pos = 0;
            }
        } else {
            prs->stack_pos = 0;
            keep = 0;
        }
        need = len - (prs->stack_max - prs->stack_pos);
        if (need > 0) {
            buf = my_malloc_func(prs->stack_max + need);
            if (!buf) return IKS_NOMEM;
            diff += buf - prs->stack;
            if (keep) memcpy(buf, prs->stack, keep);
            memcpy(buf + keep, data, len);
            my_free_func(prs->stack);
            prs->stack = buf;
            buf += keep;
            prs->stack_max += need;
        } else {
            buf = prs->stack + keep;
            memcpy(buf, data, len);
        }
        if (prs->attflag) {
            for (i = 0; i < prs->attmax * 2; i++) {
                if (prs->atts[i]) prs->atts[i] += diff;
            }
        }
    } else {
        keep = 0x100;
        if ((int)len >= 0x100) keep = len;
        buf = my_malloc_func(keep);
        if (!buf) return IKS_NOMEM;
        memcpy(buf, data, len);
        prs->stack = buf;
        prs->stack_max = keep;
    }
    prs->stack_pos += len;
    return sax_core(prs, buf, len);
}

void IKS_SECTION(iks_parser_reset) iks_parser_reset(iksparser *prs)
{
    if (prs->deleteHook) prs->deleteHook(prs->user_data);
    prs->stack_pos = 0;
    prs->context = 0;
    prs->oldcontext = 0;
    prs->tag_open = 0;
    prs->token_pos = 0;
    prs->tagtype = 0;
    prs->attcur = 0;
    prs->attflag = 0;
    prs->valflag = 0;
    prs->entpos = 0;
    prs->nr_bytes = 0;
    prs->nr_lines = 0;
    prs->uni_max = 0;
    prs->uni_len = 0;
}

void IKS_SECTION(iks_parser_delete) iks_parser_delete(iksparser *prs)
{
    if (prs->deleteHook) prs->deleteHook(prs->user_data);
    if (prs->stack) my_free_func(prs->stack);
    if (prs->atts) my_free_func(prs->atts);
    if (prs->s) iks_stack_delete(prs->s);
    else my_free_func(prs);
}
