#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_poly.h>

double function(double x) {
    return pow(0.5, x * x + 2 * x);
}

gsl_vector *approximate(double (*F)(double), double a, double b, int numberOfNodes, int grade) {
    double j, sum, power;
    int i, k, l, z;

    double *nodes = malloc((numberOfNodes + 1) * sizeof(double));
    double step = (b - a) / numberOfNodes;

    j = a;
    for (i = 0; i < (numberOfNodes + 1); i++) {
        nodes[i] = j;
        j += step;
    }

    gsl_matrix *G = gsl_matrix_calloc(grade + 1, grade + 1);
    gsl_vector *B = gsl_vector_calloc(grade + 1);
    gsl_vector *A = gsl_vector_calloc(grade + 1);

    // Vector
    for (k = 0; k < (grade + 1); k++) {
        sum = 0;
        for (i = 0; i < (numberOfNodes + 1); i++) {
            power = 1;
            for (z = 0; z < k; z++) {
                power *= nodes[i];
            }
            sum = sum + (F(nodes[i]) * power);
        }
        gsl_vector_set(B, k, sum);
    }

    // Matrix
    for (k = 0; k < (grade + 1); k++) {
        for (l = 0; l < (grade + 1); l++) {
            sum = 0;
            for (i = 0; i < (numberOfNodes + 1); i++) {
                power = 1;
                for (z = 0; z < (l + k); z++)
                    power = power * nodes[i];
                sum = sum + (power);
            }
            gsl_matrix_set(G, k, l, sum);
        }
    }


    gsl_linalg_HH_solve(G, B, A);
    free(nodes);
    gsl_vector_free(B);
    gsl_matrix_free(G);
    return A;
}

void
dataCreator(FILE *originalFunction, FILE *polynomialFunction, gsl_vector *A, double (*F)(double), double a, double b,
            int grade) {
    double j;

    double *factors = malloc((grade + 1) * sizeof(double));
    for (int i = 0; i < (grade + 1); i++)
        factors[i] = gsl_vector_get(A, i);

    double step = (b - a) / 10000;
    double x, y, ya;

    j = a;
    while (j <= b) {
        x = j;
        ya = gsl_poly_eval(factors, grade + 1, x);
        y = F(x);
        fprintf(originalFunction, "%.40g %.40g\n", x, y);
        fprintf(polynomialFunction, "%.40g %.40g\n", x, ya);
        j += step;
    }
    free(factors);
}

int main() {
    FILE *originalFunction = fopen("1.txt", "w");
    FILE *polynomialFunction = fopen("2.txt", "w");

    gsl_vector *A = approximate(function, -1.0, 1.0, 6, 5);
    dataCreator(originalFunction, polynomialFunction, A, function, -1.0, 1.0, 5);
    gsl_vector_free(A);
    return 0;
}
