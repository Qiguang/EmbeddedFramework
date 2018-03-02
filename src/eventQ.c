#include "./utils/queue.h"
#include "./utils/types.h"
#include "events.h"
#include "frameworkConfig.h"
#include "taskEngine.h"
#include "./bsp/bsp.h"

static Event eventQBuffer[EVENT_Q_SIZE];
static Queue eventQ;
Event Event_init(AppEvent eventType);

void Event_initQ()
{
    eventQ = Q_init(eventQBuffer, sizeof(eventQBuffer)/sizeof(eventQBuffer[0]), sizeof(eventQBuffer[0]));
    Event event = Event_init(SYSEVT_INIT);
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
    
    return rv;
}
Event Event_init(AppEvent eventType)
{
    Event event;
    event.generalEvt.token.type = eventType;
    event.generalEvt.token.target = NULL;
    return event;
}
Event Event_initTarget(uint8_t eventType, Task* target)
{
    Event event;
    event.generalEvt.token.type = eventType;
    event.generalEvt.token.target = target;
    return event;
    
}
uint8_t Event_getType(const Event* event)
{
    return event->generalEvt.token.type;
}
Task* Event_getTarget(const Event* event)
{
    return event->generalEvt.token.target;
}

