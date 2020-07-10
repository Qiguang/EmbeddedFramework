#ifndef TASK_ENGINE_H
#define TASK_ENGINE_H

typedef void* (* StateProc)(Event* event);
typedef struct Task_t{
    StateProc state;
    uint8_t eventSubscribeTable[(APPEVT_COUNT+7)/8];
}Task;

void unsubscribeEvent(TaskName taskName, EventToken eventToken);
void subscribeEvent(TaskName taskName, EventToken eventToken);
void taskEngineRun();
TaskName getCurrentTask();

#endif /* ifndef TASK_ENGINE_H */
