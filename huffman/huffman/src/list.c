#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void create_list(List *list) {
    list->head = NULL;
    list->size = 0;
}

void insert_ordered(List *list, Node *node) {
    Node *current;

    if (list->head == NULL) {
        list->head = node;
    } 
    else if (node->freq < list->head->freq) {
        node->next = list->head;
        list->head = node;
    }
    else {
        current = list->head;
        while (current->next != NULL && current->next->freq <= node->freq)
            current = current->next;

        node->next = current->next;
        current->next = node;
    }

    list->size++;
}

void fill_list(unsigned int tab[], List *list) {
    for (int i = 0; i < SIZE; i++) {
        if (tab[i] > 0) {
            Node *new_node = malloc(sizeof(Node));

            if (!new_node) {
                printf("Erro ao alocar memória\n");
                return;
            }

            new_node->character = i;
            new_node->freq = tab[i];
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->next = NULL;

            insert_ordered(list, new_node);
        }
    }
}

void print_list(List *list) {
    Node *current = list->head;

    printf("\nLISTA ORDENADA: TAMANHO: %d\n", list->size);

    while (current != NULL) {
        if (current->character == 32) 
            printf("Caracter: [espaco]");
        else
            printf("Caracter: %c", current->character);
        
        printf(" | Frequencia: %2d\n", current->freq);
        current = current->next;
    }
}