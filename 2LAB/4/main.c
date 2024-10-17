#include <stdio.h>
#include "include/4.h"

int main() {
    int count = 5;
    int base = 16;
    KaprekarResult results[count];
    kOpt res = FindKaprekar(results, base, count, "45", "f", "124.1", "-0004", "000000000000000000000f");

    switch (res) {
        case OPT_SUCCESS:
            for (int i = 0; i < count; i++) {
                if (results[i].result == OPT_SUCCESS) {
                    printf("%s - is Kaprekar number.\n", results[i].input);
                }else if (results[i].result == OPT_INVALID_FORMAT){
                    fprintf(stderr,"%s - isn't valid number.\n", results[i].input);
                }else{
                    printf("%s - isn't Kaprekar number.\n", results[i].input);
                }
            }
            break;
        case OPT_ERROR:
            fprintf(stderr, "Incorrect base.\n");
            break;
        case OPT_INVALID_FORMAT:
            fprintf(stderr, "Incorrect values.\n");
            break;
    }
    return 0;
}
