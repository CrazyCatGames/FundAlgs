#include "include/9.h"
#include <stdio.h>

int main() {
    int count_of_numbers = 4;
    int base = 12;
    FiniteAnswer results[count_of_numbers];
    CheckFiniteHandle(results, base, count_of_numbers, 0.5, 0.2, 0.333333, 0.111);

    for (int i = 0; i < count_of_numbers; i++) {
        if (results[i].status == OPT_SUCCESS) {
            printf("The number %.6f has a finite representation in a system with a base of %d\n", results[i].number, base);
        } else {
            printf("The number %.6f has no finite representation in a system with a base of %d\n", results[i].number, base);
        }
    }
    return 0;
}