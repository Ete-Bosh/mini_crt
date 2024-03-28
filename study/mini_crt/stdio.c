#include "minicrt.h"

int mini_crt_io_init()
{
	return 1;
}


// In this project, we define FILE* =long int.
// In real project, we need to use fileno() to convert FILE* fp -> int fd
// and use fdopen() to convert int fd -> FILE* fp
static long int open(const char* pathname, int flags, int mode)
{
	long int fd = 0;
	asm("movq $5, %%rax		\n\t"
		"movq %1, %%rbx		\n\t"
		"movq %2, %%rcx		\n\t"
		"movq %3, %%rdx		\n\t"
		"int $0x80 			\n\t"
		"movq %%rax, %0		\n\t"
		:"=m"(fd)
		:"m"(pathname), "m"(flags),"m"(mode)
		);
	return fd;
}

static long int read(long int fd, void* buffer, long int size)
{
	long int ret = 0;
	asm("movq $3, %%rax		\n\t"
		"movq %1, %%rbx		\n\t"
		"movq %2, %%rcx		\n\t"
		"movq %3, %%rdx		\n\t"
		"int $0x80 			\n\t"
		"movq %%rax, %0		\n\t"
		:"=m"(ret)
		:"m"(fd), "m"(buffer), "m"(size)
		);
	return ret;
}

static long int write(long int fd, const void* buffer,long int size)
{
	long int ret = 0;
	asm("movq $4, %%rax		\n\t"
		"movq %1, %%rbx		\n\t"
		"movq %2, %%rcx		\n\t"
		"movq %3, %%rdx		\n\t"
		"int $0x80 			\n\t"
		"movq %%rax, %0		\n\t"
		:"=m"(ret)
		:"m"(fd), "m"(buffer), "m"(size)
		);
	return ret;
}

static long int seek(long int fd, long int offset, int mode)
{
	long int ret = 0;
	asm("movq $19, %%rax	\n\t"
		"movq %1, %%rbx		\n\t"
		"movq %2, %%rcx		\n\t"
		"movq %3, %%rdx		\n\t"
		"int $0x80 			\n\t"
		"movq %%rax, %0		\n\t"
		:"=m"(ret)
		:"m"(fd), "m"(offset), "m"(mode)
		);
	return ret;
}

static long int close(long int fd)
{
	long int ret = 0;
	asm("movq $6, %%rax\n\t"
		"movq %1, %%rbx \n\t"
		"int $0x80	\n\t"
		"movq %%rax, %0	\n\t"
		:"=m"(ret)
		:"m"(fd)	
		);
	return ret;
}

FILE* fopen(const char* filename, const char* mode)
{
	long int fd = -1;
	int flags = 0;
	int access = 00700;

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define O_TRUNC 01000
#define O_APPEND 02000

	if(strcmp(mode, "w") == 0)
	{
		flags |= O_WRONLY | O_CREAT | O_TRUNC;
	}
	if(strcmp(mode, "w+") == 0)
	{
		flags |= O_RDWR | O_CREAT | O_TRUNC;
	}
	if(strcmp(mode, "r") == 0)
	{
		flags = O_RDONLY;
	}
	if(strcmp(mode, "r+") == 0)
	{
		flags |= O_RDWR | O_CREAT;
	}
	fd = open(filename, flags, access);
	return (FILE*)fd;
}

long int fread(void* buffer, long int size, long int count, FILE* stream)
{
	return read((long int)stream, buffer, size * count);
}
long int fwrite(const void* buffer, long int size,long int count, FILE* stream)
{
	return write((long int)stream, buffer, size * count);
}
long int fseek(FILE* fp,long int offset, int set)
{
	return seek((long int)fp, offset, set);
}
long int fclose(FILE* fp)
{
	return close((long int)fp);
}
