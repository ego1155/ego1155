#include "queue.h"

int queue_push(queue *q, void *data)
{
	// create new node
	node *nn = (node *)malloc(sizeof(node));
	// check malloc
	if (nn == NULL) return -1;
	// fill data
	nn->data = data;
	nn->next = NULL;
	// if there is tail, then connect tail to new node
	if (q->tail != NULL)
	{
		q->tail->next = nn;
	}
	q->tail = nn;
	// head still make sense
	if (q->head == NULL)
	{
		q->head = nn;
	}
	
	return 0;
}

void *queue_pop(queue *q)
{
	if (q->head == NULL) return NULL;
	// save head node from queue
	node *tmp = q->head;
	// save data
	void *data = tmp->data;
	// take it off from queue
	q->head = q->head->next;
	
	// tail still make sense
	if (q->head == NULL)
	{
		q->tail = NULL;
	}
	
	free(tmp);
	
	return data;
}

queue *queue_init()
{
	queue *q = (queue *)malloc(sizeof(queue));
	
	if (q)
	{
		q->head = NULL;
		q->tail = NULL;
		q->push = queue_push;
		q->pop = queue_pop;
		return q;
	}
	
	return NULL;
}

void queue_deinit(queue *q)
{
	if (q) free(q);
}