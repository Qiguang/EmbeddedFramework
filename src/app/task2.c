#include "../framework/framework.h"
#include "stdio.h"
#include "task2.h"
static void* init(Event* event);
static void* proc(Event* event);
DEFINE_TASK(task2, init);

void* init(Event* event)
{
    switch (Event_getType(event)) {
        case SYSEVT_INIT:
            subscribeEvent(&task2, APPEVT_TASK1_TIMEOUT);
            return proc;
            break;
        default:
            printf("task2:init:unhandled event %d\r\n", Event_getType(event));
            
    }
    return proc;
    
}
void* proc(Event* event)
{

    switch (Event_getType(event)) {
        case SYSEVT_ENTER:
            printf("task2:proc:event SYSEVT_ENTER\r\n");
            return proc;
            break;
        case APPEVT_TASK1_TIMEOUT:
            printf("task2:proc:event APPEVT_TASK1_TIMEOUT\r\n");
            break;
        default:
            printf("task2:init:unhandled event %d\r\n", Event_getType(event));
            
    }
    return proc;
    
}
