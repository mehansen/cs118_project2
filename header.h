// header.h

// just basically have functions that create and unpack headers, and return the necessary info
// necessary info is like:
//		- sequence number
//		- ACK number
//		- timestamp (is this technically necessary?)
//		- content length (max data length is 1K bytes)
//		- FIN packet