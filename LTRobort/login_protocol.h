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
*	@brief		登陆验证消息
*/


#ifndef LOGIN_PROTOCOL
#define LOGIN_PROTOCOL

#include "protocol_common_errorcode.h"
#define MAX_MD5_ARRAY	36
#define MAX_MIBAO		6

#pragma pack(push, 1)

//--------------------------------------------------------------------------------------------
// Login 错误代码
//--------------------------------------------------------------------------------------------
enum
{
	E_ProofResult_Account_No_Match				= 1,	//此帐号非法(帐户不存在或者密码不对,密保错误)
	E_ProofResult_Account_In_Use				= 2,	//此帐号当前已经在使用
	E_ProofResult_Account_Freezed				= 3,	//此帐号被停用
	E_ProofResult_Wrong_Build_Number			= 4,	//版本号不对
	E_ProofResult_Disabled						= 5,	//此帐号已经被封停
	E_ProofResult_Queue							= 6,	//开始排队	
	E_ProofResult_Mibao_Error					= 7,	//密保错误
	E_ProofResult_Wrong_Type					= 8,	//非法验证策略
	E_ProofResult_Proofing						= 9,	//正在验证或已经验证完成

	E_SelectWorld_Server_Full					= 11,	//该服务器当前拥挤
	E_SelectWorld_Server_Suspended				= 12,	//该服务器当前阻塞
	E_SelectWorld_Server_Maintenance			= 13,	//该服务器当前维护
	E_SelectWorld_Failed						= 14,	//出现异常，选择失败
	E_SelectWorld_Short_Time					= 15,	//间隔时间太短,请稍候重试
	E_SelectWorld_No_Select						= 16,	//你已经选择成功,不可再选
	E_SelectWorld_GameWorldName_Wrong			= 17,	//非法的游戏世界名


	E_ProofResult_Forbid_MemberCenter			= 18,	//您的会员中心账号已被封停，请联系客服
	E_ProofResult_Forbid_GMTool					= 19,	//您的游戏账号已被封停，请联系客服	
	E_ProofResult_Forbid_CellPhone				= 20,	//您的账号已被锁定，请联系客服
	E_ProofResult_Forbid_MiBao					= 21,	//您的账号已经挂失密保卡，请完成解绑后登录
};

//---------------------------------------------------------------------------------------------
// 排队时间10分钟
//---------------------------------------------------------------------------------------------
#define QUEUE_TIME	10*60


//! 角色认证消息
struct NET_C2L_proof : public tag_net_message
{
	NET_C2L_proof()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_C2L_proof");
		dw_size = sizeof(NET_C2L_proof);
	}
	CHAR	szUserName[X_SHORT_NAME];		// 用户名
	DWORD	dwType;							// 验证方式
	DWORD	dwCurVersionID;					// 当前版本ID
	DWORD	dw_world_name_crc;					// 游戏世界名的crc
	CHAR	szPsd[MAX_MD5_ARRAY];			// 密码
	CHAR	szGUID[X_LONG_NAME];			// GUID值
};

//! 角色认证结果
struct NET_L2C_proof_result : public tag_net_message
{
	NET_L2C_proof_result()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_L2C_proof_result");
		dw_size = sizeof(NET_L2C_proof_result);
	}
	DWORD	dw_error_code;					// 错误码
	BOOL	bGuard;							// 防沉迷
	DWORD	dwIndex;						// 等候序列号
	DWORD	dwVerifyCode;					// 登陆服务器发送给客户端的验证码，连接GameServer时要用到
	DWORD	dw_account_id;					// 帐号ID
	DWORD   dw_ip;							// GameServer IP 地址
	DWORD   dwPort;							// GameServer 端口号
};


//！密码保护
struct NET_L2C_mibao : public tag_net_message
{
	NET_L2C_mibao()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_L2C_mibao");
		dw_size = sizeof(NET_L2C_mibao);
	}
	CHAR	szMiBao[MAX_MIBAO];				//! 密码保护提示码
};

struct NET_C2L_mibao : public tag_net_message
{
	NET_C2L_mibao()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_C2L_mibao");
		dw_size = sizeof(NET_C2L_mibao);
	}
	DWORD	dwMBCrc;						//! 密码保护crc
};

//！登陆排队
struct NET_L2C_queue : public tag_net_message
{
	NET_L2C_queue()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_L2C_queue");
		dw_size = sizeof(NET_L2C_queue);
	}
	DWORD	dwPosition;						//! 位置
	DWORD	dw_time;						//! 剩余时间
};


#pragma pack(pop)
#endif

