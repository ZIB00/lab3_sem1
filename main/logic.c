#include <stdio.h>

typedef struct Node Node;

struct Node{
    int data;
    Node * next;
};

int Queue() {
    struct Node * list = NULL;
    Node a = {3}, b = {17}, c = {21}, t = {10};
    list = &a;
    a.next = &b;
    b.next = &c;
    c.next = NULL;
    return 0;
}