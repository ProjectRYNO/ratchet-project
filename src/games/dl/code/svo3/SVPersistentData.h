#ifndef SVPERSISTENTDATA_H
#define SVPERSISTENTDATA_H
struct SVPersistentData { // 0x1B78 (verified cookie-data prefix)
    /* 0x0000 */ unsigned char unrecovered0000[0x1388];
    /* 0x1388 */ char cookieData[2032];
};
#endif
