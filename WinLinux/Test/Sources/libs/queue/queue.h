#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct node {
	void *data;
	struct node *next;
} node;

typedef struct queue queue;
struct queue {
	node *head;
	node *tail;
	int (*push)(queue *q, void *data);
	void *(*pop)(queue *q);
};

queue *queue_init();
void queue_deinit(queue *q);

#endif