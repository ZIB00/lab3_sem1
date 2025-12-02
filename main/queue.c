#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void Hoara_sort(Elem ** BegQ, Elem ** EndQ) {
    if (!is_empty(BegQ)) {
        Elem * BegQless = NULL, * BegQequal = NULL, *BegQmore = NULL;
        Elem * EndQless = NULL, * EndQequal = NULL, *EndQmore = NULL;
        int pivot = (*BegQ)->inf, temp = 0;
        while (!is_empty(BegQ)) {
            dequeue(BegQ, EndQ, &temp);
            if (pivot > temp) {
                enqueue(&BegQless, &EndQless, temp);
            } 
            else if (pivot == temp) {
                enqueue(&BegQequal, &EndQequal, temp);
            } 
            else {
                enqueue(&BegQmore, &EndQmore, temp);
            }
        }
        if (!is_empty(&BegQless)) {
            Hoara_sort(&BegQless, &EndQless);
        }
        if (!is_empty(&BegQmore)) {
            Hoara_sort(&BegQmore, &EndQmore);
        }
        if (is_empty(&BegQless) && !is_empty(&BegQmore)) {
            *BegQ = BegQequal;
            EndQequal->link = BegQmore;
            *EndQ = EndQmore;
        }
        else if (is_empty(&BegQmore) && !is_empty(&BegQless)) {
            *BegQ = BegQless;
            EndQless->link = BegQequal;
            *EndQ = EndQequal;
        }
        else if (is_empty(&BegQless) && is_empty(&BegQmore)) {
            *BegQ = BegQequal;
            *EndQ = EndQequal;
        } else {
            *BegQ = BegQless;
            EndQless->link = BegQequal;
            EndQequal->link = BegQmore;
            *EndQ = EndQmore;
        }
    }
}


int queue(int args, char * argv[]) {
    char ch;
    int num, flag = 1, test;
    int res;
    Elem * BegQdirect = NULL, *EndQdirect = NULL;
    Elem * BegQHoara = NULL, *EndQHoara = NULL;

    if (args == 3 && strcmp(argv[1], "--file") == 0) {
        printf("Чтение из файла %s\n", argv[2]);
        FILE * f = fopen(argv[2], "r");
        if (f == NULL) {
            printf("Ошибка открытия файла\n");
            return 1;
        }
        while (fscanf(f, "%d", &num) == 1) {
            enqueue(&BegQdirect, &EndQdirect, num);
            enqueue(&BegQHoara, &EndQHoara, num);
        }
        fclose(f);
        return 0;
    } else {

    
        while (scanf("%d", &num) == 1 && scanf("%c", &ch) == 1) {
            enqueue(&BegQdirect, &EndQdirect, num);
            enqueue(&BegQHoara, &EndQHoara, num);

            if (ch != '\n') {
                break;
            }
        }
        
            
            
        printf("Empty: %s\n", is_empty(&BegQdirect) ? "YES" : "NO");

        print(BegQdirect);

        direct_sort_classic(&BegQdirect, &EndQdirect);
        print(BegQdirect);

        printf("Empty: %s\n", is_empty(&BegQdirect) ? "YES" : "NO");

        while (!is_empty(&BegQdirect)) {
            dequeue(&BegQdirect, &EndQdirect, &res);
            printf("pop %d :", res);
            print(BegQdirect);
        }

        printf("Empty: %s\n", is_empty(&BegQdirect) ? "YES" : "NO");

        
        print(BegQdirect);
        print(BegQHoara);
            

        Hoara_sort(&BegQHoara, &EndQHoara);
        print(BegQHoara);

        printf("Повторить работу? (1 - да, 0 - нет)");
        printf("(Программа считает только первый символ)\n");
        return 0;
    }
    return 0;
}