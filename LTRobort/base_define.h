/*******************************************************************************

Copyright 2010 by Shengshi Interactive Game Co., Ltd.
All rights reserved.

This software is the confidential and proprietary information of
Shengshi Interactive Game Co., Ltd. ('Confidential Information'). You shall
not disclose such Confidential Information and shall use it only in
accordance with the terms of the license agreement you entered into with
Shengshi Interactive  Co., Ltd.

*******************************************************************************/

#pragma once

// �������ֵĳ���,�������������������̵�����
#define X_LONG_NAME				256
#define X_HUGE_NAME				512
#define X_SHORT_NAME			32
#define X_IP_LEN				24
#define X_PET_NAME              7
#define INT64					__int64

CONST INT	TICK_TIME				= 200;					// ÿTick 200 ms
CONST INT	TICK_PER_SECOND			= (1000/TICK_TIME);		// ÿ�����Tick

//--------------------------------------------------------------------------------
// ������Ϸ�����ID��Χ
//--------------------------------------------------------------------------------
#define		MIN_PLAYER_ID			1
#define		MAX_PLAYER_ID			2000000000
#define		IS_PLAYER(ID)			( (ID) >= MIN_PLAYER_ID && (ID) <= MAX_PLAYER_ID )

#define		MIN_CREATURE_ID			2000000001
#define		MAX_CREATURE_ID			3000000000

#define		IS_CREATURE(ID)			( (ID) >= MIN_CREATURE_ID && (ID) <= MAX_CREATURE_ID )

#define		MIN_NORMAL_CREATURE_ID	2000000001
#define		MAX_NORMAL_CREATURE_ID	2900000000//2800000000
#define		IS_NORMAL_CREATURE(ID)	( (ID) >= MIN_NORMAL_CREATURE_ID && (ID) <= MAX_NORMAL_CREATURE_ID )

#define		MIN_DOOR_ID				2900000001
#define		MAX_DOOR_ID				2901000000
#define		IS_DOOR(ID)				( (ID) >= MIN_DOOR_ID && (ID) <= MAX_DOOR_ID )

#define		MIN_PET_ID				3000000001//2800000001
#define		MAX_PET_ID				4000000000//2900000000
#define		IS_PET(ID)				( (ID) >= MIN_PET_ID && (ID) <= MAX_PET_ID )

#define		MIN_ITEM_ID				1
#define		MAX_ITEM_ID				7999999

#define		MIN_EQUIP_ID			8000000

//------------------------------------------------------------------------
// ��Ǯtypeid
//------------------------------------------------------------------------
const DWORD		TYPE_ID_MONEY		= -1 - 10;// Ҳ���ᱻ�����õ�


//----------------------------------------------------------------
// �ж��Ƿ�Ϊװ��
//----------------------------------------------------------------
#define		MIsEquipment(dw_data_id)		( (dw_data_id) >= MIN_EQUIP_ID )

//----------------------------------------------------------------
// �ж��Ƿ�Ϊ������Ʒ
//----------------------------------------------------------------
#define		MIsQuestItem(pItemProto)			( EITE_Quest == (pItemProto)->eTypeEx )


////----------------------------------------------------------------
//// �ж�װ���Ƿ��Ѽ���
////----------------------------------------------------------------
//#define MIsIdentified(pEquip)			(pEquip->equipSpec.byQuality != (BYTE)EIQ_Null)
//
////----------------------------------------------------------------
//// �ж�װ���Ƿ�Ϊring
////----------------------------------------------------------------
//#define MIsRing(pEquip)				(EEP_Finger1 == ((tagEquipProto*)pEquip->pProtoType)->eEquipPos)
//#define MIsWeapon(pEquip)			(pEquip->pProtoType->eTySpe == EIT_Weapon)