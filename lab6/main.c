#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/resource.h>
#include <string.h>

struct rusage t0, t1, t2;

void createMatrix(double *matrix, double *matrix_copy, int n);

void createVector(double *vector, int n);

void solve(int n, gsl_matrix_view *m, gsl_vector_view *b, const gsl_vector *x);

void check(gsl_matrix_view m_copy, gsl_vector *x, gsl_vector_view b, int n);

int czas(struct rusage *ru0, struct rusage *ru1);

void fuckit(int n);

int main(int argc, char **argv) {
    int n[] = {10, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};



    for (int i = 0; i < 17; ++i) {
        fuckit(n[i]);
    }


    return 0;
}

void fuckit(int n) {
    double a_data[n * n];
    double a_data_copy[n * n];
    createMatrix(a_data, a_data_copy, n);

    double b_data[n * n];
    createVector(b_data, n);

    gsl_matrix_view m = gsl_matrix_view_array(a_data, n, n);
    gsl_matrix_view m_copy = gsl_matrix_view_array(a_data_copy, n, n);

    gsl_vector_view b = gsl_vector_view_array(b_data, n);
    gsl_vector *x = gsl_vector_alloc(n);

    solve(n, &m, &b, x);
    check(m_copy, x, b, n);

    gsl_vector_free(x);


    printf("%d ", n);
//    printf("%s", "Matrix decomposition");
    czas(&t0, &t1);
//    printf("%s", "Equation solve");

    printf(" - ");

    printf("%d ", n);
    czas(&t1, &t2);

    printf("\n");
//    printf("%s", "All time:");
//    czas(&t0, &t2);
}

void solve(int n, gsl_matrix_view *m, gsl_vector_view *b, const gsl_vector *x) {
    int s;

//    printf("--------- MATRIX %dx%d ------  \n\n", n, n);
//    gsl_matrix_fprintf(stdout, &(*m).matrix, "%g");

    gsl_permutation *p = gsl_permutation_alloc(n);


    getrusage(RUSAGE_SELF, &t0);
    gsl_linalg_LU_decomp(&(*m).matrix, p, &s);
    getrusage(RUSAGE_SELF, &t1);
    gsl_linalg_LU_solve(&(*m).matrix, p, &(*b).vector, (gsl_vector *) x);
    getrusage(RUSAGE_SELF, &t2);

//    printf("\n--------- END MATRIX ------ \n\n");

//    printf("x = \n");
//    gsl_vector_fprintf(stdout, x, "%g");

    gsl_permutation_free(p);
}

void check(gsl_matrix_view m_copy, gsl_vector *x, gsl_vector_view b, int n) {
    gsl_vector *vectorAfterMultiplication = gsl_vector_alloc(n);

    for (int i = 0; i < n; ++i) {
        double result = 0;

        for (int j = 0; j < n; ++j) {
            result += gsl_matrix_get(&m_copy.matrix, i, j) * gsl_vector_get(x, j);
        }

        gsl_vector_set(vectorAfterMultiplication, i, result);
    }

//    printf("\nTrue vector b = \n");
//    gsl_vector_fprintf(stdout, &b.vector, "%g");
//    printf("\n");

//    printf("\nAfter multiplication vector b = \n");
//    gsl_vector_fprintf(stdout, vectorAfterMultiplication, "%g");
//    printf("\n");

    gsl_vector_free(vectorAfterMultiplication);

}

void createMatrix(double *matrix, double *matrix_copy, int n) {

    for (int i = 0; i < n * n; ++i) {
        double num = (rand() % 100) / 100.0;
        matrix[i] = num;
        matrix_copy[i] = num;
    }
}

void createVector(double *vector, int n) {

    for (int i = 0; i < n; ++i) {
        double num = (rand() % 10);
        vector[i] = num;
    }
}

int czas(struct rusage *ru0, struct rusage *ru1) {

    double utime = 0, stime = 0, ttime = 0;

    /* Obliczenie czasow. Aby mikrosekundy traktowac jako czesci sekund musimy je wymnozyc przez 10^-6*/
    utime = (double) ru1->ru_utime.tv_sec
            + 1.e-6 * (double) ru1->ru_utime.tv_usec
            - ru0->ru_utime.tv_sec
            - 1.e-6 * (double) ru0->ru_utime.tv_usec;
    stime = (double) ru1->ru_stime.tv_sec
            + 1.e-6 * (double) ru1->ru_stime.tv_usec
            - ru0->ru_stime.tv_sec
            - 1.e-6 * (double) ru0->ru_stime.tv_usec;
    ttime = stime + utime;

//    /*printf("user time: %3f\n", utime);
//    printf("system time: %3f\n", stime);*/
    printf("%3f", ttime);

}
