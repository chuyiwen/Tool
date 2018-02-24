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
*	@file		role_att_protocol.h
*	@author		wmr
*	@date		2011/03/10	initial
*	@version	0.0.1.0
*	@brief		人物属性消息
*/


#ifndef ROLE_ATT_PROTOCOL
#define ROLE_ATT_PROTOCOL

#include "protocol_common_errorcode.h"
#include "RoleDefine.h"
//#include "talent_define.h"
#include "skill_define.h"
#include "buff_define.h"
//#include "QuestDef.h"
//#include "suit_define.h"
//#include "SocialDef.h"
//#include "pet_define.h"
//#include "guild_define.h"
#pragma pack(push, 1)

enum
{
	E_BidAttPoint_PointInvalid			=	1,		// 投点不合法
	E_BidAttPoint_NoEnoughAttPoint		=	2,		// 没有足够的属性点

	E_ClearAttPoint_ItemNotValid		=	10,		// 使用的物品不合法

	E_JoinHang_State					=	11,		// 已经进入挂机状态
	E_Hang_Area_Limit					=   12,		// 挂机区域限制
	E_Hang_Equip_No_Exist				=	13,		// 挂机装备不存在
	E_Hang_Item_No_Exist				=	14,		// 挂机物品不存在
	E_Hang_Num_Limit					=   15,		// 挂机次数已满
	E_Hang_NoHang_State					=	16,		// 不在挂机状态
	E_Hang_State_Limit					=   17,		// 战斗状态不能挂机

	E_Gift_BagNoEnough					=   18,		// 背包空间不足
	E_Gift_NotGet						=   19,		// 奖励时间未到，不能获取
};

enum ERoleInitType
{
	ERIT_Null = -1,
	
	ERIT_Att				=	0,			// 人物基本属性
	ERIT_Skill				=	1,			// 人物技能
	ERIT_Item				=	2,			// 所有物品
	ERIT_ClientConfig		=	3,			// 客户端配置
	ERIT_FrindAndEnemy		=	4,			// 和所有好友的同步率,以及有哪些仇敌，黑名单
	ERIT_CompleteQuest		=	5,			// 已经完成的任务
	ERIT_IncompleteQuest	=	6,			// 没有完成的任务
	ERIT_Money				=	7,			// 金钱
	ERIT_Reputation			=	8,			// 声望
	ERIT_Guild				=	9,			// 帮派
	ERIT_XSQuest			=	10,			// 悬赏任务
	ERIT_MasterPrentice		=	11,			// 师徒
	ERIT_paimai				=   12,			// 拍卖
	ERIT_Other				=   13,			// 其他数据
	ERIT_End,
};

enum EClassErrorCode
{
    ECEC_Success            =   E_Success,

    ECEC_NotUpToLevel       =   1,          // 玩家等级不够
    ECEC_IsNotBaseClass     =   2,          // 只有少侠才能进行职业专精
    ECEC_LackOfNewclassItem =   3,          // 缺少职业专精凭证道具
    ECEC_LackOfReclassItem  =   4,          // 缺少更换专精职业im道具
	ECEC_IsNotBaseClassEx	=	5,			// 已就职了英雄职业
	ECEC_ClassNotMatch		=	6,			// 英雄职业与专精职业不匹配
	ECEC_ClassNotSet		=	7,			// 未就职专精职业，不可进行职业转换
	ECEC_NPCError			=	8,			// NPC无效

    ECEC_End,
};

//-----------------------------------------------------------------------------
// 状态改变
//-----------------------------------------------------------------------------
struct NET_SIS_set_state : public tag_net_message
{
	NET_SIS_set_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_set_state");
		dw_size = sizeof(NET_SIS_set_state);
	}
	DWORD		dw_role_id;
	EState		eState;
};

struct NET_SIS_unset_state : public tag_net_message
{
	NET_SIS_unset_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_unset_state");
		dw_size = sizeof(NET_SIS_unset_state);
	}
	DWORD		dw_role_id;
	EState		eState;
};

//-----------------------------------------------------------------------------
// 玩家状态改变
//-----------------------------------------------------------------------------
struct NET_SIS_set_role_state : public tag_net_message
{
	NET_SIS_set_role_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_set_role_state");
		dw_size = sizeof(NET_SIS_set_role_state);
	}
	DWORD		dw_role_id;						// 角色ID
	ERoleState	eState;							// 状态标志
};

struct NET_SIS_unset_role_state : public tag_net_message
{
	NET_SIS_unset_role_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_unset_role_state");
		dw_size = sizeof(NET_SIS_unset_role_state);
	}
	DWORD		dw_role_id;						// 角色ID
	ERoleState	eState;							// 状态标志
};

struct NET_SIS_set_role_state_extend : public tag_net_message
{
	NET_SIS_set_role_state_extend()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_set_role_state_extend");
		dw_size = sizeof(NET_SIS_set_role_state_extend);
	}
	ERoleStateEx	eState;							// 状态标志
};

struct NET_SIS_unset_role_state_extend : public tag_net_message
{
	NET_SIS_unset_role_state_extend()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_unset_role_state_extend");
		dw_size = sizeof(NET_SIS_unset_role_state_extend);
	}
	ERoleStateEx	eState;							// 状态标志
};

//-----------------------------------------------------------------------------
// 玩家显示设置改变
//-----------------------------------------------------------------------------
// 设置时装模式
struct NET_SIC_fashion : public tag_net_message
{
	NET_SIC_fashion()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_fashion");
		dw_size = sizeof(NET_SIC_fashion);
	}
	bool			bFashion;	// 是否使用使装模式
};

// 当前外观
struct NET_SIS_avatar_equip : public tag_net_message
{
	NET_SIS_avatar_equip()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_avatar_equip");
		dw_size = sizeof(NET_SIS_avatar_equip);
	}
	DWORD			dw_role_id;
	tagAvatarEquip	sAvatarEquip;
	bool			bFashion;	// 是否使用使装模式
};

// 设置部位显示属性
struct NET_SIC_role_set_display : public tag_net_message
{
	NET_SIC_role_set_display()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_role_set_display");
		dw_size = sizeof(NET_SIC_role_set_display);
	}
	tagDisplaySet	sDisplaySet;
};

struct NET_SIS_role_set_display : public tag_net_message
{
	NET_SIS_role_set_display()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_set_display");
		dw_size = sizeof(NET_SIS_role_set_display);
	}
	DWORD			dw_role_id;
	tagDisplaySet	sDisplaySet;
};


//-----------------------------------------------------------------------------
// 玩家个人设置改变
//-----------------------------------------------------------------------------
// 修改本地玩家的个人设置
struct NET_SIC_change_personal_setting : public tag_net_message
{
	NET_SIC_change_personal_setting()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_change_personal_setting");
		dw_size = sizeof(NET_SIC_change_personal_setting);
	}
	tagDWPlayerPersonalSet	PersonalSet;
};

struct NET_SIS_change_personal_setting : public tag_net_message
{
	NET_SIS_change_personal_setting()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_personal_setting");
		dw_size = sizeof(NET_SIS_change_personal_setting);
	}
	tagDWPlayerPersonalSet	PersonalSet;
};

//-----------------------------------------------------------------------------
// 获取本地玩家初始结构
//-----------------------------------------------------------------------------
struct NET_SIC_get_role_init_state : public tag_net_message
{
	NET_SIC_get_role_init_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_get_role_init_state");
		dw_size = sizeof(NET_SIC_get_role_init_state);
	}
	ERoleInitType eType;					// 客户端需要得到数据类型
};


//-----------------------------------------------------------------------------
// 返回人物初始属性
//-----------------------------------------------------------------------------
struct NET_SIS_get_role_init_state_att : public tag_net_message
{
	NET_SIS_get_role_init_state_att()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_att");
		dw_size = sizeof(NET_SIS_get_role_init_state_att);
	}
	tagAvatarAtt	Avatar;							// 外观
	tagAvatarEquip	AvatarEquip;					// 装备外观
	tagDisplaySet	DisplaySet;						// 外观显示设置
	INT				nAtt[ERA_End];					// 当前人物属性
	INT				nAttPointAdd[X_ERA_ATTA_NUM];	// 玩家投放到各个一级属性中的值
	INT				nLevel;							// 等级
	INT				nCurLevelExp;					// 当前升级经验
	INT				nCredit;						// 信用度
	INT				nIdentity;						// 身份
	INT				nVIPPoint;						// 会员积分
	DWORD			dwState;						// 状态标志位
	DWORD			dwRoleState;					// 玩家独有状态标志位 -- 需广播给周围玩家
	DWORD			dwRoleStateEx;					// 玩家独有状态标志位 -- 只须自己知道
	ERolePKState	ePKState;						// PK状态
	INT				iPKValue;						// PK值
	DWORD			dwRebornMapID;					// 复活地图ID
	Vector3			vRebornPoint;					// 复活点
	DWORD			dwGuildID;						// 帮派id
	UINT16			u16ActTitleID;					// 当前激活称号ID
	INT				nBuffNum;						// 状态数量
	BOOL			bHasLeftMsg;					// 有留言
	EClassType      eClassType;                     // 专精职业
	EClassTypeEx    eClassTypeEx;                   // 英雄职业(未开放)
	DWORD			dwMasterID;						// 师傅ID；
	INT16			n16PetPocketNum;				// 宠物栏数量
	INT				nTotalMasterMoral;				// 总师德值
	INT				nKillNum;						// 杀人数
	ECamp			e_role_camp;					// 角色阵营
	ECamp			e_temp_role_camp;				// 角色临时阵营
	tagBuffMsgInfo	Buff[1];						// 状态列表
};


//-----------------------------------------------------------------------------
// 返回人物技能列表
//-----------------------------------------------------------------------------
//struct NET_SIS_get_role_init_state_skill : public tag_net_message
//{
//	NET_SIS_get_role_init_state_skill()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_skill");
//		dw_size = sizeof(NET_SIS_get_role_init_state_skill);
//	}
//	tagRoleTalent		Talent[X_MAX_TALENT_PER_ROLE];	// 天资
//	INT					n_num;							// 技能个数
//	tagSkillMsgInfo		Skill[1];						// 技能列表
//};

//-----------------------------------------------------------------------------
// 已经完成的任务 不定长
//-----------------------------------------------------------------------------
//struct NET_SIS_get_role_init_state_complete_quest : public tag_net_message
//{
//	NET_SIS_get_role_init_state_complete_quest()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_complete_quest");
//		dw_size = sizeof(NET_SIS_get_role_init_state_complete_quest);
//	}
//	INT					n_num;						// 任务个数
//	tagCompleteQuestMsgInfo completeQuest[1];
//};

//-----------------------------------------------------------------------------
// 当前任务
//-----------------------------------------------------------------------------
//struct NET_SIS_get_role_init_state_incomplete_quest : public tag_net_message
//{
//	NET_SIS_get_role_init_state_incomplete_quest()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_incomplete_quest");
//		dw_size = sizeof(NET_SIS_get_role_init_state_incomplete_quest);
//	}
//	INT					n_num;						// 任务个数
//	tagIncompleteQuestMsgInfo incompleteQuest[1];
//};


//-----------------------------------------------------------------------------
// 所有物品装备
//-----------------------------------------------------------------------------
struct NET_SIS_get_role_init_state_item : public tag_net_message
{
	NET_SIS_get_role_init_state_item()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_item");
		dw_size = sizeof(NET_SIS_get_role_init_state_item);
	}
	INT16	n16SzBag;					// 背包大小
	INT16	n16SzRoleWare;				// 仓库大小
	INT		n_num;						// 物品装备个数
	BYTE	byData[1];					// 技能列表
};


//-----------------------------------------------------------------------------
// 套装
//-----------------------------------------------------------------------------
struct NET_SIS_get_role_init_state_suit : public tag_net_message
{
	NET_SIS_get_role_init_state_suit()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_suit");
		dw_size = sizeof(NET_SIS_get_role_init_state_suit);
	}
	INT		nSuitNum;
	BYTE	byData[1];					// tagSuitInit
};


//-----------------------------------------------------------------------------
// 所有物品冷却时间
//-----------------------------------------------------------------------------
struct NET_SIS_get_role_init_state_itemcdtime : public tag_net_message
{
	NET_SIS_get_role_init_state_itemcdtime()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_itemcdtime");
		dw_size = sizeof(NET_SIS_get_role_init_state_itemcdtime);
	}
	INT		n_num;						// 冷却时间物品(TypeID)个数
	BYTE	byData[1];					// tagCDTime
};

//-----------------------------------------------------------------------------
// 所有金钱
//-----------------------------------------------------------------------------
//struct NET_SIS_get_role_init_state_money : public tag_net_message
//{
//	NET_SIS_get_role_init_state_money()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_money");
//		dw_size = sizeof(NET_SIS_get_role_init_state_money);
//	}
//	INT32	nBagYuanBao;
//	INT64	n64BagSilver;
//	INT64	n64BagBindSilver;
//	INT64	n64WareSilver;
//	INT32	nBaiBaoYuanBao;
//	INT32	nExchangeVolume;
//	INT32	nCurClanCon[ECLT_NUM];
//};

//-----------------------------------------------------------------------------
// 所有声望
//-----------------------------------------------------------------------------
//struct NET_SIS_get_role_init_state_reputation : public tag_net_message
//{
//	NET_SIS_get_role_init_state_reputation()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_reputation");
//		dw_size = sizeof(NET_SIS_get_role_init_state_reputation);
//	}
//	INT		nReputation[ECLT_NUM];
//	BYTE    nActiveCount[ECLT_NUM];	
//	BYTE    bisFame[ECLT_NUM];
//};

//-----------------------------------------------------------------------------
// 所在帮派信息及个人信息
//-----------------------------------------------------------------------------
//struct NET_SIS_get_role_init_state_guild : public tag_net_message
//{
//	NET_SIS_get_role_init_state_guild()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_role_init_state_guild");
//		dw_size = sizeof(NET_SIS_get_role_init_state_guild);
//	}
//	tagGuildBase	sGuildBase;			// 帮派基本属性
//	tagGuildMember	sGuildMember;		// 个人信息
//};

//------------------------------------------------------------------------------
// 获取远程玩家当前属性
//------------------------------------------------------------------------------
struct NET_SIC_get_remote_role_state : public tag_net_message
{
	NET_SIC_get_remote_role_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_get_remote_role_state");
		dw_size = sizeof(NET_SIC_get_remote_role_state);
	}
	INT		nRoleNum;
	DWORD	dw_role_id[1];	// 可能是远程人物，也可能是远程怪物，一次发送最多50个
};

//-------------------------------------------------------------------------------------------
// 客户端远程玩家同步数据消息结构
//-------------------------------------------------------------------------------------------
struct tagRemoteRoleData
{
	DWORD				dwID;						// 玩家ID
	INT					nLevel;						// 等级
	FLOAT				fPos[3];					// 位置
	FLOAT				fFaceTo[3];					// 朝向
	DWORD				dwState;					// 状态标志位
	DWORD				dwRoleState;				// 角色独有状态标志位
	ERolePKState		ePKState;					// PK状态
	INT					iPKValue;					// PK值
	//BOOL				bIsGrayName;				// 是否灰名
	DWORD				dwGuildID;					// 帮派id(INVALID_VALUE表示没有加入帮派)
	DWORD				dwTeamID;					// 队伍id(INVALID_VALUE表示没有加入队伍)
	//INT8				n8GuildPos;					// 帮派职位
	UINT16				u16CurActTitleID;			// 激活称号(INVALID_VALUE表示没有激活称号)
	BYTE				byStallLevel;				// 摊位模型等级
	DWORD				dwMountPetID;				// 骑乘宠物id
	DWORD				dwMountPetTypeID;			// 骑乘宠物typeid
	tagDisplaySet		sDisplaySet;				// 装备外观显示设置
	tagAvatarAtt		Avatar;						// 外观
	tagAvatarEquip		AvatarEquip;				// 装备外观
	INT					nAtt[ERRA_End];				// 远程玩家基本属性
	tagRemoteOpenSet	sRemoteOpenSet;				// 对远端玩家公开信息设置
    EClassType          eClassType;                 // 专精职业
    EClassTypeEx        eClassTypeEx;               // 英雄职业
	//tagDWORDTime		dwChangeSymbolTime;			// 帮会标志改变时间
	DWORD				dwSymbolValue;				// 帮会标志

	DWORD				dwMountRideTypeID;			//骑乘typeid
	BYTE				bySolidateLevel;			//强化等级

	DWORD				dwMasterID;					//师傅ID

	ECamp				e_role_camp;				// 角色阵营
	ECamp				e_temp_role_camp;			// 角色临时阵营

	BYTE				byLeader;					// 是否队长
	INT					nBuffNum;					// 状态数量
	tagBuffMsgInfo		Buff[1];					// 状态列表
};

struct NET_SIS_get_remote_role_state : public tag_net_message
{
	NET_SIS_get_remote_role_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_remote_role_state");
		dw_size = sizeof(NET_SIS_get_remote_role_state);
	}
	tagRemoteRoleData		RoleData;		// 远程玩家结构，可能到后期也会变成不定长结构
};

//---------------------------------------------------------------------
// 远程生物属性结构
//---------------------------------------------------------------------
enum ECreatureType
{
	ECT_NULL		=	0,
	ECT_Monster		=	1,		// 怪物
	ECT_GameObject	=	2,		// 可交互的地物
	ECT_NPC			=	3,		// 普通NPC
	ECT_Pet			=	4,		// 宠物
};

struct tagRemoteCreatureData
{
	DWORD			dwID;						// 生物ID
	DWORD			dw_data_id;					// 属性ID
	INT				nLevel;						// 等级
	DWORD			dwState;					// 状态标志位
	FLOAT			fPos[3];					// 位置
	FLOAT			fFaceTo[3];					// 朝向
	INT				nAtt[ERRA_End];				// 远程玩家基本属性
	DWORD			dwMapObjID;					// 地图对象ID	
	BOOL			bOpen;						// 门初始状态
	DWORD			dwGuildID;					// 所属帮会ID
	DWORD			dwTaggedOwner;				// 
	//BOOL			bCanBeAttack;				// 是否可被攻击
	ECreatureType	eCreType;					// 类型
	INT				nBuffNum;					// 状态数量
	tagBuffMsgInfo	Buff[1];					// 状态列表
};

struct NET_SIS_get_remote_creature_state : public tag_net_message
{
	NET_SIS_get_remote_creature_state()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_remote_creature_state");
		dw_size = sizeof(NET_SIS_get_remote_creature_state);
	}
	tagRemoteCreatureData	CreatureData;		// 远程生物结构
};


//---------------------------------------------------------------------
// 远程宠物属性结构
//---------------------------------------------------------------------
//struct tagRemotePetData
//{
//    DWORD           dw_role_id;                   // 宠物所属的角色id，为-1时代表有问题
//	DWORD			dwID;						// 生物ID
//	DWORD			dwProtoID;					// 原型ID
//	UPetState		uState;						// 形态
//};
//
//struct NET_SIS_get_remote_pet_state : public tag_net_message
//{
//	NET_SIS_get_remote_pet_state()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_get_remote_pet_state");
//		dw_size = sizeof(NET_SIS_get_remote_pet_state);
//	}
//	tagRemotePetData	PetData;
//};

//------------------------------------------------------------------------------
// 本地玩家属性改变
//------------------------------------------------------------------------------
struct NET_SIS_single_role_att_change : public tag_net_message
{
	NET_SIS_single_role_att_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_single_role_att_change");
		dw_size = sizeof(NET_SIS_single_role_att_change);
	}
	ERoleAttribute	eType;
	INT				nValue;
};


struct tagRoleAttValue
{
	ERoleAttribute	eType;
	INT				nValue;
};

struct NET_SIS_mutiple_role_att_change : public tag_net_message
{
	NET_SIS_mutiple_role_att_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_mutiple_role_att_change");
		dw_size = sizeof(NET_SIS_mutiple_role_att_change);
	}
	INT				n_num;
	tagRoleAttValue	value[1];
};	

//-------------------------------------------------------------------------------
// 远程玩家以及远程生物属性改变
//------------------------------------------------------------------------------
struct NET_SIS_single_remote_att_change : public tag_net_message
{
	NET_SIS_single_remote_att_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_single_remote_att_change");
		dw_size = sizeof(NET_SIS_single_remote_att_change);
	}
	DWORD			dw_role_id;
	ERemoteRoleAtt	eType;
	INT				nValue;
};


struct tagRemoteAttValue
{
	ERemoteRoleAtt	eType;
	INT				nValue;
};

struct NET_SIS_mutiple_remote_att_change : public tag_net_message
{
	NET_SIS_mutiple_remote_att_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_mutiple_remote_att_change");
		dw_size = sizeof(NET_SIS_mutiple_remote_att_change);
	}
	DWORD				dw_role_id;
	INT					n_num;
	tagRemoteAttValue	value[1];
};


//--------------------------------------------------------------------------------
// 玩家经验改变
//--------------------------------------------------------------------------------
struct NET_SIS_change_role_exp : public tag_net_message
{
	NET_SIS_change_role_exp()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_role_exp");
		dw_size = sizeof(NET_SIS_change_role_exp);
	}
	INT		nExp;				// 当前
	INT		nChange;			// 变化多少
	BOOL	bKill;				// 是否通过击杀怪物获得
};

struct NET_SIS_role_exp_share_num : public tag_net_message
{
	NET_SIS_role_exp_share_num()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_exp_share_num");
		dw_size = sizeof(NET_SIS_role_exp_share_num);
	}
	INT		nShareNum;			// 组队经验共享人数
};

//--------------------------------------------------------------------------------
// 玩家声望
//--------------------------------------------------------------------------------
struct NET_SIS_change_role_repute : public tag_net_message
{
	NET_SIS_change_role_repute()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_role_repute");
		dw_size = sizeof(NET_SIS_change_role_repute);
	}
	BYTE	byClanType;			// 氏族
	INT		nRepute;			// 当前
	INT		nChange;			// 变化多少
};

//-----------------------------------------------------------------------------
// 名人状态改变
//-----------------------------------------------------------------------------
struct NET_SIS_becomeframe : public tag_net_message
{
	NET_SIS_becomeframe()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_becomeframe");
		dw_size = sizeof(NET_SIS_becomeframe);
	}
	 BYTE    eClanType;
};

//-----------------------------------------------------------------------------
// 远程玩家帮派信息变化
//-----------------------------------------------------------------------------
struct NET_SIS_remote_role_guild_info_change : public tag_net_message
{
	NET_SIS_remote_role_guild_info_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_remote_role_guild_info_change");
		dw_size = sizeof(NET_SIS_remote_role_guild_info_change);
	}
	DWORD	dw_role_id;
	DWORD	dwGuildID;					// 帮派id(INVALID_VALUE表示没有加入帮派)
	INT8	n8GuildPos;					// 帮派职位
};


//-----------------------------------------------------------------------------
// 氏族珍宝激活次数改变
//-----------------------------------------------------------------------------
struct NET_SIS_change_treasure_act_count : public tag_net_message
{
	NET_SIS_change_treasure_act_count()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_treasure_act_count");
		dw_size = sizeof(NET_SIS_change_treasure_act_count);
	}
	BYTE    eClanType;
	BYTE    nActCount;
};

//-----------------------------------------------------------------------------
// 氏族贡献达到上限
//-----------------------------------------------------------------------------
struct NET_SIS_gens_contribute_upper_limit : public tag_net_message
{
	NET_SIS_gens_contribute_upper_limit()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_gens_contribute_upper_limit");
		dw_size = sizeof(NET_SIS_gens_contribute_upper_limit);
	}
	BYTE    eClanType;
};

//--------------------------------------------------------------------------------
// 玩家等级改变
//--------------------------------------------------------------------------------
struct NET_SIS_change_role_level : public tag_net_message
{
	NET_SIS_change_role_level()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_role_level");
		dw_size = sizeof(NET_SIS_change_role_level);
	}
	DWORD	dw_role_id;
	INT		nLevel;
	BOOL	bKill;				// 是否因为击杀怪物产生变化
};


//--------------------------------------------------------------------------------
// 玩家属性投点
//--------------------------------------------------------------------------------
struct NET_SIC_role_att_point : public tag_net_message
{
	NET_SIC_role_att_point()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_role_att_point");
		dw_size = sizeof(NET_SIC_role_att_point);
	}
	INT	nAttPointAdd[X_ERA_ATTA_NUM];
};

struct NET_SIS_role_att_point : public tag_net_message
{
	NET_SIS_role_att_point()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_att_point");
		dw_size = sizeof(NET_SIS_role_att_point);
	}
	DWORD dw_error_code;	// 错误码
};

//---------------------------------------------------------------------------------
// 玩家属性洗点
//---------------------------------------------------------------------------------
struct NET_SIC_clear_att_point : public tag_net_message
{
	NET_SIC_clear_att_point()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_clear_att_point");
		dw_size = sizeof(NET_SIC_clear_att_point);
	}
	INT64 n64ItemID;				// 洗点道具
};

struct NET_SIS_clear_att_point : public tag_net_message
{
	NET_SIS_clear_att_point()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_clear_att_point");
		dw_size = sizeof(NET_SIS_clear_att_point);
	}
	DWORD dw_error_code;				// 错误码
};

//---------------------------------------------------------------------------------
// 玩家各个一级属性投放值改变
//---------------------------------------------------------------------------------
struct NET_SIS_add_change_role_att_point : public tag_net_message
{
	NET_SIS_add_change_role_att_point()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_add_change_role_att_point");
		dw_size = sizeof(NET_SIS_add_change_role_att_point);
	}
	INT	nAttPointAdd[X_ERA_ATTA_NUM];
};


//---------------------------------------------------------------------------------
// 玩家好友
//---------------------------------------------------------------------------------
//struct NET_SIS_send_friend_list : public tag_net_message
//{
//	NET_SIS_send_friend_list()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_send_friend_list");
//		dw_size = sizeof(NET_SIS_send_friend_list);
//	}
//	INT				n_num;		  // 好友数量
//	tagFriendInfo	FriendInfo[1];
//};

//---------------------------------------------------------------------------------
// 玩家黑名单
//---------------------------------------------------------------------------------
//struct NET_SIS_send_black_list : public tag_net_message
//{
//	NET_SIS_send_black_list()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_send_black_list");
//		dw_size = sizeof(NET_SIS_send_black_list);
//	}
//	INT				n_num;
//	tagBlackInfo	BlackInfo[1];
//};

//---------------------------------------------------------------------------------
// 玩家仇人
//---------------------------------------------------------------------------------
//struct NET_SIS_send_enemy_list : public tag_net_message
//{
//	NET_SIS_send_enemy_list()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_send_enemy_list");
//		dw_size = sizeof(NET_SIS_send_enemy_list);
//	}
//	INT				n_num;
//	tagEnemyInfo	EnemyInfo[1];
//};

//---------------------------------------------------------------------------------
// 开/关门
//---------------------------------------------------------------------------------
//struct NET_SIS_open_door : public tag_net_message
//{
//	NET_SIS_open_door()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_open_door");
//		dw_size = sizeof(NET_SIS_open_door);
//	}
//	DWORD			dw_role_id;
//};
//
//struct NET_SIS_close_door : public tag_net_message
//{
//	NET_SIS_close_door()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_close_door");
//		dw_size = sizeof(NET_SIS_close_door);
//	}
//	DWORD			dw_role_id;
//};

//---------------------------------------------------------------------------------
// 怪物所属改变
//---------------------------------------------------------------------------------
struct NET_SIS_change_creuture_adscription : public tag_net_message
{
	NET_SIS_change_creuture_adscription()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_creuture_adscription");
		dw_size = sizeof(NET_SIS_change_creuture_adscription);
	}
	DWORD			dwCreatureID;
	DWORD			dwTaggedOwner;
};

//---------------------------------------------------------------------------------
// NPC对话
//---------------------------------------------------------------------------------
struct NET_SIC_npc_talk : public tag_net_message
{
	NET_SIC_npc_talk()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_npc_talk");
		dw_size = sizeof(NET_SIC_npc_talk);
	}
	DWORD			dwNPCId;
};


//----------------------------------------------------------------------------------
// 向服务器请求对方的装备
//----------------------------------------------------------------------------------
struct NET_SIC_get_remote_role_equip_info : public tag_net_message
{
	NET_SIC_get_remote_role_equip_info()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_get_remote_role_equip_info");
		dw_size = sizeof(NET_SIC_get_remote_role_equip_info);
	}
	DWORD			dw_role_id;
};

struct NET_SIS_get_remote_role_equip_info : public tag_net_message
{
	NET_SIS_get_remote_role_equip_info()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_remote_role_equip_info");
		dw_size = sizeof(NET_SIS_get_remote_role_equip_info);
	}
	DWORD			dw_role_id;					
	INT				nEquipNum;					//装备个数
	BYTE			byEquip[1];					//装备
};


//-----------------------------------------------------------------------------
// 开始挂机
//-----------------------------------------------------------------------------
struct NET_SIC_start_hang : public tag_net_message
{
	NET_SIC_start_hang()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_start_hang");
		dw_size = sizeof(NET_SIC_start_hang);
	}
};

struct NET_SIS_start_hang : public tag_net_message
{
	NET_SIS_start_hang()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_start_hang");
		dw_size = sizeof(NET_SIS_start_hang);
	}
	DWORD dwError;
};

//-----------------------------------------------------------------------------
// 取消挂机
//-----------------------------------------------------------------------------
struct NET_SIC_cancel_hang : public tag_net_message
{
	NET_SIC_cancel_hang()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_cancel_hang");
		dw_size = sizeof(NET_SIC_cancel_hang);
	}
};

struct NET_SIS_cancel_hang : public tag_net_message
{
	NET_SIS_cancel_hang()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_cancel_hang");
		dw_size = sizeof(NET_SIS_cancel_hang);
	}
	DWORD dwError;
};

//-----------------------------------------------------------------------------
// 离线关机设置
//-----------------------------------------------------------------------------
struct NET_SIC_set_leave_line_hang : public tag_net_message
{
	NET_SIC_set_leave_line_hang()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_set_leave_line_hang");
		dw_size = sizeof(NET_SIC_set_leave_line_hang);
	}
	BOOL		bExp;				// 是否使用经验丹
	BOOL		bBrotherhood;		// 是否使用义气丹 
};

//-----------------------------------------------------------------------------
// 获取离线经验
//-----------------------------------------------------------------------------
struct NET_SIC_get_leave_exp : public tag_net_message
{
	NET_SIC_get_leave_exp()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_get_leave_exp");
		dw_size = sizeof(NET_SIC_get_leave_exp);
	}
};

struct NET_SIS_get_leave_exp : public tag_net_message
{
	NET_SIS_get_leave_exp()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_leave_exp");
		dw_size = sizeof(NET_SIS_get_leave_exp);
	}
	INT			nExp;		
	INT			nBrotherHand;
	INT16		n16HangNum;
};


//-----------------------------------------------------------------------------
// 提取离线经验
//-----------------------------------------------------------------------------
struct NET_SIC_pickup_leave_exp : public tag_net_message
{
	NET_SIC_pickup_leave_exp()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_pickup_leave_exp");
		dw_size = sizeof(NET_SIC_pickup_leave_exp);
	}
	INT16		n16Type;		//1.提取离线经验	2.提取离线义气
};

struct NET_SIS_pickup_leave_exp : public tag_net_message
{
	NET_SIS_pickup_leave_exp()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_pickup_leave_exp");
		dw_size = sizeof(NET_SIS_pickup_leave_exp);
	}
	DWORD		dwError;
};

//-----------------------------------------------------------------------------
// 离线经验上线提示
//-----------------------------------------------------------------------------
struct NET_SIS_leave_exp_clueon : public tag_net_message
{
	NET_SIS_leave_exp_clueon()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_leave_exp_clueon");
		dw_size = sizeof(NET_SIS_leave_exp_clueon);
	}
	INT			nExp;				// 离线经验
	INT			nBrother;			// 离线义气
	INT			nExpItem;			// 消耗经验丹个数
	INT			nBrotherItem;		// 消耗义气丹个数
};

//-----------------------------------------------------------------------------
// 更新挂机次数挂机
//-----------------------------------------------------------------------------
struct NET_SIS_change_hang_num : public tag_net_message
{
	NET_SIS_change_hang_num()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_hang_num");
		dw_size = sizeof(NET_SIS_change_hang_num);
	}
	INT16 n16HangNum;
};

//-----------------------------------------------------------------------------
// 宠物栏数量变化
//-----------------------------------------------------------------------------
struct NET_SIS_pet_pocket_size_change : public tag_net_message
{
	NET_SIS_pet_pocket_size_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_pet_pocket_size_change");
		dw_size = sizeof(NET_SIS_pet_pocket_size_change);
	}
	INT16 n16NewSize;
};

//-----------------------------------------------------------------------------
// 帮助数据
//-----------------------------------------------------------------------------
struct NET_SIS_role_help : public tag_net_message
{	
	NET_SIS_role_help()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_help");
		dw_size = sizeof(NET_SIS_role_help);
	}
	BYTE byRoleHelp[ROLE_HELP_NUM];
};


//-----------------------------------------------------------------------------
// 修改帮助数据
//-----------------------------------------------------------------------------
struct NET_SIC_modify_role_help : public tag_net_message
{
	NET_SIC_modify_role_help()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_modify_role_help");
		dw_size = sizeof(NET_SIC_modify_role_help);
	}
	BYTE	byIndex;
};


//-----------------------------------------------------------------------------
// 人物对话数据
//-----------------------------------------------------------------------------
struct NET_SIS_role_talk : public tag_net_message
{
	NET_SIS_role_talk()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_talk");
		dw_size = sizeof(NET_SIS_role_talk);
	}
	BYTE	byRoleTalk[TALK_DATA_NUM];
};

//-----------------------------------------------------------------------------
// 修改人物对话数据
//-----------------------------------------------------------------------------
struct NET_SIC_modify_role_talk : public tag_net_message
{
	NET_SIC_modify_role_talk()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_modify_role_talk");
		dw_size = sizeof(NET_SIC_modify_role_talk);
	}
	BYTE	byIndex;
	BYTE	byState;
};

//-----------------------------------------------------------------------------
// 人物快捷键数据
//-----------------------------------------------------------------------------
struct NET_SIS_key_info : public tag_net_message
{
	NET_SIS_key_info()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_key_info");
		dw_size = sizeof(NET_SIS_key_info);
	}
	tagKeyInfo stKeyInfo[MAX_KEY_NUM];
};

//-----------------------------------------------------------------------------
// 修改人物快捷键数据
//-----------------------------------------------------------------------------
struct NET_SIC_modify_key_info : public tag_net_message
{
	NET_SIC_modify_key_info()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_modify_key_info");
		dw_size = sizeof(NET_SIC_modify_key_info);
	}
	tagKeyInfo stKeyInfo[MAX_KEY_NUM];
};

//-----------------------------------------------------------------------------
// 发送新手奖励数据
//-----------------------------------------------------------------------------
struct NET_SIS_new_role_gift : public tag_net_message
{
	NET_SIS_new_role_gift()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_new_role_gift");
		dw_size = sizeof(NET_SIS_new_role_gift);
	}
	DWORD		dwGiftID;				// 奖励物品ID
	DWORD		dwLeavingTime;			// 剩余时间
	BOOL		bCal;					// 是否启动
};

//-----------------------------------------------------------------------------
// 启动新手奖励
//-----------------------------------------------------------------------------
struct NET_SIC_start_new_role_gift : public tag_net_message
{
	NET_SIC_start_new_role_gift()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_start_new_role_gift");
		dw_size = sizeof(NET_SIC_start_new_role_gift);
	}
};

//-----------------------------------------------------------------------------
// 获取新手奖励
//-----------------------------------------------------------------------------
struct NET_SIC_get_new_role_gift : public tag_net_message
{
	NET_SIC_get_new_role_gift()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_get_new_role_gift");
		dw_size = sizeof(NET_SIC_get_new_role_gift);
	}
};

struct NET_SIS_get_new_role_gift : public tag_net_message
{
	NET_SIS_get_new_role_gift()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_new_role_gift");
		dw_size = sizeof(NET_SIS_get_new_role_gift);
	}
	DWORD	 dwError;
};

//-----------------------------------------------------------------------------
// 延迟
//-----------------------------------------------------------------------------
struct NET_SIC_get_delay : public tag_net_message
{
	NET_SIC_get_delay()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_get_delay");
		dw_size = sizeof(NET_SIC_get_delay);
	}
};

struct NET_SIS_get_delay : public tag_net_message
{
	NET_SIS_get_delay()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_get_delay");
		dw_size = sizeof(NET_SIS_get_delay);
	}
};

//-----------------------------------------------------------------------------
// 人物阵营改变
//-----------------------------------------------------------------------------
struct NET_SIS_change_role_camp : public tag_net_message
{
	NET_SIS_change_role_camp()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_change_role_camp");
		dw_size = sizeof(NET_SIS_change_role_camp);
	}
	ECamp		e_role_camp;
	ECamp		e_temp_role_camp;
};


struct NET_SIS_remove_remote : public tag_net_message
{
	NET_SIS_remove_remote()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_remove_remote");
		dw_size = sizeof(NET_SIS_remove_remote);
	}
	DWORD	dw_role_id[1];
};

#pragma pack(pop)
#endif