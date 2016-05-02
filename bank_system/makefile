
COMPILER = gcc
FLAGS = -c
OUT = -o

all: server.o client.o server.c client.c
	$(COMPILER) $(OUT) server server.c
	$(COMPILER) $(OUT) client client.c

server: server.o server.c
	$(COMPILER) $(OUT) server server.c

server.o: server.c 
	$(COMPILER) $(FLAGS) server.c 
client.o: client.c
	$(COMPILER) $(FLAGS) client.c
	
clean:
	rm -rf *.o server client
		
