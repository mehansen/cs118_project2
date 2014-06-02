CC=gcc
CFLAGS=-I.
DEPS= header.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: server.o
	$(CC) -o server server.o -I.

client: client.o
	$(CC) -o client client.o -I.

clean:
	rm -rf *o client server