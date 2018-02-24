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
*	@file		login_protocol.h
*	@author		wmr
*	@date		2011/02/28	initial
*	@version	0.0.1.0
*	@brief		��½��֤��Ϣ
*/


#ifndef LOGIN_PROTOCOL
#define LOGIN_PROTOCOL

#include "protocol_common_errorcode.h"
#define MAX_MD5_ARRAY	36
#define MAX_MIBAO		6

#pragma pack(push, 1)

//--------------------------------------------------------------------------------------------
// Login �������
//--------------------------------------------------------------------------------------------
enum
{
	E_ProofResult_Account_No_Match				= 1,	//���ʺŷǷ�(�ʻ������ڻ������벻��,�ܱ�����)
	E_ProofResult_Account_In_Use				= 2,	//���ʺŵ�ǰ�Ѿ���ʹ��
	E_ProofResult_Account_Freezed				= 3,	//���ʺű�ͣ��
	E_ProofResult_Wrong_Build_Number			= 4,	//�汾�Ų���
	E_ProofResult_Disabled						= 5,	//���ʺ��Ѿ�����ͣ
	E_ProofResult_Queue							= 6,	//��ʼ�Ŷ�	
	E_ProofResult_Mibao_Error					= 7,	//�ܱ�����
	E_ProofResult_Wrong_Type					= 8,	//�Ƿ���֤����
	E_ProofResult_Proofing						= 9,	//������֤���Ѿ���֤���

	E_SelectWorld_Server_Full					= 11,	//�÷�������ǰӵ��
	E_SelectWorld_Server_Suspended				= 12,	//�÷�������ǰ����
	E_SelectWorld_Server_Maintenance			= 13,	//�÷�������ǰά��
	E_SelectWorld_Failed						= 14,	//�����쳣��ѡ��ʧ��
	E_SelectWorld_Short_Time					= 15,	//���ʱ��̫��,���Ժ�����
	E_SelectWorld_No_Select						= 16,	//���Ѿ�ѡ��ɹ�,������ѡ
	E_SelectWorld_GameWorldName_Wrong			= 17,	//�Ƿ�����Ϸ������


	E_ProofResult_Forbid_MemberCenter			= 18,	//���Ļ�Ա�����˺��ѱ���ͣ������ϵ�ͷ�
	E_ProofResult_Forbid_GMTool					= 19,	//������Ϸ�˺��ѱ���ͣ������ϵ�ͷ�	
	E_ProofResult_Forbid_CellPhone				= 20,	//�����˺��ѱ�����������ϵ�ͷ�
	E_ProofResult_Forbid_MiBao					= 21,	//�����˺��Ѿ���ʧ�ܱ���������ɽ����¼
};

//---------------------------------------------------------------------------------------------
// �Ŷ�ʱ��10����
//---------------------------------------------------------------------------------------------
#define QUEUE_TIME	10*60


//! ��ɫ��֤��Ϣ
struct NET_C2L_proof : public tag_net_message
{
	NET_C2L_proof()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_C2L_proof");
		dw_size = sizeof(NET_C2L_proof);
	}
	CHAR	szUserName[X_SHORT_NAME];		// �û���
	DWORD	dwType;							// ��֤��ʽ
	DWORD	dwCurVersionID;					// ��ǰ�汾ID
	DWORD	dw_world_name_crc;					// ��Ϸ��������crc
	CHAR	szPsd[MAX_MD5_ARRAY];			// ����
	CHAR	szGUID[X_LONG_NAME];			// GUIDֵ
};

//! ��ɫ��֤���
struct NET_L2C_proof_result : public tag_net_message
{
	NET_L2C_proof_result()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_L2C_proof_result");
		dw_size = sizeof(NET_L2C_proof_result);
	}
	DWORD	dw_error_code;					// ������
	BOOL	bGuard;							// ������
	DWORD	dwIndex;						// �Ⱥ����к�
	DWORD	dwVerifyCode;					// ��½���������͸��ͻ��˵���֤�룬����GameServerʱҪ�õ�
	DWORD	dw_account_id;					// �ʺ�ID
	DWORD   dw_ip;							// GameServer IP ��ַ
	DWORD   dwPort;							// GameServer �˿ں�
};


//�����뱣��
struct NET_L2C_mibao : public tag_net_message
{
	NET_L2C_mibao()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_L2C_mibao");
		dw_size = sizeof(NET_L2C_mibao);
	}
	CHAR	szMiBao[MAX_MIBAO];				//! ���뱣����ʾ��
};

struct NET_C2L_mibao : public tag_net_message
{
	NET_C2L_mibao()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_C2L_mibao");
		dw_size = sizeof(NET_C2L_mibao);
	}
	DWORD	dwMBCrc;						//! ���뱣��crc
};

//����½�Ŷ�
struct NET_L2C_queue : public tag_net_message
{
	NET_L2C_queue()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_L2C_queue");
		dw_size = sizeof(NET_L2C_queue);
	}
	DWORD	dwPosition;						//! λ��
	DWORD	dw_time;						//! ʣ��ʱ��
};


#pragma pack(pop)
#endif

