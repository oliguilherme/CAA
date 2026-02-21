#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

//criar um nó que será utilizado tanto para a estrutura lista quanto para a estrutura árvore

typedef struct node {
    unsigned char character;
    int freq;
    struct node *left, *right, *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

/* ------------------------------------------------ 1 - TABELA DE FREQUENCIA ------------------------------------------------ */
void init_freq_table(unsigned int tab[SIZE]);
void count_frequencies(unsigned int tab[SIZE], unsigned char text[]);
void print_freq_table(unsigned int tab[SIZE]);


/* ------------------------------------------------ 2 - LISTA DE FREQUÊNCIA ------------------------------------------------ */
void create_list(List *list);
void insert_ordered(List *list, Node *node);
void fill_list(unsigned int tab[], List *list);
void print_list(List *list);

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

/* ------------------------------------------------ 1 - TABELA DE FREQUENCIA ------------------------------------------------ */
void init_freq_table(unsigned int tab[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        tab[i] = 0;
    }
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


/* ------------------------------------------------ 2 - LISTA DE FREQUÊNCIA ------------------------------------------------ */
void create_list(List *list) {
    list->head = NULL;
    list->size = 0;
}

void insert_ordered(List *list, Node *node) {
    Node *current;

    // a lista está vazia?
    if (list->head == NULL) {
        list->head = node;
    } 
    //sua freq é menor que a freq do primeiro nó?
    else if (node->freq < list->head->freq) {
        node->next = list->head;
        list->head = node;
    }
    //insercao no meio
    else {
        current = list->head;

        while (current->next != NULL && current->next->freq <= node->freq) {
            current = current->next;
        }
        
        node->next = current->next; //o novo no aponta para o nó imediatamente posterior a ele na frequencia
        current->next = node; //o no anterior aponta para o novo no.
    }
    
    list->size++;
}

void fill_list(unsigned int tab[], List *list) {
    Node *new_node;
    for (int i = 0; i < SIZE; i++) {
        if (tab[i] > 0) {
            new_node = malloc(sizeof(Node));
            if (new_node) {
                new_node->character = i;
                new_node->freq = tab[i];
                new_node->right = NULL;
                new_node->left = NULL;
                new_node->next = NULL;

                insert_ordered(list, new_node);
            }  else {
            printf("Erro ao alocar memoria.");
            }
        }
    }
}

void print_list(List *list) {
    Node *current = list->head;
    printf("\nLISTA ORDENADA: TAMANHO: %d\n", list->size);

    while (current != NULL) {
        printf("Caracter: %c | Frequencia: %d\n", current->character, current->freq);
        current = current->next;
    }
}