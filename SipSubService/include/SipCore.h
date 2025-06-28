/*************************************************************************
	> File Name: SipCore.h
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Sat 21 Jun 2025 03:31:49 PM CST
 ************************************************************************/
#ifndef _SIPCORE_H
#define _SIPCORE_H
#include <pjlib-util.h>
#include <pjmedia.h>
#include <pjsip.h>
#include <pjsip_ua.h>
#include <pjsip/sip_auth.h>
#include <pjlib.h>
#include "Common.h"
#include <sys/sysinfo.h>

class SipCore{
	public:
		SipCore();
		~SipCore();

		bool InitSip(int sipPort);
		pj_status_t init_transport_layer(int sipPort);
	private:
		pjsip_endpoint* m_endpt;
};


#endif
