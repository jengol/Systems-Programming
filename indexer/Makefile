all: main

run: main
	./index /ilab/users/je283/Desktop/output.txt /ilab/users/je283/Desktop/testFolder
	
main: indexer.o token.o sorted-list.o
	cc -Wall indexer.o token.o sorted-list.o -o index  

indexer.o: indexer.c indexer.h
	cc -c indexer.c

token.o: token.c
	cc -c token.c

sorted-list:o sorted-list.c sorted-list.h
	cc -c sorted-list.c

clean:
	rm -rf *.o index 

#John Eng (je283) and Marielle Jurist (mlj85)
