#include "../include/woody.h"


int woody(unsigned char *buf, size_t size) {
    struct ELFheaders64 file_header;
    struct sheaders64 *sheaders;
    int section_index = 0;

    file_header = get_elfHeader64_little_endian(buf);
    sheaders = get_section_headers_64(file_header, buf);
    if (!sheaders)
        return (1);
    section_index = get_section_index(SECTION, buf, sheaders, file_header);
    if (section_index == -1) {
        write(1, "Error: section not found\n", strlen("Error: section not found\n"));
        free(sheaders);
        return (1);
    }
    buf = change_buffer(buf, sheaders, section_index, file_header, size);
    write_file(buf, size + CODE_SIZE);
    return (0);
}

int main(int argc, char **argv) {
    int fd = -1;
    struct stat *buf = NULL;
    void *ptr = NULL;
    int res = 0;

    fd = get_fd(argc, argv, &buf);
    if (fd < 0) {
        if (buf) {
            free(buf);
        }
	    return (1);
    }
    ptr = ft_mmap(buf->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == NULL || S_ISREG(buf->st_mode) == 0) {
        perror("Error mmap");
        free(buf);
        return (1);
    }
    if (check_file(ptr, buf->st_size) != 0) {
        write(1, "Error: not a valid file\n", strlen("Error: not a valid file\n"));
        return (1);
    }
    res = woody(ptr, buf->st_size);
    munmap(ptr, buf->st_size);
    free(buf);
    return (res);
}