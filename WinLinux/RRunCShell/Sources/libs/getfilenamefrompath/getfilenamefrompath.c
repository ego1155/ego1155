#include "getfilenamefrompath.h"

char* getFileNameFromPath(const char* path)
{
#ifdef __unix__
	const char separator = '/';
#elif _WIN32
	const char separator = '\\';
#endif
	char* fname = NULL;
	if(path != NULL)
	{
		for(size_t i = strlen(path);  i > 0; --i)
		{
			if (path[i-1] == separator)
			{
				size_t len = strlen(&path[i]);
				fname = (char*)malloc(len * sizeof(char));
				strncpy(fname, &path[i], len);
				fname[len] = 0;
				break;
			}
		}
	}
	return fname;
}