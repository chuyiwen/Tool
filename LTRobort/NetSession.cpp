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
 *	@file		NetSession.cpp
 *	@author		zhaopeng
 *	@date		2011/01/19
 *	@version	
 *	@brief		
 */
#include "stdafx.h"
#include "NetSession.h"

#include "x_client.h"

NetSession::NetSession()
{	
	m_pStream = new Tang::Net::XClient;
}
//-----------------------------------------------------------------------------
//! destruction
//-----------------------------------------------------------------------------
NetSession::~NetSession()
{	
	SAFE_DELETE(m_pStream);
}


//-----------------------------------------------------------------------------
//! construction
//-----------------------------------------------------------------------------
void NetSession::Init(Tang::NetCmdMgr* pNetCmdMgr)
{
	m_pStream->Init(false);	// 关闭Nagle算法
	m_dwLastSendTime = timeGetTime();
	m_pCmdMgr = pNetCmdMgr;
	//Tang::Console::GetSingleton().RegisterCommand( _T("sendqueue"), fastdelegate::MakeDelegate(this, &NetSession::SendQueue), _T("send queue list") );
}



//-----------------------------------------------------------------------------
// Connect
//-----------------------------------------------------------------------------
void NetSession::Connect(TCHAR const* szIP, int nPort)
{
	m_strRemoteIP = szIP;
	m_pStream->TryToConnect(Tang::f_util::unicode_to_utf8(szIP), nPort);
}


//-----------------------------------------------------------------------------
// Disconnect
//-----------------------------------------------------------------------------
void NetSession::Disconnect()
{
	m_pStream->Disconnect();
}


//-----------------------------------------------------------------------------
// IsConnect
//-----------------------------------------------------------------------------
bool NetSession::IsConnect()
{
	return m_pStream->IsConnected();
}



//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------
void NetSession::Update()
{
	static DWORD dwID_Skill = Tang::f_util::get_crc("NET_SIC_skill");	// 使用技能

	// 不停收网络消息
	for(;;)
	{
		DWORD dwRecvSize = 0;
		unsigned char* pRecv = m_pStream->Recv(dwRecvSize);
		if( !IS_VALID_PTR(pRecv) )
			break;

		// 从大包中解出小包依次处理
		unsigned char* pRecvPointer = pRecv;
		DWORD dwMsgSize = 0;
		while( pRecvPointer < pRecv + dwRecvSize )
		{
			tag_net_message* pRecvCmd = (tag_net_message*)pRecvPointer;
			dwMsgSize = pRecvCmd->dw_size;
			//m_pCmdMgr->HandleCmd(pRecvCmd, dwMsgSize, 0);
            m_pCmdMgr->HandleCmd(pRecvCmd, dwMsgSize, 0);
			pRecvPointer += dwMsgSize;
		}

		m_pStream->FreeRecved(pRecv);
	}

	
	if( m_SendQueueAction.GetMsgNum() > 0 )	
	{
		// 如果是使用技能消息，瞬间发
		m_SendQueueAction.ResetIterator();

		DWORD dwMsgSize = 0;
		unsigned char* pMsg = m_SendQueueAction.PeekMsg(dwMsgSize);
		if( ((tag_net_message*)pMsg)->dw_message_id == dwID_Skill )
		{
			m_pStream->Send(pMsg, dwMsgSize);
			m_SendQueueAction.RemoveMsg();
		}
	}


	// 每次心跳发送一条
	if( timeGetTime() - m_dwLastSendTime > TICK_TIME + 20 )
	{
		// 优先发送行为队列中的消息
		DWORD dwMsgSize = 0;
		unsigned char* pMsg = m_SendQueueAction.GetMsg(dwMsgSize);
		if( pMsg )
		{
			m_pStream->Send(pMsg, dwMsgSize);
			m_SendQueueAction.FreeMsg(pMsg);
		}
		else
		{
			pMsg = m_SendQueue.GetMsg(dwMsgSize);
			if( pMsg )
			{
				m_pStream->Send(pMsg, dwMsgSize);
				m_SendQueue.FreeMsg(pMsg);
			}
			else
			{
				pMsg = m_SendQueueIdle.GetMsg(dwMsgSize);
				if( pMsg )
				{
					m_pStream->Send(pMsg, dwMsgSize);
					m_SendQueueIdle.FreeMsg(pMsg);
				}
			}
		}
		
		m_dwLastSendTime = timeGetTime();
	}

	// 监视网络状态
	//Tang::Console::GetSingleton().Watch(_T("SendQueueAction"), m_SendQueueAction.GetMsgNum());
	//Tang::Console::GetSingleton().Watch(_T("SendQueue"), m_SendQueue.GetMsgNum());
	//Tang::Console::GetSingleton().Watch(_T("SendQueueIdle"), m_SendQueueIdle.GetMsgNum());
	//Tang::Console::GetSingleton().Watch(_T("NetSendSpeed"), m_pStream->GetBytesFlowOut());
	//Tang::Console::GetSingleton().Watch(_T("NetRecvSpeed"), m_pStream->GetBytesFlowIn());
	//Tang::Console::GetSingleton().Watch(_T("NetSendPack"), m_pStream->GetTotalSendPackNum());
	//Tang::Console::GetSingleton().Watch(_T("NetRecvPack"), m_pStream->GetTotalRecvPackNum());

}


//-----------------------------------------------------------------------------
// Send
//-----------------------------------------------------------------------------
void NetSession::Send(tag_net_message* pNetCmd)
{
	static DWORD dwID_MouseMove	= Tang::f_util::get_crc("NET_SIC_mouse_walk");		// 鼠标行走
	static DWORD dwID_KeyboardMove = Tang::f_util::get_crc("NET_SIC_keyboar_walk");	// 键盘行走
	static DWORD dwID_StopKeyboardWalk = Tang::f_util::get_crc("NET_SIC_stop_walk");	// 停止键盘行走
	static DWORD dwID_Jump = Tang::f_util::get_crc("NET_SIC_jump");					// 跳跃
	static DWORD dwID_Drop = Tang::f_util::get_crc("NET_SIC_drop");					// 掉落
	static DWORD dwID_VDrop = Tang::f_util::get_crc("NET_SIC_apeak_drop");				// 垂直掉落
	static DWORD dwID_Slide = Tang::f_util::get_crc("NET_SIC_slide");				// 滑落
	static DWORD dwID_Skill = Tang::f_util::get_crc("NET_SIC_skill");				// 使用技能
	static DWORD dwID_UseItem = Tang::f_util::get_crc("NET_SIC_use_item");			// 使用物品
	static DWORD dwID_SwapWeapon = Tang::f_util::get_crc("NET_SIC_swap_weapon");		// 切换武器

	static DWORD dwID_GetRemoteRoleState = Tang::f_util::get_crc("NET_SIC_get_remote_role_state");	// 得到远程玩家信息
	static DWORD dwID_RoleGetSomeName = Tang::f_util::get_crc("NET_SIC_role_set_some_name");	// 得到远程玩家名字
	

	// 将指令分类
	if( pNetCmd->dw_message_id == dwID_MouseMove
		|| pNetCmd->dw_message_id == dwID_KeyboardMove
		|| pNetCmd->dw_message_id == dwID_StopKeyboardWalk
		|| pNetCmd->dw_message_id == dwID_Jump
		|| pNetCmd->dw_message_id == dwID_Drop
		|| pNetCmd->dw_message_id == dwID_VDrop
		|| pNetCmd->dw_message_id == dwID_Slide
		|| pNetCmd->dw_message_id == dwID_Skill
		|| pNetCmd->dw_message_id == dwID_UseItem
		|| pNetCmd->dw_message_id == dwID_SwapWeapon)
	{
		// 有些新指令可以取代队列中的老指令
		if( pNetCmd->dw_message_id == dwID_MouseMove
			|| pNetCmd->dw_message_id == dwID_KeyboardMove
			|| pNetCmd->dw_message_id == dwID_StopKeyboardWalk
			|| pNetCmd->dw_message_id == dwID_Slide
			|| pNetCmd->dw_message_id == dwID_SwapWeapon)
		{
			DWORD dwMsgSize=0;
			tag_net_message* pSendCmd=NULL;
			m_SendQueueAction.ResetIterator();
			while(pSendCmd=(tag_net_message*)m_SendQueueAction.PeekMsg(dwMsgSize))
			{
				if( pSendCmd->dw_message_id==pNetCmd->dw_message_id )
					m_SendQueueAction.RemoveMsg();
				else
					m_SendQueueAction.IncIterator();
			}
		}

		// 发送
		m_SendQueueAction.AddMsg(pNetCmd, pNetCmd->dw_size);
	}
	else
	{
		if( pNetCmd->dw_message_id == dwID_GetRemoteRoleState 
			|| pNetCmd->dw_message_id == dwID_RoleGetSomeName )
			m_SendQueueIdle.AddMsg(pNetCmd, pNetCmd->dw_size);
		else
			m_SendQueue.AddMsg(pNetCmd, pNetCmd->dw_size);
	}
}


int NetSession::GetSendQueueSize()
{
	return m_SendQueue.GetMsgNum();
}

int NetSession::GetSendQueueActionSize()
{
	return m_SendQueueAction.GetMsgNum();
}

int NetSession::GetSendQueueIdleSize()
{
	return m_SendQueueIdle.GetMsgNum();
}

void NetSession::ClearMsgQueue()
{
	static DWORD dwID = Tang::f_util::get_crc("NET_SIC_game_sentinel");	// 反外挂消息

	m_SendQueueAction.Clear();
	m_SendQueueIdle.Clear();
	
	tag_net_message* pSendCmd = NULL;
	DWORD dwMsgSize = 0;
	m_SendQueue.ResetIterator();
	while( pSendCmd = (tag_net_message*)m_SendQueue.PeekMsg(dwMsgSize) )
	{
		if( pSendCmd->dw_message_id != dwID )	// 清除掉反外挂以外所有的消息
			m_SendQueue.RemoveMsg();
		else
			m_SendQueue.IncIterator();
	}
}


// 显示sendQueue的信息
DWORD NetSession::SendQueue(TCHAR const* szCommand)
{
	DWORD dwID = _tstoi(szCommand);
	tag_net_message* pSendCmd = NULL;
	DWORD dwMsgSize = 0;

	switch(dwID)
	{
	case 1:
		m_SendQueue.ResetIterator();
		while( pSendCmd = (tag_net_message*)m_SendQueue.PeekMsg(dwMsgSize) )
		{
			CONSOLE_TRACE(_T("SendQueue: 0x%X \r\n"), pSendCmd->dw_message_id);
			m_SendQueue.IncIterator();
		}
		break;
	case 2:
		m_SendQueueIdle.ResetIterator();
		while( pSendCmd = (tag_net_message*)m_SendQueueIdle.PeekMsg(dwMsgSize) )
		{
			CONSOLE_TRACE(_T("SendQueueIdle: 0x%X \r\n"), pSendCmd->dw_message_id);
			m_SendQueueIdle.IncIterator();
		}
		break;
	default:
		m_SendQueueAction.ResetIterator();
		while( pSendCmd = (tag_net_message*)m_SendQueueAction.PeekMsg(dwMsgSize) )
		{
			CONSOLE_TRACE(_T("SendQueueAction: 0x%X \r\n"), pSendCmd->dw_message_id);
			m_SendQueueAction.IncIterator();
		}
		break;
	}
	return 0;
}
