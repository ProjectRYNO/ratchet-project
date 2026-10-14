#include "CPluginBase.h"

#define PLUGIN_SECTION(name) __attribute__((section(".svo_plugin_" #name)))

extern "C" PLUGIN_SECTION(emptyMessageQueue) void emptyMessageQueue(CPluginQueuePrefix *plugin)
{
    for (int k = 0; k < 32; k++) {
        plugin->m_messageQueue[k].sender = 0;
        plugin->m_messageQueue[k].event = -1;
    }
    plugin->m_curSender = 0;
    plugin->m_curEvent = -1;
    plugin->m_headIndex = 0;
    plugin->m_tailIndex = 0;
}
