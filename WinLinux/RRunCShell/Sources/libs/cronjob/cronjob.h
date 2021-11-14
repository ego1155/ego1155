#ifndef CRONJOB_H
#define CRONJOB_H

#include "../ccronexpr/ccronexpr.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cronjob_ cronjob;

typedef struct task_ {
	int* id;
	cron_expr* expr;
	time_t* next;
	void (*CronFunc)(void);
} task;

struct cronjob_ {
	task* task;
	int* idx;
	void (*add_task)(cronjob* self, int id, const char* expression, void (*CronFunc)(void));
	void (*process_task)(cronjob* self);
};

cronjob* cronjob_init();
void cronjob_deinit(cronjob* self);
void add_task(cronjob* self, int id, const char* expression, void (*CronFunc)(void));
void process_task(cronjob* self);


#endif