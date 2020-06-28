#ifndef TASKS_H
#define TASKS_H

#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) TASKNAME,
typedef enum {
#include "../app/taskDefinition.h"
    TASK_AMOUNT,
    ALL_TASKS
} TaskName;
#endif
