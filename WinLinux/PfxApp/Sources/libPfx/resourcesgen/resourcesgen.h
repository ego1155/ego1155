#ifndef RESOURCESGEN_H
#define RESOURCESGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <libssh/libssh.h>
#include "../../plibsys/plibsys/src/plibsys.h"
#include "../sc_str/sc_str.h"

#define CHUNK_SIZE 1024

typedef struct fileinfo_ {
	char* path;
} FileInfo;

size_t read_file_binary(FILE *fp, char **buf);
int copy_file_binary( const char* srcfilename, const char* dstfilename );
void get_list_of_files_recusive(FileInfo** fi, unsigned long* dirt, unsigned long* filet, char* path);
void resources_generate(const char* source, const char* target);

#endif
