#ifndef EVENTQ_H
#define EVENTQ_H
#include "tasks.h"
#include "events.h"
#include <stdint.h>
#include <stdbool.h>

void EventQ_init();
Event createEvent(EventToken eventToken, TaskName target, void* data);
bool dequeueEvent(Event* eventBuf);
bool enqueueEvent(const Event* event);
uint8_t eventType(const Event* event);
TaskName eventTarget(const Event* event);
void* eventData(const Event* event);
#endif /* ifndef EVENTQ_H */
