#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
// #include "../libft/libft.h"


#ifndef FT_ELF_H
#define FT_ELF_H

struct ELFheaders64 {
    unsigned int ei_mag0;
    unsigned char ei_class;
    unsigned char ei_data;
    unsigned char ei_version;
    unsigned char ei_osabi;
    unsigned char ei_abiversion;
    unsigned char ei_pad[7];
    unsigned short int e_type;
    unsigned short int e_machine;
    unsigned int e_version;
    unsigned long int e_entry;
    unsigned long int e_phoff;
    unsigned long int e_shoff;
    unsigned int e_flags;
    unsigned short int e_ehsize;
    unsigned short int e_phentsize;
    unsigned short int e_phnum;
    unsigned short int e_shentsize;
    unsigned short int e_shnum;
    unsigned short int e_shstrndx;
};


struct pheaders64 {
    unsigned int p_type;
    unsigned int p_flags;
    unsigned long int p_offset;
    unsigned long int p_vaddr;
    unsigned long int p_paddr;
    unsigned long int p_filesz;
    unsigned long int p_memsz;
    unsigned long int p_align;
};

struct sheaders64 {
    unsigned int sh_name;
    unsigned int sh_type;
    unsigned long int sh_flags;
    unsigned long int sh_addr;
    unsigned long int sh_offset;
    unsigned long int sh_size;
    unsigned int sh_link;
    unsigned int sh_info;
    unsigned long int sh_addralign;
    unsigned long int sh_entsize;
};

struct Elf64_Sym {
	unsigned int	    st_name;
	unsigned char	    st_info;
	unsigned char	    st_other;
	unsigned short int	st_shndx;
	unsigned long int	st_value;
	unsigned long int	st_size;
};

struct sym_name {
    struct Elf64_Sym sym;
    char *name;
};

typedef struct {
        unsigned long int     r_offset;
        unsigned long int     r_info;
} Elf64_Rel;
 
typedef struct {
        unsigned long int   r_offset;
        unsigned long int   r_info;
        long int            r_addend;
} Elf64_Rela;

typedef struct {
        unsigned long int d_tag;
        long unsigned int d_un;
} Elf64_Dyn;

int                 get_file_info(int fd, struct stat *buf);
char                *get_dynsym_name_64(unsigned char *buf, struct ELFheaders64 elfHeader ,struct sheaders64 *sheaders, unsigned int name);
char                *get_sym_name_64(unsigned char *buf, struct ELFheaders64 elfHeader ,struct sheaders64 *sheaders, unsigned int name);
char                *get_sym_name_from_offset(unsigned char *buf, size_t offset, struct sheaders64 *sheaders, struct ELFheaders64 elfheader);
char                *get_section_name_64(unsigned char *buf, struct ELFheaders64 elfHeader ,struct sheaders64 *sheaders, unsigned int name);
struct sheaders64   *get_section_headers_64(unsigned char *buf, struct ELFheaders64 elfHeader);
struct Elf64_Sym    *get_syms_64(struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, unsigned char *buf, size_t *size);
struct Elf64_Sym    get_sym_by_name(char *name, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfheader);
struct sym_name     *get_sys_tab_64(struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, unsigned char *buf, int *j);
struct pheaders64   *get_program_headers_64(unsigned char *buf, struct ELFheaders64 elfHeader);
int                 get_section_index(char *section, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 file_header);
size_t              get_program_header_offset(int index, struct ELFheaders64 file_header);
size_t              get_section_header_offset(int index, struct ELFheaders64 file_header);
size_t              get_symbol_offset(unsigned char *buf, char *sym, struct ELFheaders64 elfHeader, struct sheaders64 *sheaders);

struct ELFheaders64 get_elfHeader64_little_endian(unsigned char *buf);
struct pheaders64   get_pHeader64_little_endian(unsigned char *buf, struct ELFheaders64 *elfHeader, int nb);
struct sheaders64   get_sHeader64_little_endian(unsigned char *buf, struct ELFheaders64 *elfHeader, int nb);
struct Elf64_Sym    fill_sym64_struct(size_t offset, unsigned char *buf);
struct Elf64_Sym    get_sym64_section_little(unsigned char *buf, struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, int i);
Elf64_Rela          get_rela64_little_endian(unsigned char *buf, struct sheaders64 sheader, int i);
Elf64_Rel           get_rel64_little_endian(unsigned char *buf, struct sheaders64 sheader, int i);
int                 get_rel_as_count(unsigned char *buf, char *section_name, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader, unsigned long size_of_struct);
size_t              get_rel_a_offset(struct sheaders64 sheader, int i, unsigned long size_of_struct);
Elf64_Rela          *get_relas(unsigned char *buf, struct sheaders64 sheader);
Elf64_Rel           *get_rels(unsigned char *buf, struct sheaders64 sheader);
Elf64_Dyn           fill_Elf64_Dyn_little(size_t offset, unsigned char *buf);
Elf64_Dyn           *get_Elf64_Dyns_little(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader);

size_t              calcul_file_size(size_t code_size, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader);
unsigned long int   find_p_align(struct pheaders64 ph);

#endif