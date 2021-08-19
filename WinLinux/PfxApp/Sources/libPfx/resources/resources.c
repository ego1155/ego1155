#include "resources.h"

const char name1[] = "helloa/sun/computers.png";
const unsigned char data1[] = { 65,66,67,67,65,65,67,66,0 };
const char name2[] = "hello/computers/sun.png";
const unsigned char data2[] = { 65,66,67,66,65,66,67,66,0 };

cresource* get_cresource(const char* filename)
{
	if (strcmp(filename,name1) == 0)
		return create_cresource(name1, sizeof(data1)/sizeof(data1[0]), data1);
	else if (strcmp(filename,name2) == 0)
		return create_cresource(name2, sizeof(data2)/sizeof(data2[0]), data2);
	return NULL;
}
cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data)
{
	cresource* resource = NULL;
	resource = (cresource*)malloc(sizeof(cresource));
	resource->name = name;
	resource->size = size;
	resource->data = data;
	return resource;
}
void free_cresource(cresource* self)
{
	free(self);
}