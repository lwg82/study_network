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

#define BUF_LEN_1024_BYTE 	 1024	
#define RTSP_DEFAULT_PORT    554


static int gs_s32CseqCount    = 1;

static int IPC_RTSP_OPTIONSHandle(RTSP_CLIENT_Data *data,char *ps8buf,int s32Type)
{
  switch(s32Type){
    case 0:
    {
      sprintf(ps8buf,"OPTIONS %s RTSP/1.0\r\nCSeq: %d\r\nUser-Agent: Willian Lee\r\n\r\n",\
				data->arrs8RTSPUrl,gs_s32CseqCount);
      break;
    }
    
  }

  return s32Type;
}

int RTSP_CLIENT_Init(RTSP_CLIENT_Data *data)
{
  UNUSED_PARAMETER(data);
  return D_SUCCESS;
}

int RTSP_CLIENT_Release(RTSP_CLIENT_Data *data)
{
  CONSOLE_INFO_LOG_FMT("socket: %d --> -1", data->s32SockFd);

  if(data->s32SockFd > 0){
    close(data->s32SockFd);
    data->s32SockFd = -1;
  }
  
  
  
  return D_SUCCESS;
}

int RTSP_CLEINT_Session(RTSP_CLIENT_Data *data)
{
  int ret;
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
  
  if(ret < 0){
    return ret;
  }

  data->s32SockFd = socketFd;
  
  return D_SUCCESS;
}

int RTSP_Client_OPTIONS(RTSP_CLIENT_Data *data)
{
  int l_s32Ret;
  char l_arrs8Buf[BUF_LEN_1024_BYTE];
  
  int l_s32RtspSocketFd = data->s32SockFd;
  
  bzero(l_arrs8Buf,BUF_LEN_1024_BYTE); 
  for(int i=0; i<1; i++)
  {
    IPC_RTSP_OPTIONSHandle(data, l_arrs8Buf, i);// 组合 option
    l_s32Ret = NET_SocketSendData(l_s32RtspSocketFd, l_arrs8Buf, strlen(l_arrs8Buf)); // 发送命令
    
    if(l_s32Ret < 0)
    {
      CONSOLE_ERROR_LOG_FMT(l_s32Ret, "Send data error ");
      return D_ERROR;
    }
    
    // 接受数据 Replay
    bzero(l_arrs8Buf,BUF_LEN_1024_BYTE);
    l_s32Ret = NET_SocketRecvData(l_s32RtspSocketFd, l_arrs8Buf, BUF_LEN_1024_BYTE);
    if(l_s32Ret <= 0)
		{
			printf("[%s %d:] RTSP recv data error \n",__FUNCTION__,__LINE__);
			gs_s32CseqCount++;
			continue;

		}else
		{
			printf("[%s %d:] Recv Data: %s \n",__FUNCTION__,__LINE__,l_arrs8Buf);
		}
   
   // 
    
  }
  

  return D_SUCCESS;
}