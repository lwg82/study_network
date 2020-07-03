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
#ifndef _RTSP_H_
#define _RTSP_H_



#include "common.h"

/*
 * https://blog.csdn.net/li_wen01/article/details/101108667
 */


int RTSP_CLIENT_Init(RTSP_CLIENT_Data *data);
int RTSP_CLIENT_Release(RTSP_CLIENT_Data *data);
int RTSP_CLEINT_Session(RTSP_CLIENT_Data *data);

// 获取服务端提供的可用方法
int RTSP_Client_OPTIONS(RTSP_CLIENT_Data *data);

#endif



