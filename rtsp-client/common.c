#include "common.h"

#include <sys/socket.h> // socket
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>

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
  int l_s32error;

  int s32RecvBuf = 0;
  int s32SendBuf = 0;
  socklen_t opt_len = sizeof(int);

  static int flags = 0;
  struct sockaddr_in l_srSaddr;
  
  fd_set l_stRset;
  fd_set l_stWset;

  struct timeval l_stTimeval;
  
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
   
   //
     
  FD_ZERO(&l_stRset);
  FD_ZERO(&l_stWset);
  
  FD_SET(socketFd, &l_stRset);
  FD_SET(socketFd, &l_stWset);
  
 	l_stTimeval.tv_sec  = 10;
	l_stTimeval.tv_usec = 0;
 
  if((ret = select(socketFd+1, &l_stRset, &l_stWset, NULL, &l_stTimeval)) <= 0)
  {
     CONSOLE_ERROR_LOG_FMT(ret, "TCP Connect error...");
     close(socketFd);
     return D_ERROR;
  }
  
  if(FD_ISSET(socketFd, &l_stRset))
  {
    if(getsockopt(socketFd,SOL_SOCKET,SO_ERROR,&l_s32error, &opt_len) <0)
        {
            printf("TCP CONNECT: error...\n");
            close(socketFd);
            return D_ERROR;
        }
  }
  
   return D_SUCCESS;
}

int NET_SocketSendData(int s32SocketFd,char *ps8buf,int s32Size){
  int l_s32Ret;
	 if(NULL == ps8buf)
	 {
          printf("%s,%d buf is NULL\n",__FILE__,__LINE__);
          return -1;
	 }
     l_s32Ret = send(s32SocketFd,ps8buf,s32Size,0);
     if( l_s32Ret < 0)
     {
          printf("%s,%s,%d,SendFalse:%d\n",__FILE__,__FUNCTION__,__LINE__,s32SocketFd);
          return -1;
     }
     
     CONSOLE_INFO_LOG_FMT("Send data:%slen:%d", ps8buf, l_s32Ret);
     return l_s32Ret;
}


int NET_SocketRecvData(int s32SocketFd,void  *ps8buf,int s32Len)
{
	int l_s32Count = 3;
    ssize_t s32Size;
	while(l_s32Count-->0)
	{
		s32Size = recv(s32SocketFd,ps8buf,s32Len,0);
		if(s32Size==0)
		{
			usleep(300000);
			continue;
		}
		else if(s32Size < 0)
		{
			perror("recv err :");
			printf("[%s,%d:] s32SocketFd = %d, s32Size = %d\n",__FUNCTION__,__LINE__,s32SocketFd,(int)s32Size);
			return -1;
		}else if(s32Size > 0)
		{
			break;
		}
	}

    return s32Size; 
}