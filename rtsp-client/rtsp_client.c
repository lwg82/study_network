#include "rtsp_client.h"

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

int RTSP_CLIENT_Init(RTSP_CLIENT_Data *data)
{
  return D_SUCCESS;
}

int RTSP_CLIENT_Release(RTSP_CLIENT_Data *data)
{
  if(data->s32SockFd > 0){
    close(data->s32SockFd);
    data->s32SockFd = -1;
  }
  
  return D_SUCCESS;
}

int RTSP_CLEINT_Session(RTSP_CLIENT_Data *data)
{
  int ret = 0;
  int socketFd = -1;
  
  char *arrs8ServerIp = "172.18.12.201";
  unsigned short   ulPort = 554;
  
  if(data->s32SockFd > 0){
    close(data->s32SockFd);
  }
  
  
  
  socketFd = NET_SocketCreate();
  if(socketFd < 0){
     exit(EXIT_FAILURE);
  }
  
  CONSOLE_INFO_LOG_FMT("socket: %d", socketFd);
  
  ret = NET_SocketConnect(socketFd, arrs8ServerIp, ulPort);

  return D_SUCCESS;
}