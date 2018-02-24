
#include "stdafx.h"
#include "SimpleMap.h"
#include "GameLog.h"

const tstring g_szMapNames[] = 
{
	_T("m04"),	
};

SimpleMap::SimpleMap()
{
	m_MapLogicData.dwID = -1;
}

SimpleMap::~SimpleMap()
{

}

void SimpleMap::Init(/*CClientDlg* pDlg*/)
{		
	//m_pDlg = pDlg;
	
	//for test
	//m_BitmapMap.insert(make_pair(g_szMapNames[0], IDB_BITMAP_SM1));	

	//pDlg->SetSimpleMapBitmap(IDB_BITMAP_SM1);

	// set map area
	m_rcMap.left = 400;
	m_rcMap.right = m_rcMap.left + 300;
	m_rcMap.top = 100;
	m_rcMap.bottom = m_rcMap.top + 300;
}

void SimpleMap::SetSimpleMap(const TCHAR* szMapName)
{
	tstring str = szMapName;
	std::map<tstring, DWORD>::iterator iter = m_BitmapMap.find(str);
	if( iter != m_BitmapMap.end() )
	{
		DWORD dwID = iter->second;
	}
	else
	{
		ASSERT(0);
	}

}

void SimpleMap::ScreenPosToWorldPos(CPoint ptScreenPos, Vector3& vWorldPos)
{
	RECT& rect = m_rcMap;	

	if( IsMapDataLoaded() )
	{
		float fX = (ptScreenPos.x - rect.left)*1.f/(rect.right - rect.left)*m_MapLogicData.vSize.x*50;
		float fZ = (ptScreenPos.y - rect.top)*1.f/(rect.bottom - rect.top)*m_MapLogicData.vSize.y*50;

		vWorldPos = Vector3(fX, 0, fZ);
	}
	else
	{
		vWorldPos = Vector3(0, 0, 0);
	}	
}

void SimpleMap::WorldPosToScreenPos(Vector3 vWorldPos, CPoint& ptScreenPos)
{
	RECT& rect = m_rcMap;	

	if( IsMapDataLoaded() )
	{
		ptScreenPos.x = int(vWorldPos.x/50/m_MapLogicData.vSize.x*(rect.right-rect.left)) + rect.left;
		ptScreenPos.y = int(vWorldPos.z/50/m_MapLogicData.vSize.y*(rect.bottom-rect.top)) + rect.top;
	}
	else
	{
		ptScreenPos.x = 400;
		ptScreenPos.y = 100;
	}
}

void SimpleMap::WorldPosToCellPos(Vector3 vWorldPos, CPoint& ptCellPos)
{
	ptCellPos.x = int(vWorldPos.x/50);
	ptCellPos.y = int(vWorldPos.z/50);
}

void SimpleMap::CellPosToWorldPos(CPoint ptCellPos, Vector3& vWorldPos)
{
	vWorldPos.x = ptCellPos.x*50.f;
	vWorldPos.y = 0;
	vWorldPos.z = ptCellPos.y*50.f;
}

void SimpleMap::GoTo(int iX, int iY)
{

}

void SimpleMap::GetSimpleMapSize(float& iWidth, float& iHeight)
{
	iWidth = m_MapLogicData.vSize.x;
	iHeight = m_MapLogicData.vSize.y;
}


