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
*	@file		select_role_protocol.h
*	@author		wmr
*	@date		2011/03/11	initial
*	@version	0.0.1.0
*	@brief		ѡ����Ϣ
*/


#ifndef SELECT_ROLE_PROTOCOL
#define SELECT_ROLE_PROTOCOL

#pragma pack(push)
#pragma pack(1)

#include "protocol_common_errorcode.h"
#include "RoleDefine.h"
#define MAX_ROLE_NUM		3
enum										// ���ﴴ����ɾ����ѡ����صĴ������
{
	E_JoinGame_AccountOnline			=	1,
	E_JoinGame_VerifyCodeError			=	2,

	E_CreateRole_RoleCreating			=	11,
	E_CreateRole_RoleEnumNotDone		=	12,
	E_CreateRole_RoleDeleting			=	13,
	E_CreateRole_RoleNumFull			=	14,
	E_CreateRole_NameExist				=	15,
	E_CreateRole_NameInvalid			=	16,
	E_CreateRole_SafeCodeInvalid		=	17,
	E_CreateRole_InWorld				=	18,
	E_CreateRole_RoleLoading			=	19,
	E_CreateRole_RoleEnumNotSuccess		=	20,

	E_DelRole_RoleNotExist				=	21,
	E_DelRole_RoleDeleting				=	22,
	E_DelRole_RoleEnumNotDone			=	23,
	E_DelRole_RoleCreating				=	24,
	E_DelRole_SafeCodeIncorrect			=	25,
	E_DelRole_InWorld					=	26,
	E_DelRole_RoleLoading				=	27,
	E_DelRole_LeaveGuild1st				=	28,	// �����������

	E_EnumRole_RoleEnumed				=	31,
	E_EnumRole_RoleEnuming				=	32,
	E_EnumRole_InWorld					=	33,

	E_SelectRole_RoleEnumNotDone		=	41,
	E_SelectRole_RoleCreating			=	42,
	E_SelectRole_RoleDeleting			=	43,
	E_SelectRole_RoleNotExist			=	44,
	E_SelectRole_InWorld				=	45,
	E_SelectRole_RoleLoading			=	46,
};

//-----------------------------------------------------------------------------
// ���Ƽ��
//-----------------------------------------------------------------------------
struct NET_SIC_check_name : public tag_net_message
{
	NET_SIC_check_name()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_check_name");
		dw_size = sizeof(NET_SIC_check_name);
	}
	TCHAR			szRoleName[X_SHORT_NAME];
};

struct NET_SIS_check_name : public tag_net_message
{
	NET_SIS_check_name()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_check_name");
		dw_size = sizeof(NET_SIS_check_name);
	}
	DWORD	dwError;
};

//-----------------------------------------------------------------------------
// ������Ϸ
//-----------------------------------------------------------------------------
struct NET_SIC_join_game : public tag_net_message
{
	NET_SIC_join_game()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_join_game");
		dw_size = sizeof(NET_SIC_join_game);
	}
	DWORD		dw_account_id;		// �ʺ�ID
	DWORD		dwVerifyCode;		// ��½���������͸��ͻ��˵���֤��
};

struct NET_SIS_join_game : public tag_net_message
{
	NET_SIS_join_game()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_join_game");
		dw_size = sizeof(NET_SIS_join_game);
	}
	DWORD		dw_error_code;
	INT			nGMPrivilege;		// GMȨ��
};

//-----------------------------------------------------------------------------
// �����ɫ�б�
//-----------------------------------------------------------------------------
struct NET_SIC_enum_role : public tag_net_message
{
	NET_SIC_enum_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_enum_role");
		dw_size = sizeof(NET_SIC_enum_role);
	}
};

struct NET_SIS_enum_role : public tag_net_message
{
	NET_SIS_enum_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_enum_role");
		dw_size = sizeof(NET_SIS_enum_role);
	}
	DWORD			dw_error_code;
	DWORD			dwSafeCodeCrc;
	tagDWORDTime	dwTimeReset;
	tagDWORDTime	dwTimeLastLogin;	//�ϴε�¼ʱ��
	DWORD			dwIPLast;			//�ϴε�¼IP
	DWORD			dw_ip;				//���ε�¼IP
	INT				n_num;
	BOOL			b_need_verify;		//�Ƿ���Ҫ��֤
	INT				dwYuanBao;
	BYTE			bySimpleInfo[1];
};


//������ȫ��
struct NET_SIC_safe_code : public tag_net_message
{
	NET_SIC_safe_code()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_safe_code");
		dw_size = sizeof(NET_SIC_safe_code);
	}
	DWORD			dwSafeCode;
};

struct NET_SIS_safe_code : public tag_net_message
{
	NET_SIS_safe_code()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_safe_code");
		dw_size = sizeof(NET_SIS_safe_code);
	}
	DWORD			dw_error_code;
};

//���ð�ȫ��
struct NET_SIC_reset_safe_code : public tag_net_message
{
	NET_SIC_reset_safe_code()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_reset_safe_code");
		dw_size = sizeof(NET_SIC_reset_safe_code);
	}
};

struct NET_SIS_reset_safe_code : public tag_net_message
{
	NET_SIS_reset_safe_code()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_reset_safe_code");
		dw_size = sizeof(NET_SIS_reset_safe_code);
	}
	tagDWORDTime	dwTimeReset;
};


//ȡ����ȫ��
struct NET_SIC_cancel_safe_code_reset : public tag_net_message
{
	NET_SIC_cancel_safe_code_reset()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_cancel_safe_code_reset");
		dw_size = sizeof(NET_SIC_cancel_safe_code_reset);
	}
};

struct NET_SIS_cancel_safe_code_reset : public tag_net_message
{
	NET_SIS_cancel_safe_code_reset()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_cancel_safe_code_reset");
		dw_size = sizeof(NET_SIS_cancel_safe_code_reset);
	}
	DWORD			dw_error_code;
};

//-----------------------------------------------------------------------------
// ������ɫ
//-----------------------------------------------------------------------------
struct NET_SIC_create_role : public tag_net_message
{
	NET_SIC_create_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_create_role");
		dw_size = sizeof(NET_SIC_create_role);
	}
	TCHAR			szRoleName[X_SHORT_NAME];
	EPreChapStatus	eStatus;
	tagAvatarAtt	AvatarAtt;
	EClassType		eClassType;
};

struct NET_SIS_create_role : public tag_net_message
{
	NET_SIS_create_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_create_role");
		dw_size = sizeof(NET_SIS_create_role);
	}
	DWORD			dw_error_code;
	BYTE			bySimRoleInfo[1];
};

//-----------------------------------------------------------------------------
// ɾ����ɫ
//-----------------------------------------------------------------------------
struct NET_SIC_delete_role : public tag_net_message
{
	NET_SIC_delete_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_delete_role");
		dw_size = sizeof(NET_SIC_delete_role);
	}
	DWORD			dw_role_id;						
	DWORD			dwSafeCodeCrc;
};

struct NET_SIS_delete_role : public tag_net_message
{
	NET_SIS_delete_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_delete_role");
		dw_size = sizeof(NET_SIS_delete_role);
	}
	DWORD			dw_error_code;
	DWORD			dw_role_id;
};

//------------------------------------------------------------------------------
// ѡ���ɫ
//------------------------------------------------------------------------------
struct NET_SIC_select_role : public tag_net_message
{
	NET_SIC_select_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_select_role");
		dw_size = sizeof(NET_SIC_select_role);
	}
	DWORD			dw_role_id;
	DWORD			dw_verification_code_crc;	// ��֤��crc
};

struct NET_SIS_select_role : public tag_net_message
{
	NET_SIS_select_role()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_select_role");
		dw_size = sizeof(NET_SIS_select_role);
	}
	DWORD			dw_error_code;
	DWORD			dw_role_id;
};

#pragma pack(pop)
#endif