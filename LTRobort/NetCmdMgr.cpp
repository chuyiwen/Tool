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
 *	@file		NetCmdMgr.cpp
 *	@author		zhaopeng
 *	@date		2010/12/10
 *	@version	
 *	@brief		网络消息派发
 */
#include "stdafx.h"
#include "NetCmdMgr.h"

namespace Tang {

NetCmdMgr::NetCmdMgr()
{

}

NetCmdMgr::~NetCmdMgr()
{
    m_mapProc.ResetIterator();
    tagCmd* pCmd = NULL;
    while( m_mapProc.PeekNext(pCmd) )
    {
        // 将所有命令接受到的次数记录到log文件
        //m_pLog->Write(_T("%s:%d\r\n"), pCmd->strCmd.c_str(), pCmd->dwTimes);
        delete(pCmd);
    }

    m_mapProc.Clear();
}

bool NetCmdMgr::Register(LPCSTR szCmd, NETMSGPROC fp, TCHAR const* szDesc)
{
	DWORD dwID = Tang::f_util::get_crc(szCmd);
	tagCmd* pCmd = m_mapProc.Peek(dwID);
	if( IS_VALID_PTR(pCmd) )
	{
		if( pCmd->strCmd != szCmd )
		{
			SI_ASSERT(0);	// 两个命令拥有相同的CRC
			return false;
		}

		SI_ASSERT(!pCmd->listFP.IsExist(fp));	// 不能注册多次
		pCmd->listFP.PushBack(fp);
	}
	else
	{
		pCmd = new tagCmd;
		pCmd->dwTimes = 0;
		pCmd->listFP.PushBack(fp);
		pCmd->strCmd = szCmd;
		pCmd->strDesc = szDesc;
		m_mapProc.Add(dwID, pCmd);
	}
	return true;
}

bool NetCmdMgr::UnRegister(LPCSTR szCmd, NETMSGPROC fp)
{
	DWORD dwID = Tang::f_util::get_crc(szCmd);
	tagCmd* pCmd = m_mapProc.Peek(dwID);
	if( !IS_VALID_PTR(pCmd) )
		return false;

	if( false == pCmd->listFP.Erase(fp) )
		return false;
	
	if( pCmd->listFP.Size() <= 0 )
	{
		SAFE_DELETE(pCmd);
		m_mapProc.Erase(dwID);
	}

	return true;
}

bool NetCmdMgr::HandleCmd(tag_net_message* pMsg, DWORD dwMsgSize, DWORD dwParam)
{
	tagCmd* pCmd = m_mapProc.Peek(pMsg->dw_message_id);
	if( !IS_VALID_PTR(pCmd) )
	{
		// 在本地显示
		CONSOLE_TRACE(_T("Unknow net command recved[<cmdid>%d <size>%d]\r\n"), pMsg->dw_message_id, dwMsgSize);
		return false;
	}

	if( pMsg->dw_size != dwMsgSize )
	{
		// 通知客户端，命令长度非法
		CONSOLE_TRACE(_T("Invalid net command size[<cmd>%s <size>%d]\r\n"), 
			Tang::f_util::utf8_to_unicode(pCmd->strCmd.c_str()), pMsg->dw_size);
		return false;
	}

	++pCmd->dwTimes;

	NETMSGPROC fp = NULL;
	pCmd->listFP.ResetIterator();
	while(pCmd->listFP.PeekNext(fp))
		(fp)(pMsg, dwParam);
	return true;
}

}; //namespace Tang