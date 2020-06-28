#ifndef EVENTFRAMEWORK_H
#define EVENTFRAMEWORK_H
#include "events.h"
#include "eventQ.h"
#include "timer.h"
#include "task.h"
#include "../bsp/bsp.h"
#include <stdint.h>
#include "../utils/queue.h"
#include "log.h"
#include "frameworkConfig.h"
#include "../utils/types.h"
#include "taskEngine.h"
#include "task.h"
#undef DEFINE_TASK
#define DEFINE_TASK(TASKNAME, INITSTATE) extern Task TASKNAME;
#include "../app/taskDefinition.h"
#include "../app/eventDefinition.h"
#endif /* ifndef EVENTFRAMEWORK_H */
