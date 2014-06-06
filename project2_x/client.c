/*
** client.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "packet.h"

// INPUT:   ./client server_hostname server_port_number filename prob_loss prob_corruption
//          will be passed into argv
int main(int argc, char *argv[])
{
    //ARGUMENT PROCESSING
    if(argc != 6)
    {
        printf("Incorrect number of arguments. Client will not run.\n");
        exit(0);
    }

    //put parameters into variables for ease of reading
    char* hostname = argv[1];
    char* portno = argv[2];
    char* filename = argv[3];
    double prob_loss = atof(argv[4]);
    double prob_corruption = atof(argv[5]);

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], portno, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to bind socket\n");
        return 2;
    }

    //create a request packet
    struct packet req;
    req.packtype = 0;
    strcpy(req.message, filename);
    req.length = sizeof (int) * 4 + strlen(filename) + 1;

    if ((numbytes = sendto(sockfd, &req, req.length, 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("client: sendto");
        exit(1);
    }

    freeaddrinfo(servinfo);

    printf("client: sent %d bytes to %s\n", numbytes, argv[1]);
    close(sockfd);

    return 0;
}