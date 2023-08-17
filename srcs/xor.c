#include "../include/woody.h"

char *generate_random_key(size_t len) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789,.-#'?!";
    char *str = NULL;

    str = malloc(len);
    if (!str)
        return (NULL);
    if (len) {
        --len;
        for (size_t n = 0; n < len; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[len] = '\0';
    }
    return str;
}

unsigned char *apply_xor(unsigned char *buf, size_t len, char *key) {
    size_t i = 0;
    unsigned char *data = NULL;

    data = malloc(len + 1);
    if (!data)
        return (NULL);
    
    while(i < len) {
        data[i] = buf[i] ^ key[i % len];
        i++;
    }
    return (data);
}

struct crypt_res *crypt_xor(unsigned char *buf, size_t len) {
    struct crypt_res *resultat;

    resultat = malloc(sizeof(struct crypt_res));
    if (!resultat)
        return (NULL);

    resultat->len = len;
    resultat->key = generate_random_key(len);
    if (!resultat->key)
        return (NULL);
    resultat->data = apply_xor(buf, len, resultat->key);
    return (resultat);
}

struct crypt_res *decrypt_xor(struct crypt_res *ptr) {
    unsigned char *res;

    res = apply_xor(ptr->data, ptr->len, ptr->key);
    free(ptr->data);
    ptr->data = res;

    return (ptr);
}
