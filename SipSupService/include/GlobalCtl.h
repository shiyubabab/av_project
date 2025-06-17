/*************************************************************************
	> File Name: GlobalCtl.h
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Mon 16 Jun 2025 08:26:35 AM CST
 ************************************************************************/
#ifndef _GLOBALCTL_H
#define _GLOBALCTL_H
#include "Common.h"
#include "SipLocalConfig.h"

class GlobalCtl{
	public:
		static GlobalCtl* instance();
		bool init(void *param);
		SipLocalConfig *gConfig;
	private:
		GlobalCtl(void){}
		~GlobalCtl(void);
		GlobalCtl(const GlobalCtl &global);
		const GlobalCtl &operator=(const GlobalCtl &global);

		static GlobalCtl* m_pInstance;

};

#endif
