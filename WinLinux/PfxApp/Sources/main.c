#include "main.h"

typedef struct fileinfo_ {
	char* path;
} FileInfo;

void get_list_of_files_recusive(FileInfo** fi, unsigned long* dirt, unsigned long* filet, char* path)
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
			*dirt = *dirt + 1;
			get_list_of_files_recusive(&*fi, dirt, filet, path);
		}
		else if (pDirEntry->type == P_DIR_ENTRY_TYPE_FILE)
		{
			//printf("FILE :: %s\n", path);
			if (*filet == 0)
			{
				*fi = (FileInfo*)malloc(sizeof(FileInfo));
				(*fi+*filet)->path=(char*)malloc((strlen(path)+1) * sizeof(char));
				strcpy((*fi+*filet)->path, path);
			}
			else
			{
				*fi = (FileInfo*)realloc(*fi, (*filet + 1) * sizeof(FileInfo));
				(*fi+*filet)->path=(char*)malloc((strlen(path)+1) * sizeof(char));
				strcpy((*fi+*filet)->path, path);
			}
			*filet = *filet + 1;
		}
		p_dir_entry_free(pDirEntry);
	}
	p_free(orig_path);
	p_dir_free(pDir);
}

void resources_generate(const char* source, const char* target)
{
	p_libsys_init();
	FILE *fp;
	fp = fopen("resources.h", "a");
	fprintf(fp, "%s\n", "#ifndef RESOURCES_H");
	fprintf(fp, "%s\n", "#define RESOURCES_H");
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "#include <stdio.h>");
	fprintf(fp, "%s\n", "#include <stdlib.h>");
	fprintf(fp, "%s\n", "#include <string.h>");
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "typedef struct cresource_ {");
	fprintf(fp, "%s\n", "\tconst char* name;");
	fprintf(fp, "%s\n", "\tunsigned long size;");
	fprintf(fp, "%s\n", "\tconst unsigned char* data;");
	fprintf(fp, "%s\n", "} cresource;");
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "cresource* get_cresource(const char* filename);");
	fprintf(fp, "%s\n", "cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data);");
	fprintf(fp, "%s\n", "void free_cresource(cresource* self);");
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "#endif");
	fclose(fp);
	fp = fopen("resources.c", "a");
	fprintf(fp, "%s\n", "#include \"resources.h\"");
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "cresource* get_cresource(const char* filename)");
	fprintf(fp, "%s\n", "{");
	fprintf(fp, "%s\n", "}");
	fprintf(fp, "%s\n", "cresource* create_cresource(const char* name, unsigned long size, const unsigned char* data)");
	fprintf(fp, "%s\n", "{");
	fprintf(fp, "%s\n", "\tcresource* resource = NULL;");
	fprintf(fp, "%s\n", "\tresource = (cresource*)malloc(sizeof(cresource));");
	fprintf(fp, "%s\n", "\tresource->name = name;");
	fprintf(fp, "%s\n", "\tresource->size = size;");
	fprintf(fp, "%s\n", "\tresource->data = data;");
	fprintf(fp, "%s\n", "\treturn resource;");
	fprintf(fp, "%s\n", "}");
	fprintf(fp, "%s\n", "void free_cresource(cresource* self)");
	fprintf(fp, "%s\n", "{");
	fprintf(fp, "%s\n", "\tfree(self);");
	fprintf(fp, "%s\n", "}");
	fclose(fp);
	p_libsys_shutdown();
}

int main(int argc, char *argv[])
{
	printf("=========================================\n");
	printf("=========================================\n");
	
	resources_generate("C:\\Users\\nilesh\\Desktop\\ego1155\\WinLinux\\PfxApp\\Sources\\Resources", "./");

	unsigned long dirt = 0;
	unsigned long filet = 0;
	FileInfo* fi;	
	
	char* path = (char*)malloc(1000 * sizeof(char));
	//strcpy(path, "C:\\Users\\nilesh\\Desktop\\ego1155\\WinLinux\\PfxApp\\Sources\\Resources");
	strcpy(path, "C:\\");
	p_libsys_init();
	get_list_of_files_recusive(&fi, &dirt, &filet, path);
	p_libsys_shutdown();
	free(path);
	
	//for(int i=0; i < filet; i++)
	//{
		//printf("FILE :: %s\n", (fi + i)->path);
	//}
	
	for(int i=0; i < filet; i++)
		free((fi + i)->path);
	free(fi);
	
	printf("Total Dirs :: %lu\n",dirt);
	printf("Total Files :: %lu\n",filet);

	printf("=========================================\n");
	printf("=========================================\n");
	printf("Press Any Key to Continue\n");
	system("pause");
	
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
	
	/* const unsigned char data[] = { 65,66,67,0 }; // ASCII values for 'A', 'B', 'C'.
	printf("%s\n", (const char *) data);
	
	FILE* fp = fopen("data.bin","wb");	// w for write, b for binary
	fwrite(data,sizeof(data),1,fp);
	fclose(fp);
	
	fp = fopen("data.bin","r+");
	fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
	fclose(fp);
	
	printf("\nSize is %ld\n", size);
	
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
	free(arrChar); */

	//int x = 12345;
    //int numOfDigits = log10(x) + 1;
    //char* arr = calloc(numOfDigits, sizeof(char));
    //sprintf(arr, "%d", x);
	//printf("\n");
	//printf("%s\n", (char*)arr);
	//free(arr);
	
	//free(buffer);
	return 0;
}
