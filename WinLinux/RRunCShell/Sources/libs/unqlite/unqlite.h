#ifndef UNQLITE_H
#define UNQLITE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unqlite.h>
#include "../getdirpathfrompath/getdirpathfrompath.h"

typedef struct unqldb_ unqldb;

struct unqldb_
{
    unqlite *db;
    int (*add)(unqldb *self, const char *key, const char *value);
	int (*append)(unqldb *self, const char *key, const char *value);
	char *(*get)(unqldb *self, const char *key);
	char *(*get_size)(unqldb *self, const char *key, unqlite_int64 *size);
	int (*del)(unqldb *self, const char *key);
	int (*add_file)(unqldb *self, const char *key, const char *path);
	int (*backup)(unqldb *self, const char *path);
};

unqldb *unqldb_init(const char *path);
void unqldb_deinit(unqldb *self);
int unqldb_add(unqldb *self, const char *key, const char *value);
int unqldb_append(unqldb *self, const char *key, const char *value);
char *unqldb_get(unqldb *self, const char *key);
char *unqldb_get_size(unqldb *self, const char *key, unqlite_int64 *size);
int unqldb_del(unqldb *self, const char *key);
int unqldb_add_file(unqldb *self, const char *key, const char *path);
int unqldb_backup(unqldb *self, const char *path);

#endif