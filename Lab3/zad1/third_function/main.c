#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_chebyshev.h>

double function(double x, void *p) {
    if (x > 0) {
        return 1;
    }

    if (x < 0) {
        return -1;
    }

    return 0;
}

int main() {
    int n = 10000;
    gsl_cheb_series *cs = gsl_cheb_alloc(40);

    gsl_function gslFunction;
    gslFunction.function = function;
    gslFunction.params = 0;

    gsl_cheb_init(cs, &gslFunction, -1.0, 1.0);

    FILE *handle = fopen("third_function.txt", "w");
    FILE *handle10 = fopen("third_function_czebyszew_10.txt", "w");
    FILE *handle20 = fopen("third_function_czebyszew_20.txt", "w");
    FILE *handle30 = fopen("third_function_czebyszew_30.txt", "w");
    FILE *handle40 = fopen("third_function_czebyszew_40.txt", "w");

    for (int i = -10000; i < n; ++i) {
        double x = i / (double) n;

        double result10 = gsl_cheb_eval_n(cs, 10, x);
        double result20 = gsl_cheb_eval_n(cs, 20, x);
        double result30 = gsl_cheb_eval_n(cs, 30, x);
        double result40 = gsl_cheb_eval(cs, x);

        fprintf(handle, "%g %g\n", x, GSL_FN_EVAL(&gslFunction, x));
        fprintf(handle10, "%g %g\n", x, result10);
        fprintf(handle20, "%g %g\n", x, result20);
        fprintf(handle30, "%g %g\n", x, result30);
        fprintf(handle40, "%g %g\n", x, result40);
    }

    gsl_cheb_free(cs);

    return 0;
}