#include "../framework/framework.h"
#include "stdio.h"
#include "Windows.h"
#include "task1.h"
void* init(Event* event);
void* proc(Event* event);

DEFINE_TASK(task1, init);

void* init(Event* event)
{
    switch (Event_getType(event)) {
        case SYSEVT_INIT:
            printf("task1:init:event SYSEVT_INIT\r\n");
            break;
        case SYSEVT_QUIT:
            printf("task1:init:event SYSEVT_QUIT\r\n");
            break;
        default:
            printf("task1:init:unhandled event %d\r\n", Event_getType(event));
    }
    return proc;
}

void* proc(Event* event)
{
    switch (Event_getType(event)) {
        case SYSEVT_ENTER:
            printf("task1:proc:event SYSEVT_ENTER\r\n");
            setTaskTickCount(&task1, 1000U);
            break;
        case SYSEVT_TIMEOUT: {

            setTaskTickCount(&task1, 1000U);
            Event event = Event_init(APPEVT_TASK1_TIMEOUT);
            Event_put(&event);

            printf("task1:proc:event SYSEVT_TIMEOUT\r\n");
            break;
        }
        default:
            printf("task1:proc:unhandled event %d\r\n", Event_getType(event));
    }
    return proc;
}
