prog: main.o Funcoes.o
	gcc -o prog main.o Funcoes.o 

main.o: main.c Funcoes.h Estruturas.h
	gcc -c main.c Funcoes.h Estruturas.h

Funcoes.o: Funcoes.c Funcoes.h Estruturas.h
	gcc -c Funcoes.c Funcoes.h Estruturas.h