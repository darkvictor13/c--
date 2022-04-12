#include "tree.h"
#include <stdio.h>
#include <string.h>

void print(FILE *file, const treeNode *vet, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 1; j < vet[i].tabs; j++) {
            fprintf(file, "    ");
        }
        fprintf(file, "%s\n", vet[i].token_text);
    }
}

void add(treeNode *element, const char *text, int tabs) {
    (*element).tabs = tabs;
    strcpy((*element).token_text, text);
}
