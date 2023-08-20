#include "../include/woody.h"

size_t get_symbol_header_offset(int index, struct ELFheaders64 elfHeader, struct sheaders64 *sheaders) {
    size_t begin = 0;
    size_t offset = 0;

    for (int i = 0; i < elfHeader.e_shnum; i++) {
        if (sheaders[i].sh_type == 0x02) {
            begin = sheaders[i].sh_offset;
            break;
        }
    }
    offset = begin + sizeof(struct Elf64_Sym) * index;
    return (offset);
}

void    change_symbole_size(char *sym, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    struct Elf64_Sym *syms;
    size_t size = 0;
    size_t offset;
    char *name;


    syms = get_syms_64(elfHeader, sheaders, buf, &size);
    for (size_t i = 0; i < size; i++) {
      if ((syms[i].st_name != 0 || i == 0)) {
        name = get_sym_name_64(buf, elfHeader, sheaders, syms[i].st_name);
        if (name && strcmp(name, sym) == 0) {
            offset = get_symbol_header_offset(i, elfHeader, sheaders);
            if (syms[i].st_value > offset_injection)
                additionSurOctets(&(buf[offset + 0x10]), 8, CODE_SIZE);

        }
        free(name);
      }
    }
    free(syms);
}