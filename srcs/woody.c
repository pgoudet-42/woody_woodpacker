#include "../include/woody.h"



void find_offset_injection(unsigned char *buf, struct ELFheaders64 elfheader) {
    size_t diff;
    struct pheaders64 *pheaders;

    pheaders = get_program_headers_64(buf, elfheader);
    for (int i = 0; i < elfheader.e_phnum - 1; i++) {
        diff = (pheaders[i].p_offset + pheaders[i].p_memsz) - pheaders[i + 1].p_offset;
        if ((pheaders[i].p_flags & 0x01) != 0 && diff > CODE_SIZE) {
            offset_injection = pheaders[i].p_offset + pheaders[i].p_memsz;
            printf("offset injection: %lx\n", offset_injection);
        }
    }
    
}

int woody(unsigned char *buf, size_t size) {
    struct ELFheaders64 elfheader;
    char *key;
    int section_index;
    struct sheaders64 *sheaders;

    elfheader = get_elfHeader64_little_endian(buf);
    sheaders = get_section_headers_64(buf, elfheader);
    section_index = get_section_index(".text", buf, sheaders, elfheader);
    key = generate_random_key(sheaders[section_index].sh_size);
    printf("Xor key: %s\n", key);


    find_offset_injection(buf, elfheader);
    buf = change_buffer(buf, elfheader, size);
    apply_xor(&(buf[sheaders[section_index].sh_offset]), sheaders[section_index].sh_size, key);

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