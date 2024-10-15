#include "include/7.h"
#include <stdio.h>

int main() {
    double a = 0.0, b = 5.0, epsilon = 0.000001;
    double root;
    kOpt res = Bisection(Equation, a, b, epsilon, &root);

    if (res == OPT_SUCCESS) {
        printf("The root in the interval [%.6f, %.6f] with an accuracy of %.6f: %.6f\n", a, b, epsilon, root);
    } else {
        printf("ERROR: in the segment [%.6f, %.6f], the root is missing or the function does not change the sign.\n", a, b);
        return -1;
    }

    return 0;
}