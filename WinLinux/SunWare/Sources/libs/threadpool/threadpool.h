#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include "../queue/queue.h"

typedef struct threadjob threadjob;
struct threadjob {
	void * (*job)(void *arg);
	void * (*free)(void *arg);
	void *arg;
};

typedef struct threadpool threadpool;
struct threadpool {
	size_t jp;
    int num_threads;
    int active;
    queue *q;
    pthread_t *pl;
    pthread_mutex_t lock;
    //pthread_cond_t signal;
	void (*add_job)(threadpool *tp, void * (*job)(void *arg), void * (*free)(void *arg), void *arg);
	size_t (*job_pending)(threadpool *tp);
};

threadpool *threadpool_init(int num_threads);
void threadpool_deinit(threadpool *tp);

#endif