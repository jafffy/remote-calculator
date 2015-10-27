CFLAGS=-std=c99

all: server client

server: server.o
	gcc -o server server.o

client:	client.o
	gcc -o client client.o

server.o: server.c
	gcc -c server.c $(CFLAGS) 2> build-server.err

client.o: client.c
	gcc -c client.c $(CFLAGS) 2> build-client.err

clean:	
	rm server client *.o *.err
