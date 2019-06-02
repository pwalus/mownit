all:
	gcc -o i_akima.o i_akima.c -lgsl -lgslcblas;
	gcc -o i_akima_periodic.o i_akima_periodic.c -lgsl -lgslcblas;
	gcc -o i_cspline.o i_cspline.c -lgsl -lgslcblas;
	gcc -o i_cspline_periodic.o i_cspline_periodic.c -lgsl -lgslcblas;
	gcc -o i_linear.o i_linear.c -lgsl -lgslcblas;
	gcc -o i_polynomial.o i_polynomial.c -lgsl -lgslcblas;
	gcc -o i_steffen.o i_steffen.c -lgsl -lgslcblas;
clean:
	rm *.o
