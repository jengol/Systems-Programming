main: main.c sorted-list.o
	gcc -o main main.c sorted-list.o
sorted-list.o: sorted-list.h sorted-list.c
	gcc -c sorted-list.c
clean:
	rm -rf *.o
