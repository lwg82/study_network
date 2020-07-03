/************************************************************
*Copyright (C),shuangyan5230@163.com
*FileName: rtsp_client.h
*BlogAddr: 
*Description: RTSP Э�� 
*Date:	   2020-07-03
*Author:   Willian Lee
*Version:  V1.0
*Others:
*History:
***********************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#define UNUSED_PARAMETER(p)  (void)p


/***********��������***********/
#define D_SUCCESS   0
#define D_ERROR     0xFFFFFFFF

/***********��������***********/
#define MAINSTREAM  0x01   /**ֻ����������**/
#define SUBSTREAM   0x03   /**ֻ����������**/

/*
 * RTSP ����
 */
typedef struct{
  int  s32SockFd;             /** RTSP socket */

  char arrs8RTSPUrl[128];     /**RTSP��ַ**/
	char arrs8ServerIP[32];     /**RTSP�����IP**/
	int  arrs8SerRTPPort[12];	  /**�����RTP �˿ں�**/
 
  char arrs8User[32];
  char arrs8Pwd[32];
  
  int  s32StreamType;         /** �������� */
 
}RTSP_CLIENT_Data;


/*****************************************/
int NET_SocketCreate();
int NET_SocketClose(int s32SocketFd);
int NET_SocketConnect(int s32SocketFd,char *pstIP,int s32Port);
int NET_SocketSendData(int s32SocketFd,char *ps8buf,int s32Size);
int NET_SocketRecvData(int s32SocketFd,void  *ps8buf,int s32Len);

#endif