#ifndef QUEUE_H
#define QUEUE_H

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

typedef char *queueElement;
typedef struct queue *queueADT;
queueADT createQueue();
void deleteQueue(queueADT q);
int queueIsEmpty(queueADT queue);
int enqueue(queueADT queue, queueElement element);
queueElement dequeue(queueADT queue);
queueElement peek(queueADT queue);
void printQueue(queueADT queue);

#endif