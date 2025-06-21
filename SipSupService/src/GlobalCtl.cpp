/*************************************************************************
	> File Name: GlobalCtl.cpp
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Mon 16 Jun 2025 08:26:21 AM CST
 ************************************************************************/

#include "GlobalCtl.h"

GlobalCtl *GlobalCtl::m_pInstance = NULL;

GlobalCtl* GlobalCtl::instance(){
	if(!m_pInstance){
		m_pInstance = new GlobalCtl();
	}
	return m_pInstance;
}

bool GlobalCtl::init(void *param){
	gConfig = (SipLocalConfig *)param;
	if(!gConfig){
		return false;
	}
	if(!gThPool){
		gThPool = new ThreadPool;
		gThPool -> createThreadPool(10);
	}
	return true;
}
