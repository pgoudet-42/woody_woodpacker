#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <string.h>

#ifndef WOODY_H
#define WOODY_H

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

char *toBinary(int n, int len);
void ft_print_stat(struct stat *buf);
void print_elf64_sym(struct Elf64_Sym sym);
void ft_print_hexa_raw(char *buf, size_t len);
void print_pHeader64(struct pheaders64 pheader);
void print_sHeader64(struct sheaders64 sheader);
void print_elfHeader64(struct ELFheaders64 elfHeader);
void print_sections_names(struct sheaders64 *sheaders, char *buf, struct ELFheaders64 elfheader);

int get_file_info(int fd, struct stat *buf);
char *get_sym_name_64(char *buf, struct ELFheaders64 elfHeader ,struct sheaders64 *sheaders, unsigned int name);
char *get_section_name_64(char *buf, struct ELFheaders64 elfHeader ,struct sheaders64 *sheaders, unsigned int name);
struct sheaders64 *get_string_offsets_64(struct ELFheaders64 elfHeader, char *buf);
struct Elf64_Sym *get_syms_64(struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, char *buf, size_t *size);
struct sym_name *get_sys_tab_64(struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, char *buf, int *j);

struct ELFheaders64 get_elfHeader64_little_endian(char *buf);
struct pheaders64 get_pHeader64_little_endian(char *buf, struct ELFheaders64 *elfHeader);
struct sheaders64 get_sHeaders64_little_endian(char *buf, struct ELFheaders64 *elfHeader, int nb);
struct Elf64_Sym get_sym64_section_little(char *buf, struct ELFheaders64 elfHeader, struct sheaders64 *sheaders, int i);


int open_file(char *path);
void sort_tab(int **tab, size_t size);
void *ft_mmap(size_t lengthint, int prot, int flags, int fd, off_t offset);


#endif