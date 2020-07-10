#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "events.h"
#include "tasks.h"
#include "../bsp/bsp.h"
#include "../utils/log.h"
#include <string.h>

typedef struct {
    Event qBuf[EVENT_Q_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t elementCount;
    uint8_t qSize;
}Queue;

static Queue eventQ;

static bool enqueue(const void* element)
{
    bool rv = true;
    bool Q_FULL = (eventQ.elementCount == eventQ.qSize);
    if (Q_FULL) {
       log_err("event queue is full, enqueue failed");
       rv = false;
    } else {
        memcpy(&(eventQ.qBuf[eventQ.head]), element, sizeof(eventQ.qBuf[0]));
        eventQ.elementCount++;
        eventQ.head = (eventQ.head+1)%eventQ.qSize;
    }
    return rv;
}
static bool dequeue(void* elementBuf)
{
    bool rv = true;
    bool Q_EMPTY = (eventQ.elementCount == 0);
    if (Q_EMPTY) {
        rv = false;
    } else {
        memcpy(elementBuf, &(eventQ.qBuf[eventQ.tail]), sizeof(eventQ.qBuf[0]));
        eventQ.elementCount--;
        eventQ.tail = (eventQ.tail+1)%eventQ.qSize;
    }
    return rv;
}

void EventQ_init()
{
    eventQ.head = 0;
    eventQ.tail = 0;
    eventQ.elementCount = 0;
    eventQ.qSize = EVENT_Q_SIZE;
}
bool dequeueEvent(Event* eventBuf)
{
    bool rv = false;
    while (!rv) {
        ENTER_CRITICAL_SESSION();
        rv = dequeue(eventBuf);
        EXIT_CRITICAL_SESSION();
        if (!rv) {
            Bsp_onIdle();
        }
    }
    
    return rv;
}
bool enqueueEvent(const Event* event) 
{
    ENTER_CRITICAL_SESSION();
    bool rv = enqueue(event);
    EXIT_CRITICAL_SESSION();
    Bsp_exitIdle();  // now there is at least one event in the Q, so we need exit IDLE mode
    
    return rv;
}
Event createEvent(EventToken eventToken, TaskName target, void* data)
{
    Event event;
    event.token = eventToken;
    event.target = target;
    event.data = data;
    return event;
    
}
uint8_t eventType(const Event* event)
{
    return event->token;
}
TaskName eventTarget(const Event* event)
{
    return event->target;
}
void* eventData(const Event* event)
{
    return event->data;
}

