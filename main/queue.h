#ifndef QUEUE_H
#define QUEUE_H

typedef struct Elem {
    int inf;
    struct Elem * next;
} Elem;

void print(Elem * BegQ);
int is_empty(Elem ** BegQ);
void enqueue(Elem ** BegQ, Elem ** EndQ, int inf);
int dequeue(Elem ** BegQ, Elem ** EndQ, int * r);
void direct_sort_classic(Elem ** BegQ, Elem ** EndQ);
void Hoara_sort(Elem ** BegQ, Elem ** EndQ);
int queue(int args, char * argv[]);

#endif