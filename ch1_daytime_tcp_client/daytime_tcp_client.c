#include <stdlib.h>
#include <stdio.h>

#include <sys/errno.h>

#include <sys/socket.h> // socket
#include <netinet/in.h> // socketaddr_in
#include <arpa/inet.h>	// inet_pton
#include <unistd.h>     // read

#include "../include/easy_log.h"



int main(int argc, char *argv[])
{
  char *ip="172.18.12.68";
  
  int nSockFD;
  
  struct sockaddr_in   server_address;
  
  int read_bytes = 0;
  char recv_buf[BUF_STRING_LEN_4K];
  int error_code;
  
  // 创建 socket
  if((nSockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
      CONSOLE_ERROR_LOG(nSockFD);
  }
  // 服务器地址
  bzero(&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(13);
  
  if(inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0)
    CONSOLE_ERROR_LOG_FMT(0, "inet_pton error for %s", ip);
  
  if((error_code = connect(nSockFD, (struct sockaddr*)&server_address, sizeof(server_address))) < 0)
    CONSOLE_ERROR_LOG(error_code);
    
  while((read_bytes = read(nSockFD, recv_buf, BUF_STRING_LEN_4K)) > 0)
  {
     recv_buf[read_bytes] = 0;
     
     if(fputs(recv_buf, stdout) == EOF)
      CONSOLE_ERROR_LOG_FMT(0, "fputs error");
  }
  
   if(read_bytes < 0)
        CONSOLE_ERROR_LOG_FMT(read_bytes, "read error");
        
  
  exit(EXIT_SUCCESS);
}