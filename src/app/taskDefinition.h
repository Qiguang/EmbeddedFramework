#include "../framework/task.h"
#ifndef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) extern Task TASKNAME;
#endif
DEFINE_TASK(task1, Task1_init)
DEFINE_TASK(task2, Task2_init)
