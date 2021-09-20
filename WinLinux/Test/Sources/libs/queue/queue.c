#include "queue.h"

int queue_push(queue *q, void *data)
{
	node *nn = (node *)malloc(sizeof(node));
	if (nn == NULL) return -1;

	nn->data = data;
	nn->next = NULL;

	if (q->tail != NULL)
	{
		q->tail->next = nn;
	}
	q->tail = nn;

	if (q->head == NULL)
	{
		q->head = nn;
	}
	
	return 0;
}

void *queue_pop(queue *q)
{
	if (q->head == NULL) return NULL;

	node *tmp = q->head;

	void *data = tmp->data;

	q->head = q->head->next;
	

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