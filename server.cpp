// server.cpp

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

//#define MYPORT "3530"
#define BACKLOG 5

// PURPOSE:	just run everything obviously
//			parse parameters and implement the server behavior as it sends packets/ACKs, receives packets/ACKs, waits, etc.
// INPUT:	./server port_number congestion_window_size prob_loss prob_corruption
//			will be passed into argv
int main(int argc, char* argv[]) {
	if(argc != 5)
	{
		printf("Incorrect number of arguments. Server will not run.");
		exit(0);
	}

	//put parameters into variables for ease of reading
	char* portno = argv[1];
	char* congestionsz = argv[2];
	double prob_loss = atof(argv[3]);
	double prob_corruption = atof(argv[4]);

	//use getaddrinfo() to prepare to make a socket
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;

	memset(&hints, 0, sizeof hints);
	//set up hints with connection info
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if((status = getaddrinfo(NULL, portno, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	//servinfo now contains address info

	//create socket and listen()
	//we're now listening
	int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	if(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
		perror("bind failed");
		return (0);
	}
	free(servinfo);
	while(1) {
		//listen(sockfd, BACKLOG);

		//accept()
		//store the incoming socket address
		struct sockaddr_storage inc_addr;
		socklen_t addr_size = sizeof (inc_addr);
		int new_fd = accept(sockfd, (struct sockaddr *)&inc_addr, &addr_size);

		char* msgbuff;
		if (recv(new_fd, msgbuff, 10, 0) >= 0)
			printf("Message is: %s", msgbuff);
	}
}

	//go back and put listen() in loop so that it only continues if no corruption

	//pseudocode from discussion:
	//	- loop indefinitely waiting for a file request, break when incoming request is not corrupted or lost
	//	- use Go-Back-N and sliding window to track which packet to send and when to send it
	//		- use header.h to format headers and process headers of incoming packets
	//		- basic implementation: a timer is set for oldest unACKed packet, and if timeout occurs, resend all packets in
	//		  the window
	//	- once end of file is reached, send FIN and set timer
	//		- keep resending FIN until FIN ACK is received (then send ACK and close), or it times out (then close)