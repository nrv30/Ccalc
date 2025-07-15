CFLAGS = -Wall -Wextra #-Werror

calc: calc.c queue.o stack.o
	gcc $(CFLAGS) calc.c queue.o stack.o -o calc

queue.o: queue.c
	gcc -c queue.c -o queue.o

stack.o: stack.c
	gcc -c stack.c -o stack.o

clean: 
	-del *.o calc.exe