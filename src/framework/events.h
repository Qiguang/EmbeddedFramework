#ifndef EVENTS_H
#define EVENTS_H
#include <stdint.h>
/*! \enum  SysEvent
 *
 *  events generated from this framework
 */
#undef DEFINE_EVENT
#define DEFINE_EVENT(EVENT_TOKEN)  EVENT_TOKEN,
#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE)

typedef enum { 
    SYSEVT_ENTER = 0, // enter the state
    SYSEVT_TIMEOUT,
    SYSEVT_COUNT,
#include "../app/frameworkConfig.h"
    APPEVT_END,
    APPEVT_COUNT = APPEVT_END - SYSEVT_COUNT - 1
} EventToken;
typedef struct {
    EventToken token;
    enum TaskName target;
    void* data;
} Event;

#endif /* ifndef EVENTS_H */
