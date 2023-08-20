#include "../include/woody.h"


void    change_values_dyns(Elf64_Dyn *dyns, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    int i, j;
    size_t offset;
    long unsigned int ptr_val[30] = {3, 4, 5,6 ,7, 12, 13, 17, 21, 23, 25, 26, 32, 0x6000000d, 0x6000000e, \
                                        0x6000000f, 0x60000010, 0x60000011, 0x60000014, 0x60000016, 0x60000018,\
                                        0x6000001a, 0x6ffffefa, 0x6ffffefb, 0x6ffffefc, 0x6ffffefd, 0x6ffffefe,\
                                        0x6ffffeff, 0x6ffffffc, 0x6ffffffe};

    i = get_section_index(".dynamic", buf, sheaders, elfHeader);
    offset = sheaders[i].sh_offset;
    // ft_print_hexa_raw(&(buf[offset]), 100);
    j = 0;
    while(j == 0 || dyns[j].d_tag != 0x0) {
        dyns[j] = fill_Elf64_Dyn_little(offset, buf);
        if (is_in_luint_table(dyns[j].d_tag, ptr_val, 30) == 1)
            if (dyns[j].d_un > offset_injection)
                additionSurOctets(&(buf[offset + 0x08]), 8, CODE_SIZE);
        offset += sizeof(Elf64_Dyn);
        j++;
    }
}

void change_dynamic_offset(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    Elf64_Dyn *dyns;
    
    dyns = get_Elf64_Dyns_little(buf, sheaders, elfHeader);
    change_values_dyns(dyns, buf, sheaders, elfHeader);
}