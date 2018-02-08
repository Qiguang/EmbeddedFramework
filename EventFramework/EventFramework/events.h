#ifndef EVENTS_H
#define EVENTS_H
#include <stdint.h>
/*! \enum  FrameworkEvents
 *
 *  events generated from this framework
 */
typedef enum { 
    EVT_INIT = 0,
    EVT_ENTER,
    EVT_QUIT,
    EVT_TIME_TICK,
    EVT_TIMEOUT,
    EVT_COUNT
} FrameworkEvents;
/*! \enum ApplicationEvents
 *
 *  Detailed description
 */
typedef enum {
    APP_EVT_START = EVT_COUNT,
    APP_EVT_TASK1_TIMEOUT,
    APP_EVT_COUNT
} ApplicationEvents;
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
