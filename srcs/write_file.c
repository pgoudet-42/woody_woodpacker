#include "../include/woody.h"

int write_in_file(char *data, size_t size) {
    int fd = open("woody", O_WRONLY | O_CREAT, S_IRWXU);

    if (fd == -1)
        return (-1);

    return (write(fd, data, size));
}

size_t find_opcode(char *buf, size_t size, unsigned char opcode) {
    for (size_t i = 0; i < size; i++) {
        if ((unsigned char)buf[i] == opcode)
            return (i);
    }
    return (0);
}

int write_file(char *buf, size_t size, struct sheaders64 section_hd) {
    char *final = NULL;
    char middle[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
    size_t opcode_index = 0;

    final = malloc(size + 10);
    if (!final)
        return (1);
    
    opcode_index = find_opcode(&(buf[section_hd.sh_offset]), section_hd.sh_size, 0xff);
    dprintf(1, "opcode index = %ld\n", opcode_index);
    if (opcode_index == 0) {
        printf("Error: opcode not find\n");
        exit(1);
    }
    memncat(final, 0, buf, section_hd.sh_offset + opcode_index);
    memncat(final, section_hd.sh_offset + opcode_index, middle, 10);
    memncat(final, section_hd.sh_offset + opcode_index + 10, &(buf[section_hd.sh_offset + opcode_index]), size - section_hd.sh_offset - opcode_index);
    write_in_file(final, size);
    free(final);
    return (0);
}