#include <stdio.h>

int main() {
    float epsilonF = 1.0f;
    float previousEpsilonF = 0.0f;
    float testF = epsilonF + 1;

    double epsilonD = 1.0f;
    double previousEpsilonD = 0.0f;
    double testD = epsilonD + 1;

    while (testF > 1) {
        previousEpsilonF = epsilonF;
        epsilonF = epsilonF / 2.0f;
        testF = epsilonF + 1.0f;
    }

    while (testD > 1) {
        previousEpsilonD = epsilonD;
        epsilonD = epsilonD / 2.0;
        testD = epsilonD + 1.0;
    }


    printf("Epsilon dla pojedyńczej precyzji: %.50f\n", previousEpsilonF);
    printf("Epsilon dla podwójnej precyzji: %.50f\n", previousEpsilonD);

    return 0;
}
