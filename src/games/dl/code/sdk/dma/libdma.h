#ifndef LIBDMA_H
#define LIBDMA_H

typedef struct { /* 0x14, retail boot DMA environment */
    /* 0x00 */ unsigned char sts;
    /* 0x01 */ unsigned char std;
    /* 0x02 */ unsigned char mfd;
    /* 0x03 */ unsigned char release;
    /* 0x04 */ unsigned short priority;
    /* 0x06 */ unsigned short enable;
    /* 0x08 */ unsigned short skip;
    /* 0x0A */ unsigned short transfer;
    /* 0x0C */ void *ringBase;
    /* 0x10 */ unsigned int ringSize;
} DmaEnv;

/* EE boot libdma; channel pointers refer to 32-bit DMA hardware registers. */
volatile unsigned int *sceDmaGetChan(unsigned int channel);
unsigned int CheckAddress(unsigned int address);
void memclr(unsigned char *buffer, int size);
void WaitDma(volatile unsigned int *channel);
void sceDmaSend(volatile unsigned int *channel, void *address);
unsigned int sceDmaPause(volatile unsigned int *channel);

unsigned int sceDmaReset(int mode);
int sceDmaPutEnv(DmaEnv *env);

#endif
