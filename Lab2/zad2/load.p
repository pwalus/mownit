set key left top
set key box vertical spacing 1.5
set title "Wykres testowy"
set xrange [-3:3]
set yrange [-4:5]	
plot 'fun1.txt' title 'Dane z pliku fun1.txt' lt rgb 'red' with yerrorbars , \
2*cos(x*sin(x)) title 'funkcja1: 2*cos(x*sin*(x))' lt rgb 'blue' with boxes , \
sin(x**5) title 'funkcja2: sin(x^5)' lt rgb 'green' with lines , \
3*sin(x) title 'funkcja3: 3*sin(x)' lt rgb 'red' with lines