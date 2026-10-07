#ifndef CPLUGINBASE_H
#define CPLUGINBASE_H

struct SVTag;
typedef struct { // 0x08
    /* 0x00 */ int event;
    /* 0x04 */ SVTag *sender;
} PluginMessage;

typedef struct { // 0x24
    /* 0x00 */ int event;
    /* 0x04 */ char sender[32];
} PluginExpectedMessage;

// Verified prefix shared by queue operations and manager message dispatch.
typedef struct { // 0x590
    /* 0x000 */ PluginExpectedMessage m_expectedMessages[32];
    /* 0x480 */ PluginMessage m_messageQueue[32];
    /* 0x580 */ int m_headIndex;
    /* 0x584 */ int m_tailIndex;
    /* 0x588 */ int m_curEvent;
    /* 0x58C */ SVTag *m_curSender;
} CPluginQueuePrefix;

struct CPluginBaseState;
typedef struct { // 0x14 (vtable prefix)
    /* 0x00 */ void *unknown00;
    /* 0x04 */ void *unknown04;
    /* 0x08 */ void *unknown08;
    /* 0x0C */ void (*Process)(CPluginBaseState *plugin, long updateType);
    /* 0x10 */ void (*AddMessage)(CPluginBaseState *plugin, SVTag *sender, int event);
} CPluginBaseVtablePrefix;

// Retail storage extent; the middle fields have not yet been recovered here.
struct CPluginBaseState { // 0x638
    /* 0x000 */ CPluginQueuePrefix queue;
    /* 0x590 */ unsigned char unrecovered590[0xA4];
    /* 0x634 */ const CPluginBaseVtablePrefix *vtable;
};

extern "C" void emptyMessageQueue(CPluginQueuePrefix *plugin);

#endif
