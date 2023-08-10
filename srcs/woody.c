#include "../include/woody.h"

size_t get_section_offset(char *section, char *buf, struct sheaders64 *sheaders, struct ELFheaders64 elfHeader) {
    int i = 0;
    char *name = NULL;

    while(i < elfHeader.e_shnum) {
        name = get_section_name_64(buf, elfHeader, sheaders, sheaders[i].sh_name);
        dprintf(1, "name = %s\n", name);
         if (name && strncmp(name, ".plt.got", strlen(section)) == 0) {
            dprintf(1, "offset = %ld\n", sheaders[i].sh_offset);
            dprintf(1, "size = %ld\n", sheaders[i].sh_size);
        }
        if (name && strncmp(name, section, strlen(section)) == 0) {
            print_sHeader64(sheaders[i]);
            dprintf(1, "size = %ld\n", sheaders[i].sh_size);
            return (sheaders[i].sh_offset);
        }
        i++;
    }
    return (0);
}

int get_structs(char *buf) {
    struct ELFheaders64 elfHeader;
    struct sheaders64 *sheaders;
    size_t section_offset = 0;

    elfHeader = get_elfHeader64_little_endian(buf);
    sheaders = get_section_headers_64(elfHeader, buf);
    if (!sheaders)
        return (1);
    section_offset = get_section_offset(".text", buf, sheaders, elfHeader);
    dprintf(1, "offset = %ld\n", section_offset);
    return (0);
}

int main(int argc, char **argv) {
    int fd = -1;
    struct stat *buf;
    void *ptr = NULL;

    fd = get_fd(argc, argv, &buf);
    if (fd  < 0)
	return (1);
    ptr = ft_mmap(buf->st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == NULL || S_ISREG(buf->st_mode) == 0) {
        perror("Error mmap");
        free(buf);
        return (1);
    }
    get_structs(ptr);
    munmap(ptr, buf->st_size);
    return (0);
}