#include "../include/woody.h"


void    change_values_dyns(Elf64_Dyn *dyns, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    int i, j;
    size_t offset;

    i = get_section_index(".dynamic", buf, sheaders, elfHeader);
    offset = sheaders[i].sh_offset;
    ft_print_hexa_raw(&(buf[offset]), 100);
    j = 0;
    while(j == 0 || dyns[j].d_tag != 0x0) {
        // if (dyns[j].d_un > offset_injection)
            // additionSurOctets(&(buf[offset + 0x08]), 8, CODE_SIZE);
        dyns[j] = fill_Elf64_Dyn_little(offset, buf);
        offset += sizeof(Elf64_Dyn);
        j++;
    }
}

void change_dynamic_offset(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    Elf64_Dyn *dyns;
    
    dyns = get_Elf64_Dyns_little(buf, sheaders, elfHeader);
    change_values_dyns(dyns, buf, sheaders, elfHeader);
}