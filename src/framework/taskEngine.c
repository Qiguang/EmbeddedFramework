#include "framework.h"

#undef DEFINE_EVENT
#define DEFINE_EVENT(EVENT_TOKEN)

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) \
    extern void* INITSTATE(Event* event);
#include "../app/frameworkConfig.h"

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) {INITSTATE, 0},
Task taskArray[] = {
#include "../app/frameworkConfig.h"
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
    if (taskArray[taskName].eventSubscribeTable[eventType(event)/8] & (1<<eventType(event)%8)) {
        return true;
    } else {
        return false;
    }
}


void init()
{
    Bsp_init();

    EventQ_init();
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
void run()
{
    Event event;
    dequeueEvent(&event);
    dispatchEvent(&event); 
}
void dispatchEvent(Event* event)
{
    TaskName target = eventTarget(event);
    if (target != ALL_TASKS) {
        deliverEvent(target, event);
    } else {
        TaskName i;
        for (i = 0; i < TASK_AMOUNT; ++i) {
            deliverEvent(i, event);
        }
    }
}

TaskName currentTask = TASK_AMOUNT;
TaskName getCurrentTask()
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
            event = createEvent(SYSEVT_ENTER, currentTask, NULL);
            task->state(&event);
        }
    } else {
        rv = false;
    }
    return rv;
}
void taskEngineRun()
{
    init();
    // on startup, generate the first event for all tasks
    Event event = createEvent(SYSEVT_ENTER, ALL_TASKS, NULL);
    enqueueEvent(&event);

    do {
        run();
    } while (1);
}
