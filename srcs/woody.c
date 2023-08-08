#include "../include/woody.h"


int main(int argc, char **argv) {
    int fd = -1;
    struct stat *buf;
    void *ptr = NULL;
    int res = 0;

    fd = get_fd(argc, argv, &buf);
    if (fd  < 0)
	return (1);
    ptr = ft_mmap(buf->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == NULL || S_ISREG(buf->st_mode) == 0) {
        write(1, "Error: Not a file\n", strlen("Error: Not a file\n"));
        free(buf);
        return (1);
    }
    return (0)
}