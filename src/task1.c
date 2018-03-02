#include "taskEngine.h"
#include "stdio.h"
#include "events.h"
#include "eventQ.h"
#include "timer.h"
#include "Windows.h"
#include "task1.h"
void* init(Event* event);
void* proc(Event* event);

DEFINE_TASK(task1, init);

void* init(Event* event)
{
    switch (Event_getType(event)) {
        case SYS_EVT_INIT:
            printf("task1:init:event SYS_EVT_INIT\r\n");
            break;
        case SYS_EVT_QUIT:
            printf("task1:init:event SYS_EVT_QUIT\r\n");
            break;
        default:
            printf("task1:init:unhandled event %d\r\n", Event_getType(event));
    }
    return proc;
}

void* proc(Event* event)
{
    switch (Event_getType(event)) {
        case SYS_EVT_ENTER:
            printf("task1:proc:event SYS_EVT_ENTER\r\n");
            setTaskTickCount(&task1, 1000U);
            break;
        case SYS_EVT_TIMEOUT: {

            setTaskTickCount(&task1, 1000U);
            Event event = Event_init(APP_EVT_TASK1_TIMEOUT);
            Event_put(&event);

            printf("task1:proc:event SYS_EVT_TIMEOUT\r\n");
            break;
        }
        default:
            printf("task1:proc:unhandled event %d\r\n", Event_getType(event));
    }
    return proc;
}
