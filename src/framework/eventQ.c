#include "../utils/queue.h"
#include "../utils/types.h"
#include "events.h"
#include "frameworkConfig.h"
#include "task.h"
#include "../bsp/bsp.h"

static Event eventQBuffer[EVENT_Q_SIZE];
static Queue eventQ;
Event Event_init(EventToken eventToken);

void Event_initQ()
{
    eventQ = Q_init(eventQBuffer, sizeof(eventQBuffer)/sizeof(eventQBuffer[0]), sizeof(eventQBuffer[0]));
    Event event = Event_init(SYSEVT_ENTER);
    Q_putElement(&eventQ, &event);
}
bool Event_get(Event* eventBuf)
{
    ENTER_CRITICAL_SESSION();
    bool rv = Q_getElement(&eventQ, eventBuf);
    EXIT_CRITICAL_SESSION();
    
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
Event Event_init(EventToken eventToken)
{
    Event event;
    event.token = eventToken;
    event.target = NULL;
    return event;
}
Event Event_initTarget(uint8_t eventToken, Task* target)
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
Task* Event_getTarget(const Event* event)
{
    return event->target;
}

