#include "common.h"

#include <sys/socket.h> // socket
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>


#include "easy_log.h"



int NET_SocketCreate(){
  
  int socketFd = 0;
  
  socketFd = socket(AF_INET, SOCK_STREAM, 0);
  
  if(socketFd < 0){
     CONSOLE_ERROR_LOG_FMT(socketFd, "Create socket is failed ");
  }
  return socketFd;
}

int NET_SocketClose(int s32SocketFd)
{
  close(s32SocketFd);
  s32SocketFd = -1;
  return 0;
}

int NET_SocketConnect(int socketFd,char *pstIP,int s32Port)
{
  int ret = 0;

  int s32RecvBuf = 0;
  int s32SendBuf = 0;
  socklen_t opt_len = sizeof(int);

  static int flags = 0;
  struct sockaddr_in l_srSaddr;
  
  if(getsockopt(socketFd, SOL_SOCKET, SO_RCVBUF, &s32RecvBuf, &opt_len) < 0)
    exit(EXIT_FAILURE);
  CONSOLE_INFO_LOG_FMT("Get SO_RCVBUF: %dk ", s32RecvBuf/1024);
  
  if(getsockopt(socketFd, SOL_SOCKET, SO_SNDBUF, &s32SendBuf, &opt_len) < 0)
    exit(EXIT_FAILURE);
  CONSOLE_INFO_LOG_FMT("Get SO_SNDBUF: %dk ", s32SendBuf/1024);
  
  // 默认设置32K
  s32RecvBuf = 32*1024;
  s32SendBuf = 32*1024;
  
  setsockopt(socketFd,SOL_SOCKET,SO_RCVBUF,(const char*)&s32RecvBuf,opt_len);
  setsockopt(socketFd,SOL_SOCKET,SO_SNDBUF,(const char*)&s32SendBuf,opt_len);
  
  s32RecvBuf = s32SendBuf = 0;
  if(getsockopt(socketFd, SOL_SOCKET, SO_RCVBUF, &s32RecvBuf, &opt_len) < 0)
    exit(EXIT_FAILURE);
  CONSOLE_INFO_LOG_FMT("Get SO_RCVBUF: %dk ", s32RecvBuf/1024);
  
  if(getsockopt(socketFd, SOL_SOCKET, SO_SNDBUF, &s32SendBuf, &opt_len) < 0)
    exit(EXIT_FAILURE);
  CONSOLE_INFO_LOG_FMT("Get SO_SNDBUF: %dk ", s32SendBuf/1024);
  
  // 获取却是 64K, 为什么?
  
  // 非阻塞
  flags = fcntl(socketFd,F_GETFD, 0); 
	fcntl(socketFd,F_SETFD, flags|O_NONBLOCK); 
 
  // 连接
  bzero(&l_srSaddr, sizeof(struct sockaddr_in));
  l_srSaddr.sin_family = AF_INET;
  l_srSaddr.sin_port = htons(s32Port);
  l_srSaddr.sin_addr.s_addr = inet_addr(pstIP);
  
  socklen_t slen = sizeof(l_srSaddr); // 使用 socket 类型,兼容64位系统
  if((ret = connect(socketFd, (struct sockaddr *)&l_srSaddr, slen)) < 0)
  {
      CONSOLE_ERROR_LOG_FMT(ret, "connect server: %s:%d", pstIP, s32Port);
  }
  
   CONSOLE_INFO_LOG_FMT("connect server: %s:%d", pstIP, s32Port);
}