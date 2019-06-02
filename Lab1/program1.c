#include <stdio.h>

int main() {
    float xFloat = 0.01;
    double xDouble = 0.01;

    float f1, f2, f3;
    double d1, d2, d3;

    for (int i = 1; i < 201; ++i) {
        f3 = 1.0f - xFloat;
        f2 = 3.0f * xFloat ;
        f1 = f2 * f3;
        xFloat = xFloat + f1;


        d3 = 1.0 - xDouble;
        d2 = 3.0 * xDouble ;
        d1 = d2 * d3;
        xDouble = xDouble + d1;

        printf("[%d] Calc for float: %f\n", i, xFloat);
        printf("[%d] Calc for double: %f\n", i, xDouble);
        printf("\n\n");
    }


    return 0;
}