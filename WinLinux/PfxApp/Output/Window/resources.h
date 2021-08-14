#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cresource_ {
	const char* name;
	unsigned long size;
	const unsigned char* data;
} cresource;

cresource* get_cresource(const char* filename);
cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data);
void free_cresource(cresource* self);

#endif
#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cresource_ {
	const char* name;
	unsigned long size;
	const unsigned char* data;
} cresource;

cresource* get_cresource(const char* filename);
cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data);
void free_cresource(cresource* self);

#endif
#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cresource_ {
	const char* name;
	unsigned long size;
	const unsigned char* data;
} cresource;

cresource* get_cresource(const char* filename);
cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data);
void free_cresource(cresource* self);

#endif
#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cresource_ {
	const char* name;
	unsigned long size;
	const unsigned char* data;
} cresource;

cresource* get_cresource(const char* filename);
cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data);
void free_cresource(cresource* self);

#endif
