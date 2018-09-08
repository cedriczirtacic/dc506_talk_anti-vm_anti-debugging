// XXX: https://linux.die.net/man/2/ptrace
#include "common.h"

static long __ptrace(int request, pid_t pid,
                   void *addr, void *data)
{
    long ret = 0;
    __asm__ volatile(
        "movq %4, %%r10\n\t"
#ifdef __APPLE__
        "movq $26, %%rax\n\t"
#elif __linux__
        "movq $101, %%rax\n\t"
#endif
        "syscall\n\t"
        "movq %%rax, %0"
        : "=r" (ret)
        : "D"(request), "S" (pid), "d"(addr), "g"(data)
    );
    return ret;
}

int main(void)
{
    if (__ptrace(0, 0, NULL, NULL) == -1) // 0 == PTRACE_TRACEME
        __exit();
    printf("Normal execution.\n");
    return 0;
}

