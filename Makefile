CC=gcc
CFLAGS=-I.
DEPS= header.h

all: server client

server: server.o
	$(CC) server.cpp -o server

client: client.o
	$(CC) client.cpp -o client

clean:
	rm -rf *o client server
	killall -9 server