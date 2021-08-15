#include "resourcesgen.h"

size_t read_file_binary(FILE *fp, char **buf)
{
	size_t n, r;
	char* b = NULL;
	char* b2 = NULL;
	n = 0;
	b = (char*)malloc(sizeof(char) * CHUNK_SIZE);
	while ((r = fread(b, sizeof(char), CHUNK_SIZE, fp)) > 0)
	{
		n += r;
		if (!b2)
		{
			b2 = (char*)malloc(sizeof(char) * n);
			for (int i=0; i < r; i++)
				b2[n-r+i]=b[i];
		}
		else
		{
			b2 = (char*)realloc(b2, sizeof(char) * n);
			for (int i=0; i < r; i++)
				b2[n-r+i]=b[i];
		}
	}
	free(b);
	*buf = b2;
	return n;
}

int copy_file_binary( const char* srcfilename, const char* dstfilename )
{
	char* buf = NULL;
	FILE* fp  = NULL;
	
	fp = fopen( srcfilename, "rb" );
	if (!fp) return -1;
	
	size_t size = read_file_binary( fp, &buf );
	
	if (size == 0)
	{
		fclose( fp );
		free( buf );
		return -1;
	}
	
	fclose( fp );
	
	fp = fopen( dstfilename, "wb" );
	if (!fp)
	{
		free( buf );
		return -1;
	}
	
	if (!fwrite( buf, size, 1, fp ))
	{
		free( buf );
		fclose( fp );
		return -1;
	}

	fclose( fp );
	free( buf );
	return 0;
}

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
#if defined (P_OS_WIN64)
		strcat(path, "\\");
#else
		strcat(path, "/");
#endif
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
				//(*fi+*filet)->path=(char*)malloc((strlen(path)+1) * sizeof(char));
				//strcpy((*fi+*filet)->path, path);
				(*fi+*filet)->path = sc_str_create(path);
				sc_str_replace(&(*fi+*filet)->path, "\\\\", "\\");
			}
			else
			{
				*fi = (FileInfo*)realloc(*fi, (*filet + 1) * sizeof(FileInfo));
				//(*fi+*filet)->path=(char*)malloc((strlen(path)+1) * sizeof(char));
				//strcpy((*fi+*filet)->path, path);
				(*fi+*filet)->path = sc_str_create(path);
				sc_str_replace(&(*fi+*filet)->path, "\\\\", "\\");
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
	char* resources_h = sc_str_create(target);
	char* resources_c = sc_str_create(target);
#if defined (P_OS_WIN64)
	sc_str_append_fmt(&resources_h, "%s", "\\resources.h");
	sc_str_append_fmt(&resources_c, "%s", "\\resources.c");
#else
	sc_str_append_fmt(&resources_h, "%s", "/resources.h");
	sc_str_append_fmt(&resources_c, "%s", "/resources.c");
#endif
	
	p_libsys_init();
	if (p_file_is_exists(resources_h) == TRUE)
		p_file_remove(resources_h, NULL);
	if (p_file_is_exists(resources_c) == TRUE)
		p_file_remove(resources_c, NULL);
	FILE *fp;
	fp = fopen(resources_h, "a");
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
	fp = fopen(resources_c, "a");
	fprintf(fp, "%s\n", "#include \"resources.h\"");
	fprintf(fp, "%s\n", "");
	
	unsigned long dirt = 0;
	unsigned long filet = 0;
	FileInfo* fi;	
	char* path = (char*)malloc(1000 * sizeof(char));
	strcpy(path, source);
	get_list_of_files_recusive(&fi, &dirt, &filet, path);
	free(path);
	for(int i=0; i < filet; i++)
	{
		char* src = sc_str_create((fi + i)->path);
		
		sc_str_replace(&(fi + i)->path, source, "XXX");
#if defined (P_OS_WIN64)
		sc_str_replace(&(fi + i)->path, "XXX\\", "XXX");
		sc_str_replace(&(fi + i)->path, "\\", "/");
#else
		sc_str_replace(&(fi + i)->path, "XXX/", "XXX");
#endif
		//sc_str_replace(&(fi + i)->path, "XXX\\", "XXX");
		//sc_str_replace(&(fi + i)->path, "XXX/", "XXX");
		sc_str_trim(&(fi + i)->path, "XXX");
		//sc_str_replace(&(fi + i)->path, "\\", "/");
		fprintf(fp, "const char name%d[] = \"%s\";\n", i, (fi + i)->path);
		
		char* buf = NULL;
		FILE* fpp  = NULL;
		
		fpp = fopen( src, "rb" );
		size_t size = read_file_binary( fpp, &buf );
		fclose( fpp );
		
		char* arrChar = NULL;
		int idx = 0;
		for (int k=0; k < size; k++)
		{
			int x = (int)((unsigned char)*(buf+k));
			int numOfDigits = log10(x) + 1;
			if (numOfDigits < 1) numOfDigits=1;
			int ext = (k==(size-1))?0:1;
			if (!arrChar)
			{
				arrChar = malloc((numOfDigits + ext) * sizeof(char));
				char* arr = calloc(numOfDigits, sizeof(char));
				sprintf(arr, "%d", x);
				for (int j=0; j < numOfDigits; j++)
					arrChar[idx + j] = arr[j];
				free( arr );
				if (ext != 0) arrChar[idx + numOfDigits] = ',';
			}
			else
			{
				arrChar = realloc(arrChar, (idx + numOfDigits + ext) * sizeof(char));
				char* arr = calloc(numOfDigits, sizeof(char));
				sprintf(arr, "%d", x);
				for (int j=0; j < numOfDigits; j++)
					arrChar[idx + j] = arr[j];
				free( arr );
				if (ext != 0) arrChar[idx + numOfDigits] = ',';
			}
			idx += numOfDigits + ext;
		}
		arrChar = realloc(arrChar, (idx) * sizeof(char));
		arrChar[idx] = '\0';
		fprintf(fp, "const unsigned char data%d[] = { %s };\n", i, (char*)arrChar);
		free( arrChar );
		free( buf );
		
		sc_str_destroy(&src);
	}
	for(int i=0; i < filet; i++)
		//free((fi + i)->path);
		sc_str_destroy(&(fi + i)->path);
	free(fi);
	
	fprintf(fp, "%s\n", "");
	fprintf(fp, "%s\n", "cresource* get_cresource(const char* filename)");
	fprintf(fp, "%s\n", "{");
	
	for(int i=0; i < filet; i++)
	{
		if (i == 0)
			fprintf(fp, "\tif (strcmp(filename,name%d) == 0)\n", i);
		else
			fprintf(fp, "\telse if (strcmp(filename,name%d) == 0)\n", i);
		fprintf(fp, "\t\treturn create_cresource(name%d, sizeof(data%d)/sizeof(data%d[0]), data%d);\n", i, i, i, i);
	}
	
	fprintf(fp, "%s\n", "\treturn NULL;");
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
	
	sc_str_destroy(&resources_h);
	sc_str_destroy(&resources_c);
}