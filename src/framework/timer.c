#include "framework.h"
static void timeoutCallback(uint32_t elapsedTime);
TIMER* head = NULL;
TIMER* current = NULL;
void Timer_init()
{
    setTimeoutCallback(timeoutCallback);
}
void insert2TimerList(TIMER* timer)
{
    ENTER_CRITICAL_SESSION();
    TIMER** cursor = &head;
    while(*cursor && (*cursor)->time < timer->time) {
        cursor = &((*cursor)->next);
    }
    timer->next = *cursor;
    *cursor = timer;
    EXIT_CRITICAL_SESSION();
}
void refreshTimerList(uint32_t elapsedTime)
{
    ENTER_CRITICAL_SESSION();
    TIMER** cursor = &head;
    while(*cursor) {
        (*cursor)->time -= elapsedTime;
        if ((*cursor)->time == 0) {
            Event event = Event_init(SYSEVT_TIMEOUT, (*cursor)->theTask);
            event.additionalData = (void*)*cursor;
            Event_put(&event);

            *cursor = (*cursor)->next;
        }
        if (*cursor) {
            cursor = &((*cursor)->next);
        } else {
            break;
        }
    }
    EXIT_CRITICAL_SESSION();
}
void startCountDown()
{
    ENTER_CRITICAL_SESSION();
    if (head) {
        Bsp_startCountDown(head->time);
    }
    EXIT_CRITICAL_SESSION();
}
void setTimer(TIMER* timer, uint32_t time)
{
    timer->time = time;
    timer->theTask = TaskEngine_getCurrentTask();
    subscribeEvent(timer->theTask, SYSEVT_TIMEOUT);
    uint32_t elapsedTime = Bsp_stopCountDown();
    refreshTimerList(elapsedTime);
    insert2TimerList(timer);
    startCountDown();
}
void timeoutCallback(uint32_t elapsedTime)
{
    refreshTimerList(elapsedTime);
    startCountDown();
}
