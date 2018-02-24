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
 *	@file		NetCmdMgr.h
 *	@author		zhaopeng
 *	@date		2010/12/10
 *	@version	
 *	@brief		网络消息派发
 */
#pragma once

namespace Tang {

typedef fastdelegate::FastDelegate2<tag_net_message*,DWORD,DWORD> NETMSGPROC;

class NetCmdMgr
{
public:
    NetCmdMgr();
    ~NetCmdMgr();
public:
    bool Register(LPCSTR szCmd, NETMSGPROC fp, TCHAR const* szDesc);
    bool UnRegister(LPCSTR szCmd, NETMSGPROC fp);
    bool HandleCmd(tag_net_message* pMsg, DWORD dwMsgSize, DWORD dwParam);
private:
    struct tagCmd
    {
        std::string			strCmd;		// 命令名
        tstring				strDesc;	// 描述
        SList<NETMSGPROC>	listFP;		// 函数指针列表
        DWORD				dwTimes;	// 收到此命令的次数
    };

    SMap<DWORD, tagCmd*>	m_mapProc;
};

}; // namespace Tang

#define REGISTER_NET_MSG(pCmdMgr, msg_name,cls_name,mem_fun,desc)   pCmdMgr->Register  ( msg_name, fastdelegate::MakeDelegate(this, (DWORD(cls_name::*)(tag_net_message*,DWORD))&cls_name::mem_fun), desc );
#define UNREGISTER_NET_MSG(pCmdMgr, msg_name,cls_name,mem_fun)      pCmdMgr->UnRegister( msg_name, fastdelegate::MakeDelegate(this, (DWORD(cls_name::*)(tag_net_message*,DWORD))&cls_name::mem_fun) );