all: main

main: main.o sorted-list.o
	gcc -o sl main.o sorted-list.o
main.o: main.c
	gcc -c main.c
sorted-list.o: sorted-list.h sorted-list.c
	gcc -c sorted-list.c
clean:
	rm -rf *.o sl
run: 
	./sl 1 2 3 4 5 6 7

# John Eng and Jamie Liao
