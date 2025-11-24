#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node{
    int data;
    Node * next;
};

void print(Node * list) {
    for (Node * p = list; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
};

void push(Node ** plist, int d) {
    Node * p = malloc(sizeof(Node));
    p->data = d;
    p->next = *plist;
    *plist = p;
}

int Queue() {
    int test[] = {21, 17, 3, 10};
    Node * list = NULL;
    Node a = {3}, b = {17}, c = {21}, t = {10};
    for (size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
        push(&list, test[i]);
        print(list);
    }
    return 0;
}
