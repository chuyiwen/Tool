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
*	@file		buff_define.h
*	@author		lc
*	@date		2010/09/08	initial
*	@version	0.0.1.0
*	@brief		״̬��̬����
*/
#pragma once

#include "RoleDefine.h"

#pragma pack(push, 1)

//-------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------
const DWORD MAX_BUFF_PERSIST_TICK	= 7 * 24 * 60 * 60 * TICK_PER_SECOND;	// Buff�����ʱ��(��λ��tick)

//-------------------------------------------------------------------------
// Buff����
//-------------------------------------------------------------------------
enum EBuffType
{
	EBT_Null	=	0,
	EBT_Skill	=	1,		// ����״̬
	EBT_Item	=	2,		// ��Ʒ״̬
	EBT_Action	=	3,		// ��Ϊ״̬
	EBT_Other	=	4,		// ����״̬
};

//--------------------------------------------------------------------------
// Buff��������
//--------------------------------------------------------------------------
enum EBuffResistType
{
	EBRT_Null		=	0,
	EBRT_Bleeding	=	1,	// ʧѪ
	EBRT_Weak		=	2,	// ˥��
	EBRT_Choas		=	3,	// ����
	EBRT_Special	=	4,	// ����
	EBRT_Regain		=	5,	// �ָ�
};

//---------------------------------------------------------------------------
// Buff��������
//---------------------------------------------------------------------------
enum EBuffOPType
{
	EBOPT_Null		=	0,	// ��
	EBOPT_Rect		=	1,	// ����
	EBOPT_Explode	=	2,	// ��ը
};

//----------------------------------------------------------------------------
// Buff���ö��
//----------------------------------------------------------------------------
enum EBuffInterruptFlag
{
	EBIF_Move			=	0x00000001,		// �ƶ�
	EBIF_InterCombat	=	0x00000002,		// ���뱸ս
	EBIF_Manual			=	0x00000004,		// �ֶ�
	EBIF_BeAttacked		=	0x00000008,		// ������
	EBIF_Die			=	0x00000010,		// ����
	EBIF_ChangeMap		=	0x00000020,		// �л�����
	EBIF_BuffFull		=	0x00000040,		// ״̬��
	EBIF_OffLine		=	0x00000080,		// ����
	EBIF_HPLower		=	0x00000100,		// ��������
	EBIF_MPLower		=	0x00000200,		// ��������
	EBIF_RageLower		=	0x00000400,		// ŭ������
	EBIF_EnduranceLower	=	0x00000800,		// �־�������
	EBIF_VitalityLower	=	0x00001000,		// ��������
	EBIF_LeaveCombat	=   0x00002000,		// �뿪ս��״̬
};

//-----------------------------------------------------------------------------
// BuffЧ������
//-----------------------------------------------------------------------------
enum EBuffEffectType
{
	EBET_Null			=	0,		// ��
	EBET_Teleport		=	1,		// ˲���ƶ�
	EBET_InterruptSpell	=	2,		// �������
	EBET_Dizzy			=	3,		// ѣ��
	EBET_Repel			=	4,		// ����
	EBET_Assault		=	5,		// ���
	EBET_NoSkill		=	6,		// �⼼
	EBET_Spor			=	7,		// ��˯
	EBET_Tie			=	8,		// ����
	EBET_Dispel			=	9,		// ��ɢ
	EBET_Invincible		=	10,		// �޵�
	EBET_InstantDie		=	11,		// ����
	EBET_Pull			=	12,		// ��ק
	EBET_ReboundDmg		=	13,		// �����˺�
	EBET_AbsorbDmg		=	14,		// �����˺�
	EBET_TransmitDmg	=	15,		// ת���˺�
	EBET_HPDrain		=	16,		// ��Ѫ
	EBET_MPDrain		=	17,		// ����
	EBET_HPTransfer		=	18,		// ת��
	EBET_MPTransfer		=	19,		// ת��
	EBET_Revive			=	20,		// ����
	EBET_InstantCD		=	21,		// ˲����ȴ
	EBET_Lurk			=	22,		// ����
	EBET_Fly			=	23,		// ����
	EBET_ChangeEnmity	=	24,		// �ı���
	EBET_Transmit		=	25,		// ����
	EBET_Gather			=	26,		// �ɼ�
	EBET_DisArm			=	27,		// ��е
	EBET_ExchangePos	=	28,		// ����λ��
	EBET_Explode		=	29,		// ����
	EBET_Funk			=	30,		// �־�
	EBET_Pursue			=	31,		// ׷��
	EBET_NoPrepare		=	32,		// ������ʱ��
	EBET_OnWater		=	33,		// ˮ������
	EBET_MoveHPDmg		=	34,		// �ƶ���Ѫ
	EBET_IgnoreArmor	=	35,		// ���ӻ���
	EBET_Sneer			=	36,		// ����
	EBET_Cancel			=	37,		// ȥ��
	EBET_Immunity		=	38,		// ����
	EBET_Mount			=	39,		// ���
	EBET_MountInvite	=	40,		// �������
	EBET_Ring			=	41,		// �⻷
	EBET_HPExchange		=	42,		// ����HP
	EBET_FilchBuff		=	43,		// ��ȡbuff
	EBET_End			,
};

//---------------------------------------------------------------------------------
// BuffЧ���Ľ׶�ö��
//---------------------------------------------------------------------------------
enum EBuffEffectMode
{
	EBEM_Null		=	-1,		// ��
	EBEM_Persist	=	0,		// ����Ч��
	EBEM_Instant	=	1,		// ˲��Ч��
	EBEM_Inter		=	2,		// ���Ч��
	EBEM_Finish		=	3,		// ����Ч��
	EBEM_End		=	4,
};

//---------------------------------------------------------------------------------
// Buff��˲ʱ�׶Σ�����׶Σ������׶ζ�����ĵ�ǰ����Ӱ���ö��
//---------------------------------------------------------------------------------
enum EBuffEffectAtt
{
	EBEA_HP			=	0,		
	EBEA_MP			=	1,		
	//EBEA_Rage		=	2,		// ŭ��
	//EBEA_Vitality	=	3,		// ����
	//EBEA_Endurance	=	4,		// �־���
	//EBEA_Morale		=	5,		// ʿ��
	//EBEA_Injury		=	6,		// ����
	EBEA_End	
};

//---------------------------------------------------------------------------------
// Buff�ĵ����ж�ö��
//---------------------------------------------------------------------------------
enum EBuffFriendEnemy
{
	EBFE_Friendly		=	0,		// �ѷ�
	EBFE_Hostile		=	1,		// �з�
	EBFE_All			=	2,		// ȫ��
	EBFE_Independent	=	3,		// ����
};

//---------------------------------------------------------------------------------
// ״̬��̬���Խṹ
//---------------------------------------------------------------------------------
struct tagBuffProto
{
	DWORD				dwID;
	EBuffType			eType;						// ����
	INT					nType2;						// ������
	INT					nType3;						// ������

	EBuffResistType		eResistType;				// ��������

	BOOL				bBenifit;					// �Ƿ�����
	EBuffFriendEnemy	eFriendly;					// �Ƿ��������ѷ���TRUEΪ�ѷ���FALSEΪ�з�
	BOOL				bInstant;					// �Ƿ�˲ʱbuff

	DWORD				dwGroupFlag;				// ״̬���ͱ��

	DWORD				dwTargetAddLimit;			// ��Ӷ�������
	DWORD				dwTargetLimit;				// ���ö�������

	DWORD				dwTargetAddStateLimit;		// ���Ŀ��״̬����
	DWORD				dwTargetStateLimit;			// ����Ŀ��״̬����

	INT					nLevel;						// �ȼ�

	EBuffOPType			eOPType;					// ��������
	FLOAT				fOPDistance;				// ���þ���
	FLOAT				fOPRadius;					// ���÷�Χ

	INT					nPersistTick;				// ����ʱ�䣨��λ��tick��
	INT					nInterOPTick;				// �������ʱ�䣨��λ��tick��
	INT					nWarpTimes;					// ��������
	BOOL				bOfflineConsume;			// ���߼�ʱ

	DWORD				dwInterruptFlag;			// ������־���ƶ������뱸ս���ֶ����������������л�������
													// ״̬�������ߣ��������ڣ��������ڣ��־������ڣ�ŭ�����ڣ��������ڣ�ĳ״̬��ʧ��

	INT					nAttackInterruptRate;		// ������������
	INT					nHPInterruptLimit;			// ������ʧֵ
	INT					nMPInterruptLimit;			// ������ʧֵ
	//INT					nRageInterruptLimit;		// ŭ����ʧֵ
	//INT					nEnduranceInterruptLimit;	// �־�����ʧֵ
	//INT					nVitalityInterruptLimit;	// ������ʧֵ
	INT					dwBuffInterruptID;			// ������ʧBuffID

	DWORD				dwOPTrigger;				// ״̬���ô�����

	EBuffEffectType		eEffect[EBEM_End];			// Ч������
	DWORD				dwEffectMisc1[EBEM_End];	// Ч������1
	DWORD				dwEffectMisc2[EBEM_End];	// Ч������2

	INT					nInstantAttMod[EBEA_End];	// ˲ʱ�׶�����Ӱ��
	INT					nInterAttMod[EBEA_End];		// ����׶�����Ӱ��
	INT					nFinishAttMod[EBEA_End];	// �����׶�����Ӱ��

	//mutable package_map<ERoleAttribute, INT> mapRoleAttMod;	// �������Ӱ�죨���ڳ�����Ӱ�죩
	//mutable package_map<ERoleAttribute, INT> mapRoleAttModPct;	// ������԰ٷֱ�Ӱ�죨���ڳ�����Ӱ�죩

	// δ��������ԣ����ƣ�������������ţ���Ч��ţ�ͼ���ţ�����ģ�ͱ�ţ�����ģ�ͱ�ţ�����ʱ����
};

struct tagBuffProtoClient : public tagBuffProto
{
	TCHAR				szName[X_SHORT_NAME];		// ����
	TCHAR				szDesc[X_HUGE_NAME];		// ����
	TCHAR				szIcon[X_SHORT_NAME];		// ͼ����
	TCHAR				szActionMod[X_SHORT_NAME];	// �������
	TCHAR				szEffectMod[X_LONG_NAME];	// ��Ч���
	TCHAR				szEffectTag[X_LONG_NAME];	// ��Ч�ҵ�
};

//---------------------------------------------------------------------------
// Buff��Ϣ�ṹ
//---------------------------------------------------------------------------
struct tagBuffMsgInfo
{
	DWORD				dwBuffTypeID;				// Buff����ID
	INT					nPersistTimeLeft;			// Buff��ʧʱ�䵹��ʱ�����룩
	INT					nMaxPersistTime;			// Buff�ܳ���ʱ�䣨���룩
	INT					nWarpTimes;					// ��ǰ���Ӵ���
};

// 9999601	����  ����״̬
CONST DWORD MOUNT_BUFF_ID	= 9999601;

// 9999701	ͬ��  ������״̬
CONST DWORD MOUNT2_BUFF_ID	= 9999701;

#pragma pack(pop)