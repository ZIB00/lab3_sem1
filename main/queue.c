#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

typedef struct Queue { 
    Node * head; 
    Node * tail; 
} Queue;

void print(Queue * q) { 
    Node * p = q->head; 
    for (p; p != NULL; p = p->next) { 
        printf("%d ", p->data); 
    } 
    printf("\n"); 
}

void enqueue1(Queue * q, int data) {
    Node * new_Node = malloc(sizeof(Node));
    new_Node->data = data;
    new_Node->next = NULL;

    if (q->head == NULL) {
        q->head = new_Node;
        q->tail = new_Node;
    } else {
        q->tail->next = new_Node;
        q->tail = new_Node;
    }
}


void enqueue(Node ** phead, Node ** ptail, int d) {
    Node * p = malloc(sizeof(Node));
    p->data = d;
    p->next = NULL;

    if (*phead == NULL) {
        *phead = p;
        *ptail = p;
    } else {
        (*ptail)->next = p;
        *ptail = p;
    }
}

int dequeue(Node ** phead, Node ** ptail) {
    Node * p = *phead;
    int res = p->data;

    *phead = p->next;

    if (*phead == NULL) {
        *ptail = NULL;
    }

    free(p);
    return res;
}

int is_empty(Node * list) {
    return list == NULL;
}

int queue() {
    int test[] = {21, 17, 3, 10};
    Node * head = NULL;
    Node * tail = NULL;

    printf("Empty: %s\n", is_empty(head) ? "YES" : "NO");

    for (size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
        enqueue(&head, &tail, test[i]);
        print(head);
    }

    printf("Empty: %s\n", is_empty(head) ? "YES" : "NO");

    while (!is_empty(head)) {
        int d = dequeue(&head, &tail);
        printf("pop %d :", d);
        print(head);
    }

    printf("Empty: %s\n", is_empty(head) ? "YES" : "NO");
    return 0;
}
