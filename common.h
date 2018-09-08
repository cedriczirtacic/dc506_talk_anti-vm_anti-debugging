#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void __exit(void)
{
    __asm__ (
#ifdef __APPLE__
            "movq $1, %rax\n\t"
#elif __linux__
            "movq $60, %rax\n\t"
#endif
            "xorq %rdi, %rdi\n\t"
            "incb %dil\n\t"
            "negb %dil\n\t"
            "syscall"
    );
}

