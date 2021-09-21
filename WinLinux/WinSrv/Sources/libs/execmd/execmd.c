#include "execmd.h"

char *exe_cmd(const char *cmd)
{
	char *bfmout = NULL;
	
	FILE *fp = NULL;
	fp = popen(cmd, "r");
	if (!fp) {
		return bfmout;
	}
	
	char buffer[256];
	size_t bfread;
    size_t bfmalloc = 256;
    size_t bfmlen = 0;
    bfmout = malloc(bfmalloc);
	
	if (!bfmout) {
		return bfmout;
	}
	
	while ((bfread = fread(buffer, 1, sizeof(buffer), fp)) != 0) {
		if (bfmlen + bfread >= bfmalloc) {
			bfmalloc *= 2;
			bfmout = realloc(bfmout, bfmalloc);
		}
		memmove(bfmout + bfmlen, buffer, bfread);
		bfmlen += bfread;
	}
	pclose(fp);
	
	return bfmout;
}