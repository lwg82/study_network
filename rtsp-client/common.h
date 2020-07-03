/************************************************************
*Copyright (C),shuangyan5230@163.com
*FileName: rtsp_client.h
*BlogAddr: 
*Description: RTSP 协议 
*Date:	   2020-07-03
*Author:   Willian Lee
*Version:  V1.0
*Others:
*History:
***********************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#define UNUSED_PARAMETER(p)  (void)p


/***********错误类型***********/
#define D_SUCCESS   0
#define D_ERROR     0xFFFFFFFF

/***********码流类型***********/
#define MAINSTREAM  0x01   /**只开启主码流**/
#define SUBSTREAM   0x03   /**只开启子码流**/

/*
 * RTSP 数据
 */
typedef struct{
  int  s32SockFd;             /** RTSP socket */

  char arrs8RTSPUrl[128];     /**RTSP地址**/
	char arrs8ServerIP[32];     /**RTSP服务端IP**/
	int  arrs8SerRTPPort[12];	  /**服务端RTP 端口号**/
 
  char arrs8User[32];
  char arrs8Pwd[32];
  
  int  s32StreamType;         /** 主从码流 */
 
}RTSP_CLIENT_Data;


/*****************************************/
int NET_SocketCreate();
int NET_SocketClose(int s32SocketFd);
int NET_SocketConnect(int s32SocketFd,char *pstIP,int s32Port);
int NET_SocketSendData(int s32SocketFd,char *ps8buf,int s32Size);
int NET_SocketRecvData(int s32SocketFd,void  *ps8buf,int s32Len);

#endif