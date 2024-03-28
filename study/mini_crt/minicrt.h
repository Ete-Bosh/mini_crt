#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C"{
#endif

//malloc.c
#ifndef NULL
#define NULL (0)
#endif

void free(void* ptr);
void* malloc(unsigned size);
static void* brk(void* end_data_segment);
int mini_crt_heap_init();

//string.c
int strcmp(const char* src, const char* dst);
int strlen(const char* s);
void strcpy(char* dst,const char* src);

//stdio.c
typedef long int FILE;
#define EOF 	(-1)
#define stdin	((FILE*)0)
#define stdout	((FILE*)1)
#define stderr	((FILE*)2)

int mini_crt_io_init();
FILE* fopen(const char* filename, const char* mode);
long int fread(void* buffer,long int size,long int count, FILE* mode);
long int fwrite(const void* buffer, long int size, long int count, FILE* mode);
long int fclose(FILE* fp);
long int fseek(FILE* fp, long int offset, int set);

#ifdef __cplusplus
}
#endif

#endif __MINI_CRT_H__
