all: main

run: main
	./index
	
main: indexer.o tokenizer.o sorted-list.o
	cc -Wall indexer.o tokenizer.o sorted-list.o -o index  

indexer.o: indexer.c indexer.h
	cc -c indexer.c

tokenizer.o: tokenizer.c
	cc -c tokenizer.c

sorted-list:o sorted-list.c sorted-list.h
	cc -c sorted-list.c

clean:
	rm -rf *.o index 

#John Eng (je283) and Marielle Jurist (mlj85)
