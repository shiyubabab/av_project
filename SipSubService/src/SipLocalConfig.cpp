/*************************************************************************
	> File Name: SipLocalConfig.cpp
	> Author: mlxh
	> Mail: mlxh_gto@163.com 
	> Created Time: Sat 14 Jun 2025 06:31:48 PM CST
 ************************************************************************/

#include "SipLocalConfig.h"

#define CONFIGFILE_PATH "../../conf/SipSubService.conf"
#define LOCAL_SECTION "localserver"
#define SIP_SECTION "sipserver"

static const string keyLocalIp = "local_ip";
static const string keyLocalPort = "local_port"; 
static const string keySipId = "sip_id";
static const string keySipIp = "sip_ip";
static const string keySipPort = "sip_port";
static const string keySipRealm = "sip_realm";
static const string keySipUsr = "sip_usr";
static const string keySipPwd = "sip_pwd";
static const string keyRtpPortBegin = "rtp_port_begin";
static const string keyRtpPortEnd = "rtp_port_end";

static const string keySupNodeNum = "supnode_num";
static const string keySupNodeId = "sip_supnode_id";
static const string keySupNodeIp = "sip_supnode_ip";
static const string keySupNodePort = "sip_supnode_port";
static const string keySupNodePoto = "sip_supnode_poto";
static const string keySupNodeAuth = "sip_supnode_auth";

SipLocalConfig::SipLocalConfig()
:m_conf(CONFIGFILE_PATH){
	m_localIp = "";
	m_localPort = 0;
	m_sipId = "";
	m_sipIp = "";
	m_sipPort = 0;
	m_sipRealm = "";
	m_supNodeIp = "";
	m_supNodePort = 0;
	m_supNodePoto = 0;
	m_supNodeAuth = 0;
}

SipLocalConfig::~SipLocalConfig(){

}

int SipLocalConfig::ReadConf(){
	int ret = 0;
	m_conf.setSection(LOCAL_SECTION);
	m_localIp = m_conf.readStr(keyLocalIp);
	if(m_localIp.empty()){
		ret = -1;
		LOG(ERROR) << "localIp is wrong";
		return ret;
	}
	m_localPort = m_conf.readInt(keyLocalPort);
	if(m_localPort<=0){
		ret = -1;
		LOG(ERROR) << "localPort is wrong";
		return ret;
	}

	m_conf.setSection(SIP_SECTION);
	m_sipId = m_conf.readStr(keySipId);
	if(m_sipId.empty()){
		ret = -1;
		LOG(ERROR) << "sipId is wrong";
		return ret;
	}
	m_sipIp = m_conf.readStr(keySipIp);
	if(m_sipIp.empty()){
		ret = -1;
		LOG(ERROR) << "sipIp is wrong";
		return ret;
	}
	m_sipPort = m_conf.readInt(keySipPort);
	if(m_sipPort <= 0){
		ret = -1;
		LOG(ERROR) << "sipPort is wrong";
		return ret;
	}
	m_sipRealm = m_conf.readStr(keySipRealm);
	if(m_sipRealm.empty()){
		ret = -1;
		LOG(ERROR) << "sipRealm is wrong";
		return ret;
	}

	m_usr = m_conf.readStr(keySipUsr);
	if(m_usr.empty()){
		ret = -1;
		LOG(ERROR) << "usr is wrong";
		return ret;
	}

	m_pwd = m_conf.readStr(keySipPwd);
	if(m_pwd.empty()){
		ret = -1;
		LOG(ERROR) << "pwd is wrong";
		return ret;
	}
	LOG(INFO)<<"localip:"<<m_localIp<<",localport:"<<m_localPort<<",sipid:"<<m_sipId<<",sipip:"<<m_sipIp<<",sipport:"<<m_sipPort<<",sipRealm:"<<m_sipRealm;

	int num = m_conf.readInt(keySupNodeNum);
	LOG(INFO)<< "num:" <<num;
	for(int i =1;i<=num;i++){
		string id = keySupNodeId + to_string(i);
		string ip = keySupNodeIp + to_string(i);
		string port = keySupNodePort + to_string(i);
		string poto = keySupNodePoto + to_string(i);
		string auth = keySupNodeAuth + to_string(i);

		m_supNodeIp = m_conf.readStr(ip);
		m_supNodePort = m_conf.readInt(port);
		m_supNodePoto = m_conf.readInt(poto);
		m_supNodeAuth = m_conf.readInt(auth);

		LOG(INFO) << "supNodeIp:"<<m_supNodeIp<<",supNodePort:"<<m_supNodePort<<",supNodePoto:"<<m_supNodePoto<<",supNodeAuth:"<<m_supNodeAuth;
	}
	return ret;
}
