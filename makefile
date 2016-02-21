all: main

main: main.o sorted-list.o
	gcc -o program main.o sorted-list.o
main.o: main.c
	gcc -c main.c
sorted-list.o: sorted-list.h sorted-list.c
	gcc -c sorted-list.c
clean:
	rm -rf *.o program


# John Eng and Jamie Liao