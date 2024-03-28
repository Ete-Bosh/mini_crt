# Mini_crt
It is a tiny implemetation of C runtime library for 64-bit Linux in *程序员的自我修养--链接、装载与库 (chapter 13.1)*, and it is programmed on Ubuntu 20.04.6 LTS (GNU/Linux 5.4.0-153-generic x86_64).
It does **not** support Windows or 32-bit Linux.

All system calls are implemeted by assembly: asm(""::).

### entry.c
It calculates the `argc` and `argv`, and passes them to `main()`.

### malloc.c
It provides `malloc` and `free` by `sys_brk()`. It uses a linklist of `struct heap_header` to manage space.

### stdio.c
It provieds fundamental file operations like `fopen`, `fclose`,`fwrite`, `fread`, `fseek`.

### string.c
It provids fundamental string operations like 'strcpy', 'strcmp', 'strlen'.


Build
---
```
$ cd study/mini_crt
$ make all
$ ./test {argc1} {argc2} ...
$ cat ./test1
$ make clean
```
Others
---
The original codes in the book can **not** run on 64-bit Linux. 
1.I change the assembly code for 64-bit, like "movl %%eax" ->"movq %%rax". 
2.All address-related or assembly-related variables should fit for 64-bit OS.
3.In the test.c, we need to use `malloc` for the integer `len`.Otherwise, it will not work on writing a integer in the file.

This is the [question](https://stackoverflow.com/questions/78215186/when-i-assigned-a-static-global-pointer-segmentation-fault-occurred?noredirect=1#comment137895688_78215186) I asked when I tried to implement malloc.c. 
