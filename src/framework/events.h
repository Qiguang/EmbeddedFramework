#ifndef EVENTS_H
#define EVENTS_H
#include <stdint.h>
/*! \enum  SysEvent
 *
 *  events generated from this framework
 */
#undef EVENT_DEF
#define EVENT_DEF(EVENT_TOKEN)  EVENT_TOKEN,

typedef enum { 
    SYSEVT_ENTER = 0, // enter the state
    SYSEVT_TIMEOUT,
    SYSEVT_COUNT,
#include "../app/eventDefinition.h"
    APPEVT_END,
    APPEVT_COUNT = APPEVT_END - SYSEVT_COUNT - 1
} EventToken;
typedef struct {
    EventToken token;
    void* additionalData;
    enum TaskName target;
} Event;

#endif /* ifndef EVENTS_H */
