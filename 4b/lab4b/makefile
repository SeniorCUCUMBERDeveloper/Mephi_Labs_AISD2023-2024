COMPILER = gcc


all: run 

run: main
	$(COMPILER) main.c -L./ -l:osn.a -o run -lm
	rm osn.a

main:
	$(COMPILER) -c ./lib.c -o osnov.o
	$(COMPILER) -c ./dialog.c -o osn.o
	ar r osn.a osn.o osnov.o
	rm osnov.o
	rm osn.o
