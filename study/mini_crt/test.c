#include "minicrt.h"

int main(int argc, char* argv[])
{
	FILE* fp;
	char **v = malloc(argc * sizeof(char*));
	long int* len = malloc(sizeof(long int*));
	for(int i = 0; i < argc; i++)
	{
		v[i] = malloc(strlen(argv[i]) + 1);
		strcpy(v[i], argv[i] );
	}
	
	//write parameters into test.txt
	
	fp = fopen("test1","w");
	for(int i = 0; i < argc; i++)
	{
		
		*len = strlen(v[i]);
		
		fwrite(len, 1, sizeof(long int), fp);
		fwrite(v[i], 1, *len, fp);
	}
	fclose(fp);
	

	fp = fopen("test.txt","r");
	for(int i = 0; i < argc; i++)
	{
		char* buf;
		
		fread(len, 1, sizeof(long int), fp);
		buf = malloc(*len + 1);
		fread(buf, 1, *len, fp);
		buf[*len] = '\0';
		free(buf);
		free(v[i]);
	}
	fclose(fp);

}
