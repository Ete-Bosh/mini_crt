#include "minicrt.h"

typedef struct _heap_header
{
	enum{
		HEAP_BLOCK_FREE = 0xABABABAB,
		HEAP_BLOCK_USED = 0xCDCDCDCD,
	} type;
	unsigned size;
	struct _heap_header *next;
	struct _heap_header *prev;
}heap_header;

#define ADDR_ADD(a, o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

heap_header* list_head = NULL;

void free(void* ptr)
{
	heap_header* header = (heap_header*)ADDR_ADD(ptr, -HEADER_SIZE);
	if(header->type != HEAP_BLOCK_USED) return;
	header->type = HEAP_BLOCK_FREE;

	//Merge prev
	if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE)
	{
		header->prev->next = header->next;
		if(header->next != NULL)
		{
			header->next->prev = header->prev;
		}
		header->prev->size += header->size;
		header = header->prev;
	}

	//Merge next
	if(header->next != NULL && header->next->type == HEAP_BLOCK_FREE)
	{
		header->size += header->next->size;
		header->next = header->next->next;
	}
}

void* malloc(unsigned size)
{
	heap_header *header;
	if(!size) return NULL;

	header = list_head;
	while(header)
	{
		if(header->type == HEAP_BLOCK_USED)
		{
			header = header->next;
			continue;
		}

		if(header->size > size + HEADER_SIZE && header->size <= size + HEADER_SIZE * 2)
		{
			header->type = HEAP_BLOCK_USED;
			return ADDR_ADD(header, HEADER_SIZE);
		}

		if(header->size > size + HEADER_SIZE * 2)
		{
			heap_header* next = (heap_header*)ADDR_ADD(header, size + HEADER_SIZE);
			next->prev = header;
			next->next = header->next;
			if(header->next != NULL)
			{
				header->next->prev = next;
			}
			header->next = next;

			next->type = HEAP_BLOCK_FREE;
			header->type = HEAP_BLOCK_USED;

			next->size = header->size - size - HEADER_SIZE;
			header->size = size + HEADER_SIZE;
			
			return ADDR_ADD(header, HEADER_SIZE);
		}

		header = header->next;
	}
	return NULL;
}

//Linux brk system call
static void* brk(void* end_data_segment)
{
	void* ret = 0;
	asm("movq $45, %%rax	\n\t"
		"movq %1 , %%rbx	\n\t"
		"int $0x80			\n\t"
		"movq %%rax, %0		\n\t"
		: "=m"(ret)
		: "m"(end_data_segment)
		);
	return ret;
}

int mini_crt_heap_init()
{
	void* base = NULL;
	heap_header* header = NULL;
	unsigned heap_size =  1024 * 32;

	base = (void*)brk(0);
	void* end = ADDR_ADD(base, heap_size);
	end = (void*)brk(end);
	if(!end) return 0;


	header = (heap_header*)base;
	header->size = heap_size;
	header->type = HEAP_BLOCK_FREE;
	header->next = NULL;
	header->prev = NULL;
	
	list_head = header;
	return 1;
}
