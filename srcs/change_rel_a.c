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