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

void    change_symboles_from_symtab(char *sym, int section_index, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    struct Elf64_Sym *syms;
    size_t size = 0;
    size_t offset;
    char *name;
    int index_sym = 0;


    syms = get_syms_64(elfHeader, sheaders, buf, &size);
    for (size_t i = 0; i < size; i++) {
      if ((syms[i].st_name != 0 || i == 0)) {
        name = get_sym_name_64(buf, elfHeader, sheaders, syms[i].st_name);
        if (name && strcmp(name, sym) == 0) {
            index_sym = i;
            offset = get_symbol_header_offset(i, elfHeader, sheaders);
            additionSurOctets(&(buf[offset + 0x10]), 8, CODE_SIZE);

        }
        else if (syms[i].st_shndx == section_index && i > (size_t)index_sym) {
            offset = get_symbol_header_offset(i, elfHeader, sheaders);
            additionSurOctets(&(buf[offset + 0x08]), 8, CODE_SIZE);
        }
        free(name);
      }
    }
    free(syms);
}

void change_symboles_from_dynsym(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader)  {
    struct Elf64_Sym sym;
    size_t offset;
    int i = 0;

    i = get_section_index(".dynsym", buf, sheaders, elfHeader);
    for (long unsigned int j = 0; j < sheaders[i].sh_size / sizeof(struct Elf64_Sym); j++) {
        offset = sheaders[i].sh_offset + sizeof(struct Elf64_Sym) * j;
        sym = fill_sym64_struct(offset, buf);
        char *name = get_dynsym_name_64(buf, elfHeader, sheaders, sym.st_name);
        printf("name = %s\n", name);
    }
}

void    change_symbole_size(char *sym, int section_index, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    change_symboles_from_symtab(sym, section_index, buf, sheaders, elfHeader);
    // change_symboles_from_dynsym(buf, sheaders, elfHeader);
}