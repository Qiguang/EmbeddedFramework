#include "taskEngine.h"
void subscribeEvent(Task* task, EventType eventType)
{
    // TODO: assert eventType < APP_EVT_COUNT
    task->eventSubscribeTable[eventType/8] |= (1 << eventType%8);
    
}
void unsubscribeEvent(Task* task, EventType eventType)
{
    // TODO: assert eventType < APP_EVT_COUNT
    task->eventSubscribeTable[eventType/8] &= ~(1 << eventType%8);
    
}

