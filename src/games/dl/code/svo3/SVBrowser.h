#ifndef SVBROWSER_H
#define SVBROWSER_H

struct CPage;
// Verified prefix used by PageHistory; not the complete browser allocation.
typedef struct { // 0xA8 (prefix)
    /* 0x00 */ unsigned char unrecovered[0xA4];
    /* 0xA4 */ CPage *m_pMainPage;
} SVBrowserPrefix;

extern "C" SVBrowserPrefix *GetInstance(void);
extern "C" {
long BrowserIsIdle(SVBrowserPrefix *browser);
void SetLogout(SVBrowserPrefix *browser);
}
#endif
