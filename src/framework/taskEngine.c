#include "framework.h"

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) \
    extern void* INITSTATE(Event* event);
#include "../app/taskDefinition.h"

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) {INITSTATE, 0},
Task taskArray[] = {
#include "../app/taskDefinition.h"
};

void dispatchEvent(Event* event);
void initTasks();
bool deliverEvent(TaskName taskName, Event* event);

Task* getTask(TaskName taskName)
{
    return &taskArray[taskName];
}
void subscribeEvent(TaskName taskName, EventToken eventToken)
{
    // TODO: assert eventToken < APPEVT_COUNT
    taskArray[taskName].eventSubscribeTable[eventToken/8] |= (1 << eventToken%8);
    
}
void unsubscribeEvent(TaskName taskName, EventToken eventToken)
{
    // TODO: assert eventToken < APPEVT_COUNT
    taskArray[taskName].eventSubscribeTable[eventToken/8] &= ~(1 << eventToken%8);
    
}
bool isEvtSubscribed(TaskName taskName, const Event* event)
{
    if (taskArray[taskName].eventSubscribeTable[Event_getType(event)/8] & (1<<Event_getType(event)%8)) {
        return true;
    } else {
        return false;
    }
}


void TaskEngine_init()
{
    Bsp_init();

    Event_initQ();
    initTasks();
    Timer_init();
}
void initTasks()
{
    TaskName i;
    for (i = 0; i < TASK_AMOUNT; ++i) {
        subscribeEvent(i, SYSEVT_ENTER);
    }
}
void TaskEngine_run()
{
    Event event;
    Event_get(&event);
    dispatchEvent(&event); 
}
void dispatchEvent(Event* event)
{
    TaskName eventTarget = Event_getTarget(event);
    if (eventTarget != ALL_TASKS) {
        deliverEvent(eventTarget, event);
    } else {
        TaskName i;
        for (i = 0; i < TASK_AMOUNT; ++i) {
            deliverEvent(i, event);
        }
    }
}

TaskName currentTask = TASK_AMOUNT;
TaskName TaskEngine_getCurrentTask()
{
    return currentTask;
}
bool deliverEvent(TaskName taskName, Event* event)
{
    bool rv = true;
    if (isEvtSubscribed(taskName, event)) {
        // TODO: assert state != null;
        currentTask = taskName;
        Task* task = getTask(taskName);
        StateProc nextState = (StateProc)task->state(event);
        if (nextState != task->state) {
            // state is changing
            task->state = nextState;

            Event event;
            event = Event_init(SYSEVT_ENTER, currentTask);
            task->state(&event);
        }
    } else {
        rv = false;
    }
    return rv;
}
void TaskEngine_thread()
{
    TaskEngine_init();
    do {
        TaskEngine_run();
    } while (1);

}
