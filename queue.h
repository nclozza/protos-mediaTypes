#ifndef QUEUE_H
#define QUEUE_H

typedef char *queueElement;

typedef struct node
{
    queueElement element;
    struct node *next;
} node;

struct queue
{
    node *first;
    node *last;
};

typedef struct queue *queueADT;

queueADT createQueue();
void deleteQueue(queueADT q);
void emptyQueue(queueADT queue);
int queueIsEmpty(queueADT queue);
int enqueue(queueADT queue, queueElement element);
queueElement dequeue(queueADT queue);
queueElement peek(queueADT queue);
void printQueue(queueADT queue);

#endif
