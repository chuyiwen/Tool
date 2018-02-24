#pragma once
#include <map>
#include <string>
#include "sigslot.h"
#include "../LogSystem/protocal.h"

inline DWORD crc32(LPCSTR sz_message_name_)
{
	UINT u_result;
	LPBYTE p_data = (LPBYTE)sz_message_name_;
	if( 0 == p_data[0] ) 
		return (DWORD)-1;
	u_result = *p_data++ << 24;
	if( *p_data )
	{
		u_result |= *p_data++ << 16;
		if( *p_data )
		{
			u_result |= *p_data++ << 8;
			if( *p_data ) u_result |= *p_data++;
		}
	}
	u_result = ~ u_result;
	while( *p_data )
	{
		u_result = (u_result << 8 | *p_data) ^ crc32_table[u_result >> 24];
		p_data++;
	}
	return ~u_result;
}


enum CurDateType
{
	CDT_FROM , 
	CDT_TO
};

enum CurSendType
{
	CST_NULL,
	CST_ITEM_LOG , 
	CST_CHAR_LOG,
	CST_MONEY_LOG , 
	CST_YUANBAO_LOG
};


struct information
{
	bool checked;
	std::wstring msg;
	std::wstring time;
};

struct sDoubleInfo
{
	bool switcher[3];
	DWORD hourStart[3];
	DWORD minuteStart[3];
	DWORD continueMinutes[3];
	DWORD hourEnd[3];
	DWORD minuteEnd[3];
	int bei[3];
	sDoubleInfo()
	{
		switcher[0] = true;
		switcher[1] = true;
		switcher[2] = true;
		hourStart[0] = 0;
		hourStart[1] = 0;
		hourStart[2] = 0;
		minuteStart[0] = 0;
		minuteStart[1] = 0;
		minuteStart[2] = 0;
		continueMinutes[0] = 0;
		continueMinutes[1] = 0;
		continueMinutes[2] = 0;
		hourEnd[0] = 0;
		hourEnd[1] = 0;
		hourEnd[2] = 0;
		minuteEnd[0] = 0;
		minuteEnd[1] = 0;
		minuteEnd[2] = 0;
		bei[0] = 0;
		bei[1] = 0;
		bei[2] = 0;
	}
};


class net_session
{
private:
	CRITICAL_SECTION mCS;
	few_connect_client* mXC;
	std::map<DWORD , Signal<void , NP_NET_CMD*> > m_cmd_map;


	HANDLE mUpdate;
	volatile BOOL mTerimante;
public:

	Signal<void , bool> _sig_double;
	BYTE mFMonth;
	BYTE mFDay;
	BYTE mTMonth;
	BYTE mTDay;
	CurDateType mCdt;
	CurSendType mCST;
	std::string ip;
	short port;
	DWORD continueTime;
	information info[5];
	bool start;


	//!gmserver专用
	std::wstring gmip;
	//!double专区
	std::map<std::wstring , sDoubleInfo> mDoublePolicy;
public:
	net_session();
	virtual ~net_session();
public:
	static few_connect_client* instance();
	static net_session* instance2();
	template <typename C , typename F>
	void register_cmd(const char* cmd , C obj , F func)
	{
		EnterCriticalSection(&mCS);
		DWORD id = crc32(cmd);
		std::map<DWORD , Signal<void , NP_NET_CMD*> >::iterator p = m_cmd_map.find(id);
		if(p!=m_cmd_map.end())
			p->second.Connect(obj , func);
		else
		{
			Signal<void , NP_NET_CMD*> sig;
			sig.Connect(obj , func);
			m_cmd_map.insert(std::make_pair(id , sig));
		}
		::LeaveCriticalSection(&mCS);
	}

	template<typename C , typename F>
	void unregister_cmd(const char* cmd , C obj , F func)
	{
		EnterCriticalSection(&mCS);
		DWORD id = crc32(cmd);
		std::map<DWORD , Signal<void , NP_NET_CMD*> >::iterator p = m_cmd_map.find(id);
		if(p!=m_cmd_map.end())
		{
			p->second.Disconnect(obj , func);
		}
		::LeaveCriticalSection(&mCS);
	}

	UINT process_net_msg();
};



