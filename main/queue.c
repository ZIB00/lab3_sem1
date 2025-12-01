#include <stdio.h>
#include <stdlib.h>

typedef struct Elem {
    int inf;
    struct Elem * link;
} Elem;

void print(Elem * BegQ) { 
    Elem * p = BegQ;
    for (; p != NULL; p = p->link) { 
        printf("%d ", p->inf); 
    } 
    printf("\n"); 
}

int is_empty(Elem ** BegQ) {
    if (*BegQ == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(Elem ** BegQ, Elem ** EndQ, int inf) {
    Elem * p;
    p = (Elem *)malloc(sizeof(Elem));
    p->inf = inf;
    p->link = NULL;

    if (is_empty(BegQ)) {
        *BegQ = p;
        *EndQ = p;
    } else {
        (*EndQ)->link = p;
        *EndQ = p;
    }
}


int dequeue(Elem ** BegQ, Elem ** EndQ, int * r) {
    Elem * p;
    if (!is_empty(BegQ)) {
        p = *BegQ;
        *r = p->inf;
        (*BegQ) = (*BegQ)->link;

        if (*BegQ == NULL) {
            *EndQ = NULL;
        }

        free(p);
        return 1;
    }
    return 0;
}

void direct_sort_classic(Elem ** BegQ, Elem ** EndQ) {
    Elem * BegQ2 = NULL;
    Elem * EndQ2 = NULL;
    int min = (*BegQ)->inf;
    int curr = 0;
    Elem * p = *BegQ;
    while (*BegQ != NULL) {
        min = p->inf;
        while (p!= NULL) {
            if (min > p->inf) {
                min = p->inf;
            }
            p = p->link;
        }
        dequeue(BegQ, EndQ, &curr);
        if (curr == min) {
           enqueue(&BegQ2, &EndQ2, curr);
        } else {
           enqueue(BegQ, EndQ, curr);
        }
        p = *BegQ;
    }
    *BegQ = BegQ2;
    *EndQ = EndQ2;
}    


int queue() {
    int test[] = {21, 17, 3, 10};
    int res;
    Elem * BegQ = NULL;
    Elem * EndQ = NULL;


    printf("Empty: %s\n", is_empty(&BegQ) ? "YES" : "NO");

    for (size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
        enqueue(&BegQ, &EndQ, test[i]);
        print(BegQ);
    }

    direct_sort_classic(&BegQ, &EndQ);
    print(BegQ);

    printf("Empty: %s\n", is_empty(&BegQ) ? "YES" : "NO");

    while (!is_empty(&BegQ)) {
        dequeue(&BegQ, &EndQ, &res);
        printf("pop %d :", res);
        print(BegQ);
    }

    printf("Empty: %s\n", is_empty(&BegQ) ? "YES" : "NO");
    return 0;
}
