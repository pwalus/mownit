#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float calculate(float (*function)(float), float a, float b, int n);

float function(float x) {
    return (float) (1 / sqrt(x));
}

float calculate(float (*function)(float), float a, float b, int n) {

    float integral = 0;

    float interval = (b - a) / n;
    float x = a;
    float xi;

    for (int i = 0; i < n; ++i) {
        xi = x + interval;
        integral += (interval) * function((x + xi) / 2);
        x = xi;
    }

    return integral;
}

int main() {
    float trueResult = (float) 2;
    float searchPrecisions[4] = {0.001, 0.0001, 0.00001, 0.000001};

    float result = 0;
    float actualPrecision = 0;

    int x = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = x; j < 10000000; ++j) {
            result = calculate(function, 0, 1, j);
            actualPrecision = fabsf(result - trueResult);
            if (actualPrecision < searchPrecisions[i]) {
                printf("Integral error is less than %f for %i subinterval\n", searchPrecisions[i], j);
                x = j;
                break;
            }

            if (j % 1000 == 0) {
                printf("%ld %f\n", (long) (j / 1000), actualPrecision);
            }
        }
    }

    return 0;
}
