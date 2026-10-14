# iksemel sax_core: byte-exact switch version

`sax_core` (0x01EE4204, 0x89C) builds from a compact, nonmatching if-chain in
`code/iksemel/src/sax.c` (0x898 bytes; see [IKSEMEL.md](IKSEMEL.md#jump-table-functions)).
The C below is the recovered `switch` form. With only the jump-table address fields masked,
it compiles to retail's exact 551 instructions under SCE ee-gcc 2.96 `-Os`
(`IKSEMEL_COMPILE_FLAGS`; probe, 2026-10-13). Its `switch` dispatches through `jtbl_0019AFA0`
in core.rdata, and no iksemel object can place `.rodata`. With rodata slot support, this
version replaces the if-chain as a byte-exact function. The if-chain was derived from it.

Its strings use the same names as sax.c (`iksEntityNameAmp`..`iksEntityNameGt`,
`iksCDataBracket`, `iksCDataBrackets`; see [IKSEMEL_GLOBALS.csv](../symbols/IKSEMEL_GLOBALS.csv)).

This is upstream iksemel's state machine with SCE changes. It parses in place in the
`iks_parse` buffer, with no token stack. An entity is decoded into the buffer at the
`;` and becomes part of the following character data. `tag_open` and `token_pos` record
an open tag for `iks_parse`, and attribute growth goes through `AllocateMoreAttrs`.

```c
enum {
    C_CDATA = 0, C_TAG_START, C_TAG, C_TAG_END, C_ATTRIBUTE, C_ATTRIBUTE_1, C_ATTRIBUTE_2,
    C_VALUE, C_VALUE_APOS, C_VALUE_QUOT, C_WHITESPACE, C_ENTITY, C_COMMENT, C_COMMENT_1,
    C_COMMENT_2, C_COMMENT_3, C_MARKUP, C_MARKUP_1, C_SECT, C_SECT_CDATA, C_SECT_CDATA_1,
    C_SECT_CDATA_2, C_SECT_CDATA_3, C_SECT_CDATA_4, C_SECT_CDATA_C, C_SECT_CDATA_E,
    C_SECT_CDATA_E2, C_PI
};

int sax_core(iksparser *prs, char *buf, int len)
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
```
