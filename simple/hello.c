/*
 * ≤‚ ‘ makefile
 */

#include <stdlib.h> // EXIT_SUCCESS
#include <stdio.h>
#include <stdint.h> // uintptr_t

int main(int argc, char *argv[])
{
  printf("hello \r\n");
  printf("uintptr_t=%ld \r\n", sizeof(uintptr_t));

  exit(EXIT_SUCCESS);
}
