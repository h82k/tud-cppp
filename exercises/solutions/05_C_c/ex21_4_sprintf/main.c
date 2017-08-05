#include <stdio.h>  // 'printf', 'sprintf'
#include <stdlib.h> // 'malloc'

/*
 * This program demonstrates the usage of sprintf
 */ 
int main(void) {
  char *buffer = malloc(100 * sizeof(char));
  
  // Printing an uninitialized buffer is risky
  printf("Uninitialized buffer content:'%s'\n", buffer);
  buffer[0] = '\0';
  printf("Safe buffer:'%s'\n", buffer);
  
  // We concatenate 'Hello, ' with the given name
  const char* name = "Julius";
  sprintf(buffer, "Hello, %s!\n", name);
  // The buffer may be passed to printf as is.
  printf(buffer);
  
  int i;
  char c = 'a';
  sprintf(buffer, "c = %c, i = %3d", c, i);
  // Or: When invoking printf, the buffer may be used with '%s'
  printf("Refilled buffer: '%s'\n", buffer);
}
