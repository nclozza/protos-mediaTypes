#ifndef QUEUE_H
#define QUEUE_H

typedef char *queueElement;
typedef struct queue *queueADT;

queueADT createQueue();
void deleteQueue(queueADT q);
int queueIsEmpty(queueADT queue);
int enqueue(queueADT queue, queueElement element);
queueElement dequeue(queueADT queue);
queueElement peek(queueADT queue);
void printQueue(queueADT queue);
void check(queueADT mediaRangeQueue, queueADT mediaTypesQueue);

#endif
