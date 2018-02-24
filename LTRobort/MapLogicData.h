#pragma once

#include "..\..\..\siEngineSDK\Include\siCore\Math\siMathBaseDefine.h"
using namespace si;
//#include "WorldDefine\MapAttDefine.h"
#include "..\..\..\client\Client\f_data_base.h"


/** 地图逻辑数据
*/
struct tagMapLogicData
{
	DWORD						dwID;				//地图ID，根据szName生成的CRC
	tstring						szName;				//程序内部名称
	tstring						szShowName;			//显示名称
	Vector2						vSize;				//大小	
	
	//more
};

/** \class MapLogicData
	\brief 地图逻辑数据
*/
class MapLogicData
	: public f_data_base
{
public:
	MapLogicData(void);
	~MapLogicData(void);

	static MapLogicData* Inst();

	/** 载入属性文件
	*/
	virtual void load();
	/** 获取地图逻辑数据
	*/
	const tagMapLogicData* FindMapLogicData(DWORD dwMapID)
	{
		return get_map_value(m_mapMapLogicData, dwMapID);
	}
	/** 获取地图显示名称
	*/
	LPCTSTR FindMapShowName(DWORD dwMapID);	
	const map<DWORD, tagMapLogicData>& GetDataMap() { return m_mapMapLogicData; }
private:
	map<DWORD, tagMapLogicData>		m_mapMapLogicData;		// 地图逻辑数据

};