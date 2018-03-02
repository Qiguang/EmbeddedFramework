#include "./utils/queue.h"
#include "events.h"
#include "frameworkConfig.h"
#include "taskEngine.h"
#include "./bsp/bsp.h"

Event eventQBuffer[EVENT_Q_SIZE];
Queue eventQ;
Event initEvent(ApplicationEvents eventType);

void initEventQ()
{
    eventQ = initQ(eventQBuffer, sizeof(eventQBuffer)/sizeof(eventQBuffer[0]), sizeof(eventQBuffer[0]));
    Event event = initEvent(EVT_INIT);
    event.generalEvt.token.type = EVT_INIT;
    putElement(&eventQ, &event);
}
bool getEvent(Event* eventBuf)
{
    ENTER_CRITICAL_SESSION();
    bool rv = getElement(&eventQ, eventBuf);
    EXIT_CRITICAL_SESSION();
    
    return rv;
}
bool putEvent(const Event* event) 
{
    ENTER_CRITICAL_SESSION();
    bool rv = putElement(&eventQ, event);
    EXIT_CRITICAL_SESSION();
    
    return rv;
}
Event initEvent(ApplicationEvents eventType)
{
    Event event;
    event.generalEvt.token.type = eventType;
    event.generalEvt.token.target = null;
    return event;
}
Event initEventTarget(uint8_t eventType, Task* target)
{
    Event event;
    event.generalEvt.token.type = eventType;
    event.generalEvt.token.target = target;
    return event;
    
}
uint8_t getEventType(const Event* event)
{
    return event->generalEvt.token.type;
}
Task* getEventTarget(const Event* event)
{
    return event->generalEvt.token.target;
}

