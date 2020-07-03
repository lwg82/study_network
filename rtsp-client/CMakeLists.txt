project(rtsp-client)

set(HEAD_FILES
  ../include/easy_log.h

  rtsp_client.h
  common.h
)

set(SRC_FILES
 ../include/easy_log.c
  rtsp_client.c
  common.c
  main.c
)


add_executable(${PROJECT_NAME}
  ${HEAD_FILES}
  ${SRC_FILES}
)