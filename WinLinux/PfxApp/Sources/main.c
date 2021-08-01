#include "main.h"

int main(int argc, char *argv[])
{
	p_libsys_init();
	
	printf("test ok...\n");
	printf("test ok...\n");
	printf("test ok...\n");
	
	PDir* pDir;
	pDir = p_dir_new("C:\\Users\\nilesh\\Desktop\\ego1155\\WinLinux\\PfxApp\\Output\\Window", NULL);
	if (pDir == NULL) {
        return -1;
	}
	PDirEntry* pDirEntry = NULL;
	while ((pDirEntry = p_dir_get_next_entry (pDir, NULL)) != NULL) {
		printf("%s\n", pDirEntry->name);
	}
	p_dir_entry_free(pDirEntry);
	p_dir_free(pDir);
	
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
	
	p_libsys_shutdown();
	return 0;
}