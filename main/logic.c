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
    struct Node * list = NULL;
    Node a = {3}, b = {17}, c = {21}, t = {10};
    list = &a;
    a.next = &b;
    b.next = &c;
    c.next = NULL;
    print(list);
    push(&list, 10);
    print(list);
    return 0;
}
