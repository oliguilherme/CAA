#include <stdio.h>
#include "freq.h"

void init_freq_table(unsigned int tab[SIZE]) {
    for (int i = 0; i < SIZE; i++)
        tab[i] = 0;
}

void count_frequencies(unsigned int tab[SIZE], unsigned char text[]) {
    int i = 0;
    while (text[i] != '\0') {
        tab[text[i]]++;
        i++;
    }
}

void print_freq_table(unsigned int tab[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (tab[i] != 0)
            printf("%d --- %u --- %c\n", i, tab[i], i);
    }
}