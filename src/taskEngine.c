#include "taskEngine.h"
#include "eventQ.h"
void subscribeEvent(Task* task, EventType eventType)
{
    // TODO: assert eventType < APPEVT_COUNT
    task->eventSubscribeTable[eventType/8] |= (1 << eventType%8);
    
}
void unsubscribeEvent(Task* task, EventType eventType)
{
    // TODO: assert eventType < APPEVT_COUNT
    task->eventSubscribeTable[eventType/8] &= ~(1 << eventType%8);
    
}
bool isEvtSubscribed(const Task* task, const Event* event)
{
    if (task->eventSubscribeTable[Event_getType(event)/8] & (1<<Event_getType(event)%8)) {
        return true;
    } else {
        return false;
    }
}

