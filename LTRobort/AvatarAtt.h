#pragma once

#pragma pack(push, 1)

//�������
enum  EPreChapStatus
{
	EPCS_OutKungSword = 0,		//�⹦������ɫ
	EPCS_InKungEeriness,		//�����ڹ�
	EPCS_OutKungBow,			//�⹦����
	EPCS_InKungSing,			//�ڹ�����
	EPCS_End,
};

// �Ա�
enum ERoleSex
{
	ERS_Woman		= 0,
	ERS_Man			= 1,
};

//�ڽ�ɫ������ʱ��ָ�������ԣ�����Ϸ��һ�㲻��ı�
#define DressMdIDInvalid		255		// ����>255,�������ݿⱣ��������(tinyint)
struct tagAvatarAtt
{
	WORD			wHairMdlID;			// ����
	WORD			wHairTexID;			// ��ɫ
	WORD			wFaceMdlID;			// �沿���
	WORD			wFaceDetailTexID;	// �沿ϸ��
	WORD			wDressMdlID;		// ��װ��ʽ
	BYTE			bySex;				// 0:girl��1:boy(�����Ժ���չ)
	BYTE			byClass;			// ��ɫְҵ
	BYTE			byVisualize;		// ��ɫ����
	tagAvatarAtt() { memset(this, 0, sizeof(*this)); }
};

//��װ����
//Avatarϵͳ���ɶ��ٸ�ģ����� 
enum EAvatarElement		
{
	EAE_Start	= 0,

	EAE_Head	= 0,	// ͷ
	EAE_Face	= 1,	// �沿
	EAE_Upper	= 2,	// ����
	EAE_Lower	= 3,	// ����
	EAE_Glove	= 4,	// ��
	EAE_Boot	= 5,	// ��
	EAE_Back	= 6,	// ����
	EAE_RWeapon	= 7,	// ��������
	EAE_LWeapon	= 8,	// ��������

	EAE_End		= 8,
};

const INT32 X_AVATAR_ELEMENT_NUM	= EAE_End - EAE_Start + 1;

// װ��������Ч
enum EEquipEffect
{
	EEE_Null		= 0,	// ��
	EEE_Simple		= 1,	// ��һ����Ч
	EEE_Complex		= 2,	// �ڶ�����Ч
	EEE_All
};

// װ�����
struct tagEquipDisplay
{
	DWORD			dw_data_id;
	BYTE			byDisplayPos;	// ģ��λ��
	BYTE			byFlareVal;		// ����ֵ
	BYTE			byEquipEffect;	// ����Ч��
	INT8			n8ColorID;		// ��ɫ

	VOID Set(BYTE byDisplayPos, DWORD dw_data_id, BYTE byFlareVal, INT8 n8ColorID)
	{
		this->byDisplayPos	= byDisplayPos;
		this->byFlareVal	= byFlareVal;
		this->n8ColorID		= n8ColorID;
		this->dw_data_id		= dw_data_id;
	}

	VOID Set(BYTE byEquipEffect)
	{
		this->byEquipEffect	= byEquipEffect;
	}
};

const BYTE X_DEFAULT_FLARE_VAL	= 0;

// װ�����
struct tagAvatarEquip
{
	tagEquipDisplay		AvatarEquip[X_AVATAR_ELEMENT_NUM];
	DWORD				dwSuitEffectID;						// ��װ��Ч���

	VOID Set(BYTE byDisplayPos, DWORD dw_data_id, BYTE byFlareVal, INT8 n8ColorID)
	{
		AvatarEquip[byDisplayPos].Set(byDisplayPos, dw_data_id, byFlareVal, n8ColorID);
	}

	VOID Set(BYTE byDisplayPos, BYTE byEquipEffect)
	{
		AvatarEquip[byDisplayPos].Set(byEquipEffect);
	}

	BOOL IsNull(BYTE byDisplayPos) const
	{
		return (AvatarEquip[byDisplayPos].dw_data_id == -1 ||
			AvatarEquip[byDisplayPos].dw_data_id == 0);
	}
};

const INT32 SIZE_AVATAR_EQUIP = sizeof(tagAvatarEquip);

// װ����ʾ����
struct tagDisplaySet
{
	bool	bFashionDisplay	: 1;	// �Ƿ���ʾʱװ
	bool	bHideHead		: 1;	// �Ƿ�����ͷ��
	bool	bHideFace		: 1;	// �Ƿ������沿
	bool	bHideBack		: 1;	// �Ƿ����ر���

	tagDisplaySet(BYTE byData = 0) { memcpy(this, &byData, sizeof(*this)); }
	operator BYTE(){ return *(BYTE*)this; }

	VOID Set(bool bHead, bool bFace, bool bBack)
	{
		bHideHead = bHead;
		bHideFace = bFace;
		bHideBack = bBack;
	}
};

#pragma pack(pop)
