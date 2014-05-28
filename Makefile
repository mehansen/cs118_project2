CC=gcc
CFLAGS=-I.
DEPS= header.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

client: client.o
	$(CC) -o client client.o -I.

server: server.o
	$(CC) -o server server.o -I.

clean:
	rm -rf *o client server