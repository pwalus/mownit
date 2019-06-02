#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/time.h>

double function1(double x);

double function2(double x);

double monteCarlo(double (*function)(double), double a, double b, double min, double max, int numberOfIteration);

int main() {
    srand(time(0));

    double good1 = 1.0/3.0;
    double good2 = 2.0;

    FILE* plik1 = fopen("plik1.dat", "w");
    FILE* plik2 = fopen("plik2.dat", "w");

    for (int i = 1; i < 100000; i += 10) {
        fprintf(plik1,"%d %f\n", i, fabs(monteCarlo(function1, 0.0, 1.0, 0.0, 1.0, i) - good1));
        fprintf(plik2,"%d %f\n", i, fabs(monteCarlo(function2, 0.0, 1.0, 0.0, DBL_MAX, i) - good2));
    }
    return 0;
}

double function1(double x) {
    return x * x;
}

double function2(double x) {
    return x == 0 ? DBL_MAX : 1 / sqrt(x);
}

double monteCarlo(double (*function)(double), double a, double b, double min, double max, int numberOfIteration) {
    double rectangleSurface = (b - a) * (max - min);
    double counter = 0;
    for (int i = 0; i < numberOfIteration; i++) {
        double randomX = (rand() / (((double) RAND_MAX + 1) / b)) + a;
        double randomY = (rand() / (((double) RAND_MAX + 1) / max)) + min;

        if (randomY <= function(randomX)) {
            counter++;
        }
    }

    return rectangleSurface * (counter / numberOfIteration);
}
