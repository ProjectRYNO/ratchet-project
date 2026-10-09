#ifndef SVPERSISTENTDATA_H
#define SVPERSISTENTDATA_H
struct SVPersistentData { // 0x1B78 (verified cookie-data prefix)
    /* 0x0000 */ unsigned char unrecovered0000[0x100];
    /* 0x0100 */ char serverName[128];
    /* 0x0180 */ unsigned char unrecovered0180[0x200];
    /* 0x0380 */ unsigned short port;
    /* 0x0382 */ unsigned char unrecovered0382[0x1006];
    /* 0x1388 */ char cookieData[2032];
};
#endif
