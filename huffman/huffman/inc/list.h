#ifndef LIST_H
#define LIST_H

#include "freq.h"

typedef struct node {
    unsigned char character;
    int freq;
    struct node *left, *right, *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

void create_list(List *list);
void insert_ordered(List *list, Node *node);
void fill_list(unsigned int tab[], List *list);
void print_list(List *list);

#endif