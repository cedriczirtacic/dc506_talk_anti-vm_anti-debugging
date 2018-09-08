// XXX: http://man7.org/linux/man-pages/man2/prctl.2.html
#include "common.h"

#ifdef __APPLE__
#warning "Not suitable for macOS. Skipping..."
int main(void){}
#else
static void __prctl(int option, unsigned long arg2, unsigned long arg3,
                    unsigned long arg4, unsigned long arg5)
{
    __asm__ volatile(
        "movq %4, %%r10\n\t"
        "movq $157, %%rax\n\t"
        "syscall\n\t"
        :
        : "D"(option), "S" (arg2), "c"(arg3), "d"(arg4), "g" (arg5)
    );
}
int main(void)
{
    __prctl(4, 0, 0, 0, 0); // 4 == PT_SET_DUMPABLE
/*
 * XXX: Also
 *  Processes that are not dumpable can not be attached via
 *  ptrace(2) PTRACE_ATTACH; see ptrace(2) for further details.
 */
    return 0;
}
#endif
