#include "stdafx.h"
#include "NetSession.h"
#include "../WorldDefine/time.h"
#include <process.h>
#include "../LogSystem/protocal.h"

UINT WINAPI thread_func(LPVOID pParam)
{
	return ((net_session*)pParam)->process_net_msg();
}

net_session gns;

bool InitNetwork()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	// ÏÈ³¢ÊÔwinsocket2.2
	wVersionRequested = MAKEWORD( 2, 2 );
	INT nErr = WSAStartup( wVersionRequested, &wsaData );
	if( 0 != nErr ) 
	{
		// ³¢ÊÔwinsocket2.1
		wVersionRequested = MAKEWORD( 2, 1 );
		nErr = WSAStartup( wVersionRequested, &wsaData );
		if( 0 != nErr ) 
		{
			// ³¢ÊÔwinsocket1.1
			wVersionRequested = MAKEWORD( 1, 1 );
			nErr = WSAStartup( wVersionRequested, &wsaData );
			if( 0 != nErr ) 
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void DestroyNetwork()
{
	::WSACleanup();
}



net_session::net_session()
{
	InitNetwork();
	port = 0;
	mXC = new few_connect_client;
	mXC->init(FALSE);

	mUpdate = (HANDLE)_beginthreadex(NULL, 0, thread_func, this, 0, NULL);

	mTerimante = FALSE;
	::InitializeCriticalSectionAndSpinCount(&mCS , 0);
	mFMonth = -1;
	mFDay = -1;
	mTMonth = -1;
	mTDay = -1;
	mCST = CST_NULL;
	start = false;
	ZeroMemory(info , 5*sizeof(information));
}

net_session::~net_session()
{
	::DeleteCriticalSection(&mCS);
	::InterlockedExchange((LONG*)&mTerimante, TRUE);
	DWORD dwResult = WaitForSingleObject(mUpdate, 100);	
	if(mUpdate) 
		CloseHandle(mUpdate);
	mUpdate = 0;
	if(mXC)
	{
		delete mXC;
		mXC = 0;
	}
	DestroyNetwork();
}

UINT net_session::process_net_msg()
{
	while(!mTerimante)
	{
		EnterCriticalSection(&mCS);

		///!¶¨Ê±Æ÷
		std::map<std::wstring , sDoubleInfo>::iterator iter = mDoublePolicy.begin();
		for(;iter!=mDoublePolicy.end();++iter)
		{
			sDoubleInfo& info = iter->second;
			for(int i = 0 ; i < 3 ; ++i)
			{
				SYSTEMTIME time;
				GetLocalTime(&time);
				if((!info.switcher[i])&&time.wHour == info.hourEnd[i] && time.wMinute == info.minuteEnd[i])
				{
					info.switcher[i] = true;
				}
				if((info.switcher[i])&&(info.bei[i])&&
					(time.wHour == info.hourStart[i])&&(time.wMinute == info.minuteStart[i]))
				{
					NET_C2GMS_SetDoublePolicy cmd;
					cmd.eType = (EGMDoubleType)i;
					cmd.dwValue = info.bei[i]*100;
					_tcscpy(cmd.szServerName, iter->first.c_str());
					tagDWORDTime time = GetCurrentDWORDTime();
					DWORD secs = ((info.hourEnd[i] - info.hourStart[i])*60+
						(info.minuteEnd[i] - info.minuteStart[i]))*60;
					cmd.dwStartTime = time;
					cmd.dwPersistSeconds = secs;
					net_session::instance()->send_msg(&cmd , cmd.dw_size);
					info.switcher[i] = false;
				}
			} 
		}


		DWORD msgsz;
		LPBYTE msg = mXC->recv_msg(msgsz);
		if(!msg)
		{
			::LeaveCriticalSection(&mCS);
			Sleep(1);
			continue;
		}
		NP_NET_CMD* net_cmd = (NP_NET_CMD*)msg;
		if( net_cmd->dw_size != msgsz )
		{
			::MessageBox(0 , _T("net message length error!") , _T("ERROR") , 0);
			mXC->free_recv_msg(msg);
			::LeaveCriticalSection(&mCS);
			return 1;
		}
		
		std::map<DWORD , Signal<void , NP_NET_CMD*> >::iterator p = m_cmd_map.find(net_cmd->dw_message_id);
		if(p!=m_cmd_map.end())
		{
			p->second.Emit(net_cmd);
		}
		mXC->free_recv_msg(msg);

		

		::LeaveCriticalSection(&mCS);
		Sleep(1);
	}
	return 0;
}

few_connect_client* net_session::instance()
{
	return gns.mXC;
}

net_session* net_session::instance2()
{
	return &gns;
}