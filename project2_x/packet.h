#define DATA_SIZE 128

struct packet
{
  int packtype; //1: ACK, 2: request, 3: data, 4: FIN
  int ack_no;
  int seq_no;
  int length;
  char message[DATA_SIZE];
  
};