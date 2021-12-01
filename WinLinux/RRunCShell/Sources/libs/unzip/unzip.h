#ifndef UNZIP_H
#define UNZIP_H

#include <minizip/unzip.h>

#define dir_delimter '/'
#define MAX_FILENAME 512
#define READ_SIZE 8192

int unzip(const char *fname, const char *path);

#endif