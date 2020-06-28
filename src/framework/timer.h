#ifndef TIMER_H
#define TIMER_H
#include "task.h"
#include "types.h"
typedef struct TIMER{
    uint32_t time;
    Task* theTask;
    struct TIMER* next;
} TIMER;
void Timer_init();
void setTimer(TIMER* timer, uint32_t time);
#endif /* ifndef TIMER_H */

