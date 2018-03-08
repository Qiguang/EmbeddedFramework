#ifndef EVENTS_H
#define EVENTS_H
#include <stdint.h>
/*! \enum  SysEvent
 *
 *  events generated from this framework
 */
typedef enum { 
    SYSEVT_INIT = 0, // system startup
    SYSEVT_ENTER, // enter the state
    SYSEVT_QUIT,  // quit the state
    SYSEVT_TIMETICK,
    SYSEVT_TIMEOUT,
    SYSEVT_COUNT
} SysEventToken;
#define EventToken uint8_t
typedef struct {
    EventToken token;
    uint32_t additionalData;
    struct Task_t* target;
} Event;

#define EVENT_DEF_BEGIN()  \
typedef enum {  \
    APPEVT_START = SYSEVT_COUNT,
#define EVENT_DEF_END()  \
    APPEVT_COUNT  \
} AppEventToken;

#define EVENT_DEF(EVENT_TOKEN)  \
EVENT_TOKEN,

#endif /* ifndef EVENTS_H */
