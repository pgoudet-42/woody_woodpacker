#include "../include/woody.h"

char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *encrypt(char *buf, size_t size) {
    char *encrypt_buf = NULL;
    size_t i = 0, j = 0;
    size_t output_length = ((size + 2) / 3) * 4;

    encrypt_buf = malloc(output_length + 1);
    if (!encrypt_buf) {
        perror("Error malloc");
        return (NULL);
    }
    ft_bzero(encrypt_buf, output_length);
    while (i < size) {
        unsigned char octet1 = buf[i];
        unsigned char octet2 = (i + 1 < size) ? buf[i + 1] : 0;
        unsigned char octet3 = (i + 2 < size) ? buf[i + 2] : 0;

        encrypt_buf[j++] = base64_chars[octet1 >> 2];
        encrypt_buf[j++] = base64_chars[((octet1 & 3) << 4) | (octet2 >> 4)];
        encrypt_buf[j++] = base64_chars[((octet2 & 15) << 2) | (octet3 >> 6)];
        encrypt_buf[j++] = base64_chars[octet3 & 63];
        if (j > output_length - 1) {
            if (octet2 == 0)
                encrypt_buf[j - 2] = '=';
            if (octet3 == 0)
                encrypt_buf[j - 1] = '=';
        }
        encrypt_buf[j] = 0;
        i += 3;
    }
    encrypt_buf[output_length + 1] = 0;
    return (encrypt_buf);
}

char decLookupTable[] = {
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,\
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,\
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 62, 80, 80, 80, 63,\
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 80, 80, 80, 64, 80, 80,\
    80,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,\
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 80, 80, 80, 80, 80,\
    80, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,\
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 80, 80, 80, 80, 80
};

char *decrypt(char *buf, size_t size) {
    char *decrypt_buf = NULL;
    size_t i = 0, j = 0;
    size_t output_length = (size / 4) * 3;
    char index[4];

    if (buf[size - 1] == '=')
        output_length--;
    if (buf[size - 2] == '=')
        output_length--;

    decrypt_buf = malloc(output_length + 1);
    if (!decrypt_buf) {
        perror("Error malloc");
        return (NULL);
    }
    ft_bzero(decrypt_buf, output_length);

    for (i = 0; i < size; i += 4) {
        index[0] = decLookupTable[(unsigned char)buf[i]];
        index[1] = decLookupTable[(unsigned char)buf[i + 1]];
        index[2] = decLookupTable[(unsigned char)buf[i + 2]];
        index[3] = decLookupTable[(unsigned char)buf[i + 3]];

        decrypt_buf[j++] = (index[0] << 2 | ((index[1] & 0xF0) >> 4));
        decrypt_buf[j++] = (((index[1] & 0x0F) << 4) | ((index[2] & 0x3C) >> 2));
        decrypt_buf[j++] = (((index[2] & 0x03) << 6) | (index[3] & 0x3F));
    }
    decrypt_buf[j] = 0;
    return (decrypt_buf);
}