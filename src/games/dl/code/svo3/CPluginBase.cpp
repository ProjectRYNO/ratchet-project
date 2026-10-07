#include "CPluginBase.h"

extern "C" __attribute__((section(".svo_plugin_emptyMessageQueue")))
void emptyMessageQueue(CPluginQueuePrefix *plugin)
{
    PluginMessage *message = plugin->m_messageQueue;
    int remaining = 32;
    do {
        message->sender = 0;
        message->event = -1;
        ++message;
    } while (--remaining);
    plugin->m_curEvent = -1;
    plugin->m_tailIndex = 0;
    plugin->m_curSender = 0;
    plugin->m_headIndex = 0;
}
