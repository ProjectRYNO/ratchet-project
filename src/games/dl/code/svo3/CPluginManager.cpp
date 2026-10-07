#include "common.h"
// Retain the unresolved wrapper at its original address.
#if !defined(M2CTX) && !defined(PERMUTER) && !defined(ALLOW_NONMATCHING)
#undef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__(".section .svo_plugin_manager_" #NAME ",\"ax\",@progbits\n" \
            ".set noat\n.set noreorder\n" \
            ".include \"" FOLDER "/" #NAME ".s\"\n" \
            ".set reorder\n.set at\n.text\n")
#endif

#include "CPluginManager.h"
#include "SVTag.h"
#include <string.h>

extern "C" {
extern char svoPluginManagerSource[];
extern char svoPluginNullSenderName[];
void __SVO_Assert_Handler(const char *file, int line);
}
#define PLUGIN_MANAGER_SECTION(name) __attribute__((section(".svo_plugin_manager_" #name)))

// Retail tail-call wrappers await compact compiler output.
INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPluginManager", CPluginManager);

void PLUGIN_MANAGER_SECTION(Initialize___dupe5) Initialize___dupe5(CPluginManagerState *manager)
{
    for (int i = 0; i < 10; ++i) {
        manager->m_pluginList[i] = 0;
        manager->m_popupRequests[i] = 0;
    }
    manager->m_curPopupRequest = 0;
    manager->m_numPlugins = 0;
}

void PLUGIN_MANAGER_SECTION(Update___dupe112) Update___dupe112(CPluginManagerState *manager, long updateType)
{
    for (int i = 0; i < manager->m_numPlugins; ++i) {
        CPluginBaseState *plugin = manager->m_pluginList[i];
        plugin->vtable->Process(plugin, updateType);
    }
}

void PLUGIN_MANAGER_SECTION(AddMessage) AddMessage(CPluginManagerState *manager, SVTag *sender, int event)
{
    for (int i = 0; i < manager->m_numPlugins; ++i) {
        for (int j = 0; j < 32; ++j) {
            // Reload the plugin each iteration: callbacks may change the list.
            PluginExpectedMessage *expected = &manager->m_pluginList[i]->queue.m_expectedMessages[j];
            int expectedEvent = expected->event;
            char *expectedName = expected->sender;
            if (!strlen(expectedName)) break;
            char *name = svoPluginNullSenderName;
            if (sender) name = sender->vtable->GetTagName(sender);
            if (!name) __SVO_Assert_Handler(svoPluginManagerSource, 0x45);
            if (!strcmp(expectedName, name) && expectedEvent == event) {
                CPluginBaseState *plugin = manager->m_pluginList[i];
                plugin->vtable->AddMessage(plugin, sender, event);
            }
        }
    }
}

void PLUGIN_MANAGER_SECTION(EmptyMessageQueue) EmptyMessageQueue(CPluginManagerState *manager)
{
    for (int i = 0; i < manager->m_numPlugins; ++i)
        emptyMessageQueue(&manager->m_pluginList[i]->queue);
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/svo3/CPluginManager", operator.new___dupe11);
