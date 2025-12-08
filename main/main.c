#include "queue.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>

int main(int args, char * argv[]) {
    setlocale(LC_ALL, "Russian");
    if (args == 3 && strcmp(argv[1], "--file") == 0) {
        read(args, argv);
    } else {
        queue();
    }
    return 0;
}