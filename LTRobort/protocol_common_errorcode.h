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
*	@file		protocol_common_errorcode.h
*	@author		wmr
*	@date		2011/03/01	initial
*	@version	0.0.1.0
*	@brief		���ô������
*/


#ifndef PROTOCOL_COMMON_ERRORCODE
#define PROTOCOL_COMMON_ERRORCODE

//------------------------------------------------------------------------
// ����������Ϣ��ͬ�Ĵ�����
// 
// ����E_Success�����д������Ϊ������������Ϣ���еĴ�����ɴ�1��ʼ
//------------------------------------------------------------------------
enum
{
	E_Success						= 0,
	E_SystemError					= -1,

	E_Item_NotFound					= -2,		// û���ҵ���Ʒ
	E_Item_NotEquipment				= -3,		// ����װ��

	E_Item_CanNotAdd				= -4,		// ������ӵ�ָ����������
	E_Item_CanNotRemove				= -5,		// ���ܴ�����ɾ����Ʒ
	E_Item_CanNotMove_Other			= -6,		// �����ƶ�������������
	E_Item_AddFailed				= -7,		// �������в���ʱʧ��

	E_Item_Place_NotFree			= -8,		// Ŀ��λ�ò�Ϊ��

	//E_Item_LevelLimit				= -9,		// �ȼ�������Ҫ��
	//E_Item_SexLimit					= -10,		// �Ա�����Ҫ��
	//E_Item_ClassLimit				= -11,		// ְҵ������Ҫ��
	//E_Item_TalentLimit				= -12,		// ���ʲ�����Ҫ��
	//E_Item_ClanRepLimit				= -13,		// ��������������Ҫ��
	//E_Item_OtherClanRepLimit		= -14,		// ��������������Ҫ��
	//E_Item_RoleStatusLimit			= -15,		// ���״̬(ս������ս��)������Ҫ��
	//E_Item_AttA_Limit				= -16,		// һ�����Բ�����

	E_Item_NotEnough				= -20,		// ��Ʒ��������

	E_Item_MaxHold					= -25,		// ��Ʒ�ﵽ��ӵ������

	E_Item_Used_NotValid			= -30,		// ʹ�õ���Ʒ�Ƿ�

	E_Bag_NotEnoughSpace			= -100,		// ����û���㹻�Ŀռ�
	E_Con_NotEnoughSpace			= -101,		// û���㹻�Ŀռ�
	E_Con_PswNotPass				= -102,		// δ�������������

	E_BagYuanBao_NotEnough			= -200,		// ������Ԫ������
	E_BagSilver_NotEnough			= -201,		// �����н�Ǯ����
	E_ExVolume_NotEnough			= -202,		// ��ɫ���㲻��

	E_Role_Not_ExistIn_World		= -300,		// ��Ϸ�����в�����ָ����ɫ
	E_Role_Not_Online				= -301,		// ��ɫ������
	E_Role_CantMove					= -302,		// ��ɫ���ڲ������ƶ�״̬

	E_NPC_NotFound					= -310,		// û���ҵ�ָ��NPC
	E_NPC_NotValid					= -311,		// ְ�����Ͳ���
	E_NPC_TooFar					= -312,		// ����NPC̫Զ

	E_Filter_Name_InFilterFile		= -351,		// �ڹ��˴ʱ���
	E_Filter_Name_TooLong			= -352,		// ����̫��
	E_Filter_Name_Null				= -353,		// ����Ϊ��
	E_Filter_Name_Illegal			= -354,		// ���ְ��������ַ�
	E_Filter_Chat_NoContent			= -355,		// ��������Ϊ��
	E_Filter_Text_TooLong			= -356,		// ����̫��

	E_Return_NotNeedFeed			= -10000,	// ������ͻ��˷��� -- ��ֵΪ�����������ͻ�����Ϣ��
};
#endif