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
*	@brief		ս�����Э��
*/

#ifndef COMBAT_PROTOCOL
#define COMBAT_PROTOCOL

#include "protocol_common_errorcode.h"
#include "buff_define.h"
#include "move_define.h"

#pragma pack(push, 1)
//----------------------------------------------------------------------------
// ������ö��
//----------------------------------------------------------------------------
enum
{
	E_UseSkill_SkillNotExist		=	1,		// ���ܲ�����
	E_UseSkill_TargetInvalid		=	2,		// Ŀ��Ƿ�
	E_UseSkill_PassiveSkill			=	3,		// �������ܲ���ʹ��
	E_UseSkill_SkillTargetInvalid	=	4,		// ���ܱ����������ս��Ŀ��
	E_UseSkill_CoolDowning			=	5,		// ����������ȴ
	E_UseSkill_Operating			=	6,		// �������ڷ���
	E_UseSkill_UseLimit				=	7,		// ��������������
	E_UseSkill_SexLimit				=	8,		// �Ա�����
	E_UseSkill_PosLimitFront		=	9,		// λ�ò����㣨��������ǰ��
	E_UseSkill_PosLimitBack			=	10,		// λ�ò����㣨���������
	E_UseSkill_DistLimit			=	11,		// ���벻����
	E_UseSkill_RayLimit				=	12,		// ���߼�ⲻ����
	E_UseSkill_CostLimit			=	13,		// ���Ĳ���
	E_UseSkill_TargetLimit			=	14,		// Ŀ������
	E_UseSkill_StallLimit			=	15,		// ��̯״̬�²���ʹ�ü���
	E_UseSkill_WeaponLimit			=	16,		// ��������
	E_UseSkill_SelfStateLimit		=	17,		// ����״̬����
	E_UseSkill_TargetStateLimit		=	18,		// Ŀ��״̬����
	E_UseSkill_SelfBuffLimit		=	19,		// ����Buff����
	E_UseSkill_TargetBuffLimit		=	20,		// Ŀ��Buff����
	E_UseSkill_Mount_NoPreparingPet	=	21,		// û��Ԥ������
	E_UseSkill_VocationLimit		=	22,		// ְҵ����
	E_UseSkill_MapLimit				=	23,		// �޷��ڸõ�ͼ��ʹ��

	E_UseItem_ItemNotExist			=	30,		// ��Ʒ������
	E_UseItem_TargetInvalid			=	31,		// Ŀ��Ƿ�
	E_UseItem_ItemCanNotUse			=	32,		// ��Ʒ����ʹ��
	E_UseItem_CoolDowning			=	33,		// ��Ʒ������ȴ
	E_UseItem_SexLimit				=	34,		// �Ա�����
	E_UseItem_LevelLimit			=   35,		// �ȼ�����
	E_UseItem_DistLimit				=	36,		// ���벻����
	E_UseItem_RayLimit				=	37,		// ���߼�ⲻ����
	E_UseItem_UseLimit				=	38,		// ����������,����ʹ��
	E_UseItem_Operating				=	39,		// ��Ʒ���ڱ�ʹ��
	E_UseItem_NotEnoughSpace		=   40,		// �����ռ䲻��
	E_UseItem_ReAcceptQuest			=	41,		// ���Ѿ���ȡ��������
	E_UseItem_ActivityLimit			=	42,		// �õ�����ֻ���ڹ̶����ʹ��
	E_UseItem_PosLimit				=	43,		// �����ڸ�λ��ʹ�ø���Ʒ
	E_UseItem_SelfStateLimit		=	44,		// �������״̬����
	E_UseItem_AcceptSimQuest		=	45,		// �������Ѿ���ͬ������
	E_UseItem_VocationLimit			=	46,		// ְҵ������Ʒʹ��
	E_UseItem_MapLimit				=	47,		// �޷��ڸõ�ͼ��ʹ��
	E_UseItem_ItemOutOfNumber		=	48,		// ��Ʒ��������
	E_UseItem_CantUseInBattle		=	49,		// ս���в���ʹ�ø���Ʒ

	E_Revive_Unknown				=	50,		// δ֪��������
	E_Revive_NotDead				=	51,		// ��������״̬
	E_Revive_CanNotTransmit			=	52,		// �سǸ���ʱ����ʧ��
	E_Revive_ItemLimit				=	53,		// ԭ�ظ���ʱȱ����Ӧ����
	E_Revive_CanNotAccept			=	54,		// ���ܸ���ʱʧ��
	E_Revive_MapNotFound			=	55,		// û���ҵ������ͼ
};

//----------------------------------------------------------------------------
// ��ɫHP�仯ԭ��
//----------------------------------------------------------------------------
enum ERoleHPChangeCause
{
	ERHPCC_SkillDamage,				//�����˺�����
	ERHPCC_BuffDamage,				//Buff�˺�����
	ERHPCC_Other,					//����ԭ��
};

//----------------------------------------------------------------------------
// ��ɫ����ԭ��
//----------------------------------------------------------------------------
enum ERoleDeadCause
{
	ERDC_Skill,						//�����˺�����
	ERDC_Buff,						//Buff�˺�����
	ERDC_Other,						//����ԭ��
};

//----------------------------------------------------------------------------
// ����Ŀ��ԭ��
//----------------------------------------------------------------------------
enum EHitTargetCause
{
	EHTC_Skill,						//ʹ�ü���
	EHTC_Item,						//ʹ����Ʒ
};

//----------------------------------------------------------------------------
// ������Ч����
//----------------------------------------------------------------------------
enum ESceneEffectType
{
	ESET_ByObjID,					//ʹ��ObjID���в���
	ESET_ByPos,						//��ָ��λ�ò���
};

//----------------------------------------------------------------------------
// ������Ч����
//----------------------------------------------------------------------------
enum ESceneMusicType
{
	ESMT_2D,						//2D����
	ESMT_3D,						//3D��Ч
};

//----------------------------------------------------------------------------
// ����/�뿪ս��
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
// ���ܹ���
//----------------------------------------------------------------------------
struct NET_SIC_skill : public tag_net_message
{
	NET_SIC_skill()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_skill");
		dw_size = sizeof(NET_SIC_skill);
	}
	Vector3		vSrcPos;			//�����ߵ�ǰ����
	DWORD		dwTargetRoleID;		//Ŀ��ID
	DWORD		dwSkillID;			//����ID
	DWORD		dwSerial;			//��Ϣ���к�
};

struct NET_SIS_skill : public tag_net_message
{
	NET_SIS_skill()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_skill");
		dw_size = sizeof(NET_SIS_skill);
	}
	DWORD		dwSrcRoleID;		//������ID
	DWORD		dwTarRoleID;		//Ŀ��ID
	DWORD		dwSkillID;			//����ID
	DWORD		dwSerial;			//��Ϣ���к�
	INT			nSpellTime;			//����ʱ�䣬���������ļ���Ϊ0
	DWORD		dw_error_code;		//�������
};


//----------------------------------------------------------------------------
// ���ܴ��
//----------------------------------------------------------------------------
struct NET_SIC_skill_interrupt : public tag_net_message
{
	NET_SIC_skill_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_skill_interrupt");
		dw_size = sizeof(NET_SIC_skill_interrupt);
	}
	DWORD		dwSkillID;			//����ID
};

struct NET_SIS_skill_interrupt : public tag_net_message
{
	NET_SIS_skill_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_skill_interrupt");
		dw_size = sizeof(NET_SIS_skill_interrupt);
	}
	DWORD		dw_role_id;			//������ID
	DWORD		dwSkillID;			//����ID
};


//----------------------------------------------------------------------------
// ʹ����Ʒ
//----------------------------------------------------------------------------
struct NET_SIC_use_item : public tag_net_message
{
	NET_SIC_use_item()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_use_item");
		dw_size = sizeof(NET_SIC_use_item);
	}
	Vector3		vSrcPos;			//��Ʒʹ���ߵ�ǰ����
	DWORD		dwTargetRoleID;		//Ŀ��ID
	INT64		n64ItemID;			//��Ʒ64λID
	DWORD		dwSerial;			//��Ϣ���к�
};

struct NET_SIS_use_item : public tag_net_message
{
	NET_SIS_use_item()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_use_item");
		dw_size = sizeof(NET_SIS_use_item);
	}
	DWORD		dwSrcRoleID;		//��Ʒʹ����ID
	DWORD		dwTarRoleID;		//Ŀ��ID
	INT64		n64ItemID;			//��Ʒ64λID
	DWORD		dw_data_id;			//��ƷTypeID
	DWORD		dwSerial;			//��Ϣ���к�
	INT			nSpellTime;			//����ʱ�䣬������������ƷΪ0
	DWORD		dw_error_code;		//�������
	bool		bInmmediate;		//�Ƿ�˲����
};


//----------------------------------------------------------------------------
// ʹ����Ʒ���
//----------------------------------------------------------------------------
struct NET_SIC_use_item_interrupt : public tag_net_message
{
	NET_SIC_use_item_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_use_item_interrupt");
		dw_size = sizeof(NET_SIC_use_item_interrupt);
	}
	INT64		n64ItemID;			//��Ʒ64λID
};

struct NET_SIS_use_item_interrupt : public tag_net_message
{
	NET_SIS_use_item_interrupt()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_use_item_interrupt");
		dw_size = sizeof(NET_SIS_use_item_interrupt);
	}
	DWORD		dw_role_id;			//������ID
	INT64		n64ItemID;			//��Ʒ64λID
	DWORD		dw_data_id;			//��ƷTypeID
};

//----------------------------------------------------------------------------
// ʹ�ü��ܻ���Ʒ����Ŀ��
//----------------------------------------------------------------------------
struct NET_SIS_hit_target : public tag_net_message
{
	NET_SIS_hit_target()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_hit_target");
		dw_size = sizeof(NET_SIS_hit_target);
	}
	DWORD		dw_role_id;			//��ɫID
	DWORD		dwSrcRoleID;		//������ID
	EHitTargetCause	eCause;			//ԭ��
	DWORD		dwMisc;				//����Ǽ��ܣ���Ϊ����ID�������ʹ����Ʒ����Ϊ��ƷTypeID
	DWORD		dwSerial;			//����Ǽ��ܣ���Ϊ������Ϣ���кţ��������Ʒ��Ϊʹ����Ʒ��Ϣ���к�
};


//----------------------------------------------------------------------------
// HP�ı���ʾ��Ϣ
//----------------------------------------------------------------------------
struct NET_SIS_role_hp_change : public tag_net_message
{
	NET_SIS_role_hp_change()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_hp_change");
		dw_size = sizeof(NET_SIS_role_hp_change);
	}
	DWORD		dw_role_id;			//��ɫID
	ERoleHPChangeCause	eCause;		//HP�仯ԭ��
	bool		bMiss;				//�Ƿ�Miss
	bool		bCrit;				//�Ƿ񱩻�
	bool		bBlocked;			//�Ƿ񱻸�
	INT			nHPChange;			//HP�仯ֵ
	DWORD		dwSrcRoleID;		//������ID
	DWORD		dwMisc;				//����ԭ��������
	DWORD		dwMisc2;			//����ԭ��������
	DWORD		dwSerial;			//����ԭ�������壬����Ǽ��ܣ���Ϊ������Ϣ���кţ�����ԭ����INVALID_VALUE
};

//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
enum ERoleReviveType
{
	ERRT_Start			= 0,

	ERRT_ReturnCity		= 0,		// �سǸ���
	ERRT_Locus			= 1,		// ԭ�ظ���
	ERRT_Accept			= 2,		// ���ܸ���
	ERRT_Prison			= 3,		// ���и���
	ERRT_Instance		= 4,		// ��������
	ERRT_Yamun			= 5,		// ���Ÿ���

	ERRT_None,						//�޽���
	ERRT_End			= ERRT_None,
	
};

//----------------------------------------------------------------------------
// ��ɫ������Ϣ
//----------------------------------------------------------------------------
struct NET_SIS_role_dead : public tag_net_message
{
	NET_SIS_role_dead()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_role_dead");
		dw_size = sizeof(NET_SIS_role_dead);
	}
	DWORD		dw_role_id;			//��ɫID
	ERoleDeadCause eCause;			//����ԭ��
	DWORD		dwSrcRoleID;		//������ID
	DWORD		dwMisc;				//����Ǽ��ܣ���Ϊ����ID�������buff����Ϊbuff id
	DWORD		dwMisc2;			//����Ǽ��ܣ���Ϊ�ܵ����к�
	DWORD		dwSerial;			//����Ǽ��ܣ���Ϊ������Ϣ���кţ�����ԭ����INVALID_VALUE
	ERoleReviveType eSuggestRevive;//���ʽ����ΪERRT_None ��������Լ�ѡ��
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
	INT64			n64ItemID;		// ԭ�ظ����������Ʒ64λID
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
// ���ɾ������һ��Buff
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
	tagBuffMsgInfo	Buff;				// Buff����
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
	DWORD			dwBuffTypeID;		// Buff����ID
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
	tagBuffMsgInfo	Buff;				// Buff����
};


//----------------------------------------------------------------------------
// �ͻ���ȡ��һ��Buff
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
// �ͻ���ֹͣ������Ϊ
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
// �������ս�������ڿͻ��˲�����Ч
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
// �����ƶ������ˣ���棬˲�Ƶȣ�
//----------------------------------------------------------------------------
struct NET_SIS_special_move : public tag_net_message
{
	NET_SIS_special_move()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_special_move");
		dw_size = sizeof(NET_SIS_special_move);
	}
	ESpecialMoveType	eType;          // �ƶ�����
	DWORD				dw_role_id;       // ��ɫID
	Vector3				vDestPos;       // Ŀ���
};

//----------------------------------------------------------------------------
// ���ﲥ��һ������
//----------------------------------------------------------------------------
struct NET_SIS_monster_play_action : public tag_net_message
{
	NET_SIS_monster_play_action()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_monster_play_action");
		dw_size = sizeof(NET_SIS_monster_play_action);
	}
	DWORD			dw_role_id;				// ��ɫID
	DWORD			dwActionFourCC;			// ����FourCC
};


//----------------------------------------------------------------------------
// ����˵��
//----------------------------------------------------------------------------
struct NET_SIS_monster_say : public tag_net_message
{
	NET_SIS_monster_say()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_monster_say");
		dw_size = sizeof(NET_SIS_monster_say);
	}
	DWORD				dw_role_id;			// ��ɫID
	DWORD				dwSayID;			// ˵������ID����ӦNpcSay.xml�е�һ����¼
};

//----------------------------------------------------------------------------
// ����һ��������Ч
//----------------------------------------------------------------------------
struct NET_SIS_play_scene_effect : public tag_net_message
{
	NET_SIS_play_scene_effect()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_play_scene_effect");
		dw_size = sizeof(NET_SIS_play_scene_effect);
	}
	ESceneEffectType	eType;				// ������Ч����
	DWORD				dwObjID;			// ��ЧObjID
	Vector3				vPos;				// ��������
	DWORD				dwEffectID;			// ��ЧID��������Ч�ļ�����ʽ��SCN+��ЧID��������Ч�����ָ��Ŀ¼
};

//----------------------------------------------------------------------------
// ֹͣһ��������Ч(���޵�ͼobj��ʽ)
//----------------------------------------------------------------------------
struct NET_SIS_stop_scene_effect : public tag_net_message
{
	NET_SIS_stop_scene_effect()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIS_stop_scene_effect");
		dw_size = sizeof(NET_SIS_stop_scene_effect);
	}
	 DWORD           dwObjID;                // ��ЧobjID
};

//��ʼ���� �������
struct NET_SIC_practice_begin : public tag_net_message
{
	NET_SIC_practice_begin()
	{
		ZeroMemory(this, sizeof(*this));
		dw_message_id = message_id_crc("NET_SIC_practice_begin");
		dw_size = sizeof(NET_SIC_practice_begin);
	}
	INT64		n64SerialEquip;			//����
	DWORD		dw_speed_item_data_id;	//���ٵ���dataId
	DWORD		dw_speed_item_number;	//���ٵ�������
};


//----------------------------------------------------------------------------
// ����һ���������ֻ���Ч
//----------------------------------------------------------------------------
//struct NET_SIS_play_scene_music : public tag_net_message
//{
//	NET_SIS_play_scene_music()
//	{
//		ZeroMemory(this, sizeof(*this));
//		dw_message_id = message_id_crc("NET_SIS_play_scene_music");
//		dw_size = sizeof(NET_SIS_play_scene_music);
//	}
//	ESceneMusicType		eType;				// �������ֻ���Ч����
//	Vector3				vPos;				// 3D��Ч����
//	DWORD				dwMusicID;			// ���ֻ���ЧID��SCN+��ЧID ��ӦSoundTable.xml�е�һ����¼
//};

//----------------------------------------------------------------------------
// ���͸ı�
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