#pragma once

#include "..\..\..\siEngineSDK\Include\siCore\Math\siMathBaseDefine.h"
using namespace si;
//#include "WorldDefine\MapAttDefine.h"
#include "..\..\..\client\Client\f_data_base.h"


/** ��ͼ�߼�����
*/
struct tagMapLogicData
{
	DWORD						dwID;				//��ͼID������szName���ɵ�CRC
	tstring						szName;				//�����ڲ�����
	tstring						szShowName;			//��ʾ����
	Vector2						vSize;				//��С	
	
	//more
};

/** \class MapLogicData
	\brief ��ͼ�߼�����
*/
class MapLogicData
	: public f_data_base
{
public:
	MapLogicData(void);
	~MapLogicData(void);

	static MapLogicData* Inst();

	/** ���������ļ�
	*/
	virtual void load();
	/** ��ȡ��ͼ�߼�����
	*/
	const tagMapLogicData* FindMapLogicData(DWORD dwMapID)
	{
		return get_map_value(m_mapMapLogicData, dwMapID);
	}
	/** ��ȡ��ͼ��ʾ����
	*/
	LPCTSTR FindMapShowName(DWORD dwMapID);	
	const map<DWORD, tagMapLogicData>& GetDataMap() { return m_mapMapLogicData; }
private:
	map<DWORD, tagMapLogicData>		m_mapMapLogicData;		// ��ͼ�߼�����

};