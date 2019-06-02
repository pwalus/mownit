#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <memory.h>

#include "demo_fn.h"

/*
program stosuje rozne metody typu root polishing
dla rownania
x^2 - 2x + 1 = 0

rozwiazaniem jest x = 1
*/

int
main (int argc, char** args)
{
    int status; // stan rozwiazania
    int iter = 0, max_iter = 100; // aktualna i maksymalna ilosc iteracji
    const gsl_root_fdfsolver_type *T; // typ solvera
    gsl_root_fdfsolver *s; // solver (fdf, z pochodnymi)
    double r0, r = 5.0, r_expected = 1.0; // poprzedni pierwiastek numeryczny, aktualny p. numeryczny i p. analityczny
    gsl_function_fdf F; // nasza funkcja (fdf)

    struct quadratic_params params = {1.0, -2.0, 1.0}; // x^2-2x+1
    F.f = &quadratic;
    F.df = &quadratic_deriv;
    F.fdf = &quadratic_fdf;
    F.params = &params;

    if(argc!=2)
    {
        printf("Uzycie: fdf metoda, gdzie metoda = {newton, secant, steffenson}\n");
        return 1;
    }
    if(strcmp(args[1],"newton")==0)
        T = gsl_root_fdfsolver_newton; // wybor metody (newton)
    else if(strcmp(args[1],"secant")==0)
        T = gsl_root_fdfsolver_secant; // wybor metody (uproszczony newton)
    else if(strcmp(args[1],"steffenson")==0)
        T = gsl_root_fdfsolver_steffenson; // wybor metody (steffenson)
    else
    {
        printf("Uzycie: fdf metoda, gdzie metoda = {newton, secant, steffenson}\n");
        return 1;
    }

    s = gsl_root_fdfsolver_alloc (T); // alokacja solvera na bazie tej metody
    gsl_root_fdfsolver_set (s, &F, r); // przypisanie solverowi funkcji i puntu startowego

    printf ("using %s method\n",
            gsl_root_fdfsolver_name (s)); // wypisanie nazwy metody

    printf ("%-5s %10s %10s %10s\n", "iter", "root", "err", "err(est)");

    do
    {
        iter++;
        status = gsl_root_fdfsolver_iterate (s);
        r0 = r;
        r = gsl_root_fdfsolver_root (s);
        status = gsl_root_test_delta (r, r0, 0, 1e-3);

        if (status == GSL_SUCCESS)
            printf ("Converged:\n");

        printf ("%5d %10.7f %+10.7f %10.7f\n",
                iter, r, r - r_expected, r - r0);
    }
    while (status == GSL_CONTINUE && iter < max_iter);
    gsl_root_fdfsolver_free(s);
    return status;
}
