// XXX: https://en.wikipedia.org/wiki/CPUID
#include "common.h"

/* common vendors stolen from pafish */
// https://github.com/a0rtega/pafish/blob/master/pafish/cpu.c
char vendors[7][13] = {
    "XenVMMXenVMM", // Xen
    "Microsoft Hv", // Microsoft Hyper-V or Windows Virtual PC
    "prl hyperv  ", // Parallels
    "VBoxVBoxVBox", // Virtual Box
    "KVMKVMKVM\0\0\0", // KVM
    "VMwareVMware", // Vmware
    ""
};

void detected (void)
{
    printf("THIS IS A VM!! ABORT!!\n");
    exit(-1);
}

int main(void)
{
    unsigned int ebx, ecx, edx;
    __asm__ volatile (
            "movq $0, %%rax\n\t"
            "cpuid"
            : "=b"(ebx), "=c"(ecx), "=d"(edx)
            );

    void *vendor = malloc(13);
    memset(vendor, 0, 13);
    memcpy(vendor, (void *)&ebx, 4);
    memcpy(vendor+4, (void *)&ebx, 4);
    memcpy(vendor+8, (void *)&ebx, 4);
    printf("Vendor: %s\n", (char *)vendor);

    int i = 0;
    while (strcmp(vendors[i],"") != 0) {
        if ((strcmp(vendors[i++], (char *)vendor)) == 0) {
            detected();
        }
    }

    printf("Not a VM, huh? 3:)\n");

    free(vendor);
    
    return 0;
}

