COMPILER = gcc


all: run 

run: main
	$(COMPILER) main.c -L./ -l:osnov.a -o run -lm
	rm osnov.a

main:
	$(COMPILER) -c ./newlib.c -o osnov.o
	ar r osnov.a osnov.o
	rm osnov.o
