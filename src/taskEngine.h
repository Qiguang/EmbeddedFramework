#ifndef TASK_ENGINE_H
#define TASK_ENGINE_H
#include "task.h"
typedef struct {
    Task** tasks;
    uint8_t count;
} Tasks;

void run();
void Framework_init();
Tasks* getTasks();
#endif /* ifndef TASK_ENGINE_H */
