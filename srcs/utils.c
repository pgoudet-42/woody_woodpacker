#include "../include/woody.h"

int open_file(char *path) {
    int fd = -1;
    
    fd = open(path, O_RDONLY);
    return (fd);
}

void    sort_tab(int **tab, size_t size) {
    int tmp = 0;

    for (size_t j = 0; j < size; j++) {
        for (size_t i = 0; i < size; i++) {
            if (i < size - 1) {
                if ((*tab)[i] > (*tab)[i + 1]) {
                    tmp = (*tab)[i];
                    (*tab)[i] = (*tab)[i + 1];
                    (*tab)[i + 1] = tmp;
                }
            }
        }
    }
}

void *ft_mmap(size_t lengthint, int prot, int flags, int fd, off_t offset) {
    char *buf = NULL;

    buf = mmap(NULL, lengthint, prot, flags, fd, offset);
    return (buf);
}