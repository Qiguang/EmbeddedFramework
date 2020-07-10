#ifndef TASKS_H
#define TASKS_H

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) TASKNAME,
#undef DEFINE_EVENT
#define DEFINE_EVENT(EVENT_TOKEN)
typedef enum {
#include "../app/frameworkConfig.h"
    TASK_AMOUNT,
    ALL_TASKS
} TaskName;

#endif
