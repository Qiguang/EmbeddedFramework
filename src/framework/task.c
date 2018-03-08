#include "task.h"
#include "eventQ.h"

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) \
    extern void* INITSTATE(Event* event); \
    Task TASKNAME = {0, INITSTATE, 0};
#include "../app/taskDefinition.h"

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) &TASKNAME,
Task* taskList[] = {
#include "../app/taskDefinition.h"
};
Tasks tasks = {taskList, sizeof(taskList)/sizeof(taskList[0])};
Tasks* getTasks()
{
    return &tasks;
}
void subscribeEvent(Task* task, EventToken eventToken)
{
    // TODO: assert eventToken < APPEVT_COUNT
    task->eventSubscribeTable[eventToken/8] |= (1 << eventToken%8);
    
}
void unsubscribeEvent(Task* task, EventToken eventToken)
{
    // TODO: assert eventToken < APPEVT_COUNT
    task->eventSubscribeTable[eventToken/8] &= ~(1 << eventToken%8);
    
}
bool isEvtSubscribed(const Task* task, const Event* event)
{
    if (task->eventSubscribeTable[Event_getType(event)/8] & (1<<Event_getType(event)%8)) {
        return true;
    } else {
        return false;
    }
}

