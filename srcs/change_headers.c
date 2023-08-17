#include "../include/woody.h"

void change_file_header(unsigned char *buf, struct ELFheaders64 *file_header, struct sheaders64 section_hd) {
    if ((size_t)file_header->e_shoff > section_hd.sh_offset) {
        additionSurOctets(&(buf[0x28]), 2, CODE_SIZE);
        if (file_header->e_shstrndx > section_hd.sh_offset)
            additionSurOctets(&(buf[0x3E]), 2, CODE_SIZE);
    }
    else
        dprintf(1, "section_offset = %ld file_header->e_shoff = %ld\n", section_hd.sh_offset, file_header->e_shoff);
}

void    change_program_offset(unsigned char *buf, struct ELFheaders64 file_header) {
    size_t offset = 0;

    for (int i = 0; i < file_header.e_phnum; i++) {
        offset = get_program_header_offset(i, file_header);
        additionSurOctets(&(buf[offset + 0x08]), 8, CODE_SIZE);
    }
}

void    change_program_header_offsets(unsigned char *buf, int ph_index, struct ELFheaders64 file_header, unsigned char is_exec_seg, struct pheaders64 *pheaders) {
    size_t offset;
    unsigned long int align = 0;

    offset = get_program_header_offset(ph_index, file_header);
    if (pheaders[ph_index].p_offset > file_header.e_entry || is_exec_seg) {
        if (is_exec_seg) {
            additionSurOctets(&(buf[offset + 0x20]), 8, CODE_SIZE);
            additionSurOctets(&(buf[offset + 0x28]), 8, CODE_SIZE);
        }
        else {
            additionSurOctets(&(buf[offset + 0x08]), 8, CODE_SIZE);
            additionSurOctets(&(buf[offset + 0x10]), 8, CODE_SIZE);
            additionSurOctets(&(buf[offset + 0x18]), 8, CODE_SIZE);
        }
        align = find_p_align(pheaders[ph_index]);
        memcpy(&(buf[offset + 0x30]), &align, 8);
    }
}

void    change_program_header(unsigned char *buf, struct pheaders64 *pheaders, struct ELFheaders64 elfHeader) {
    unsigned char is_exec_seg = 0;        
    
    for (int i = 0; i < elfHeader.e_phnum; i++) {
        if (pheaders[i].p_type == 0x00000001) {
            if (elfHeader.e_entry >= pheaders[i].p_vaddr && elfHeader.e_entry < (pheaders[i].p_vaddr + pheaders[i].p_memsz)) {
                if (pheaders[i].p_flags & 0x01)
                    is_exec_seg = 1;
            }
        }
        change_program_header_offsets(buf, i, elfHeader, is_exec_seg, pheaders);
        is_exec_seg = 0;
    }
}

void    change_sections_header_offset(unsigned char *buf, int section_index, struct ELFheaders64 file_header) {
    size_t offset = 0;

    for (int i = section_index; i < file_header.e_shnum; i++) {
        offset = get_section_header_offset(i, file_header);
        if (i == section_index) {
            additionSurOctets(&(buf[offset + 0x20]), 8, CODE_SIZE);
        }
        else {
            additionSurOctets(&(buf[offset + 0x10]), 8, CODE_SIZE);
            additionSurOctets(&(buf[offset + 0x18]), 8, CODE_SIZE);
        }
    }
}