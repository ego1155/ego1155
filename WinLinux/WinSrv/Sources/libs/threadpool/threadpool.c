#include "threadpool.h"

size_t job_pending(threadpool *tp)
{
	size_t jp = 0;
	pthread_mutex_lock(&tp->lock);
	jp = tp->jp;
	pthread_mutex_unlock(&tp->lock);
	return jp;
}

void add_job(threadpool *tp, void * (*job)(void *arg), void * (*free)(void *arg), void *arg)
{
	threadjob *tj = (threadjob *)malloc(sizeof(threadjob));
	tj->job = job;
	tj->free = free;
	tj->arg = arg;
	pthread_mutex_lock(&tp->lock);
	tp->q->push(tp->q, (void *)tj);
	tp->jp = tp->jp+1;
	//pthread_cond_signal(&tp->signal);
	pthread_mutex_unlock(&tp->lock);
}

void * generic_thread_function(void *arg)
{
    threadpool *tp = (threadpool *)arg;
    while (tp->active == 1)
    {
        pthread_mutex_lock(&tp->lock);
        //pthread_cond_wait(&tp->signal, &tp->lock);
		threadjob *tj = (threadjob *)tp->q->pop(tp->q);
        pthread_mutex_unlock(&tp->lock);
		if (tj != NULL)
		{
			if (tj->job)
			{
				tj->job(tj->arg);
			}
			if (tj->free)
			{
				tj->free(tj->arg);
			}
			free(tj);
			pthread_mutex_lock(&tp->lock);
			tp->jp = tp->jp-1;
			pthread_mutex_unlock(&tp->lock);
		}
    }
    return NULL;
}

threadpool *threadpool_init(int num_threads)
{
	threadpool *tp = (threadpool *)malloc(sizeof(threadpool));
	
	if (tp)
	{
		tp->jp = 0;
		tp->num_threads = num_threads;
		tp->active = 1;
		tp->q = queue_init();
		tp->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		//tp->signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		pthread_mutex_lock(&tp->lock);
		tp->pl = (pthread_t *)malloc(sizeof(pthread_t[num_threads]));
		for (int i = 0; i < num_threads; i++)
		{
			pthread_create(&tp->pl[i], NULL, generic_thread_function, tp);
		}
		pthread_mutex_unlock(&tp->lock);
		tp->add_job = add_job;
		tp->job_pending = job_pending;
		return tp;
	}
	
	return NULL;
}

void threadpool_deinit(threadpool *tp)
{	if (tp)
	{
		tp->active = 0;
		//for (int i=0; i < tp->num_threads; i++)
		//{
			//pthread_cond_signal(&tp->signal);
		//}
		for (int i=0; i < tp->num_threads; i++)
		{
			pthread_join(tp->pl[i], NULL);
		}
		free(tp->pl);
		while(1)
		{
			threadjob *tj = (threadjob *)tp->q->pop(tp->q);
			if (tj != NULL)
			{
				if (tj->free)
				{
					tj->free(tj->arg);
				}
				free(tj);
			}
			else
			{
				break;
			}
		}
		queue_deinit(tp->q);
		free(tp);
	}
}