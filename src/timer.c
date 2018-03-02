#include "events.h"
#include "eventQ.h"
#include "timer.h"
#include "EventFramework.h"
#include "taskEngine.h"
#include "./bsp/bsp.h"
void tickCountDown(Task* task);
static void timeTickCallback();
void initTimer()
{

    setTimeTickCallback(timeTickCallback);
    
}
void setTaskTickCount(Task* task, uint16_t tickCount)
{
    subscribeEvent(task, EVT_TIMEOUT);
    ENTER_CRITICAL_SESSION();
    task->timeTickCount = tickCount;
    EXIT_CRITICAL_SESSION();
}
void timeTickCallback()
{
    Event event = initEvent(EVT_TIME_TICK);
    putEvent(&event);

    Tasks* tasks = getTasks();
    int i;
    for (i = 0; i < tasks->count; ++i) {
        Task* task = tasks->tasks[i];
        tickCountDown(task);
    }
    
}
void tickCountDown(Task* task)
{
    ENTER_CRITICAL_SESSION();
    bool tickOut = false;
    if (task->timeTickCount) {
        task->timeTickCount--;
        if (!task->timeTickCount) {
            tickOut = true;
        }
    }
    EXIT_CRITICAL_SESSION();
    if (tickOut) {
        Event event = initEventTarget(EVT_TIMEOUT, task);
        putEvent(&event);
    }
}
