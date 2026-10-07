#ifndef SVCHRONOGRAPH_H
#define SVCHRONOGRAPH_H

struct CSystemContextBase;
typedef struct { // 0x10
    /* 0x00 */ int start;
    /* 0x04 */ int stop;
    /* 0x08 */ int lastlap;
    /* 0x0C */ CSystemContextBase *m_pSystemContext;
} SVChronographState;

extern "C" {
int SV_timerGetMilliseconds(CSystemContextBase *context);
void SVChronograph(SVChronographState *timer, int startnow);
void _SVChronograph(SVChronographState *timer, unsigned int flags);
// The split names contain dots, which are not legal C identifiers.
void *SVChronographNew(unsigned int size) __asm__("operator.new___dupe5");
void SVChronographDelete(void *memory) __asm__("operator.delete___dupe4");
void Start___dupe3(SVChronographState *timer);
void Stop___dupe3(SVChronographState *timer);
void Reset___dupe5(SVChronographState *timer);
int Elapsed(SVChronographState *timer);
int ElapsedMS(SVChronographState *timer);
int IsRunning(SVChronographState *timer);
int IsStopped(SVChronographState *timer);
}
#endif
