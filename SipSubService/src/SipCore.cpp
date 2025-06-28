/*************************************************************************
	> File Name: SipCore.cpp
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Sat 21 Jun 2025 03:38:38 PM CST
 ************************************************************************/

#include "SipCore.h"
#include "SipDef.h"

static int pollingEvent(void* arg){
	LOG(INFO)<<"polling event thread start success";
	pjsip_endpoint* ept = (pjsip_endpoint*)arg;
	while(true){
		pj_time_val timeout = {0,500};
		pj_status_t status = pjsip_endpt_handle_events(ept,&timeout);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<< "polling events failed,code: "<<status;
			return -1;
		}
	}
	return 0;
}

pj_bool_t onRxRequest(pjsip_rx_data *rdata){
	return PJ_SUCCESS;
}

static pjsip_module recv_mod ={
	NULL,NULL,
	{"mod-recv",8},
	-1,
	PJSIP_MOD_PRIORITY_APPLICATION,
	NULL,
	NULL,
	NULL,
	NULL,
	onRxRequest,
	NULL,
	NULL,
	NULL,
	NULL,
};
SipCore::SipCore():m_endpt(NULL){

}

SipCore::~SipCore(){
	pjsip_endpt_destroy(m_endpt);
}

bool SipCore::InitSip(int sipPort){
	pj_status_t status;
	pj_log_set_level(0);

	do{
		status = pj_init();
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"init pjlib faild,code: "<<status;
			break;
		}

		status = pjlib_util_init();
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"init pjlib util faild,code: "<<status;
			break;
		}

		pj_caching_pool cachingPool;
		pj_caching_pool_init(&cachingPool,NULL,SIP_STACK_SIZE);

		status = pjsip_endpt_create(&cachingPool.factory,NULL,&m_endpt);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"create endpt faile,code: "<<status;
			break;
		}
		
		status = pjsip_tsx_layer_init_module(m_endpt);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"init tsx layer faile,code: "<<status;
			break;
		}

		status = pjsip_ua_init_module(m_endpt,NULL);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"init UA layer faild,code: "<<status;
			break;
		}

		status = init_transport_layer(sipPort);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"init transport layer faild,code: "<<status;
			break;
		}

		status = pjsip_endpt_register_module(m_endpt,&recv_mod);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"register recv module faild, code: "<<status;
			break;
		}

		pj_pool_t* pool = pjsip_endpt_create_pool(m_endpt,NULL,SIP_ALLOC_POOL_1M,SIP_ALLOC_POOL_1M);
		if(NULL == pool){
			LOG(ERROR)<<"create pool faild";
			break;
		}
		pj_thread_t* eventThread = NULL;
		status = pj_thread_create(pool,NULL,&pollingEvent,m_endpt,0,0,&eventThread);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"create pjsip thread faild, code: "<<status;
			break;
		}

	}while(0);

	bool bret = true;
	if(PJ_SUCCESS != status){
		bret = false;
	}
	return bret;
}

pj_status_t SipCore::init_transport_layer(int sipPort){
	pj_sockaddr_in addr;
	pj_bzero(&addr,sizeof(addr));
	addr.sin_family = pj_AF_INET();
	addr.sin_addr.s_addr = 0;
	addr.sin_port = pj_htons((pj_uint16_t)sipPort);

	pj_status_t status;
	do{
		status = pjsip_udp_transport_start(m_endpt,&addr,NULL,1,NULL);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"start udp server faild,code: "<<status;
			break;
		}
		
		status = pjsip_tcp_transport_start(m_endpt,&addr,1,NULL);
		if(PJ_SUCCESS != status){
			LOG(ERROR)<<"start tcp server faild,code: "<<status;
			break;
		}

		LOG(INFO)<<"sip tcp:" << sipPort <<" udp:"<<sipPort<<" running";
	}while(0);

	return status;
}
