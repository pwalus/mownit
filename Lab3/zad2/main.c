#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_chebyshev.h>

double function(double x, void *p) {
    return pow(0.5, (x * x + 2 * x));
}

int main() {
    int n = 10000;
    gsl_cheb_series *cs = gsl_cheb_alloc(40);

    gsl_function gslFunction;
    gslFunction.function = function;
    gslFunction.params = 0;

    gsl_cheb_init(cs, &gslFunction, -1.0, 1.0);

    FILE *handle = fopen("function.txt", "w");
    FILE *handleResult10 = fopen("function10.txt", "w");
    FILE *handleResult20 = fopen("function20.txt", "w");
    FILE *handleResult30 = fopen("function30.txt", "w");
    FILE *handleResult40 = fopen("function40.txt", "w");

    for (int i = -10000; i < n; ++i) {
        double x = i / (double) n;

        double result10 = gsl_cheb_eval_n(cs, 10, x);
        double result20 = gsl_cheb_eval_n(cs, 20, x);
        double result30 = gsl_cheb_eval_n(cs, 30, x);
        double result40 = gsl_cheb_eval_n(cs, 40, x);

        fprintf(handle, "%g %g\n", x, GSL_FN_EVAL(&gslFunction, x));
        fprintf(handleResult10, "%g %g\n", x, result10);
        fprintf(handleResult20, "%g %g\n", x, result20);
        fprintf(handleResult30, "%g %g\n", x, result30);
        fprintf(handleResult40, "%g %g\n", x, result40);
    }

    gsl_cheb_free(cs);

    return 0;
}