#ifndef LIBMTAP_H
#define LIBMTAP_H

/* Retail boot EE multitap RPC client. */
void DPRINT(const char *format, ...);
int sceMtapSetWorkAddr(void *work);
int sceMtapInit(void);
int sceMtapEnd(void);
int sceMtapPortOpen(int port);
int sceMtapPortClose(int port);
int sceMtapGetConnection(int port);
int sceMtapGetModVersion(void);

#endif
