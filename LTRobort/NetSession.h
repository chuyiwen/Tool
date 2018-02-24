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
//! ���Ʒ���Ƶ����ÿ������һ����ͬʱ�ṩ��أ����Բ鿴����Щ��Ϣ�ۻ�
//! ���Է�����滻�����е���Ϣ
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

	// �õ�Զ��IP
	TCHAR const* GetRemoteIPString() { return m_strRemoteIP.c_str(); }

	NetSession();
	~NetSession();
protected:
	Tang::Net::XClient*			m_pStream;
	Tang::NetCmdMgr*					m_pCmdMgr;

	tstring						m_strRemoteIP;
	DWORD						m_dwLastSendTime;

	Tang::Net::MsgQueue			m_SendQueueAction;	// ��Ϊ����
	Tang::Net::MsgQueue			m_SendQueue;		// ��ͨ����
	Tang::Net::MsgQueue			m_SendQueueIdle;	// ��Ҫ��Ϣ����

	DWORD SendQueue(TCHAR const* szCommand);	// ��ʾsendQueue����Ϣ
};
