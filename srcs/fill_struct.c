#include "../include/woody.h"

struct ELFheaders64 get_elfHeader64_little_endian(char *buf) {
    struct ELFheaders64 elfHeader;

    elfHeader.ei_mag0 = ((unsigned char)buf[0x0]) + ((unsigned char)buf[0x1] << 8) + ((unsigned char)buf[0x2] << 16) + ((unsigned char)buf[0x3] << 24);
    elfHeader.ei_class = buf[0x04];
    elfHeader.ei_data = buf[0x05];
    elfHeader.ei_version = buf[0x06];
    elfHeader.ei_osabi = buf[0x07];
    elfHeader.ei_abiversion = buf[0x08];
    elfHeader.ei_pad[0] = buf[0x09];
    elfHeader.ei_pad[1] = buf[0x0a];
    elfHeader.ei_pad[2] = buf[0x0b];
    elfHeader.ei_pad[3] = buf[0x0c];
    elfHeader.ei_pad[4] = buf[0x0d];
    elfHeader.ei_pad[5] = buf[0x0e];
    elfHeader.ei_pad[6] = buf[0x0f];
    elfHeader.e_type = ((unsigned char)buf[0x10]) + ((unsigned char)buf[0x11] << 8);
    elfHeader.e_machine = ((unsigned char)buf[0x12]) + ((unsigned char)buf[0x13] << 8);
    elfHeader.e_version = ((unsigned char)buf[0x14]) + ((unsigned char)buf[0x15] << 8) + ((unsigned char)buf[0x16] << 16) + ((unsigned char)buf[0x17] << 24);
    elfHeader.e_entry = ((unsigned char)buf[0x18]) + ((unsigned char)buf[0x19] << 8) + ((unsigned char)buf[0x1a] << 16) + ((unsigned char)buf[0x1b] << 24) + ((unsigned long)buf[0x1c] << 32) + ((unsigned long)buf[0x1d] << 40) + ((unsigned long)buf[0x1e] << 48) + ((unsigned long)buf[0x1f] << 56);
    elfHeader.e_phoff = ((unsigned char)buf[0x20]) + ((unsigned char)buf[0x21] << 8) + ((unsigned char)buf[0x22] << 16) + ((unsigned char)buf[0x23] << 24) + ((unsigned long)buf[0x24] << 32) + ((unsigned long)buf[0x25] << 40) + ((unsigned long)buf[0x26] << 48) + ((unsigned long)buf[0x27] << 56);
    elfHeader.e_shoff = ((unsigned char)buf[0x28]) + ((unsigned char)buf[0x29] << 8) + ((unsigned char)buf[0x2a] << 16) + ((unsigned char)buf[0x2b] << 24) + ((unsigned long)buf[0x2c] << 32) + ((unsigned long)buf[0x2d] << 40) + ((unsigned long)buf[0x2e] << 48) + ((unsigned long)buf[0x2f] << 56);
    elfHeader.e_flags = ((unsigned char)buf[0x30]) + ((unsigned char)buf[0x31] << 8) + ((unsigned char)buf[0x32] << 16) + ((unsigned char)buf[0x33] << 24);
    elfHeader.e_ehsize = ((unsigned char)buf[0x34]) + ((unsigned char)buf[0x35] << 8);
    elfHeader.e_phentsize = ((unsigned char)buf[0x36]) + ((unsigned char)buf[0x37] << 8);
    elfHeader.e_phnum = ((unsigned char)buf[0x38]) + ((unsigned char)buf[0x39] << 8);
    elfHeader.e_shentsize = ((unsigned char)buf[0x3a]) + ((unsigned char)buf[0x3b] << 8);
    elfHeader.e_shnum = ((unsigned char)buf[0x3c]) + ((unsigned char)buf[0x3d] << 8);
    elfHeader.e_shstrndx = ((unsigned char)buf[0x3e]) + ((unsigned char)buf[0x3f] << 8);

    return (elfHeader);
}


struct pheaders64 get_pHeader64_little_endian(char *buf, struct ELFheaders64 *elfHeader) {
    struct pheaders64 pheader;
    size_t offset;

    offset = elfHeader->e_phoff;
    memset(&pheader, 0, sizeof(struct pheaders64));
    if (offset < 0x40)
        return (pheader);
    
    pheader.p_type = ((unsigned char)buf[offset + 0x00]) + ((unsigned char)buf[offset + 0x01] << 8) + ((unsigned char)buf[offset + 0x02] << 16) + ((unsigned char)buf[offset + 0x03] << 24);
    pheader.p_flags = ((unsigned char)buf[offset + 0x04]) + ((unsigned char)buf[offset + 0x05] << 8) + ((unsigned char)buf[offset + 0x06] << 16) + ((unsigned char)buf[offset + 0x07] << 24);
    pheader.p_offset = ((unsigned char)buf[offset + 0x08]) + ((unsigned char)buf[offset + 0x09] << 8) + ((unsigned char)buf[offset + 0x0a] << 16) + ((unsigned char)buf[offset + 0x0b] << 24) +\
    ((unsigned long)buf[offset + 0x0c] << 32) + ((unsigned long)buf[offset + 0x0d] << 40) + ((unsigned long)buf[offset + 0x0e] << 48) + ((unsigned long)buf[offset + 0x0f] << 56); 
    pheader.p_vaddr = ((unsigned char)buf[offset + 0x10]) + ((unsigned char)buf[offset + 0x11] << 8) + ((unsigned char)buf[offset + 0x12] << 16) + ((unsigned char)buf[offset + 0x13] << 24) +\
    ((unsigned long)buf[offset + 0x14] << 32) + ((unsigned long)buf[offset + 0x15] << 40) + ((unsigned long)buf[offset + 0x16] << 48) + ((unsigned long)buf[offset + 0x17] << 56); 
    pheader.p_paddr = ((unsigned char)buf[offset + 0x18]) + ((unsigned char)buf[offset + 0x19] << 8) + ((unsigned char)buf[offset + 0x1a] << 16) + ((unsigned char)buf[offset + 0x1b] << 24) +\
    ((unsigned long)buf[offset + 0x1c] << 32) + ((unsigned long)buf[offset + 0x1d] << 40) + ((unsigned long)buf[offset + 0x1e] << 48) + ((unsigned long)buf[offset + 0x1f] << 56); 
    pheader.p_filesz = ((unsigned char)buf[offset + 0x20]) + ((unsigned char)buf[offset + 0x21] << 8) + ((unsigned char)buf[offset + 0x22] << 16) + ((unsigned char)buf[offset + 0x23] << 24) +\
    ((unsigned long)buf[offset + 0x24] << 32) + ((unsigned long)buf[offset + 0x25] << 40) + ((unsigned long)buf[offset + 0x26] << 48) + ((unsigned long)buf[offset + 0x27] << 56); 
    pheader.p_memsz = ((unsigned char)buf[offset + 0x28]) + ((unsigned char)buf[offset + 0x29] << 8) + ((unsigned char)buf[offset + 0x2a] << 16) + ((unsigned char)buf[offset + 0x2b] << 24) +\
    ((unsigned long)buf[offset + 0x2c] << 32) + ((unsigned long)buf[offset + 0x2d] << 40) + ((unsigned long)buf[offset + 0x2e] << 48) + ((unsigned long)buf[offset + 0x2f] << 56); 
    pheader.p_flags = ((unsigned char)buf[offset + 0x30]) + ((unsigned char)buf[offset + 0x31] << 8) + ((unsigned char)buf[offset + 0x32] << 16) + ((unsigned char)buf[offset + 0x33] << 24) +\
    ((unsigned long)buf[offset + 0x34] << 32) + ((unsigned long)buf[offset + 0x35] << 40) + ((unsigned long)buf[offset + 0x36] << 48) + ((unsigned long)buf[offset + 0x37] << 56); 
    pheader.p_align = ((unsigned char)buf[offset + 0x38]) + ((unsigned char)buf[offset + 0x39] << 8) + ((unsigned char)buf[offset + 0x3a] << 16) + ((unsigned char)buf[offset + 0x3b] << 24) +\
    ((unsigned long)buf[offset + 0x3c] << 32) + ((unsigned long)buf[offset + 0x3d] << 40) + ((unsigned long)buf[offset + 0x3e] << 48) + ((unsigned long)buf[offset + 0x3f] << 56); 

    return (pheader);
}

struct sheaders64 get_sHeader64_little_endian(char *buf, struct ELFheaders64 *elfHeader, int nb) {
    struct sheaders64 sheader;
    size_t offset;

    offset = elfHeader->e_shoff + elfHeader->e_shentsize * nb;
    memset(&sheader, 0, sizeof(struct sheaders64));
    if (offset < 0x40)
        return (sheader);


    sheader.sh_name = ((unsigned char)buf[offset + 0x00]) + ((unsigned char)buf[offset + 0x01] << 8) + ((unsigned char)buf[offset + 0x02] << 16) + ((unsigned char)buf[offset + 0x03] << 24);
    sheader.sh_type = ((unsigned char)buf[offset + 0x04]) + ((unsigned char)buf[offset + 0x05] << 8) + ((unsigned char)buf[offset + 0x06] << 16) + ((unsigned char)buf[offset + 0x07] << 24);

    sheader.sh_flags = ((unsigned char)buf[offset + 0x08]) + ((unsigned char)buf[offset + 0x09] << 8) + ((unsigned char)buf[offset + 0x0a] << 16) + ((unsigned char)buf[offset + 0x0b] << 24) +\
    ((unsigned long)buf[offset + 0x0c] << 32) + ((unsigned long)buf[offset + 0x0d] << 40) + ((unsigned long)buf[offset + 0x0e] << 48) + ((unsigned long)buf[offset + 0x0f] << 56);

    sheader.sh_addr = ((unsigned char)buf[offset + 0x10]) + ((unsigned char)buf[offset + 0x11] << 8) + ((unsigned char)buf[offset + 0x12] << 16) + ((unsigned char)buf[offset + 0x13] << 24) +\
    ((unsigned long)buf[offset + 0x14] << 32) + ((unsigned long)buf[offset + 0x15] << 40) + ((unsigned long)buf[offset + 0x16] << 48) + ((unsigned long)buf[offset + 0x17] << 56);

    sheader.sh_offset = ((unsigned char)buf[offset + 0x18]) + ((unsigned char)buf[offset + 0x19] << 8) + ((unsigned char)buf[offset + 0x1a] << 16) + ((unsigned char)buf[offset + 0x1b] << 24) +\
    ((unsigned long)buf[offset + 0x1c] << 32) + ((unsigned long)buf[offset + 0x1d] << 40) + ((unsigned long)buf[offset + 0x1e] << 48) + ((unsigned long)buf[offset + 0x1f] << 56); 

    sheader.sh_size = ((unsigned char)buf[offset + 0x20]) + ((unsigned char)buf[offset + 0x21] << 8) + ((unsigned char)buf[offset + 0x22] << 16) + ((unsigned char)buf[offset + 0x23] << 24) +\
    ((unsigned long)buf[offset + 0x24] << 32) + ((unsigned long)buf[offset + 0x25] << 40) + ((unsigned long)buf[offset + 0x26] << 48) + ((unsigned long)buf[offset + 0x27] << 56);

    sheader.sh_link = ((unsigned char)buf[offset + 0x28]) + ((unsigned char)buf[offset + 0x29] << 8) + ((unsigned char)buf[offset + 0x2a] << 16) + ((unsigned char)buf[offset + 0x2b] << 24);
    sheader.sh_info = ((unsigned char)buf[offset + 0x2c]) + ((unsigned char)buf[offset + 0x2d] << 8) + ((unsigned char)buf[offset + 0x2e] << 16) + ((unsigned char)buf[offset + 0x2f] << 24);

    sheader.sh_addralign = ((unsigned char)buf[offset + 0x30]) + ((unsigned char)buf[offset + 0x31] << 8) + ((unsigned char)buf[offset + 0x32] << 16) + ((unsigned char)buf[offset + 0x33] << 24) +\
    ((unsigned long)buf[offset + 0x34] << 32) + ((unsigned long)buf[offset + 0x35] << 40) + ((unsigned long)buf[offset + 0x36] << 48) + ((unsigned long)buf[offset + 0x37] << 56); 

    sheader.sh_entsize = ((unsigned char)buf[offset + 0x38]) + ((unsigned char)buf[offset + 0x39] << 8) + ((unsigned char)buf[offset + 0x3a] << 16) + ((unsigned char)buf[offset + 0x3b] << 24) +\
    ((unsigned long)buf[offset + 0x3c] << 32) + ((unsigned long)buf[offset + 0x3d] << 40) + ((unsigned long)buf[offset + 0x3e] << 48) + ((unsigned long)buf[offset + 0x3f] << 56); 


    return (sheader);
}

struct Elf64_Sym get_sym64_section_little(char *buf, struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, int i) {
    struct Elf64_Sym sym;
    size_t offset = 0;
    size_t begin = 0;

    for (int i = 0; i < elfHeader.e_shnum; i++) {
        if (sheaders[i].sh_type == 0x02) {
            begin = sheaders[i].sh_offset;
            break;
        }
    }

    memset(&sym, 0, sizeof(struct Elf64_Sym));
    offset = begin + sizeof(struct Elf64_Sym) * i;
    sym.st_name = ((unsigned char)buf[offset + 0x00]) + ((unsigned char)buf[offset + 0x01] << 8) + ((unsigned char)buf[offset + 0x02] << 16) + ((unsigned char)buf[offset + 0x03] << 24);
    sym.st_info = (unsigned char)buf[offset + 0x04];
    sym.st_other = (unsigned char)buf[offset + 0x05];
    sym.st_shndx = ((unsigned char)buf[offset + 0x06]) + ((unsigned char)buf[offset + 0x07] << 8);
    sym.st_value =  ((unsigned char)buf[offset + 0x08]) + ((unsigned char)buf[offset + 0x09] << 8) + ((unsigned char)buf[offset + 0x0a] << 16) + ((unsigned char)buf[offset + 0x0b] << 24) +\
    ((unsigned long)buf[offset + 0x0c] << 32) + ((unsigned long)buf[offset + 0x0d] << 40) + ((unsigned long)buf[offset + 0x0e] << 48) + ((unsigned long)buf[offset + 0x0f] << 56);
    sym.st_size = ((unsigned char)buf[offset + 0x10]) + ((unsigned char)buf[offset + 0x11] << 8) + ((unsigned char)buf[offset + 0x12] << 16) + ((unsigned char)buf[offset + 0x13] << 24) +\
    ((unsigned long)buf[offset + 0x14] << 32) + ((unsigned long)buf[offset + 0x15] << 40) + ((unsigned long)buf[offset + 0x16] << 48) + ((unsigned long)buf[offset + 0x17] << 56);
    return (sym);
}
