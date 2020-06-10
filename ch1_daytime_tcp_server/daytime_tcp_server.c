#include <stdlib.h>
#include <stdio.h>

#include <sys/errno.h>

#include <sys/socket.h> // socket
#include <netinet/in.h> // socketaddr_in
#include <arpa/inet.h>	// inet_pton
#include <unistd.h>     // read
#include <time.h>       // time_t

#include "../include/easy_log.h"

/*
 * netstat -ntlp | grep 13 # 查看 TCP 13 端口监听情况
 */
int main(int argc, char *argv[])
{
  time_t ticks;
  char buf[BUF_STRING_LEN_4K];

  int socket_listen_fd;
  int socket_conn_fd;
  
  struct sockaddr_in server_addr;
  
  char *ptr;
  int backlog = SOMAXCONN;
  
  socket_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  bzero(&server_addr, sizeof(server_addr));
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(13);
  
  // bind
  if(bind(socket_listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
     CONSOLE_ERROR_LOG_FMT(0, "bind error");
     
  // listen
  if((ptr = getenv("LISTENQ")) != NULL)
    backlog = atoi(ptr);
    
  if(listen(socket_listen_fd, backlog) < 0)
     CONSOLE_ERROR_LOG_FMT(0, "listen error");
  
  for(;;)
  {
    socket_conn_fd = accept(socket_listen_fd, (struct sockaddr*)NULL, NULL);
    if(socket_conn_fd < 0)
      CONSOLE_ERROR_LOG_FMT(0, "accept error");
      
    printf("client connect fd=%d\r\n", socket_conn_fd);
      
    ticks = time(NULL);
    bzero(buf, BUF_STRING_LEN_4K);
    
    int nBytes = snprintf(buf, BUF_STRING_LEN_4K, "%.24s\r\n", ctime(&ticks));
    
    if(write(socket_conn_fd, buf, nBytes) < 0)
      CONSOLE_ERROR_LOG_FMT(0, "write error");
      
    if(close(socket_conn_fd) == -1)
      CONSOLE_ERROR_LOG_FMT(0, "close error");
  }
  
  exit(EXIT_SUCCESS);
}