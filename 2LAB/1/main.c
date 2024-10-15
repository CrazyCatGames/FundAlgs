#include <stdio.h>
#include <stdlib.h>

#include "include/1.h"

int main(int argc, char *argv[]) {
    kOpts opt = 0;
    int number = 0;
    char *output = NULL;
    kOpts res;
    kOpts (*func[4])(const char *, char **) = { FlagL, FlagR, FlagU, FlagN};

    int result = GetOpts(argc, argv, &opt, &number);
    if (result != 0) {
        switch (result) {
            case 1:
                printf("Incorrect number of arguments.\n");
                break;
            case 2:
                printf("Error: %s isn't a natural number.\n", argv[2]);
                break;
            case 3:
                printf("Unknown flag: %s\n", argv[1]);
                break;
            case 4:
                printf("%s must be positive number.\n", argv[3]);
                break;
            default:
                printf("Unknown error.\n");
        }
        return 1;
    }

    if (opt == OPT_C) {
        res = FlagC(&output, number, argc, argv);
    } else {
        res = func[opt](argv[2], &output);
    }

    if (res == OPT_SUCCESS) {
        printf("%s\n", output);
    } else {
        printf("%s", output);
        printf("Error occurred.\n");
    }
    free(output);
    return 0;
}
