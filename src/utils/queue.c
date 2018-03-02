#include "queue.h"
#include "../bsp/bsp.h"
#include "../log.h"
#include <string.h>
Queue Q_init(void* bufferPointer, uint8_t queueSize, uint8_t elementSize)
{
    Queue q;
    q.buffer = bufferPointer;
    q.head = 0;
    q.tail = 0;
    q.elementSize = elementSize;
    q.elementCount = 0;
    q.qSize = queueSize;
    return q;
}
bool Q_putElement(Queue* q, const void* element)
{
    bool rv = true;
    bool Q_FULL = (q->elementCount == q->qSize);
    if (Q_FULL) {
       log_err("queue is full");
       rv = false;
    } else {
        uint8_t insertPosition = (q->head*q->elementSize);
        memcpy(&(q->buffer[insertPosition]), element, q->elementSize);
        q->elementCount++;
        q->head = (q->head+1)%q->qSize;
    }
    return rv;
}
bool Q_getElement(Queue* q, void* elementBuf)
{
    bool rv = true;
    bool Q_EMPTY = (q->elementCount == 0);
    if (Q_EMPTY) {
        rv = false;
    } else {
        uint8_t elementPosition = (q->tail*q->elementSize);
        memcpy(elementBuf, &(q->buffer[elementPosition]), q->elementSize);
        q->elementCount--;
        q->tail = (q->tail+1)%q->qSize;
    }
    return rv;
}

