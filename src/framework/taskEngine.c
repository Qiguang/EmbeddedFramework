#include "framework.h"
void dispatchEvent(Event* event);
void initTasks();
bool deliverEvent(Task* task, Event* event);

void TaskEngine_init()
{
    Bsp_init();

    Event_initQ();
    initTasks();
    Timer_init();
}
void initTasks()
{
    int i;
    Tasks* tasks = getTasks();
    for (i = 0; i < tasks->count; ++i) {
        Task* task = tasks->taskList[i];
        subscribeEvent(task, SYSEVT_ENTER);
        subscribeEvent(task, SYSEVT_QUIT);
    }
}
void TaskEngine_run()
{
   Event event;
   if (Event_get(&event)) {
      dispatchEvent(&event); 
   } else {
      Bsp_onIdle();
   }
}
void dispatchEvent(Event* event)
{
    int i;
    Task* eventTarget = Event_getTarget(event);
    if (eventTarget != NULL) {
        deliverEvent(eventTarget, event);
    } else {
        Tasks* tasks = getTasks();
        int i;
        for (i = 0; i < tasks->count; ++i) {
            Task* task = tasks->taskList[i];
            deliverEvent(task, event);
        }
    }
}

Task* currentTask = NULL;
Task* TaskEngine_getCurrentTask()
{
    return currentTask;
}
bool deliverEvent(Task* task, Event* event)
{
    bool rv = true;
    if (isEvtSubscribed(task, event)) {
        // TODO: assert state != null;
        currentTask = task;
        StateProc nextState = (StateProc)task->state(event);
        if (nextState != task->state) {
            // state is changing
            task->previousState = task->state;
            task->state = nextState;

            Event event;
            event = Event_init(SYSEVT_QUIT);
            task->previousState(&event);
            event = Event_init(SYSEVT_ENTER);
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
