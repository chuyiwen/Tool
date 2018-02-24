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
*	@brief		��ͼ��Ϣ
*/

#ifndef MAP_PROTOCOL
#define MAP_PROTOCOL


#include "protocol_common_errorcode.h"

#pragma pack(push, 1)

enum
{
	E_BindRebornMap_NPCInvalid	=	1,	// ְ��NPC�Ƿ�
	E_BindRebornMap_MapInvalid	=	2,	// ��ͼ�Ƿ���������ͨ��ͼ��
	E_BindRebornMap_Already		=	3,	// �Ѿ����ڸõ�ͼ
	E_BindRebornMap_NPCNotFound	=	4,	// û���ҵ�ָ����NPC
	E_BindRebornMap_TooFar		=	5,	// ����̫Զ

	E_Instance_Not_Exit			=	11,	// ����������
	E_Instance_Role_Not_Exit	=	12,	// ��Ҳ�����
	E_Instance_Role_Full		=	13,	// ���������ѵ�����
	E_Instance_Level_Down_Limit =	14,	// ������͵ȼ�����
	E_Instance_Level_Up_Limit	=	15,	// ������ߵȼ�����
	E_Instance_Not_Same_Team	=	16,	// ����ͬһС��
	E_Instance_Role_Lack		=	17,	// ��������δ������
	E_Instance_End_Delete		=	18,	// �����Ѿ����������Ѿ��ر�
	E_Instance_Already			=	19,	// �Ѿ���������������
	E_Instance_Full				=	20,	// ����������������
	E_Instance_Not_Same_Guild   =   21, // ���Ǳ����ɳ�Ա���ܽ�����
	E_Instance_GuildUp			=   22, // ��������������
	E_Instance_Guild_NotFormal  =   23, // ������ʽ����
	E_Instance_Not_Enemy_Guild  =   24,	// ����ս���ж԰��
	E_Instance_Prepare_NoMap	=   25, // ׼��ս��״̬���ܽ����ḱ��
	E_Instance_Lobby_Repair		=   26, // �������޸���
	E_Instance_Act_NoBegin		=   27, // �û�п�ʼ
	E_Instance_NoGuild			=   28,	// û�а��
	E_Instance_EnterNum_Limit	=	29,	// �����������
};

//------------------------------------------------------------------------------
// �ȵ���ͼ������
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
	DWORD	dwMisc;			// �������ͨ������������������Ѷȣ�
};


//------------------------------------------------------------------------------
// ���븱��
//------------------------------------------------------------------------------
struct NET_SIS_enter_instance : public tag_net_message
{
	NET_SIS_enter_instance()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_enter_instance");
		dw_size = sizeof(NET_SIS_enter_instance);
	}
	DWORD	dwTimeLimit;	// ʱ�޸�����ʣʱ�䣬��λ����( ��ʱ�޸���ΪINVALID_VALUE��
	DWORD	dw_error_code;
};


//------------------------------------------------------------------------------
//�뿪����
//------------------------------------------------------------------------------
struct NET_SIS_leave_instance : public tag_net_message
{
	NET_SIS_leave_instance()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_leave_instance");
		dw_size = sizeof(NET_SIS_leave_instance);
	}
	INT		nType;		// 1.�����������
};


//-----------------------------------------------------------------------------
// ȥ�µ�ͼ
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
// ֪ͨ��������Ƿ��ٻ�����
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
// ֪ͨ���ж����Ƿ���븱��
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
// ��������������
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
// �����뿪����
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
// ͬ����������ʱ
//-----------------------------------------------------------------------------
struct NET_SIS_synchronize_instance_time : public tag_net_message
{
	NET_SIS_synchronize_instance_time()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_synchronize_instance_time");
		dw_size = sizeof(NET_SIS_synchronize_instance_time);
	}
	DWORD	dwTimeLeft;			// ����ʣ��ʱ�䣺��λ����
};

//-----------------------------------------------------------------------------
// �󶨸����
//-----------------------------------------------------------------------------
struct NET_SIC_bind_reborn_map : public tag_net_message
{
	NET_SIC_bind_reborn_map()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_bind_reborn_map");
		dw_size = sizeof(NET_SIC_bind_reborn_map);
	}
	DWORD	dwNPCID;		// ְ��NPCID
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
// �ͻ��˼������
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

