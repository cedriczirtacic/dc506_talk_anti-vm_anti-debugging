#include "common.h"

#ifdef __APPLE__
extern void __attribute__ ((naked)) _start(void) 
{
    __asm__ __volatile__ ("nop");
}
#elif __linux__
extern unsigned char *_start;
extern unsigned char *__etext;
#endif

void more_evil_stuff(void)
{
    printf("EVIL DOINGS TO THE MAX!\n");
}


void do_evil_stuff(void)
{
    printf("EVIL DOINGS!\n");
    more_evil_stuff();
}

#ifdef __APPLE__
static void __attribute__ ((naked)) _end(void) 
{
    __asm__ __volatile__ ("nop");
}
#endif
int main(void)
{
#ifdef __APPLE__
    char *start = (char *)&_start;
    char *end = (char *)_end;
#elif __linux__
    char *start = (char *)_start;
    char *end = (char *)__etext;
#endif
    printf("start: %p\nend: %p\n\n", start, end);

    while (start != end) {
        if (((*(volatile unsigned *)start) & 0xff) == 0xcc)
            __exit();
        start++;
    }
    do_evil_stuff();

    return 0;
}

