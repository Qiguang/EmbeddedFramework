#ifndef EVENTS_H
#define EVENTS_H
#include <stdint.h>
/*! \enum  SysEvent
 *
 *  events generated from this framework
 */
typedef enum { 
    SYSEVT_INIT = 0,
    SYSEVT_ENTER, // enter the state
    SYSEVT_QUIT,  // quit the state
    SYSEVT_TIMETICK,
    SYSEVT_TIMEOUT,
    SYSEVT_COUNT
} SysEvent;
/*! \enum AppEvent
 *
 *  Detailed description
 */
typedef enum {
    APPEVT_START = SYSEVT_COUNT,
    APPEVT_TASK1_TIMEOUT,
    APPEVT_COUNT
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
