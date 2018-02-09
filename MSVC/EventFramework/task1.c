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
    switch (getEventType(event)) {
        case EVT_INIT:
            printf("task1:init:event EVT_INIT\r\n");
            break;
        case EVT_QUIT:
            printf("task1:init:event EVT_QUIT\r\n");
            break;
        default:
            printf("task1:init:unhandled event %d\r\n", getEventType(event));
    }
    return proc;
}

void* proc(Event* event)
{
    switch (getEventType(event)) {
        case EVT_ENTER:
            printf("task1:proc:event EVT_ENTER\r\n");
            setTaskTickCount(&task1, 1000U);
            break;
        case EVT_TIMEOUT: {

            setTaskTickCount(&task1, 1000U);
            Event event = initEvent(APP_EVT_TASK1_TIMEOUT);
            putEvent(&event);

            printf("task1:proc:event EVT_TIMEOUT\r\n");
            break;
        }
        default:
            printf("task1:proc:unhandled event %d\r\n", getEventType(event));
    }
    return proc;
}
