#include "queue.h"
#include <stdio.h>
#include <locale.h>

int main(int args, char * argv[]) {
    setlocale(LC_ALL, "Russian");

    queue(args, argv);
    return 0;
}