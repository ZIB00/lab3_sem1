#include "queue.h"
#include <stdio.h>
#include <locale.h>

int main(int args, char * argv[]) {
    setlocale(LC_ALL, "Russian");

    
    printf("Вводите числа по очереди, для завершения введите любой нечисловой символ");
    printf("(если ввести и число, и нечисловой символ, программа примет число и остановит ввод, если наоборот - сразу остановит ввод)\n");
    queue(args, argv);
    return 0;
}