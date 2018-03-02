#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include "types.h"
typedef struct {
    uint8_t* buffer;
    uint8_t head;
    uint8_t tail;
    uint8_t elementSize;
    uint8_t elementCount;
    uint8_t qSize;
}Queue;
Queue initQ(void* bufferPointer, uint8_t queueSize, uint8_t elementSize);
bool putElement(Queue* q, const void* element);
bool getElement(Queue* q, void* elementBuf);
#endif /* ifndef QUEUE_H */
