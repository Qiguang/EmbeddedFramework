#ifndef EVENTQ_H
#define EVENTQ_H
#include "tasks.h"
#include "events.h"
#include <stdint.h>
#include <stdbool.h>

void Event_initQ();
Event Event_init(EventToken eventToken, TaskName target);
bool Event_get(Event* eventBuf);
bool Event_put(const Event* event);
uint8_t Event_getType(const Event* event);
TaskName Event_getTarget(const Event* event);
#endif /* ifndef EVENTQ_H */
