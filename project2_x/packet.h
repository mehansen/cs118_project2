#define DATA_SIZE 128

struct packet
{
  int ack_no;
  int seq_no;
  int length;
  char data[DATA_SIZE];
  
};