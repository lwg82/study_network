/*
 * 测试 makefile
 */

#include <stdlib.h> // EXIT_SUCCESS
#include <stdio.h>
#include <stdint.h> // uintptr_t

#define UNUSED_PARAMETER(param) (void)param

// 大端，小端
// centos  小端
// windows 大端
void byte_order()
{
   union{
     short s;
     char  c[sizeof(short)];
   } un;
  
   un.s = 0x0102;
   
   if(sizeof(short) == 2)
   {
     if(un.c[0] == 1 &&  un.c[1] == 2)
       printf("big-endian\n");
     else if(un.c[0] == 2 && un.c[1] == 1)
       printf("little-endian\n");
     else 
       printf("unknown\n");
   }
   else
     printf("sizeof(short)=%ld\n", sizeof(short));
}

int main(int argc, char *argv[])
{
  printf("hello \r\n");
  printf("uintptr_t=%ld \r\n", sizeof(uintptr_t));

  byte_order();
  
  UNUSED_PARAMETER(argc);
  UNUSED_PARAMETER(argv);
  exit(EXIT_SUCCESS);
}
