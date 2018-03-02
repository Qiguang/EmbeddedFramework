#ifndef TASKENGINE_H
#define TASKENGINE_H
#include "events.h"
typedef void* (* StateProc)(Event* event);
typedef struct Task_t{
    StateProc previousState;
    StateProc state;
    uint8_t eventSubscribeTable[(APPEVT_COUNT+7)/8];
    uint16_t timeTickCount;
    uint16_t timeTickCountSec;
}Task;
void unsubscribeEvent(Task* task, EventType eventType);
void subscribeEvent(Task* task, EventType eventType);
#define DEFINE_TASK(TASKNAME, INITSTATE) Task TASKNAME = {0, INITSTATE, 0}
//#ifdef __GNUC__
//#define DEFINE_TASK(TASKNAME, INITSTATE)                        \
        //static Task TASKNAME = {0, INITSTATE, 0};        \
        //Task* pTask __attribute__((section ("taskList"))) = &TASKNAME;
//#elif _MSVC_VER
//#define DEFINE_TASK(TASKNAME, INITSTATE)                        \
        //static Task TASKNAME = {0, INITSTATE, 0};   \
        //#pragma data_seg(".taskList") \
        //__declspec(allocate("taskList")) Task* pTask = &task1;
//#endif
#endif /* ifndef TASKENGINE_H */

