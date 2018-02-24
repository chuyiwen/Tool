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
*	@file		map_protocol.h
*	@author		wmr
*	@date		2011/03/08	initial
*	@version	0.0.1.0
*	@brief		地图消息
*/

#ifndef MAP_PROTOCOL
#define MAP_PROTOCOL


#include "protocol_common_errorcode.h"

#pragma pack(push, 1)

enum
{
	E_BindRebornMap_NPCInvalid	=	1,	// 职能NPC非法
	E_BindRebornMap_MapInvalid	=	2,	// 地图非法（不是普通地图）
	E_BindRebornMap_Already		=	3,	// 已经绑定在该地图
	E_BindRebornMap_NPCNotFound	=	4,	// 没有找到指定的NPC
	E_BindRebornMap_TooFar		=	5,	// 距离太远

	E_Instance_Not_Exit			=	11,	// 副本不存在
	E_Instance_Role_Not_Exit	=	12,	// 玩家不存在
	E_Instance_Role_Full		=	13,	// 副本人数已到上限
	E_Instance_Level_Down_Limit =	14,	// 副本最低等级限制
	E_Instance_Level_Up_Limit	=	15,	// 副本最高等级限制
	E_Instance_Not_Same_Team	=	16,	// 不是同一小队
	E_Instance_Role_Lack		=	17,	// 副本人数未到下限
	E_Instance_End_Delete		=	18,	// 副本已经结束或者已经关闭
	E_Instance_Already			=	19,	// 已经创建了其它副本
	E_Instance_Full				=	20,	// 副本创建数量已满
	E_Instance_Not_Same_Guild   =   21, // 不是本帮派成员不能进副本
	E_Instance_GuildUp			=   22, // 帮派正在升级中
	E_Instance_Guild_NotFormal  =   23, // 不是正式家族
	E_Instance_Not_Enemy_Guild  =   24,	// 不是战斗敌对帮会
	E_Instance_Prepare_NoMap	=   25, // 准备战斗状态不能进入帮会副本
	E_Instance_Lobby_Repair		=   26, // 帮会大厅修复中
	E_Instance_Act_NoBegin		=   27, // 活动没有开始
	E_Instance_NoGuild			=   28,	// 没有帮会
	E_Instance_EnterNum_Limit	=	29,	// 进入次数限制
};

//------------------------------------------------------------------------------
// 踩到地图触发器
//------------------------------------------------------------------------------
struct NET_SIC_role_map_trigger : public tag_net_message
{
	NET_SIC_role_map_trigger()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_role_map_trigger");
		dw_size = sizeof(NET_SIC_role_map_trigger);
	}
	DWORD	dwTriggerID;
	DWORD	dwMisc;			// 如果是普通或随机副本，代表副本难度；
};


//------------------------------------------------------------------------------
// 进入副本
//------------------------------------------------------------------------------
struct NET_SIS_enter_instance : public tag_net_message
{
	NET_SIS_enter_instance()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_enter_instance");
		dw_size = sizeof(NET_SIS_enter_instance);
	}
	DWORD	dwTimeLimit;	// 时限副本所剩时间，单位是秒( 非时限副本为INVALID_VALUE）
	DWORD	dw_error_code;
};


//------------------------------------------------------------------------------
//离开副本
//------------------------------------------------------------------------------
struct NET_SIS_leave_instance : public tag_net_message
{
	NET_SIS_leave_instance()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_leave_instance");
		dw_size = sizeof(NET_SIS_leave_instance);
	}
	INT		nType;		// 1.副本进度完成
};


//-----------------------------------------------------------------------------
// 去新地图
//-----------------------------------------------------------------------------
struct NET_SIS_goto_new_map : public tag_net_message
{
	NET_SIS_goto_new_map()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_goto_new_map");
		dw_size = sizeof(NET_SIS_goto_new_map);
	}
	DWORD	dwMapID;
	Vector3	pos;
	Vector3	faceTo;
};


//-----------------------------------------------------------------------------
// 通知本地玩家是否召唤队友
//-----------------------------------------------------------------------------
struct NET_SIS_instance_nofity : public tag_net_message
{
	NET_SIS_instance_nofity()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_instance_nofity");
		dw_size = sizeof(NET_SIS_instance_nofity);
	}
};

struct NET_SIC_instance_notify : public tag_net_message
{
	NET_SIC_instance_notify()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_instance_notify");
		dw_size = sizeof(NET_SIC_instance_notify);
	}
	bool	bNotify;
};


//-----------------------------------------------------------------------------
// 通知所有队友是否进入副本
//-----------------------------------------------------------------------------
struct NET_SIS_instance_agree : public tag_net_message
{
	NET_SIS_instance_agree()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_instance_agree");
		dw_size = sizeof(NET_SIS_instance_agree);
	}
	DWORD   dwInviterID;
	DWORD	dwMapID;
	DWORD	dwMisc;
};

struct NET_SIC_instance_agree : public tag_net_message
{
	NET_SIC_instance_agree()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_instance_agree");
		dw_size = sizeof(NET_SIC_instance_agree);
	}
	bool	bAgree;
};


//-----------------------------------------------------------------------------
// 副本完成条件达成
//-----------------------------------------------------------------------------
struct NET_SIS_instance_complete : public tag_net_message
{
	NET_SIS_instance_complete()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_instance_complete");
		dw_size = sizeof(NET_SIS_instance_complete);
	}
};


//-----------------------------------------------------------------------------
// 请求离开副本
//-----------------------------------------------------------------------------
struct NET_SIC_leave_instance : public tag_net_message
{	
	NET_SIC_leave_instance()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_leave_instance");
		dw_size = sizeof(NET_SIC_leave_instance);
	}
};


//-----------------------------------------------------------------------------
// 同步副本倒计时
//-----------------------------------------------------------------------------
struct NET_SIS_synchronize_instance_time : public tag_net_message
{
	NET_SIS_synchronize_instance_time()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_synchronize_instance_time");
		dw_size = sizeof(NET_SIS_synchronize_instance_time);
	}
	DWORD	dwTimeLeft;			// 副本剩余时间：单位毫秒
};

//-----------------------------------------------------------------------------
// 绑定复活点
//-----------------------------------------------------------------------------
struct NET_SIC_bind_reborn_map : public tag_net_message
{
	NET_SIC_bind_reborn_map()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_bind_reborn_map");
		dw_size = sizeof(NET_SIC_bind_reborn_map);
	}
	DWORD	dwNPCID;		// 职能NPCID
};

struct NET_SIS_bind_reborn_map : public tag_net_message
{
	NET_SIS_bind_reborn_map()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_bind_reborn_map");
		dw_size = sizeof(NET_SIS_bind_reborn_map);
	}
	DWORD	dw_error_code;
	DWORD	dwBornMapID;
	Vector3	vBornPos;
};


//-----------------------------------------------------------------------------
// 客户端加载完成
//-----------------------------------------------------------------------------
struct NET_SIC_load_complete : public tag_net_message
{
	NET_SIC_load_complete()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_load_complete");
		dw_size = sizeof(NET_SIC_load_complete);
	}
};


#pragma pack(pop)
#endif

