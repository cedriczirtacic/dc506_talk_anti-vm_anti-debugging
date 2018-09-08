#include "common.h"

#ifdef __APPLE__
#warning "Not suitable for macOS. Skipping..."
int main(void){}
#else
const char *cpuinfo_path = "/proc/cpuinfo";
const char *cpuinfo_flag = "hypervisor";

int main(void)
{
    FILE *fd = fopen(cpuinfo_path, "r");
    if (fd == NULL)
        goto bail;

    char *l = NULL;
    size_t ln =  0;
    while (getline(&l, &ln, fd) != -1) {
        // check if is the flag line
        char *lptr = l;
        if (*lptr != 'f')
            continue;
        while (*lptr != '\n' && *lptr != '\0' && *lptr != ' ' &&
               *lptr != '\t')
            lptr++;
        *lptr = '\0';

        if (strcmp(l, "flags") == 0)
            // found it, now look for the flag
            lptr++;
            while (*lptr != '\n' && *lptr != '\0') {
                if (*lptr == cpuinfo_flag[0]) {
                    char *cptr = lptr;
                    const char *fptr = cpuinfo_flag;

                    while (*cptr != ' ' && *cptr != '\n' ) {
                        cptr++;
                        fptr++;
                        if (*fptr == '\0' && (*cptr == '\n' || *cptr == ' ')) {
                            printf("FUCK! IS A VM!\n");
                            exit(-1);
                        }
                    } 
                }
                lptr++;
            }
    }

printf("Not a VM!... Time for some business... :}\n");

bail:
    if (fd != NULL)
        fclose(fd);
    return 0;
}
#endif
