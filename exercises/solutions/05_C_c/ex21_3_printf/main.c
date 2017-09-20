#include <stdio.h>  // 'printf'
#include <string.h> // 'strcpy'
#include <stdlib.h> // 'malloc'

/*
 * This program demonstrates 
 * (i)  a few usage examples of printf
 * (ii) how to print out memory contents (on the heap) by removing the terminating '\0'
 * (iii)how to shorten C strings by inserting '\0'
 */ 
int main(void) {
  /*
   * Basic experiments with printf
   */
  printf("Hello World\n");
  int i;
  printf("i = %d\n", i);
  printf("i = %3d\n", i);
  char c;
  printf("c = %c, i = %3d\n", c, i);
  
  /*
   * Breaking the convention that C strings are '\0'-terminated
   */
  // Option 1: 
  // String 'Hello' resides in 'data' segment. 
  // Writing to this segment results in a runtime error ('Segmentation fault')
  // char *myString = "Hello!!";
  
  // Option 2: 
  // String 'Hello' resides on heap. 
  char *dummyBuffer = malloc(19 * sizeof(char));
  strcpy(dummyBuffer, "AlterTextAlterText");
  free(dummyBuffer);
  printf("Address of dummyBuffer: %p\n", dummyBuffer);
  char *buffer = malloc(6 * sizeof(char));
  printf("Address of buffer:      %p\n", buffer);
  for (int i = 0; i < 19; ++i)
  {
	  printf("%x ", buffer[i]);
  }
  
  strcpy(buffer, "Hello!!");
  printf("%s\n", buffer);
  
  // 'buffer' is a char-array of length 6 (incl. '\0')
  buffer[strlen(buffer)] = '_';
  printf("%s\n", buffer); // (for option 2): Should produce 'Hello_' + something surprising

  
  /*
   * Quick 'n' dirty shortening of a C string
   */
  buffer[2] = '\0';
  printf("%s\n", buffer); 
}
