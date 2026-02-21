#ifndef FREQ_H
#define FREQ_H

#define SIZE 256

void init_freq_table(unsigned int tab[SIZE]);
void count_frequencies(unsigned int tab[SIZE], unsigned char text[]);
void print_freq_table(unsigned int tab[SIZE]);

#endif