#include "minicrt.h"

extern int main(int argc, char* argv[]);
void exit();

static void crt_fatal_error(const char *msg)
{
	exit(1);
}

void mini_crt_entry()
{
	int ret;
	int argc;
	char **argv;
	char* rbp_reg = 0;
	asm("movq  %%rbp, %0 \n\t" 
		:"=r"(rbp_reg)
		:
		);
	argc = *((int*)(rbp_reg + 8));
	argv = (char**)(rbp_reg + 16);
	if(!mini_crt_heap_init())	crt_fatal_error("heap initialize failed");
	if(!mini_crt_io_init())		crt_fatal_error("io initialize failed");

	// path occupy the first position
	argc -= 1;
	argv += 1;//
	ret = main(argc, argv);
	exit(ret);
}

void exit(int exitCode)
{
	asm("movq %0 ,%%rbx \n\t"
		"movq $1 ,%%rax \n\t"
		"int $0x80		\n\t"
		"hlt			\n\t"
		:
		:"m"(exitCode)
		);
}
