#define DATA_SIZE 128

struct packet
{
  int packtype; //0: request, 1: ACK, 2: data, 3: FIN
  int ack_no;
  int seq_no;
  int length;
  char message[DATA_SIZE];
  
};