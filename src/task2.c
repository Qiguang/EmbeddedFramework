#include "taskEngine.h"
#include "stdio.h"
#include "events.h"
#include "eventQ.h"
#include "timer.h"
#include "task2.h"
static void* init(Event* event);
static void* proc(Event* event);
DEFINE_TASK(task2, init);

void* init(Event* event)
{
    switch (getEventType(event)) {
        case EVT_INIT:
            subscribeEvent(&task2, APP_EVT_TASK1_TIMEOUT);
            return proc;
            break;
        default:
            printf("task2:init:unhandled event %d\r\n", getEventType(event));
            
    }
    return proc;
    
}
void* proc(Event* event)
{

    switch (getEventType(event)) {
        case EVT_ENTER:
            printf("task2:proc:event EVT_ENTER\r\n");
            return proc;
            break;
        case APP_EVT_TASK1_TIMEOUT:
            printf("task2:proc:event APP_EVT_TASK1_TIMEOUT\r\n");
            break;
        default:
            printf("task2:init:unhandled event %d\r\n", getEventType(event));
            
    }
    return proc;
    
}
