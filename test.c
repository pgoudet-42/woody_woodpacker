#include <stdio.h>

void    _print(char c) {
    printf("%c", c);
}

void    _loop(char tab[]) {
    int i = 0xf;

    while (i > 0) {
        _print(tab[i]);
    }
}

int main() {
    char tab[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};

    _loop(tab);
}