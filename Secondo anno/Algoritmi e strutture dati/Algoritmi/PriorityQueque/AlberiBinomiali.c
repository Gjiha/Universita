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
    int numberOfChild;
} node;

typedef struct arrayOfNode {
    node *array;
    int len;
} arrayOfNode;

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
node *nodeCreate(element);
arrayOfNode arrayNodeInit(void);
void arrayNodeCreation(arrayOfNode *, node);
void nodeAllocation(node *, node *);
tree treeInitialize(arrayOfNode);
binomialTree binomialCreate(arrayOfNode);
void printTree(Tree);
void printFatherChild(node);
void printNode(node);
void printElement(element);

int main() {
    char *parola = "mamma";
    int key = 3;
    char *parola2 = "figlio";
    int key2 = 8;
    char *parola3 = "figlia";
    int key3 = 5;

    element c = elementCreate(key, parola);
    element d = elementCreate(key2, parola2);
    element e = elementCreate(key3, parola3);

    node *C = nodeCreate(c);
    node *D = nodeCreate(d);
    node *E = nodeCreate(e);

    nodeAllocation(C, D);
    nodeAllocation(C, E);
    printFatherChild(*C);

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

node *nodeCreate(element object) {
    node *nodo = malloc(sizeof(node));
    nodo->object = object;
    nodo->child = malloc(sizeof(node));
    nodo->father = NULL;
    nodo->numberOfChild = 0;
    return nodo;
}

void nodeAllocation(node *father, node *figlio) {

    father->numberOfChild++;
    father->child =
        realloc(father->child, (father->numberOfChild) * sizeof(node));
    father->child[father->numberOfChild - 1] = *figlio;
    figlio->father = father;
    return;
}

arrayOfNode arrayNodeInit() {
    arrayOfNode Aon = {malloc(sizeof(node)), 0};
    return Aon;
}

void arrayNodeCreation(arrayOfNode *lista, node nodo) {}

tree treeInitialize(arrayOfNode lista) {
    node n = lista.array[lista.len - 1];
    node p = lista.array[lista.len - 2];
    lista.len = lista.len - 2;

    node *father = malloc(sizeof(node));
    node *child = malloc(sizeof(node));

    if (n.object.key > p.object.key) {
        node father = n;
        node child = p;
    } else {
        node father = p;
        node child = n;
    }
    nodeAllocation(father, child);

    tree T1 = {2, malloc(sizeof(node))};
    T1.root = father;
    return T1;
}

void printFatherChild(node nodo) {
    printf("il padre è [");
    printElement(nodo.object);

    for (int i = 0; i < nodo.numberOfChild; i++) {
        printNode(nodo.child[i]);
    }
    printf("] questo è il figlio\n");
}

void printNode(node nodo) {
    printElement(nodo.object);
    return;
}

void printElement(element object) {
    printf("[ %d, %s ]\n", object.key, object.parola);
    return;
}
