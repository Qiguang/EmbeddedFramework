#ifndef EVENTS_H
#define EVENTS_H
#include <stdint.h>
/*! \enum  SysEvent
 *
 *  events generated from this framework
 */
typedef enum { 
    SYS_EVT_INIT = 0,
    SYS_EVT_ENTER,
    SYS_EVT_QUIT,
    SYS_EVT_TIMETICK,
    SYS_EVT_TIMEOUT,
    SYS_EVT_COUNT
} SysEvent;
/*! \enum AppEvent
 *
 *  Detailed description
 */
typedef enum {
    APP_EVT_START = SYS_EVT_COUNT,
    APP_EVT_TASK1_TIMEOUT,
    APP_EVT_COUNT
} AppEvent;
#define EventType uint8_t
typedef struct {
    EventType type;
    struct Task_t* target;
} EventToken;
typedef struct {
    EventToken token;
    /* data */
}GeneralEvent;
/*! \enum Event
 *
 *  Event
 */
typedef union{
    GeneralEvent generalEvt;
}Event;

#endif /* ifndef EVENTS_H */
