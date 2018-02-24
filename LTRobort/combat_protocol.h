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
*	@file		combat_protocol.h
*	@author		wmr
*	@date		2011/03/01	initial
*	@version	0.0.1.0
*	@brief		战斗相关协议
*/

#ifndef COMBAT_PROTOCOL
#define COMBAT_PROTOCOL

#include "protocol_common_errorcode.h"
#include "buff_define.h"
#include "move_define.h"

#pragma pack(push, 1)
//----------------------------------------------------------------------------
// 错误码枚举
//----------------------------------------------------------------------------
enum
{
	E_UseSkill_SkillNotExist		=	1,		// 技能不存在
	E_UseSkill_TargetInvalid		=	2,		// 目标非法
	E_UseSkill_PassiveSkill			=	3,		// 被动技能不能使用
	E_UseSkill_SkillTargetInvalid	=	4,		// 技能本身不是针对于战斗目标
	E_UseSkill_CoolDowning			=	5,		// 技能正在冷却
	E_UseSkill_Operating			=	6,		// 技能正在发动
	E_UseSkill_UseLimit				=	7,		// 发动条件不满足
	E_UseSkill_SexLimit				=	8,		// 性别不满足
	E_UseSkill_PosLimitFront		=	9,		// 位置不满足（必须在身前）
	E_UseSkill_PosLimitBack			=	10,		// 位置不满足（必须在身后）
	E_UseSkill_DistLimit			=	11,		// 距离不满足
	E_UseSkill_RayLimit				=	12,		// 射线检测不满足
	E_UseSkill_CostLimit			=	13,		// 消耗不够
	E_UseSkill_TargetLimit			=	14,		// 目标限制
	E_UseSkill_StallLimit			=	15,		// 摆摊状态下不可使用技能
	E_UseSkill_WeaponLimit			=	16,		// 武器限制
	E_UseSkill_SelfStateLimit		=	17,		// 自身状态限制
	E_UseSkill_TargetStateLimit		=	18,		// 目标状态限制
	E_UseSkill_SelfBuffLimit		=	19,		// 自身Buff限制
	E_UseSkill_TargetBuffLimit		=	20,		// 目标Buff限制
	E_UseSkill_Mount_NoPreparingPet	=	21,		// 没有预备宠物
	E_UseSkill_VocationLimit		=	22,		// 职业限制
	E_UseSkill_MapLimit				=	23,		// 无法在该地图内使用

	E_UseItem_ItemNotExist			=	30,		// 物品不存在
	E_UseItem_TargetInvalid			=	31,		// 目标非法
	E_UseItem_ItemCanNotUse			=	32,		// 物品不可使用
	E_UseItem_CoolDowning			=	33,		// 物品正在冷却
	E_UseItem_SexLimit				=	34,		// 性别不满足
	E_UseItem_LevelLimit			=   35,		// 等级限制
	E_UseItem_DistLimit				=	36,		// 距离不满足
	E_UseItem_RayLimit				=	37,		// 射线检测不满足
	E_UseItem_UseLimit				=	38,		// 人物以死亡,不能使用
	E_UseItem_Operating				=	39,		// 物品正在北使用
	E_UseItem_NotEnoughSpace		=   40,		// 背包空间不足
	E_UseItem_ReAcceptQuest			=	41,		// 您已经接取过该任务
	E_UseItem_ActivityLimit			=	42,		// 该道道具只可在固定活动中使用
	E_UseItem_PosLimit				=	43,		// 不可在该位置使用该物品
	E_UseItem_SelfStateLimit		=	44,		// 玩家自身状态限制
	E_UseItem_AcceptSimQuest		=	45,		// 您身上已经有同类任务
	E_UseItem_VocationLimit			=	46,		// 职业限制物品使用
	E_UseItem_MapLimit				=	47,		// 无法在该地图内使用
	E_UseItem_ItemOutOfNumber		=	48,		// 物品数量不足
	E_UseItem_CantUseInBattle		=	49,		// 战斗中不可使用该物品

	E_Revive_Unknown				=	50,		// 未知复活类型
	E_Revive_NotDead				=	51,		// 不在死亡状态
	E_Revive_CanNotTransmit			=	52,		// 回城复活时传送失败
	E_Revive_ItemLimit				=	53,		// 原地复活时缺少相应道具
	E_Revive_CanNotAccept			=	54,		// 接受复活时失败
	E_Revive_MapNotFound			=	55,		// 没有找到复活地图
};

//----------------------------------------------------------------------------
// 角色HP变化原因
//----------------------------------------------------------------------------
enum ERoleHPChangeCause
{
	ERHPCC_SkillDamage,				//技能伤害引起
	ERHPCC_BuffDamage,				//Buff伤害引起
	ERHPCC_Other,					//其它原因
};

//----------------------------------------------------------------------------
// 角色死亡原因
//----------------------------------------------------------------------------
enum ERoleDeadCause
{
	ERDC_Skill,						//技能伤害引起
	ERDC_Buff,						//Buff伤害引起
	ERDC_Other,						//其它原因
};

//----------------------------------------------------------------------------
// 命中目标原因
//----------------------------------------------------------------------------
enum EHitTargetCause
{
	EHTC_Skill,						//使用技能
	EHTC_Item,						//使用物品
};

//----------------------------------------------------------------------------
// 场景特效类型
//----------------------------------------------------------------------------
enum ESceneEffectType
{
	ESET_ByObjID,					//使用ObjID进行播放
	ESET_ByPos,						//在指定位置播放
};

//----------------------------------------------------------------------------
// 场景音效类型
//----------------------------------------------------------------------------
enum ESceneMusicType
{
	ESMT_2D,						//2D音乐
	ESMT_3D,						//3D音效
};

//----------------------------------------------------------------------------
// 进入/离开战斗
//----------------------------------------------------------------------------
struct NET_SIC_enter_combat : public tag_net_message
{
	NET_SIC_enter_combat()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_enter_combat");
		dw_size = sizeof(NET_SIC_enter_combat);
	}
};

struct NET_SIC_leave_combat : public tag_net_message
{
	NET_SIC_leave_combat()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_leave_combat");
		dw_size = sizeof(NET_SIC_leave_combat);
	}
};


//----------------------------------------------------------------------------
// 技能攻击
//----------------------------------------------------------------------------
struct NET_SIC_skill : public tag_net_message
{
	NET_SIC_skill()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_skill");
		dw_size = sizeof(NET_SIC_skill);
	}
	Vector3		vSrcPos;			//攻击者当前坐标
	DWORD		dwTargetRoleID;		//目标ID
	DWORD		dwSkillID;			//技能ID
	DWORD		dwSerial;			//消息序列号
};

struct NET_SIS_skill : public tag_net_message
{
	NET_SIS_skill()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_skill");
		dw_size = sizeof(NET_SIS_skill);
	}
	DWORD		dwSrcRoleID;		//攻击者ID
	DWORD		dwTarRoleID;		//目标ID
	DWORD		dwSkillID;			//技能ID
	DWORD		dwSerial;			//消息序列号
	INT			nSpellTime;			//吟唱时间，不带吟唱的技能为0
	DWORD		dw_error_code;		//错误代码
};


//----------------------------------------------------------------------------
// 技能打断
//----------------------------------------------------------------------------
struct NET_SIC_skill_interrupt : public tag_net_message
{
	NET_SIC_skill_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_skill_interrupt");
		dw_size = sizeof(NET_SIC_skill_interrupt);
	}
	DWORD		dwSkillID;			//技能ID
};

struct NET_SIS_skill_interrupt : public tag_net_message
{
	NET_SIS_skill_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_skill_interrupt");
		dw_size = sizeof(NET_SIS_skill_interrupt);
	}
	DWORD		dw_role_id;			//发起者ID
	DWORD		dwSkillID;			//技能ID
};


//----------------------------------------------------------------------------
// 使用物品
//----------------------------------------------------------------------------
struct NET_SIC_use_item : public tag_net_message
{
	NET_SIC_use_item()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_use_item");
		dw_size = sizeof(NET_SIC_use_item);
	}
	Vector3		vSrcPos;			//物品使用者当前坐标
	DWORD		dwTargetRoleID;		//目标ID
	INT64		n64ItemID;			//物品64位ID
	DWORD		dwSerial;			//消息序列号
};

struct NET_SIS_use_item : public tag_net_message
{
	NET_SIS_use_item()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_use_item");
		dw_size = sizeof(NET_SIS_use_item);
	}
	DWORD		dwSrcRoleID;		//物品使用者ID
	DWORD		dwTarRoleID;		//目标ID
	INT64		n64ItemID;			//物品64位ID
	DWORD		dw_data_id;			//物品TypeID
	DWORD		dwSerial;			//消息序列号
	INT			nSpellTime;			//吟唱时间，不带吟唱的物品为0
	DWORD		dw_error_code;		//错误代码
	bool		bInmmediate;		//是否瞬发？
};


//----------------------------------------------------------------------------
// 使用物品打断
//----------------------------------------------------------------------------
struct NET_SIC_use_item_interrupt : public tag_net_message
{
	NET_SIC_use_item_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_use_item_interrupt");
		dw_size = sizeof(NET_SIC_use_item_interrupt);
	}
	INT64		n64ItemID;			//物品64位ID
};

struct NET_SIS_use_item_interrupt : public tag_net_message
{
	NET_SIS_use_item_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_use_item_interrupt");
		dw_size = sizeof(NET_SIS_use_item_interrupt);
	}
	DWORD		dw_role_id;			//发起者ID
	INT64		n64ItemID;			//物品64位ID
	DWORD		dw_data_id;			//物品TypeID
};

//----------------------------------------------------------------------------
// 使用技能或物品命中目标
//----------------------------------------------------------------------------
struct NET_SIS_hit_target : public tag_net_message
{
	NET_SIS_hit_target()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_hit_target");
		dw_size = sizeof(NET_SIS_hit_target);
	}
	DWORD		dw_role_id;			//角色ID
	DWORD		dwSrcRoleID;		//发起者ID
	EHitTargetCause	eCause;			//原因
	DWORD		dwMisc;				//如果是技能，则为技能ID；如果是使用物品，则为物品TypeID
	DWORD		dwSerial;			//如果是技能，则为技能消息序列号；如果是物品则为使用物品消息序列号
};


//----------------------------------------------------------------------------
// HP改变显示消息
//----------------------------------------------------------------------------
struct NET_SIS_role_hp_change : public tag_net_message
{
	NET_SIS_role_hp_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_hp_change");
		dw_size = sizeof(NET_SIS_role_hp_change);
	}
	DWORD		dw_role_id;			//角色ID
	ERoleHPChangeCause	eCause;		//HP变化原因
	bool		bMiss;				//是否Miss
	bool		bCrit;				//是否暴击
	bool		bBlocked;			//是否被格挡
	INT			nHPChange;			//HP变化值
	DWORD		dwSrcRoleID;		//发起者ID
	DWORD		dwMisc;				//根据原因来定义
	DWORD		dwMisc2;			//根据原因来定义
	DWORD		dwSerial;			//根据原因来定义，如果是技能，由为技能消息序列号；其它原因填INVALID_VALUE
};

//----------------------------------------------------------------------------
// 复活
//----------------------------------------------------------------------------
enum ERoleReviveType
{
	ERRT_Start			= 0,

	ERRT_ReturnCity		= 0,		// 回城复活
	ERRT_Locus			= 1,		// 原地复活
	ERRT_Accept			= 2,		// 接受复活
	ERRT_Prison			= 3,		// 狱中复活
	ERRT_Instance		= 4,		// 副本复活
	ERRT_Yamun			= 5,		// 衙门复活

	ERRT_None,						//无建议
	ERRT_End			= ERRT_None,
	
};

//----------------------------------------------------------------------------
// 角色死亡消息
//----------------------------------------------------------------------------
struct NET_SIS_role_dead : public tag_net_message
{
	NET_SIS_role_dead()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_dead");
		dw_size = sizeof(NET_SIS_role_dead);
	}
	DWORD		dw_role_id;			//角色ID
	ERoleDeadCause eCause;			//死亡原因
	DWORD		dwSrcRoleID;		//攻击者ID
	DWORD		dwMisc;				//如果是技能，则为技能ID；如果是buff，则为buff id
	DWORD		dwMisc2;			//如果是技能，则为管道序列号
	DWORD		dwSerial;			//如果是技能，则为技能消息序列号；其它原因填INVALID_VALUE
	ERoleReviveType eSuggestRevive;//复活方式，若为ERRT_None 则由玩家自己选择
};

struct NET_SIC_role_revive : public tag_net_message
{
	NET_SIC_role_revive()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_role_revive");
		dw_size = sizeof(NET_SIC_role_revive);
	}
	ERoleReviveType	eType;
	INT64			n64ItemID;		// 原地复活所需的物品64位ID
};

struct NET_SIS_role_revive : public tag_net_message
{
	NET_SIS_role_revive()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_revive");
		dw_size = sizeof(NET_SIS_role_revive);
	}
	DWORD			dw_error_code;
	DWORD			dw_role_id;
};

struct NET_SIS_role_revive_notify : public tag_net_message
{
	NET_SIS_role_revive_notify()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_revive_notify");
		dw_size = sizeof(NET_SIS_role_revive_notify);
	}
};

//----------------------------------------------------------------------
// 添加删除更新一个Buff
//----------------------------------------------------------------------
struct NET_SIS_add_role_buffer : public tag_net_message
{
	NET_SIS_add_role_buffer()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_add_role_buffer");
		dw_size = sizeof(NET_SIS_add_role_buffer);
	}
	DWORD			dw_role_id;			// ID
	tagBuffMsgInfo	Buff;				// Buff内容
};

struct NET_SIS_remove_role_buffer : public tag_net_message
{
	NET_SIS_remove_role_buffer()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_remove_role_buffer");
		dw_size = sizeof(NET_SIS_remove_role_buffer);
	}
	DWORD			dw_role_id;			// ID
	DWORD			dwBuffTypeID;		// Buff属性ID
};

struct NET_SIS_update_role_buffer : public tag_net_message
{
	NET_SIS_update_role_buffer()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_update_role_buffer");
		dw_size = sizeof(NET_SIS_update_role_buffer);
	}
	DWORD			dw_role_id;			// ID
	tagBuffMsgInfo	Buff;				// Buff内容
};


//----------------------------------------------------------------------------
// 客户端取消一个Buff
//----------------------------------------------------------------------------
struct NET_SIC_cancel_buffer : public tag_net_message
{
	NET_SIC_cancel_buffer()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_cancel_buffer");
		dw_size = sizeof(NET_SIC_cancel_buffer);
	}
	DWORD			dwBuffTypeID;
};

//----------------------------------------------------------------------------
// 客户端停止所有行为
//----------------------------------------------------------------------------
struct NET_SIS_stop_action : public tag_net_message
{
	NET_SIS_stop_action()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_stop_action");
		dw_size = sizeof(NET_SIS_stop_action);
	}
	DWORD			dw_role_id;
	Vector3			curPos;
	Vector3			faceTo;
	bool			bSwim;
};


//----------------------------------------------------------------------------
// 怪物进入战斗，用于客户端播放音效
//----------------------------------------------------------------------------
struct NET_SIS_monster_enter_combat : public tag_net_message
{
	NET_SIS_monster_enter_combat()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_monster_enter_combat");
		dw_size = sizeof(NET_SIS_monster_enter_combat);
	}
	DWORD			dw_role_id;
};

//----------------------------------------------------------------------------
// 特殊移动（击退，冲锋，瞬移等）
//----------------------------------------------------------------------------
struct NET_SIS_special_move : public tag_net_message
{
	NET_SIS_special_move()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_special_move");
		dw_size = sizeof(NET_SIS_special_move);
	}
	ESpecialMoveType	eType;          // 移动类型
	DWORD				dw_role_id;       // 角色ID
	Vector3				vDestPos;       // 目标点
};

//----------------------------------------------------------------------------
// 怪物播放一个动作
//----------------------------------------------------------------------------
struct NET_SIS_monster_play_action : public tag_net_message
{
	NET_SIS_monster_play_action()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_monster_play_action");
		dw_size = sizeof(NET_SIS_monster_play_action);
	}
	DWORD			dw_role_id;				// 角色ID
	DWORD			dwActionFourCC;			// 动作FourCC
};


//----------------------------------------------------------------------------
// 怪物说话
//----------------------------------------------------------------------------
struct NET_SIS_monster_say : public tag_net_message
{
	NET_SIS_monster_say()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_monster_say");
		dw_size = sizeof(NET_SIS_monster_say);
	}
	DWORD				dw_role_id;			// 角色ID
	DWORD				dwSayID;			// 说话内容ID，对应NpcSay.xml中的一条记录
};

//----------------------------------------------------------------------------
// 播放一个场景特效
//----------------------------------------------------------------------------
struct NET_SIS_play_scene_effect : public tag_net_message
{
	NET_SIS_play_scene_effect()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_play_scene_effect");
		dw_size = sizeof(NET_SIS_play_scene_effect);
	}
	ESceneEffectType	eType;				// 场景特效类型
	DWORD				dwObjID;			// 特效ObjID
	Vector3				vPos;				// 播放坐标
	DWORD				dwEffectID;			// 特效ID，最终特效文件名格式：SCN+特效ID，场景特效存放于指定目录
};

//----------------------------------------------------------------------------
// 停止一个场景特效(仅限地图obj方式)
//----------------------------------------------------------------------------
struct NET_SIS_stop_scene_effect : public tag_net_message
{
	NET_SIS_stop_scene_effect()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_stop_scene_effect");
		dw_size = sizeof(NET_SIS_stop_scene_effect);
	}
	 DWORD           dwObjID;                // 特效objID
};

//开始修炼 领悟武魂
struct NET_SIC_practice_begin : public tag_net_message
{
	NET_SIC_practice_begin()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_practice_begin");
		dw_size = sizeof(NET_SIC_practice_begin);
	}
	INT64		n64SerialEquip;			//武器
	DWORD		dw_speed_item_data_id;	//加速道具dataId
	DWORD		dw_speed_item_number;	//加速道具数量
};


//----------------------------------------------------------------------------
// 播放一个场景音乐或音效
//----------------------------------------------------------------------------
//struct NET_SIS_play_scene_music : public tag_net_message
//{
//	NET_SIS_play_scene_music()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_play_scene_music");
//		dw_size = sizeof(NET_SIS_play_scene_music);
//	}
//	ESceneMusicType		eType;				// 场景音乐或音效类型
//	Vector3				vPos;				// 3D音效坐标
//	DWORD				dwMusicID;			// 音乐或音效ID，SCN+音效ID 对应SoundTable.xml中的一条记录
//};

//----------------------------------------------------------------------------
// 类型改变
//----------------------------------------------------------------------------
//struct NET_SIS_monster_type_change : public tag_net_message
//{
//	NET_SIS_monster_type_change()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_monster_type_change");
//		dw_size = sizeof(NET_SIS_monster_type_change);
//	}
//	DWORD			dw_role_id;
//	ECreatureType	eCreType;
//};

#pragma pack(pop)
#endif