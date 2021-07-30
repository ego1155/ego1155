#include "cronjob.h"

cronjob* cronjob_init()
{
	cronjob* self = (cronjob*)malloc(sizeof(cronjob));
	self->task = NULL;
	self->idx = (int*)calloc(1, sizeof(int));
	if (self->idx == NULL) return NULL;
	self->add_task = add_task;
	self->process_task = process_task;
	return self;
}

void cronjob_deinit(cronjob* self)
{
	for(int i=0; i < *self->idx; i++)
	{
		free((self->task + i)->id);
		free((self->task + i)->expr);
		free((self->task + i)->next);
	}
	free(self->task);
	free(self->idx);
	free(self);
}

void add_task(cronjob* self, int id, const char* expression, void (*CronFunc)(void))
{
	if (id <= 0 || !expression || !CronFunc) return;
	if (*self->idx == 0)
	{
		cron_expr* expr = (cron_expr*)calloc(1, sizeof(cron_expr));
		if (expr == NULL) return;
		time_t* next = (time_t*)calloc(1, sizeof(time_t));
		if (next == NULL)
		{
			free(expr);
		}
		const char* err = NULL;
		cron_parse_expr(expression, expr, &err);
		if (err) {
			free(expr);
			free(next);
			return;
		}
		int* idd = (int*)calloc(1, sizeof(int));
		if (idd == NULL) {
			free(expr);
			free(next);
			return;
		}
		task* taskd = (task*)malloc(sizeof(task));
		if (taskd == NULL) {
			free(expr);
			free(next);
			free(idd);
			return;
		}
		self->task = taskd;
		(self->task + *self->idx)->id = idd;
		(self->task + *self->idx)->expr = expr;
		(self->task + *self->idx)->next = next;
		(self->task + *self->idx)->CronFunc = CronFunc;
		*(self->task + *self->idx)->id = id;
		time_t cur = time(NULL);
		*(self->task + *self->idx)->next = cron_next((self->task + *self->idx)->expr, cur);
		*self->idx = *self->idx + 1;
	}
	else
	{
		cron_expr* expr = (cron_expr*)calloc(1, sizeof(cron_expr));
		if (expr == NULL) return;
		time_t* next = (time_t*)calloc(1, sizeof(time_t));
		if (next == NULL)
		{
			free(expr);
		}
		const char* err = NULL;
		cron_parse_expr(expression, expr, &err);
		if (err) {
			free(expr);
			free(next);
			return;
		}
		int* idd = (int*)calloc(1, sizeof(int));
		if (idd == NULL) {
			free(expr);
			free(next);
			return;
		}
		task* taskd = (task*)realloc(self->task, (*self->idx+1) * sizeof(task));
		if (taskd == NULL) {
			free(expr);
			free(next);
			free(idd);
			return;
		}
		self->task = taskd;
		(self->task + *self->idx)->id = idd;
		(self->task + *self->idx)->expr = expr;
		(self->task + *self->idx)->next = next;
		(self->task + *self->idx)->CronFunc = CronFunc;
		*(self->task + *self->idx)->id = id;
		time_t cur = time(NULL);
		*(self->task + *self->idx)->next = cron_next((self->task + *self->idx)->expr, cur);
		*self->idx = *self->idx + 1;
	}
}

void process_task(cronjob* self)
{
	time_t cur = time(NULL);
	for(int i=0; i < *self->idx; i++)
	{
		if (cur >= *((self->task+i)->next))
		{
			(self->task+i)->CronFunc();
			*((self->task+i)->next) = cron_next((self->task+i)->expr, cur);
			//printf("%d next :: %s", i, ctime((self->task+i)->next));
		}
	}
}