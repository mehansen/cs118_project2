NOTES & SOURCES:

creating a socket:
	http://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html

beej's guide:
	http://www.beej.us/guide/bgnet/output/html/singlepage/bgnet.html#getaddrinfo




GO-BACK-N Notes
* TA's link to demo: http://www.ccs-labs.org/teaching/rn/animations/gbn_sr/
* Main Idea
	- sender allowed to transmit multpile packets without waiting for ackowlegement, but is constrained to having no more than N unacknowledged packets in the pipeline
* window size N = max range of permissible sequence numbers for transmitted but not yet acknowledged sequence numbers
* about packet sequence numbers
	- carried in a fixed-length field in packet header
	- if k is the number of bits in the packet sequence number field, then range of number is 0 to 2^k-1
	- with finite range of sequence numbers => use modulo 2^k arithmetic 
* Finite state machine of ACK-based, NAK-free Go-Back-N protocol on page 221 in textbook (ch 3.4.3)
* 3 types of events that Go-Back-N sender must respond to
	- Invocation from above: 
			~ call send(), then first check to see if window is full (N unACK-ed packages) 
				~If window not full, packet created and sent (& variables updated)
				~If window full, sender returns data back to upper layer (upper layer would try again later or perhaps would buffer the data or have a synchronization mechanism that allows the upper layer to call send() only when it's not full)
	- Receipt of an ACK: 
			~ acknowledgement for a packet with sequence number n is a cumulative acknowledgment, i.e. an indication that all packets with a sequence number up to and including n have been correctly received at the receiver
	- Timeout event: 
			~ timer used to recover from lost data or ACK packets (like in the stop-and-wait protocol)
			~ if timeout occurs, sender resends all packets that have been previously sent but not yet acknowleged
			~ if ACK is received but there are still additional transmitted but not yet acknowledged packets, timer is restarted
			~ if there are no outstanding, unacknowledged packets, the timer is stopped
* receiver's actions in Go-Back-N
	- if a packet with sequence number n is received correctly in order (right after a packet with sequence number n-1 was delivered to the upper layer), receiver sends an ACK for packet n and delivers the data to the upper layer
	- in all other cases, receiver discards packet and resends an ACK for the most recently received in-order packet (note: since packets are delivered one at a time to upper layer, if packet k has been received & delivered, then all packets with a sequence number lower than k have also been delivered)
* receivers don't need to buffer out of order packets because, if packet n is lost, both packet n and packet n + 1 will eventually be retransmitted
	=> receiver only needs to maintain sequence number of the next-in-order package
	=> sender must maintain upper and lower bounds of its window and the position of the next sequence number within this window
*  summary of techniques in GBN protocol: sequence numbers, cumulative acknowledgements, checksums, and a timeout/retransmit operation