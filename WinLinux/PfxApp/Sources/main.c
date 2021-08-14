#include "main.h"

int main(int argc, char *argv[])
{
	//printf("=========================================\n");
	//printf("=========================================\n");
	
#if defined (P_OS_WIN64)
	const char* src_path = ".\\..\\Resources";
	const char* dest_path = ".\\..\\libPfx\\resources";
#else
	const char* src_path = "./../Resources";
	const char* dest_path = "./../libPfx/resources";
#endif
	resources_generate(src_path, dest_path);

	cresource* cresourceb = get_cresource("index.jpg");
	FILE* fp = fopen("index.jpg","wb");	// w for write, b for binary
	fwrite(cresourceb->data,cresourceb->size,1,fp);
	fclose(fp);
	printf("%s\n", (const char*) cresourceb->name);
	printf("%lu\n", cresourceb->size);
	printf("%s\n", (const char*) cresourceb->data);
	free(cresourceb);
	
	cresourceb = get_cresource("m.jpg");
	fp = fopen("m.jpg","wb");	// w for write, b for binary
	fwrite(cresourceb->data,cresourceb->size,1,fp);
	fclose(fp);
	printf("%s\n", (const char*) cresourceb->name);
	printf("%lu\n", cresourceb->size);
	printf("%s\n", (const char*) cresourceb->data);
	free(cresourceb);
	
	cresourceb = get_cresource("ssh_tunnel.c");
	fp = fopen("ssh_tunnel.c","wb");	// w for write, b for binary
	fwrite(cresourceb->data,cresourceb->size,1,fp);
	fclose(fp);
	printf("%s\n", (const char*) cresourceb->name);
	printf("%lu\n", cresourceb->size);
	printf("%s\n", (const char*) cresourceb->data);
	free(cresourceb);
	
	cresourceb = get_cresource("HelloWorld.txt");
	fp = fopen("HelloWorld.txt","wb");	// w for write, b for binary
	fwrite(cresourceb->data,cresourceb->size,1,fp);
	fclose(fp);
	printf("%s\n", (const char*) cresourceb->name);
	printf("%lu\n", cresourceb->size);
	printf("%s\n", (const char*) cresourceb->data);
	free(cresourceb);
	
	//printf("=========================================\n");
	//printf("=========================================\n");
	//printf("Press Any Key to Continue\n");
	//system("pause");
	return 0;
}
