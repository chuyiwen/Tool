#include "stdafx.h"
#include "MapLogicData.h"

MapLogicData::MapLogicData()
{
}

MapLogicData::~MapLogicData()
{
}

MapLogicData g_mapLogicData;
MapLogicData* MapLogicData::Inst()
{
	return &g_mapLogicData;
}

void MapLogicData::load()
{
	TCHAR const* szMapProto = _T("data\\config\\table\\SceneInfo.xml");

	list<tstring> MapProtoFieldList;
	list<tstring>::iterator iter;


	//读取map_logic_proto
	Tang::f_data_set VarMapProto;
	if(!VarMapProto.load(szMapProto, "id", &MapProtoFieldList))
		CONSOLE_TRACE(_T("load file SceneInfo.xml failed\r\n"));

	for(iter = MapProtoFieldList.begin(); iter != MapProtoFieldList.end(); ++iter)
	{
		tagMapLogicData data;
		data.szName = VarMapProto.get_string(_T("id"), (*iter).c_str());
		data.dwID = Tang::f_util::get_crc(data.szName.c_str());
		data.vSize.x = VarMapProto.get_float(_T("SceneWidth"), (*iter).c_str());
		data.vSize.y = VarMapProto.get_float(_T("SceneHeight"), (*iter).c_str());
		//data.eMapType = (EMapType)(VarMapProto.get_int(_T("SceneType"), (*iter).c_str()));		// 地图类型
		//more

		m_mapMapLogicData.insert(make_pair(data.dwID, data));
	}


	
}

//LPCTSTR MapLogicData::FindMapShowName( DWORD dwMapID )
//{
//	const tagMapLogicData* pData = FindMapLogicData(dwMapID);
//	if( !(pData) )
//		return _T("");
//	return pData->szShowName.c_str();
//}



