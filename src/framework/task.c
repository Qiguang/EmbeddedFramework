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
#undef TASK_LIST_INIT
Tasks tasks = {taskList, sizeof(taskList)/sizeof(taskList[0])};
Tasks* getTasks()
{
    return &tasks;
}
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

