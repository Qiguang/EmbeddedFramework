#ifndef TASKENGINE_H
#define TASKENGINE_H
#include "events.h"
#include "../utils/types.h"
typedef void* (* StateProc)(Event* event);
typedef struct Task_t{
    StateProc previousState;
    StateProc state;
    uint8_t eventSubscribeTable[(APPEVT_COUNT+7)/8];
    uint16_t timeTickCount;
    uint16_t timeTickCountSec;
}Task;
typedef struct {
    Task** taskList;
    uint8_t count;
} Tasks;
Tasks* getTasks();
void unsubscribeEvent(Task* task, EventType eventType);
void subscribeEvent(Task* task, EventType eventType);
bool isEvtSubscribed(const Task* task, const Event* event);
#define DEFINE_TASK(TASKNAME, INITSTATE) Task TASKNAME = {0, INITSTATE, 0}
#endif /* ifndef TASKENGINE_H */

