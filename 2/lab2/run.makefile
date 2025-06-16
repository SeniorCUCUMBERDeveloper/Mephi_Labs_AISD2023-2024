COMPILER = gcc
export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH

all: run 

run: queue_v
	$(COMPILER) main.c -L./ -l:queue.a -o run
	rm queue.a

queue_v:
	$(COMPILER) -c ./listv.c -o queue.o
	ar r queue.a queue.o
	rm queue.o

run_list: queue_l
	$(COMPILER) main.c -L./ -l:queue.a -o run
	rm queue.a

queue_l:
	$(COMPILER) -c ./listl.c -o queue.o
	ar r queue.a queue.o
	rm queue.o


run_list_d: queue_l_d
	$(COMPILER) main.c -ldl -L./ -l:queue.so -o run -ldl

queue_l_d:
	$(COMPILER) -c  ./listl.c -o queue.o -fPIC
	$(COMPILER) -shared -o queue.so queue.o
	rm queue.o


run_vector_d: queue_v_d
	$(COMPILER) main.c -ldl -L./ -l:queue.so -o run -ldl


queue_v_d:
	$(COMPILER) -c  ./listv.c -o queue.o -fPIC
	$(COMPILER) -shared -o queue.so queue.o
	rm queue.o
