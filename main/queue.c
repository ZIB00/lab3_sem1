#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <ctype.h>

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

int enqueue(Elem ** BegQ, Elem ** EndQ, int inf) {
    Elem * p;
    p = (Elem *)malloc(sizeof(Elem));
    if (p == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 0;
    }
    p->inf = inf;
    p->link = NULL;

    if (is_empty(BegQ)) {
        *BegQ = p;
        *EndQ = p;
    } else {
        (*EndQ)->link = p;
        *EndQ = p;
    }
    return 1;
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
        //Идея: 3 очереди - меньше, равно, больше опорного элемента, рекурсивно сортируем меньше и больше, затем склеиваем
        Elem * BegQless = NULL, * BegQequal = NULL, *BegQmore = NULL;
        Elem * EndQless = NULL, * EndQequal = NULL, *EndQmore = NULL;
        int pivot = (*BegQ)->inf, temp = 0; //опорный элемент и временная переменная для перемещения
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

void clear_queue(Elem** BegQ, Elem** EndQ) {
    int num;
    while (!is_empty(BegQ)) {
        dequeue(BegQ, EndQ, &num);
    }
}

int queue(int args, char * argv[]) {
    char ch;
    int num, flag = 1, test;
    int res, c;
    Elem * BegQdirect = NULL, *EndQdirect = NULL;
    Elem * BegQHoara = NULL, *EndQHoara = NULL;
    Elem * p = BegQdirect; //для работы с файлом
    FILE * f;
    clock_t start, end;
    double duration;

    if (args == 3 && strcmp(argv[1], "--file") == 0) {
        printf("Чтение из файла %s\n", argv[2]);
        f = fopen(argv[2], "r");
        if (f == NULL) {
            printf("Ошибка открытия файла\n");
            return 1;
        }
        while (fscanf(f, "%d", &num) == 1) {
            enqueue(&BegQdirect, &EndQdirect, num);
            ch = fgetc(f);
            if (ch == '\n' || ch == EOF) break;
        }

        while (fscanf(f, "%d", &num) == 1) {
            enqueue(&BegQHoara, &EndQHoara, num); //Здесь я использую список Хоара для записи сортированного ряда(просто, чтобы не создавать новый)
            ch = fgetc(f);
            if (ch == '\n' || ch == EOF) break;
        }
        fclose(f);
        print(BegQdirect);
        print(BegQHoara);
        return 0;
    } else {
        while (1) {
            printf("Вводите целые числа по очереди. Для завершения введите любой нечисловой символ:\n");

            // Пока scanf успешно читает целое число
            while (scanf("%d", &num) == 1) {
                enqueue(&BegQdirect, &EndQdirect, num);
                enqueue(&BegQHoara, &EndQHoara, num);
            }
            
            while((c = getchar()) != '\n' && c != EOF);
            printf("Ввод завершён.\n");
            
            if (!is_empty(&BegQdirect)) {
                f = fopen("series_of_numbers.txt", "w");
                if (f == NULL) {
                    printf("Не удалось открыть файл для записи\n");
                    return 1;
                }
                p = BegQdirect;
                while (p->link != NULL) {
                    fprintf(f, "%d ", p->inf);
                    p = p->link;
                }
                fprintf(f, "%d\n", p->inf);

                start = clock();
                direct_sort_classic(&BegQdirect, &EndQdirect);
                end = clock();
                duration = (double)(end - start) / CLOCKS_PER_SEC;
                printf("Время прямой сортировки: %.6f сек.\n", duration);

                p = BegQdirect;
                while (p->link != NULL) {
                    fprintf(f, "%d ", p->inf);
                    p = p->link;
                }
                fprintf(f, "%d", p->inf);
                fclose(f);        

                //Демонстрация работы сортировки Хоара
                printf("Несортированный ряд:\n");
                print(BegQHoara);
                start = clock();
                Hoara_sort(&BegQHoara, &EndQHoara);
                end = clock();
                duration = (double)(end - start) / CLOCKS_PER_SEC;
                printf("Время прямой сортировки: %.6f сек.\n", duration);
                printf("Отсортированный ряд методом Хоара:\n");
                print(BegQHoara);
            }
            
            
            while (1) {
                printf("Повторить работу? (1 - да, 0 - нет): ");
                if (scanf("%d", &num) == 1 && (num == 0 || num == 1)) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Ошибка: введите 1 или 0.\n");
                }
            }
            if (num == 0) {
                break;
            } else {
                //Очистка очередей перед повторным вводом
                clear_queue(&BegQdirect, &EndQdirect);
                clear_queue(&BegQHoara, &EndQHoara);
            }
        }
    }   
}