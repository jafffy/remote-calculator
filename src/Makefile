CFLAGS=-std=c99

all: server client

server: server.o common.o
	gcc -o server server.o

client:	client.o common.o
	gcc -o client client.o

server.o: server.c
	gcc -c server.c $(CFLAGS) 2> build-server.err

client.o: client.c
	gcc -c client.c $(CFLAGS) 2> build-client.err

common.o: common.c
	gcc -c common.c $(CFLAGS) 2> build-common.err

clean:	
	rm server client *.o *.err
