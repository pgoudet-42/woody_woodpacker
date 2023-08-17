#include "../include/woody.h"

#define NAME 0
#define TYPE 4
#define FLAGS 8
#define ADDR 16
#define OFFSET 24
#define SIZE 32
#define LINK 36
#define INFO 40
#define ALIGN 48
#define ENTSIZE 56


size_t offset_injection;

void    change_entry_point(unsigned char *buf, size_t new_entry_point) {
    buf[0x1f] = (unsigned char)(new_entry_point >> 56);
    buf[0x1e] = (unsigned char)(new_entry_point >> 48);
    buf[0x1d] = (unsigned char)(new_entry_point >> 40);
    buf[0x1c] = (unsigned char)(new_entry_point >> 32);
    buf[0x1b] = (unsigned char)(new_entry_point >> 24);
    buf[0x1a] = (unsigned char)(new_entry_point >> 16);
    buf[0x19] = (unsigned char)(new_entry_point >> 8);
    buf[0x18] = (unsigned char)(new_entry_point);
}

unsigned char *get_new_buff(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader, size_t file_size) {
    unsigned char *final = NULL;
    size_t opcode_index = 0;
    size_t size = 0;
    unsigned char code[] = {(unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90,\
    (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90,\
    (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90, (unsigned char)0x90,};

    size = calcul_file_size(buf, sheaders, elfHeader);
    final = malloc(size);
    if (!final)
        return (NULL);
    offset_injection = get_symbol_offset(buf, SYMBOL, elfHeader, sheaders);

    opcode_index = 2;
    if (opcode_index == 0 || offset_injection == (size_t)-1) {
        printf("Error: opcode or symbol not found\n");
        exit(1);
    }
    memncat(final, 0, buf, offset_injection + opcode_index);
    memncat(final, offset_injection + opcode_index, code, CODE_SIZE);
    memncat(final, offset_injection + opcode_index + CODE_SIZE, &(buf[offset_injection + opcode_index]), file_size - offset_injection - opcode_index);
    // change_entry_point(final, offset + opcode_index);
    return (final);
}

void change_rel_offset(unsigned char *buf, struct sheaders64 sheader, Elf64_Rel *rels) {
    int nb = 0;
    size_t offset;

    nb = sheader.sh_size / sizeof(Elf64_Rel);
    for (int j = 0; j < nb; j++) {
        offset = get_rel_a_offset(sheader, j, sizeof(Elf64_Rel));
        printf("j = %d\n", j);
        print_rel64(rels[j]);
        if (rels[j].r_offset > offset_injection)
            additionSurOctets(&(buf[offset]), 8, CODE_SIZE);
        rels[j] = get_rel64_little_endian(buf, sheader, j);
        print_rel64(rels[j]);
        printf("\n");
    }
}

void change_rela_offset(unsigned char *buf, struct sheaders64 sheader, Elf64_Rela *relas) {
    int nb = 0;
    size_t offset;

    nb = sheader.sh_size / sizeof(Elf64_Rela);
    for (int j = 0; j < nb; j++) {
        offset = get_rel_a_offset(sheader, j, sizeof(Elf64_Rela));
        printf("j = %d\n", j);
        print_rela64(relas[j]);
        if (relas[j].r_offset > offset_injection)
            additionSurOctets(&(buf[offset]), 8, CODE_SIZE);
        relas[j] = get_rela64_little_endian(buf, sheader, j);
        print_rela64(relas[j]);
        printf("\n");
    }
}

void     change_rela(unsigned char *buf,struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    char **rela_names;
    char **rel_names;
    Elf64_Rela *relas;
    Elf64_Rel *rels;

    rel_names = get_rel_sections_names(buf, sheaders, elfHeader);
    rela_names = get_rela_sections_names(buf, sheaders, elfHeader);

    for (int i = 0; i < elfHeader.e_shnum; i++) {
        char *name = get_section_name_64(buf, elfHeader, sheaders, sheaders[i].sh_name);
        if (ft_contains(name, rela_names) != -1){
            relas = get_relas(buf, sheaders[i]);
            change_rela_offset(buf, sheaders[i], relas);
            
        }
        else if (ft_contains(name, rel_names) != -1) {
            rels = get_rels(buf, sheaders[i]);
            change_rel_offset(buf, sheaders[i], rels);
        }
    }
}

unsigned char *change_buffer(unsigned char *buf, struct sheaders64 *sheaders, int section_index, struct ELFheaders64 elfHeader, size_t file_size) {
    struct pheaders64 *pheaders;

    pheaders = get_program_headers_64(elfHeader, buf);
    buf = get_new_buff(buf, sheaders, elfHeader, file_size);
    change_file_header(buf, &elfHeader, sheaders[section_index]);
    change_program_header(buf, pheaders, elfHeader);

    elfHeader = get_elfHeader64_little_endian(buf);
    change_sections_header_offset(buf, section_index, elfHeader);
    sheaders = get_section_headers_64(elfHeader, buf);
    change_symbole_size(SYMBOL, section_index, buf, sheaders, CODE_SIZE, elfHeader);
    change_rela(buf, sheaders, elfHeader);
    return (buf);
}