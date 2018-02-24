/*******************************************************************************

	Copyright 2010 by Shengshi Interactive Game Co., Ltd.
	All rights reserved.
	
	This software is the confidential and proprietary information of
	Shengshi Interactive Game Co., Ltd. ('Confidential Information'). You shall
	not disclose such Confidential Information and shall use it only in
	accordance with the terms of the license agreement you entered into with
	Shengshi Interactive  Co., Ltd.

*******************************************************************************/
/**
 *	@file		NetSession.h
 *	@author		zhaopeng
 *	@date		2011/01/19
 *	@version	
 *	@brief		
 */
#pragma once
#include "msg_queue.h"

namespace Tang { 
namespace Net {
class XClient;
} }

//-----------------------------------------------------------------------------
//!\brief net session
//! 控制发包频率在每次心跳一个，同时提供监控，可以查看有哪些消息累积
//! 可以方便的替换队列中的消息
//-----------------------------------------------------------------------------
class NetSession 
{
public:
	void Init(Tang::NetCmdMgr* pNetCmdMgr);
	void Connect(TCHAR const* szIP, int nPort);
	void Disconnect();
	bool IsConnect();
	void ClearMsgQueue();

	void Update();

	void Send(tag_net_message* pNetCmd);
	int	GetSendQueueSize();
	int	GetSendQueueActionSize();
	int	GetSendQueueIdleSize();

	// 得到远程IP
	TCHAR const* GetRemoteIPString() { return m_strRemoteIP.c_str(); }

	NetSession();
	~NetSession();
protected:
	Tang::Net::XClient*			m_pStream;
	Tang::NetCmdMgr*					m_pCmdMgr;

	tstring						m_strRemoteIP;
	DWORD						m_dwLastSendTime;

	Tang::Net::MsgQueue			m_SendQueueAction;	// 行为队列
	Tang::Net::MsgQueue			m_SendQueue;		// 普通队列
	Tang::Net::MsgQueue			m_SendQueueIdle;	// 次要消息队列

	DWORD SendQueue(TCHAR const* szCommand);	// 显示sendQueue的信息
};
