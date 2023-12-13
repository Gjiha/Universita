#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
    int key;
    char *parola;
} element;

typedef struct node {
    element object;
    struct node *child;
    struct node *father;
} node;

typedef struct tree {
    int numberOfNode;
    node *root;
} tree;

typedef struct binomialTree {
    int numberOfTree;
    int allNode;
    tree *arrayOfTree;
} binomialTree;

element elementCreate(int, char *);
node nodeCreate(element);
void nodeAllocation(node);
void printElement(element);

int main() {
    char *parola = "mamma";
    int key = 3;

    element c = elementCreate(key, parola);
    printElement(c);

    return 0;
}

element elementCreate(int key, char *parola) {
    element object = {0, NULL};
    object.key = key;
    int len = strlen(parola);

    object.parola = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++) {
        object.parola[i] = parola[i];
    }
    return object;
}

node nodeCreate(element object) {
    node nodo = {object, NULL, malloc(sizeof(node))};
    return nodo;
}

void nodeAllocation(node nodo, node father) {

    int len = sizeof(father.child) / sizeof(node);
    father.child = realloc(father.child, (len + 1) * sizeof(node));
    return;
}

void printElement(element object) {
    printf("[ %d, %s ]\n", object.key, object.parola);
    return;
}
