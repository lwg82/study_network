#include <stdlib.h>

#include "../include/easy_log.h"
#include "rtsp_client.h"

#define TEST_RTSP_URL_MAIN "rtsp://172.18.12.201:554/user=admin_password=y77t349x_channel=1_stream=0.sdp?real_stream"
#define TEST_RTSP_URL_SUB  "rtsp://172.18.12.201:554/user=admin_password=y77t349x_channel=1_stream=1.sdp?real_stream"

void ForDebug(){
  int nRet = D_SUCCESS;
  RTSP_CLIENT_Data rtsp_client_data = {0};
  
  nRet = RTSP_CLIENT_Init(&rtsp_client_data);
  
  if(nRet != D_SUCCESS){
    CONSOLE_ERROR_LOG_FMT(0, "Rtsp client init error %d ", nRet);
    return;
  }
   
  // 初始化 rtsp 
  snprintf(rtsp_client_data.arrs8RTSPUrl, 128, "%s", TEST_RTSP_URL_MAIN);
  snprintf(rtsp_client_data.arrs8ServerIP, 32, "%s", "172.18.12.201");
  // 没有设置默认端口号
  snprintf(rtsp_client_data.arrs8User, 32, "%s", "admin");
  snprintf(rtsp_client_data.arrs8Pwd, 32, "%s", "wiscom123");
  
  rtsp_client_data.s32StreamType = MAINSTREAM;
  
  // 建立 session
  if((nRet=RTSP_CLEINT_Session(&rtsp_client_data)) != D_SUCCESS){
    CONSOLE_ERROR_LOG_FMT(0, "Rtsp client session error %d ", nRet);
    return;
  }
  
  // option
  if((nRet=RTSP_Client_OPTIONS(&rtsp_client_data)) != D_SUCCESS){
    CONSOLE_ERROR_LOG_FMT(0, "Rtsp client option error %d ", nRet);
    return;
  }
  
  
  // release
  if((nRet=RTSP_CLIENT_Release(&rtsp_client_data)) != D_SUCCESS){
    CONSOLE_ERROR_LOG_FMT(0, "Rtsp client release error %d ", nRet);
    return;
  }
}

int main(int argc, char* argv[])
{
  ForDebug();
  
  exit(EXIT_SUCCESS);
}