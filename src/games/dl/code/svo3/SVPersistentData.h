#ifndef SVPERSISTENTDATA_H
#define SVPERSISTENTDATA_H
struct SVPersistentData { // 0x1B9C
    /* 0x0000 */ unsigned char unrecovered0000[0x100];
    /* 0x0100 */ char serverName[128];
    /* 0x0180 */ unsigned char unrecovered0180[0x200];
    /* 0x0380 */ unsigned short port;
    /* 0x0382 */ unsigned char padding0382[2];
    /* 0x0384 */ char szURIStore[4096];
    /* 0x1384 */ int SVOGameID;
    /* 0x1388 */ char cookieData[2032];
    /* 0x1B78 */ char szMD5Hash[33];
    /* 0x1B99 */ unsigned char padding1B99[3];
};
#endif
