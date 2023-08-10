#include "../include/woody.h"

int open_file(char *path) {
    int fd = -1;
    
    fd = open(path, O_RDWR);
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

int get_fd(int argc, char **argv, struct stat **buf) {
    int fd;

    if (argc == 1)
        argv[1] = "./a.out";
    fd = open_file(argv[1]);
    if (fd == -1) {
        write(1, "Error: file opening failed\n", strlen("Error: file opening failed\n"));
        return (-1);
    }
    *buf = malloc(sizeof(struct stat));
    if (*buf == NULL)
        return(-1);
    if (get_file_info(fd, *buf) == -1) {
        write(1, "Error: fstat failed on file\n", strlen("Error: fstat failed on file\n"));
        return (-1);
    }
    return (fd);
}

int memncat(void *src, size_t index, void *dst, size_t n) {
    size_t i = -1;
    
    while (++i < n)
        ((unsigned char *)src)[index + i] = ((unsigned char *)dst)[i];
    return (0);
}