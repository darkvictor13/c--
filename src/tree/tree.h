#ifndef TREE
#define TREE

#include <stdio.h>

typedef struct tree_node {
    char token_text[50];
    int tabs;
}treeNode;

void print(FILE *file, const treeNode *vet, int size);

void add(treeNode *element, const char *text, int tabs);

#endif
