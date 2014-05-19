// server.cpp

// PURPOSE:	just run everything obviously
//			parse parameters and implement the server behavior as it sends packets/ACKs, receives packets/ACKs, waits, etc.
// INPUT:	./server port_number congestion_window_size prob_loss prob_corruption
//			will be passed into argv
int main(int argc, char* argv[]) {
	if(argc != 4)
	{
		printf("Incorrect number of arguments. Server will not run.");
		exit(0);
	}

	//parse parameters
	//find out how to send stuff over UDP
	//	will probably be similar to how we sent stuff to the browser in project 1

	//pseudocode from discussion:
	//	- loop indefinitely waiting for a file request, break when incoming request is not corrupted or lost
	//	- use Go-Back-N and sliding window to track which packet to send and when to send it
	//		- use header.h to format headers and process headers of incoming packets
	//		- basic implementation: a timer is set for oldest unACKed packet, and if timeout occurs, resend all packets in
	//		  the window
	//	- once end of file is reached, send FIN and set timer
	//		- keep resending FIN until FIN ACK is received (then send ACK and close), or it times out (then close)