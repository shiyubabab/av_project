/************************************************************************
	> File Name: main.cpp
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Fri 13 Jun 2025 09:37:25 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<glog/logging.h>
#include<signal.h>
#include<pjlib-util.h>
#include<pjmedia.h>
#include<pjsip.h>
#include<pjsip_ua.h>
#include<pjsip/sip_auth.h>

#include<rtpsession.h>
#include<rtpsourcedata.h>
#include<rtptcptransmitter.h>
#include<rtptcptransmitter.h>
#include"tinyxml2.h"
#include<json/json.h>

#include<event2/event.h>
#include<event2/buffer.h>

#include"SipLocalConfig.h"
#include"GlobalCtl.h"
#include"ECThread.h"
using namespace EC;

class GlobalCtl;
#define GBOJ(obj) GlobalCtl::instance()->obj

#define LOG_DIR "/home/mlxh/av_project/log"
#define LOG_FILE_NAME "SipServer.log"

class SetGlogLevel{
	public:
		SetGlogLevel(const int type){
			google::InitGoogleLogging(LOG_FILE_NAME);
			FLAGS_stderrthreshold = type;
			FLAGS_colorlogtostderr = true;
			FLAGS_logbufsecs = 0;
			FLAGS_log_dir = LOG_DIR;
			FLAGS_max_log_size = 4;
			google::SetLogDestination(google::GLOG_WARNING,"");
			google::SetLogDestination(google::GLOG_ERROR,"");
			signal(SIGPIPE,SIG_IGN);
		}
		~SetGlogLevel(){
			google::ShutdownGoogleLogging();
		}

};

void* func(void* argc){
	pthread_t id = pthread_self();
	LOG(INFO) << "current thread id: "<<id;
	return NULL;
}

int main(void){
	//signal(SIGINT,SIG_IGN);
	SetGlogLevel glog(0);
	SipLocalConfig *config = new SipLocalConfig();
	int ret = config->ReadConf();
	if(ret<0){
		LOG(ERROR) << "Read Config file error.";
		return ret;
	}
	bool re = GlobalCtl::instance()->init(config);
	if(!re){
		LOG(ERROR) << "Init Error.";
		return -1;
	}
	LOG(INFO)<< "Local Ip: " <<GBOJ(gConfig)->localIp();
	pthread_t pid;
	ret = EC::ECThread::createThread(func,NULL,pid);
	if(ret != 0){
		ret = -1;
		LOG(ERROR)<<"create thread error.";
		return ret;
	}
	LOG(INFO) << "create thread pid:" << pid;
	LOG(INFO) << "main thread pid:" << pthread_self();
	
	while(true){
		sleep(30);
	}
	return 0;
}
