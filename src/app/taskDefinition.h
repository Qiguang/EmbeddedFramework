#ifndef TASK_DEFINITION
#define TASK_DEFINITION
#include "../framework/task.h"
extern Task task1;
extern Task task2;
Task* taskList[] = {&task1, &task2};
Tasks tasks = {taskList, sizeof(taskList)/sizeof(taskList[0])};
#endif /* ifndef TASK_DEFINITION */
