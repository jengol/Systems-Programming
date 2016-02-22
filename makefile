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
	./sl 4 5 3 6 2 7 1

# John Eng and Jamie Liao
