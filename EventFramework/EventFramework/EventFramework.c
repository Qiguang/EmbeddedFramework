#include <stdint.h>
#include "Queue.h"
#include "Win32/bsp.h"
#include "log.h"
#include "events.h"
#include "frameworkConfig.h"
#include "taskEngine.h"
#include "types.h"
#include "eventQ.h"
#include "timer.h"
#include "../task1.h"
#include "../task2.h"
#include "EventFramework.h"
void dispatchEvent(Event* event);
void initTasks();
bool deliverEvent(Task* task, Event* event);

Task* taskList[] = {&task1, &task2};
Tasks tasks = {taskList, sizeof(taskList)/sizeof(taskList[0])};
Tasks* getTasks()
{
    return &tasks;
}
void initFramework()
{
    initEventQ();
    initTasks();
    initTimer();
    
    initBsp();
}
void initTasks()
{
    int i;
    for (i = 0; i < sizeof(taskList)/sizeof(taskList[0]); ++i) {
        subscribeEvent(taskList[i], EVT_INIT);
        subscribeEvent(taskList[i], EVT_ENTER);
        subscribeEvent(taskList[i], EVT_QUIT);
    }
}
void run()
{
   Event event;
   if (getEvent(&event)) {
      dispatchEvent(&event); 
   } else {
      onIdle();
   }
}
void dispatchEvent(Event* event)
{
    int i;
    Task* taskTarget = getEventTarget(event);
    if (taskTarget != null) {
        deliverEvent(taskTarget, event);
    } else {
        for (i = 0; i < sizeof(taskList)/sizeof(taskList[0]); ++i) {
            Task* task = taskList[i];
            deliverEvent(task, event);
        }
    }
}
bool deliverEvent(Task* task, Event* event)
{
    bool rv = true;
    if (task->eventSubscribeTable[getEventType(event)/8] & (1<<getEventType(event)%8)) {
        // TODO: assert state != null;
        StateProc nextState = (StateProc)task->state(event);
        if (nextState != task->state) {
            // state is changing
            task->previousState = task->state;
            task->state = nextState;

            Event event;
            event = initEvent(EVT_QUIT);
            task->previousState(&event);
            event = initEvent(EVT_ENTER);
            task->state(&event);
        }
    } else {
        rv = false;
    }
    return rv;
}
