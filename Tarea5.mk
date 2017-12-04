Resultados_hw5.pdf : plot.png
	pdflatex Resultados_hw5.tex
	rm Resultados_hw5.log Resultados_hw5.aux plot.png dato.dat bayfit.dat curvaRotacion.o

plot.png : dato.dat bayfit.dat
	python Plots.py

dato.dat bayfit.dat: CurvaRotacion.c
	cc -o curvaRotacion.o CurvaRotacion.c -lm
	./curvaRotacion.o
	
	
