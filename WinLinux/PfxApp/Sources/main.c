#include "main.h"

typedef struct file_ {
	char* path;
} file;

//void get_list_of_files_recusive(file** flist, int* ft, const char* dirname)
void get_list_of_files_recusive(file** flist, int* dt, int* ft, char* path)
{
	PDir* pDir;
	PDirEntry* pDirEntry;
	
	pDir = p_dir_new(path, NULL);
	if (!pDir) return;
	pchar* orig_path = p_dir_get_path(pDir);
	
	while ((pDirEntry = p_dir_get_next_entry(pDir, NULL)) != NULL) {
		// Construct new path from our base path
		strcpy(path, orig_path);
		strcat(path, "\\");
		strcat(path, pDirEntry->name);
		if (pDirEntry->type == P_DIR_ENTRY_TYPE_DIR && strcmp(pDirEntry->name,".") != 0 && strcmp(pDirEntry->name,"..") != 0)
		{
			//printf("DIR :: %s\n", path);
			*dt = *dt + 1;
			get_list_of_files_recusive(&*flist, dt, ft, path);
		}
		else if (pDirEntry->type == P_DIR_ENTRY_TYPE_FILE)
		{
			//printf("FILE :: %s\n", path);
			if (*ft == 0)
			{
				*flist = (file*)malloc(sizeof(file));
				//(*flist+*ft)->path = (char*)malloc(10 * sizeof(char));
			}
			else
			{
				*flist = (file*)realloc(*flist, (*ft + 1) * sizeof(file));
				//(*flist+*ft+1)->path = (char*)malloc(10 * sizeof(char));
			}
			*ft = *ft + 1;
		}
		p_dir_entry_free(pDirEntry);
	}
	p_free(orig_path);
	p_dir_free(pDir);
}

int main(int argc, char *argv[])
{
	printf("test ok...\n");
	printf("test ok...\n");
	printf("test ok...\n");
	
	int dt = 0;
	int ft = 0;
	file* flist;
	
	char* path = (char*)malloc(1000 * sizeof(char));
	strcpy(path, "C:\\Users\\nilesh\\Desktop\\ego1155\\WinLinux\\PfxApp");
	p_libsys_init();
	get_list_of_files_recusive(&flist, &dt, &ft, path);
	p_libsys_shutdown();
	free(path);
	
	
	printf("Total Dirs :: %d\n",dt);
	printf("Total Files :: %d\n",ft);
	//free(flist);
	
	printf("test ok...\n");
	printf("test ok...\n");
	printf("test ok...\n");
	
	//cresource* cresourceb = get_cresource("helloa/sun/computers.png");
	//printf("%s\n", (const char*) cresourceb->name);
	//printf("%lu\n", cresourceb->size);
	//printf("%s\n", (const char*) cresourceb->data);
	//free(cresourceb);
	//cresource* cresourcea = get_cresource("hello/computers/sun.png");
	//printf("%s\n", (const char*) cresourcea->name);
	//printf("%lu\n", cresourcea->size);
	//printf("%s\n", (const char*) cresourcea->data);
	//free(cresourcea);
	
	const unsigned char data[] = { 65,66,67,0 }; // ASCII values for 'A', 'B', 'C'.
	printf("%s\n", (const char *) data);
	
	FILE* fp = fopen("data.bin","wb");	// w for write, b for binary
	fwrite(data,sizeof(data),1,fp);
	fclose(fp);
	
	fp = fopen("data.bin","r+");
	fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
	fclose(fp);
	
	printf("\nSize is %d\n", size);
	
	unsigned char* buffer = (unsigned char*)malloc(size * sizeof(char));
	fp = fopen("data.bin","rb");	// r for read, b for binary
	fread(buffer,sizeof(buffer),1,fp);
	fclose(fp);
	printf("%s\n", (const char *) buffer);
	
	for (int i=0; i < size; i++)
		printf("%d", (int)*(buffer+i));
	printf("\n");
	
	char* arrChar = NULL;
	int idx = 0;
	for (int i=0; i < size; i++)
	{
		int x = (int)*(buffer+i);
		printf("%d\n", x);
		int numOfDigits = log10(x) + 1;
		if (numOfDigits < 1) numOfDigits=1;
		int ext = (i==(size-1))?0:1;
		if (!arrChar)
		{
			arrChar = malloc((numOfDigits + ext) * sizeof(char));
			char* arr = calloc(numOfDigits, sizeof(char));
			sprintf(arr, "%d", x);
			for (int j=0; j < numOfDigits; j++)
				arrChar[idx + j] = arr[j];
			free(arr);
			if (ext != 0) arrChar[idx + numOfDigits] = ',';
		}
		else
		{
			arrChar = realloc(arrChar, (idx + numOfDigits + ext) * sizeof(char));
			char* arr = calloc(numOfDigits, sizeof(char));
			sprintf(arr, "%d", x);
			for (int j=0; j < numOfDigits; j++)
				arrChar[idx + j] = arr[j];
			free(arr);
			if (ext != 0) arrChar[idx + numOfDigits] = ',';
		}
		idx += numOfDigits + ext;
	}
	arrChar = realloc(arrChar, (idx) * sizeof(char));
	arrChar[idx] = '\0';
	printf("idx : %d\n", idx);
	printf("const unsigned char data[] = { %s };\n", (char*)arrChar);
	free(arrChar);

	//int x = 12345;
    //int numOfDigits = log10(x) + 1;
    //char* arr = calloc(numOfDigits, sizeof(char));
    //sprintf(arr, "%d", x);
	//printf("\n");
	//printf("%s\n", (char*)arr);
	//free(arr);
	
	free(buffer);
	return 0;
}