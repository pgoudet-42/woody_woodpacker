#include "../include/woody.h"


int woody(char *buf, size_t size) {
    struct ELFheaders64 elfHeader;
    struct sheaders64 *sheaders;
    int section_index = 0;

    elfHeader = get_elfHeader64_little_endian(buf);
    sheaders = get_section_headers_64(elfHeader, buf);
    if (!sheaders)
        return (1);
    section_index = change_offset_sections(buf, sheaders, elfHeader);
    if (section_index == -1) {
        free(sheaders);
        return (1);
    }
    write_file(buf, size, sheaders[section_index]);
    return (0);
}

int main(int argc, char **argv) {
    int fd = -1;
    struct stat *buf;
    void *ptr = NULL;

    fd = get_fd(argc, argv, &buf);
    if (fd  < 0) {
        free(buf);
	    return (1);
    }
    ptr = ft_mmap(buf->st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == NULL || S_ISREG(buf->st_mode) == 0) {
        perror("Error mmap");
        free(buf);
        return (1);
    }
    woody(ptr, buf->st_size);
    munmap(ptr, buf->st_size);
    free(buf);
    return (0);
}