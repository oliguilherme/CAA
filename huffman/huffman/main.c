#include <stdio.h>
#include <stdlib.h>
#include "freq.h"
#include "list.h"

int main() {
    system("clear");

    unsigned char text[] = "Vamos aprender a programar";
    unsigned int tab[SIZE];
    List list;

    init_freq_table(tab);
    count_frequencies(tab, text);
    print_freq_table(tab);

    create_list(&list);
    fill_list(tab, &list);
    print_list(&list);

    return 0;
}