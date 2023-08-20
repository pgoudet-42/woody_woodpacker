#include "../include/woody.h"

int start_with(char *ref, char *str) {
    size_t len, i;

    len = (strlen(ref));
    if(!str)
        return (0);
    i = 0;
    while (i < len) {
        if (ref[i] != str[i])
            return (0);
        i++;
    }
    return (1);
}

char **get_rela_sections_names(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    char **names;
    int nb = 0;
    char *n = NULL;
    int j = 0;

    for (int i = 0; i < elfHeader.e_shnum; i++) {
        n = get_section_name_64(buf, elfHeader, sheaders, sheaders[i].sh_name);
        if (start_with(".rela.", n) != 0)
            nb++;
        free(n);
    }
    if (nb == 0)
        return (NULL);
    names = malloc((nb + 1) * sizeof(void *));
    if (!names) {
        perror("Error get_rel_names:");
        exit(1);
    }
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        n  = get_section_name_64(buf, elfHeader, sheaders, sheaders[i].sh_name);
        if (start_with(".rela.", n) != 0) {
            names[j] = ft_strdup(n);
            names[j++ + 1] = NULL;
        }
        free(n);
    }
    return (names);
}

char **get_rel_sections_names(unsigned char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    char **names;
    int nb = 0;
    char *n = NULL;

    for (int i = 0; i < elfHeader.e_shnum; i++) {
        n = get_section_name_64(buf, elfHeader, sheaders, sheaders[i].sh_name);
        if (start_with(".rel.", n) != 0)
            nb++;
        free(n);
    }
    if (nb == 0)
        return (NULL);
    names = malloc(nb * sizeof(char *));
    if (!names) {
        perror("Error get_rel_names:");
        exit(1);
    }
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        n  = get_section_name_64(buf, elfHeader, sheaders, sheaders[i].sh_name);
        if (start_with(".rel.", n) != 0) {
            names[i] = ft_strdup(n);
            names[i + 1] = NULL;
        }
        free(n);
    }
    return (names);
}

void change_rel_offset(unsigned char *buf, struct sheaders64 sheader, Elf64_Rel *rels) {
    int nb = 0;
    size_t offset;

    nb = sheader.sh_size / sizeof(Elf64_Rel);
    for (int j = 0; j < nb; j++) {
        offset = get_rel_a_offset(sheader, j, sizeof(Elf64_Rel));
        if (rels[j].r_offset > offset_injection)
            additionSurOctets(&(buf[offset]), 8, CODE_SIZE);
        rels[j] = get_rel64_little_endian(buf, sheader, j);
    }
}

void change_rela_offset(unsigned char *buf, struct sheaders64 sheader, Elf64_Rela *relas) {
    int nb = 0;
    size_t offset;

    nb = sheader.sh_size / sizeof(Elf64_Rela);
    for (int j = 0; j < nb; j++) {
        offset = get_rel_a_offset(sheader, j, sizeof(Elf64_Rela));
        if (relas[j].r_offset + relas[j].r_addend > offset_injection)
            additionSurOctets(&(buf[offset + 0x16]), 8, CODE_SIZE);
        relas[j] = get_rela64_little_endian(buf, sheader, j);
    }
}