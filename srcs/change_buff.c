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

int find_offset_nentry_oentry(size_t oep, size_t nep) {
    int offset = 0xFFFFFFFF;
    int diff;

    diff = oep < nep ? (int)(nep - oep) : (int)(oep - nep);
    offset = offset - diff;
    return (offset + 1);
}

void    cpy_mem_little(unsigned char *code, int offset) {
    code[0] = offset >> 0;
    code[1] = offset >> 8;
    code[2] = offset >> 16;
    code[3] = offset >> 24;
}

void    change_entry_point(unsigned char *buf, size_t new_entry_point) {
    buf[0x1f] = new_entry_point >> 56;
    buf[0x1e] = new_entry_point >> 48;
    buf[0x1d] = new_entry_point >> 40;
    buf[0x1c] = new_entry_point >> 32;
    buf[0x1b] = new_entry_point >> 24;
    buf[0x1a] = new_entry_point >> 16;
    buf[0x19] = new_entry_point >> 8;
    buf[0x18] = new_entry_point;
}

unsigned char *get_new_buff(unsigned char *buf, struct ELFheaders64 elfHeader, size_t file_size) {
    int offset;
    unsigned char *final = NULL;
    unsigned char code[] = {0x90U, 0x90U, 0x90U, 0x90U, 0x90U,\
                            0x90U, 0x90U, 0x90U, 0x90U, 0x90U, 0x90U,\
                            0xE9U, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

    offset_injection = 0x000000000000115d;
    offset = find_offset_nentry_oentry(elfHeader.e_entry, 0x115dUL + CODE_SIZE);
    cpy_mem_little(&(code[CODE_SIZE - 4]), offset);

    final = malloc(file_size);
    if (!final)
        return (NULL);
    memncat(final, 0, buf, offset_injection);
    memncat(final, offset_injection, code, CODE_SIZE);
    memncat(final, offset_injection + CODE_SIZE, &(buf[offset_injection + CODE_SIZE]), file_size - offset_injection - CODE_SIZE);
    change_entry_point(final, offset_injection);
    return (final);
}


unsigned char *change_buffer(unsigned char *buf, struct ELFheaders64 elfHeader, size_t file_size) {
    struct pheaders64 *pheaders;
    struct sheaders64 *sheaders;
    char *sym_name;

    pheaders = get_program_headers_64(buf, elfHeader);
    buf = get_new_buff(buf, elfHeader, file_size);
    elfHeader = get_elfHeader64_little_endian(buf);
    change_program_header(buf, pheaders, elfHeader);

    change_sections_header_offset(buf, elfHeader);
    sheaders = get_section_headers_64(buf, elfHeader);
    sym_name = get_sym_name_from_offset(buf, offset_injection, sheaders, elfHeader);
    if (sym_name)
        change_symbole_size(sym_name, buf, sheaders, elfHeader);
    free(sym_name);
    return (buf);
}