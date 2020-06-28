#include "framework.h"
void tickCountDown(Task* task);
static void timeTickCallback();
void Timer_init()
{

    setTimeTickCallback(timeTickCallback);
    
}
void setTaskTickCount(Task* task, uint16_t tickCount)
{
    subscribeEvent(task, SYSEVT_TIMEOUT);
    ENTER_CRITICAL_SESSION();
    task->timeTickCount = tickCount;
    EXIT_CRITICAL_SESSION();
}
void timeTickCallback()
{
    Tasks* tasks = getTasks();
    int i;
    for (i = 0; i < tasks->count; ++i) {
        Task* task = tasks->taskList[i];
        tickCountDown(task);
    }
}
void tickCountDown(Task* task)
{
    bool tickOut = false;
    ENTER_CRITICAL_SESSION();
    if (task->timeTickCount) {
        task->timeTickCount--;
        if (!task->timeTickCount) {
            tickOut = true;
        }
    }
    EXIT_CRITICAL_SESSION();
    if (tickOut) {
        Event event = Event_initTarget(SYSEVT_TIMEOUT, task);
        Event_put(&event);
    }
}
