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
*	@file		gm_protocol.h
*	@author		wmr
*	@date		2011/03/03	initial
*	@version	0.0.1.0
*	@brief		gm命令消息
*/

#ifndef GM_PROTOCOL
#define GM_PROTOCOL


#include "protocol_common_errorcode.h"

#pragma pack(push, 1)
//----------------------------------------------------------------------------
// 错误码枚举
//----------------------------------------------------------------------------
enum
{
	E_GMCmd_Low_Privilege,	// 权限不够

};



#define MAX_GM_COMMAND_LEN 128 
//----------------------------------------------------------------------------
// 消息结构
//----------------------------------------------------------------------------
struct NET_SIC_gm_command : public tag_net_message
{
	NET_SIC_gm_command()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_gm_command");
		dw_size = sizeof(NET_SIC_gm_command);
	}
	TCHAR	szCommand[MAX_GM_COMMAND_LEN];
};


//----------------------------------------------------------------------------
// 游戏世界发给客户端，控制某个任务为已完成，或者未完成
//----------------------------------------------------------------------------
struct NET_SIS_gm_command_state : public tag_net_message
{
	NET_SIS_gm_command_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_gm_command_state");
		dw_size = sizeof(NET_SIS_gm_command_state);
	}
	UINT16		u16QuestID;		// 任务ID
	BOOL		bDone;			// 任务状态 TRUE：已完成，FALSE：未完成
};


//----------------------------------------------------------------------------
#pragma pack(pop)
#endif