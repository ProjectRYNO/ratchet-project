#ifndef CPLUGINMANAGER_H
#define CPLUGINMANAGER_H
#include "CPluginBase.h"

typedef struct { // 0x58
    /* 0x00 */ CPluginBaseState *m_pluginList[10];
    /* 0x28 */ int m_numPlugins;
    /* 0x2C */ int m_popupRequests[10];
    /* 0x54 */ int m_curPopupRequest;
} CPluginManagerState;

extern "C" {
void CPluginManager(CPluginManagerState *manager);
void Initialize___dupe5(CPluginManagerState *manager);
// Retail forwards the full 64-bit argument register to Process.
void Update___dupe112(CPluginManagerState *manager, long updateType);
void AddMessage(CPluginManagerState *manager, SVTag *sender, int event);
void EmptyMessageQueue(CPluginManagerState *manager);
}
#endif
