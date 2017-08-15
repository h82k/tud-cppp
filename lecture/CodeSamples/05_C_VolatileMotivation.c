#include <stdio.h>  // For printf
#include <unistd.h> // For sleep

int signal;

void receiverThread(void) {
  signal = 0; // Set default state
  while(signal == 0); // Empty loop   
  printf("Received signal!\n");
}

void senderThread(void) {
  sleep(1000);
  signal = 1;
}

int main() {
  // Start receiverThread asynchronously
  // Start senderThread asynchronously
  // Wait for threadA and threadB to terminate
}