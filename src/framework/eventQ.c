#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "../utils/queue.h"
#include "events.h"
#include "frameworkConfig.h"
#include "tasks.h"
#include "../bsp/bsp.h"

static Event eventQBuffer[EVENT_Q_SIZE];
static Queue eventQ;
Event Event_init(EventToken eventToken, TaskName target);

void Event_initQ()
{
    eventQ = Q_init(eventQBuffer, sizeof(eventQBuffer)/sizeof(eventQBuffer[0]), sizeof(eventQBuffer[0]));
    Event event = Event_init(SYSEVT_ENTER, ALL_TASKS);
    Q_putElement(&eventQ, &event);
}
bool Event_get(Event* eventBuf)
{
    bool rv = false;
    while (!rv) {
        ENTER_CRITICAL_SESSION();
        rv = Q_getElement(&eventQ, eventBuf);
        EXIT_CRITICAL_SESSION();
        if (!rv) {
            Bsp_onIdle();
        }
    }
    
    return rv;
}
bool Event_put(const Event* event) 
{
    ENTER_CRITICAL_SESSION();
    bool rv = Q_putElement(&eventQ, event);
    EXIT_CRITICAL_SESSION();
    Bsp_exitIdle();  // now there is at least one event in the Q, so we need exit IDLE mode
    
    return rv;
}
Event Event_init(EventToken eventToken, TaskName target)
{
    Event event;
    event.token = eventToken;
    event.target = target;
    return event;
    
}
uint8_t Event_getType(const Event* event)
{
    return event->token;
}
TaskName Event_getTarget(const Event* event)
{
    return event->target;
}

