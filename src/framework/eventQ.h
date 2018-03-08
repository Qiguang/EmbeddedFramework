#ifndef EVENTQ_H
#define EVENTQ_H
#include "../utils/types.h"
#include "task.h"
void Event_initQ();
Event Event_init(EventToken eventToken);
Event Event_initTarget(uint8_t eventToken, Task* target);
bool Event_get(Event* eventBuf);
bool Event_put(const Event* event);
uint8_t Event_getType(const Event* event);
Task* Event_getTarget(const Event* event);
#endif /* ifndef EVENTQ_H */
