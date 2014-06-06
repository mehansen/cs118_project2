CC=gcc
CFLAGS=-I.
DEPS= header.h

all: server client

server: server.o
	$(CC) server.c -o server

client: client.o
	$(CC) client.c -o client

clean:
	rm -rf *o client server
	killall -9 server