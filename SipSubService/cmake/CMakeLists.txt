SET(EXE_NAME SipSubService)
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

#SET(CMAKE_EXE_LINKER_FLAGS " -no-pie")

ADD_DEFINITIONS(-g)
	
#ADD_DEFINITIONS(-D_GLIBCXX_USE_CXX11_ABI=0)

AUX_SOURCE_DIRECTORY(../src SRC)
AUX_SOURCE_DIRECTORY(../src/h26x SRC1)
INCLUDE_DIRECTORIES(../include)
INCLUDE_DIRECTORIES(../include/h26x)
INCLUDE_DIRECTORIES(../../3rd/include)
INCLUDE_DIRECTORIES(../../3rd/include/pjsip)
INCLUDE_DIRECTORIES(../../3rd/include/jrtplib3)
INCLUDE_DIRECTORIES(../../3rd/include/jthread)
INCLUDE_DIRECTORIES(../../3rd/include/tinyxml2)
INCLUDE_DIRECTORIES(../../3rd/include/libevent)
INCLUDE_DIRECTORIES(../../3rd/include/mpege)

LINK_DIRECTORIES(../../3rd/lib)

ADD_EXECUTABLE(${EXE_NAME} ${SRC} ${SRC1})

TARGET_LINK_LIBRARIES(${EXE_NAME} libglog.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} -lpthread libgflags.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} -lpjsua2-x86_64-unknown-linux-gnu -lpjsua-x86_64-unknown-linux-gnu -lpjsip-ua-x86_64-unknown-linux-gnu -lpjsip-simple-x86_64-unknown-linux-gnu -lpjsip-x86_64-unknown-linux-gnu -lpjmedia-codec-x86_64-unknown-linux-gnu -lpjmedia-videodev-x86_64-unknown-linux-gnu -lpjmedia-audiodev-x86_64-unknown-linux-gnu -lpjmedia-x86_64-unknown-linux-gnu -lpjnath-x86_64-unknown-linux-gnu -lpjlib-util-x86_64-unknown-linux-gnu -lsrtp-x86_64-unknown-linux-gnu -lresample-x86_64-unknown-linux-gnu -lgsmcodec-x86_64-unknown-linux-gnu -lspeex-x86_64-unknown-linux-gnu -lilbccodec-x86_64-unknown-linux-gnu -lg7221codec-x86_64-unknown-linux-gnu -lyuv-x86_64-unknown-linux-gnu -lwebrtc-x86_64-unknown-linux-gnu -lpj-x86_64-unknown-linux-gnu -lpjsdp-x86_64-unknown-linux-gnu -lasound)
TARGET_LINK_LIBRARIES(${EXE_NAME} -lstdc++ libjrtp.a libjthread.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} libtinyxml2.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} libjsoncpp.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} libevent.a libevent_pthreads.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} libmpeg.a)
TARGET_LINK_LIBRARIES(${EXE_NAME} -luuid)
