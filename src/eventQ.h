#ifndef EVENTQ_H
#define EVENTQ_H
#include "types.h"
#include "taskEngine.h"
void initEventQ();
Event initEvent(ApplicationEvents eventType);
Event initEventTarget(uint8_t eventType, Task* target);
bool getEvent(Event* eventBuf);
bool putEvent(const Event* event);
uint8_t getEventType(const Event* event);
Task* getEventTarget(const Event* event);
#endif /* ifndef EVENTQ_H */
