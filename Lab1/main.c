#include <stdio.h>

int main() {
    float xFloat = 0.01;
    double xDouble = 0.01;

    for (int i = 1; i < 20; ++i) {
        xFloat = xFloat + 3.0 * xFloat * (1 - xFloat);
        xDouble = xDouble + 3.0 * xDouble * (1 - xDouble);

        printf("[%d] Calc for float: %f\n", i, xFloat);
        printf("[%d] Calc for double: %f\n", i, xDouble);
        printf("\n\n");
    }


    return 0;
}