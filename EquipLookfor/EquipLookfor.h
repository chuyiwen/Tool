// EquipLookfor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEquipLookforApp:
// �йش����ʵ�֣������ EquipLookfor.cpp
//

class CEquipLookforApp : public CWinApp
{
public:
	CEquipLookforApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEquipLookforApp theApp;