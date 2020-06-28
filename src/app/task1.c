#include "../framework/framework.h"
#include "stdio.h"
#include "Windows.h"
#include "task1.h"
void* Task1_init(Event* event);
void* proc(Event* event);

void* Task1_init(Event* event)
{
    switch (Event_getType(event)) {
        case SYSEVT_ENTER:
            printf("task1:init:event SYSEVT_ENTER\r\n");
            break;
        case SYSEVT_QUIT:
            printf("task1:init:event SYSEVT_QUIT\r\n");
            break;
        default:
            printf("task1:init:unhandled event %d\r\n", Event_getType(event));
    }
    return proc;
}

static TIMER timer;
void* proc(Event* event)
{
    switch (Event_getType(event)) {
        case SYSEVT_ENTER:
            printf("task1:proc:event SYSEVT_ENTER\r\n");
            setTimer(&timer, 100U);
            /* clearTimer(&timer); */
            break;
        case SYSEVT_TIMEOUT: {
            setTimer(&timer, 100U);
            Event event = Event_init(TASK1_TIMEOUT);
            Event_put(&event);

            printf("task1:proc:event SYSEVT_TIMEOUT\r\n");
            break;
        }
        default:
            printf("task1:proc:unhandled event %d\r\n", Event_getType(event));
    }
    return proc;
}
