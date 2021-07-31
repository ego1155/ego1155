#include "main.h"

int main(int argc, char *argv[])
{
	p_libsys_init();
	
	printf("test ok...\n");
	printf("test ok...\n");
	printf("test ok...\n");
	
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

	for (int i=0; i < size; i++)
		printf("%d = %d = %d\n", i, (int)*(buffer+i), log10((int)*(buffer+i)) + 1);
	
	int x = 12345;
    int numOfDigits = log10(x) + 1;
    char* arr = calloc(numOfDigits, sizeof(char));
    sprintf(arr, "%d", x);
	printf("\n");
	printf("%s\n", (char*)arr);
	free(arr);
	//int* arrInt = (int*)malloc(size * sizeof(int));
	//for(int i=0; i < size; i++)
		//arrInt[i] = (int)*(buffer+i);
	//for (int i=0; i < size; i++)
		//printf("%d", (int)*(arrInt+i));
	//printf("\n");
	
	//char* arrChar = (char*)malloc(size * sizeof(char));
	//for (int i=0; i < size; i++)
		//arrChar[i] = arrInt[i];
	//for (int i=0; i < size; i++)
		//printf("%c", arrChar[i]);
	//printf("\n");
	//printf("%s\n", (char*)arrChar);
	//free(arrChar);
	//free(arrInt);
	
	free(buffer);
	
	p_libsys_shutdown();
	return 0;
}