#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

struct node
{
	char * value;
	struct node *next;	
};

struct node *queueFront;
struct node *queueLast;
int queueSize;

void newQueue()
{
	queueFront = NULL;
	queueLast = NULL;
	queueSize = 0;
}

char* peek()
{
	return queueFront->value;
}

char * dequeue()
{
	if(isEmpty())
		return NULL;
	queueSize--;
	struct node *aux = queueFront;
	char * data = aux->value;
	queueFront = queueFront->next;
	free(aux);
	return data;
}

void enqueue(char * data)
{	
	queueSize++;	
	if(queueFront==NULL)
	{		
		queueFront = (struct node *)malloc(sizeof(struct node));
		queueFront->value = malloc(strlen(data)+1);
		strcpy(queueFront->value,data);
		queueFront->value[strlen(data) + 1] = '\0';
		queueFront->next = NULL;
		queueLast = queueFront;
	}
	else
	{
		queueLast->next = (struct node *)malloc(sizeof(struct node));
		queueLast->value = malloc(strlen(data)+1);
		strcpy(queueLast->value,data);
		queueLast->value[strlen(data) + 1] = '\0';
		queueLast->next->next = NULL;
		queueLast = queueLast->next;
	}	
}

int isEmpty()
{
	return queueSize==0;
}

int sizeQueue()
{
	return queueSize;
}

void printQueue()
{
    struct node *aux = queueFront;
    while(aux->next != NULL){
        printf("%s\n",aux->value);
        aux = aux->next;
    }
}