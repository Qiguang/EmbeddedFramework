#include "../framework/task.h"
#ifndef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) extern Task TASKNAME;
#endif
// USAGE HINTS
// DEFINE_TASK(task_name, the_entry_function)
// use DEFINE_TASK to define a task, it require a task name, after defining, this name can be used in other functions which require a task name.
// the entry function is the function you want the framework calling when startup. It can be a task process or a init function or any StateProc function you defined
// e.g. 
// you defined task as
// DEFINE_TASK(task1, Task1_init)
// DEFINE_TASK(task2, Task2_init)
// and then you can create new *.c files to define the function Task1_init and Task2_init
// add #include "../framework/framework.h"
// to the files you created for using the framework APIs.
// that's all you should do. Then,
// enjoy the framework.
DEFINE_TASK(task1, Task1_init)
DEFINE_TASK(task2, Task2_init)
