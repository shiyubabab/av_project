/*************************************************************************
	> File Name: ECThread.h
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Mon 16 Jun 2025 09:15:07 AM CST
 ************************************************************************/

#ifndef _ECTHREAD_H
#define _ECTHREAD_H
#include <pthread.h>
#include <string>
#include <sys/prctl.h>

namespace EC{
	typedef void* (*ECThreadFunc)(void *);
	class ECThread{
		public:
			static int createThread(ECThreadFunc startRoutine,void* args,pthread_t& id);
			static int detachSelf();
			static void exitSelf(void *rval);
			static void waitThread(const pthread_t &id);
			static int terminateThread(const pthread_t &id);
		private:
			ECThread(){}
			~ECThread(){}
	};
}

#endif
