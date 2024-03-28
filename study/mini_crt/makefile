


STATIC_SRC = malloc.c stdio.c string.c
STATIC_OBJ = $(patsubst %.c,%.o,$(STATIC_SRC))

CFLAGS =  -c -fno-builtin -nostdlib -fno-stack-protector  

static:
	gcc -g $(CFLAGS) $(STATIC_SRC) entry.c
	ar -rs minicrt.a $(STATIC_OBJ)
test:
	gcc -g $(CFLAGS) test.c
	ld -static  -e mini_crt_entry entry.o test.o minicrt.a -o test
all: static test

clean:
	rm -f *.o *.a  core* test1 test
