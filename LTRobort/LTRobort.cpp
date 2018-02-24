// LTRobort.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "LTRobort.h"
#include "LTRobortDlg.h"
#include "Robort.h"
#include "SimpleMap.h"
#include "NetSession.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLTRobortApp

BEGIN_MESSAGE_MAP(CLTRobortApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLTRobortApp ����

CLTRobortApp::CLTRobortApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLTRobortApp ����

CLTRobortApp theApp;


// CLTRobortApp ��ʼ��

BOOL CLTRobortApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	//m_pGUI->Register(TWrap<EditEx>(), _T("EditEx"), _T("EditEx"));
	
	//vEngine::Register(TWrap<>(), "SimpleClient");	
	//vEngine::Register(TWrap<SimpleMap>(), "SimpleMap");	

	CWinApp::InitInstance();
	Tang::f_util::GetSingleton().tool_randomize(::timeGetTime());
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CLTRobortDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
