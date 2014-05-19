// client.cpp

// PURPOSE:	just run everything obviously
// INPUT:	./client server_hostname server_port_number filename prob_loss prob_corruption
//			will be passed into argv
int main(int argc, char* argv[]) {
	if(argc != 5)
	{
		printf("Incorrect number of arguments. Client will not run.");
		exit(0);
	}
}

//pseudocode from discussion:
//	- DNS lookup, create socket, then connect()
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