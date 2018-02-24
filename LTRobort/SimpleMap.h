#pragma once

#include "..\..\..\siEngineSDK\Include\siCore\Math\siMathBaseDefine.h"

using namespace si;

#include "action_protocol.h"
#include "role_att_protocol.h"
#include "map_protocol.h"
#include "NetSession.h"
#include "MapLogicData.h"

//class CClientDlg;

class SimpleMap
{
public:
	SimpleMap();
	~SimpleMap();

	void	Init();
	void	SetSimpleMap(const TCHAR* szMapName);
	void	GetSimpleMapSize(float& iWidth, float& iHeight);
	bool	IsSimpleMapPointReachable(int iX, int iY);
	std::map<tstring, DWORD>& GetBitmapMap()	{ return m_BitmapMap; }
	
	void	ScreenPosToWorldPos(CPoint ptScreenPos, Vector3& vWorldPos);
	void	WorldPosToScreenPos(Vector3 vWorldPos, CPoint& ptScreenPos);
	void	WorldPosToCellPos(Vector3 vWorldPos, CPoint& ptCellPos);
	void	CellPosToWorldPos(CPoint ptCellPos, Vector3& vWorldPos);

	void	GoTo(int iX, int iY);
	inline void	SetMapLogicData(tagMapLogicData data)	{ m_MapLogicData = data; };
	inline bool IsMapDataLoaded()	{ return m_MapLogicData.dwID != -1; }
	
private:
	//CClientDlg* m_pDlg;
	//HBITMAP m_hBitmap; 
	std::map<tstring, DWORD>	m_BitmapMap;
	tagMapLogicData		m_MapLogicData;
	RECT	m_rcMap;
};
