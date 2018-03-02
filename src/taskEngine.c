#include <stdint.h>
#include "./utils/queue.h"
#include "./bsp/bsp.h"
#include "log.h"
#include "events.h"
#include "frameworkConfig.h"
#include "task.h"
#include "./utils/types.h"
#include "eventQ.h"
#include "timer.h"
#include "task1.h"
#include "task2.h"
#include "framework.h"
void dispatchEvent(Event* event);
void initTasks();
bool deliverEvent(Task* task, Event* event);

Task* taskList[] = {&task1, &task2};
Tasks tasks = {taskList, sizeof(taskList)/sizeof(taskList[0])};
Tasks* getTasks()
{
    return &tasks;
}
void Framework_init()
{
    Event_initQ();
    initTasks();
    Timer_init();
    
    Bsp_init();
}
void initTasks()
{
    int i;
    for (i = 0; i < sizeof(taskList)/sizeof(taskList[0]); ++i) {
        subscribeEvent(taskList[i], SYSEVT_INIT);
        subscribeEvent(taskList[i], SYSEVT_ENTER);
        subscribeEvent(taskList[i], SYSEVT_QUIT);
    }
}
void run()
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
        for (i = 0; i < sizeof(taskList)/sizeof(taskList[0]); ++i) {
            Task* task = taskList[i];
            deliverEvent(task, event);
        }
    }
}
bool deliverEvent(Task* task, Event* event)
{
    bool rv = true;
    if (isEvtSubscribed(task, event)) {
        // TODO: assert state != null;
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
