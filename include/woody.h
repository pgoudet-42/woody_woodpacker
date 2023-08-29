#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../libelf/ft_elf.h"
#include "../libft/libft.h"

#ifndef WOODY_H
#define WOODY_H

extern unsigned char code[];



struct crypt_res {
    unsigned char *data;
    char *key;
    size_t len;
};



struct code {
    size_t offset_injection;
    size_t key_size;
    unsigned char *key;
    size_t code_size;
    unsigned char *code;
};

extern struct code glob_code;


char                *toBinary(int n, int len);
void                ft_print_stat(struct stat *buf);
void                print_elf64_sym(struct Elf64_Sym sym);
void                ft_print_hexa_raw(unsigned char *buf, size_t len);
void                print_pHeader64(struct pheaders64 pheader);
void                print_sHeader64(struct sheaders64 sheader);
void                print_elfHeader64(struct ELFheaders64 elfHeader);
void                print_sections_names(struct sheaders64 *sheaders, unsigned char *buf, struct ELFheaders64 elfheader);
void                print_rela64(Elf64_Rela rela);
void                print_rel64(Elf64_Rel rel);
void                print_Elf64_Dyn(Elf64_Dyn dyn);



int                 open_file(char *path);
void                sort_tab(int **tab, size_t size);
void                *ft_mmap(size_t lengthint, int prot, int flags, int fd, off_t offset);
int                 get_fd(int argc, char **argv, struct stat **buf);
int                 memncat(void *src, size_t index, void *dst, size_t n);
int                 check_file(unsigned char *buf, size_t size);
size_t              find_opcode(unsigned char *buf, size_t size, unsigned char *opcodes, size_t size_opcodes, int num);
void                additionSurOctets(unsigned char *buffer, size_t taille, unsigned int nombre);
int                 is_in_luint_table(long unsigned int wanted, long unsigned int *table, size_t size);

unsigned char       *encrypt_b64(unsigned char *buf, size_t size);
unsigned char       *decrypt_b64(unsigned char *buf, size_t size);

unsigned char       *generate_random_key(size_t len);
void                apply_xor(unsigned char *buf, size_t len, char *key);


int                 write_file(unsigned char *buf, size_t size);

unsigned char       *change_buffer(struct code *code, unsigned char *buf, struct ELFheaders64 file_header, size_t file_size);
int                 get_section_index(char *section, unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 file_header);

void                change_symbole_size(size_t offset_injection, size_t code_size, char *sym, unsigned char *buf);

void                change_sections_header_offset(size_t size, size_t offset_injection, unsigned char *buf, struct ELFheaders64 elfheader);
void                change_program_header(size_t size, unsigned char *buf, struct pheaders64 *pheaders, struct ELFheaders64 elfHeader);
void                change_program_offset(size_t size, unsigned char *buf, struct ELFheaders64 file_header);
void                change_file_header(size_t size, unsigned char *buf, struct ELFheaders64 *file_header, struct sheaders64 section_hd);

char                **get_rel_sections_names(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader);
char                **get_rela_sections_names(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader);
void                change_rela_offset(unsigned char *buf, struct sheaders64 sheader, Elf64_Rela *relas);
void                change_rel_offset(unsigned char *buf, struct sheaders64 sheader, Elf64_Rel *rels);

void                change_dynamic_offset(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader);

unsigned char       *get_code(size_t *size);

#endif