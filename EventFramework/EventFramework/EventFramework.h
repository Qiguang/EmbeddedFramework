#ifndef EVENTFRAMEWORK_H
#define EVENTFRAMEWORK_H
#include "taskEngine.h"
typedef struct {
    Task** tasks;
    uint8_t count;
} Tasks;

void run();
void initFramework();
Tasks* getTasks();
#endif /* ifndef EVENTFRAMEWORK_H */
