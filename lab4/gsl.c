#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f(double x, void *params) {
    return 1.0/sqrt(x);
}

int main(void) {
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);

    double result, error;
    double expected = 2.0;

    gsl_function F;
    F.function = &f;

    gsl_integration_qag(&F, 0, 1, 0, 1e-6, 1000, GSL_INTEG_GAUSS15, w, &result, &error);

    printf("result          = % .18f\n", result);
    printf("exact result    = % .18f\n", expected);
    printf("estimated error = % .18f\n", error);
    printf("actual error    = % .18f\n", result - expected);
    printf("intervals       = %zu\n", w->size);

    gsl_integration_workspace_free(w);

    return 0;
}