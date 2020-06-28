#ifndef TIMER_H
#define TIMER_H
#include "tasks.h"
#include <stdint.h>
typedef struct TIMER{
    uint32_t time;
    TaskName theTask;
    struct TIMER* next;
} TIMER;
void Timer_init();
void setTimer(TIMER* timer, uint32_t time);
#endif /* ifndef TIMER_H */

