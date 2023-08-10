#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void rc4_init(unsigned char *key, size_t key_length, unsigned char *state) {
    unsigned char j = 0;
    for (int i = 0; i < 256; i++) {
        state[i] = i;
    }

    for (int i = 0; i < 256; i++) {
        j = (j + state[i] + key[i % key_length]) % 256;
        swap(&state[i], &state[j]);
    }
}

void rc4_encrypt_decrypt(unsigned char *input, size_t length, unsigned char *state) {
    unsigned char i = 0;
    unsigned char j = 0;

    for (size_t k = 0; k < length; k++) {
        i = (i + 1) % 256;
        j = (j + state[i]) % 256;
        swap(&state[i], &state[j]);
        unsigned char keystream = state[(state[i] + state[j]) % 256];
        input[k] = input[k] ^ keystream;
    }
}

int main() {
    unsigned char key[] = "mysecretkey";
    unsigned char plaintext[] = "Hello, RC4 Encryption!";
    size_t length = strlen((char *)plaintext);

    unsigned char state[256];
    rc4_init(key, strlen((char *)key), state);

    printf("Texte clair : %s\n", plaintext);

    // Chiffrement
    rc4_encrypt_decrypt(plaintext, length, state);
    printf("Chiffre : ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    // Déchiffrement
    rc4_init(key, strlen((char *)key), state); // Réinitialiser l'état pour le déchiffrement
    rc4_encrypt_decrypt(plaintext, length, state);
    printf("Déchiffre : %s\n", plaintext);

    return 0;
}