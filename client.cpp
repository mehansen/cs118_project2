// client.cpp

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define INET6_ADDSTRLEN 46

// PURPOSE:	just run everything obviously
// INPUT:	./client server_hostname server_port_number filename prob_loss prob_corruption
//			will be passed into argv
int main(int argc, char* argv[]) {
	if(argc != 6)
	{
		printf("Incorrect number of arguments. Client will not run.\n");
		exit(0);
	}

	//put parameters into variables
	char* hostname = argv[1];
	char* portno = argv[2];
	char* filename = argv[3];
	double prob_loss = atof(argv[4]);
	double prob_corruption = atof(argv[5]);

	//use getaddrinfo()
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;

	memset(&hints, 0, sizeof hints);
	//set up hints with connection info
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if((status = getaddrinfo(hostname, portno, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}

	//iterate through servinfo and print the IPs
	printf("IP addresses for %s:\n\n", argv[1]);
	struct addrinfo *p;
	for(p = servinfo; p != NULL; p = p->ai_next) {
		void *addr;
		char *ipver;

		if(p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		char ipstr[INET6_ADDSTRLEN];
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("  %s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(servinfo);		//eventually have to free servinfo
}

//pseudocode from discussion:
//	- DNS lookup, create socket, then connect() IN PROGRESS
//		- can also hardcode 'localhost', because this will always be the server
//		- if you look up, you can use getaddrinfo() I think
//	- transmit file request over UDP until ACK is received from server
//		- will need to resend request in cases of corruption or loss
//	- open a file to read into and receive data
//		- write data to the file for every uncorrupted and in-order packet received
//		- send ACK for next expected byte
//		- for every out-of-order or corrupted packet, resend last ACK to get better version of packet
//	- detect FIN fron server
//		- send FIN ACK on timer until either receive server's ACK or until it times out