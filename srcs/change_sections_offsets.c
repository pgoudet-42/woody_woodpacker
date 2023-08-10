#include "../include/woody.h"

#define NAME 0
#define TYPE 4
#define FLAGS 8
#define ADDR 16
#define OFFSET 24
#define SIZE 32
#define LINK 36
#define INFO 40
#define ALIGN 48
#define ENTSIZE 56


size_t get_section_offset(int index, struct ELFheaders64 file_header) {
    size_t offset = 0;

    offset = file_header.e_shoff + file_header.e_shentsize * index;
    return (offset);
}

int get_section_index(char *section, char *buf, struct sheaders64 *sheaders, struct ELFheaders64 file_header) {
    int i = 0, index = -1;
    unsigned char section_found = 0;
    char *name = NULL;
    size_t offset = 0;

    while(i < file_header.e_shnum) {
        name = get_section_name_64(buf, file_header, sheaders, sheaders[i].sh_name);
        printf("name = %s\n", name);
        if (name && strncmp(name, section, strlen(section)) == 0) {
            index = i;
            section_found = 1;
            offset = get_section_offset(i, file_header);
            (unsigned long int)((unsigned char *)buf)[offset + SIZE] = (unsigned long int)(sheaders[i].sh_size) + VIRUS_SIZE;
        }
        if (section_found) {
            offset = get_section_offset(i, file_header);
            buf[offset + OFFSET] = sheaders[i].sh_offset + 255;
        }
        free(name);
        i++;
    }
    return (index);
}

int change_offset_sections(char *buf, struct sheaders64 *sheaders, struct ELFheaders64 file_header) {
    struct sheaders64 *sheaders2;
    int index = 0;

    index = get_section_index(".text", buf, sheaders, file_header);
    if (index == -1) {
        dprintf(1, "Error: section non trouvee\n");
        return (-1);
    }
    dprintf(1, "index = %d\n", index);
    sheaders2 = get_section_headers_64(file_header, buf);
    print_sHeader64(sheaders2[index]);
    print_sHeader64(sheaders[index]);
    return (index);
}