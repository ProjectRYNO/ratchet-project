#include "CPluginBase.h"

extern "C" __attribute__((section(".svo_plugin_emptyMessageQueue")))
void emptyMessageQueue(CPluginQueuePrefix *plugin)
{
    int k = 0;
    int i = 31;
    do {
        plugin->m_messageQueue[k].sender = 0;
        plugin->m_messageQueue[k].event = -1;
        k++;
    } while (--i >= 0);
    plugin->m_curSender = 0;
    plugin->m_curEvent = -1;
    plugin->m_headIndex = 0;
    plugin->m_tailIndex = 0;
}
