#write by lifuling(lifulinghan@126.com)
cmake_minimum_required(VERSION 2.5)
project(Afetion)

IF(UNIX)
link_directories(/usr/lib/x86_64-linux-gnu)
link_libraries(curl)
#include_directories()
ENDIF(UNIX)

IF(WIN32)
link_directories("E:\\code\\SDK\\curl-7.28.0\\lib")
link_libraries(libcurld_imp)
include_directories("E:\\code\\SDK\\curl-7.28.0\\include")

ENDIF(WIN32)

add_executable(Afetion parson.c netCore.c msg.c login.c libfetion.c  friend.c main.c)
