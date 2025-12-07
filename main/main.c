#include "queue.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>

int main(int args, char * argv[]) {
    setlocale(LC_ALL, "Russian");
    if (args >= 2 && strcmp(argv[1], "--benchmark") == 0) {
        benchmark_generated_data();
    } else  if (args == 3 && strcmp(argv[1], "--file") == 0) {
        read(args, argv);
    }
    return 0;
}