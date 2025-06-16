COMPILER = gcc


all: run 

run: main
	$(COMPILER) main.c -L./ -l:osnov.a -o run
	rm osnov.a

main:
	$(COMPILER) -c ./lib.c -o osnov.o
	ar r osnov.a osnov.o
	rm osnov.o

dop: dopl
	$(COMPILER) main.c -L./ -l:dop.a -o run
	rm dop.a

dopl:
	$(COMPILER) -c ./lib2.c -o dop.o
	ar r dop.a dop.o
	rm dop.o
