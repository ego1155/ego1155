#include "getdirpathfrompath.h"

char* getDirPathFromPath(const char* path)
{
#ifdef __unix__
	const char separator = '/';
#elif _WIN32
	const char separator = '\\';
#endif
	char* parent = NULL;
    int parentLen;
    char* last = strrchr(path, separator);

    if (last != NULL)
	{
		parentLen = strlen(path) - strlen(last + 1);
		parent = (char*)malloc(parentLen * sizeof(char));
        strncpy(parent, path, parentLen);
		parent[parentLen] = 0;
    }
	return parent;
}