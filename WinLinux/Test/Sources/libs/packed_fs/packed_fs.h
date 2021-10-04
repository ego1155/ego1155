#ifndef PACKED_FS_H
#define PACKED_FS_H

#include <stddef.h>
#include <string.h>
#include <time.h>

const char *mg_unlist(size_t no);
const char *mg_unpack(const char *name, size_t *size, time_t *mtime);

#endif