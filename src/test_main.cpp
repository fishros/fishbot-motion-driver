#include "communicate/serial_communicate.h"
int main(int argc,char* argv[])
{
  SerialCommunicate s("/dev/ttyS12");
  sleep(1000);
  return 0;
}