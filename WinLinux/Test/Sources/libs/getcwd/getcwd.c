#include "getcwd.h"

char *get_cwd(void)
{
	char *cwd = NULL;
	
	cwd = (char *)malloc(1024 * sizeof(char));
	
	if (getcwd(cwd, 1024) == NULL)
		return NULL;
	
	return cwd;
}