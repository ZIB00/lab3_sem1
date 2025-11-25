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

void enqueue(Queue * q, int data) {
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
int is_empty(Queue * q) {
    if (q->head == NULL) {
        return 1;
    } else {
        return 0;
    }
}
int dequeue(Queue * q, int * r) {
    if (!is_empty(q)) {
        Node * old_head = q->head;
        *r = q->head->data;
        q->head = q->head->next;

        if (q->head == NULL) {
            q->tail = NULL;
        }

        free(old_head);
        return 1;
    }
    return 0;
}

int queue() {
    int test[] = {21, 17, 3, 10};
    int res, *r = res;
    Queue * q = {NULL, NULL};

    printf("Empty: %s\n", is_empty(q) ? "YES" : "NO");

    for (size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
        enqueue(&q, test[i]);
        print(q);
    }

    printf("Empty: %s\n", is_empty(q) ? "YES" : "NO");

    while (!is_empty(q)) {
        int d = dequeue(q, &r);
        printf("pop %d :", d);
        print(q);
    }

    printf("Empty: %s\n", is_empty(q) ? "YES" : "NO");
    return 0;
}
