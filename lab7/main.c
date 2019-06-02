#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_vegas.h>

double function1(double *x, size_t dim, void *p);

double function2(double *x, size_t dim, void *p);

int main() {
    double error, result, exact = 1.0/3.0;

    FILE* file1 = fopen("gsl_plain_1.dat", "w");

    for (int n = 1; n < 100000; n += 10) {
        double xl[1] = {0.0};
        double xu[1] = {1.0};
        gsl_monte_function F;
        F.f = &function1;
        F.dim = 1;
        F.params = 0;

        const gsl_rng_type *T;
        gsl_rng *r;
        gsl_rng_env_setup();
        T = gsl_rng_default;
        r = gsl_rng_alloc(T);


        gsl_monte_plain_state *state = gsl_monte_plain_alloc(1);
        gsl_monte_plain_init(state);
        gsl_monte_plain_integrate(&F, xl, xu, 1, n, r, state, &result, &error);

        printf ("======================\n");
        printf ("wynik          = % .6f\n", result);
        printf ("blad           = % .6f\n", error);
        printf ("wynik poprawny = % .6f\n", exact);
        printf ("parametr calls =  %d\n", n);

        fprintf(file1,"%d %f\n", n, fabs(result - exact));

        gsl_rng_free(r);
        gsl_monte_plain_free(state);

    }


    return 0;
}

double function1(double *x, size_t dim, void *p) {
    return (*x)*(*x);
}

double function2(double *x, size_t dim, void *p) {
    return 1/sqrt(*x);
}