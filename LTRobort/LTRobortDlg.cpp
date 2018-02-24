// LTRobortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LTRobort.h"
#include "LTRobortDlg.h"
#include "Robort.h"
#include "GameLog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLTRobortDlg 对话框




CLTRobortDlg::CLTRobortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLTRobortDlg::IDD, pParent)
	, m_nRobortNum(0),
	m_bQuit(FALSE),
	m_bUpdate(true),
	m_hUpdate(NULL),
	nOnlineNum(0),
	dwTime1(0),
	dwTime2(0),
	bReConnect(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListRobort = NULL;

	m_pFS     = new Tang::ClientVFS;
	Tang::f_data_set::set_default_fs( m_pFS );
}

CLTRobortDlg::~CLTRobortDlg()
{
	EndRobort();
	SAFE_DELETE(m_pFS);
	delete CoreLib::GetInstancePtr();

}
void CLTRobortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nRobortNum);
	DDX_Control(pDX, IDC_EDIT3, m_CEthreadNum);
	DDX_Control(pDX, IDC_LIST4, m_LogOutListBox);
	DDX_Control(pDX, IDC_LIST5, m_OutLog);
	DDX_Control(pDX, IDC_EDIT2, m_CEonlineNum);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_CLASS, mClass);
	DDX_Control(pDX, IDC_SEX, mSex);
}

BEGIN_MESSAGE_MAP(CLTRobortDlg, CDialog)
//	ON_WM_PAINT()
//	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLTRobortDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDCANCEL, &CLTRobortDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CLTRobortDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLTRobortDlg 消息处理程序

BOOL CLTRobortDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	SetTimer(1, 1000, NULL);
	dwTime1 = timeGetTime();
	dwTime2 = timeGetTime();
	// TODO: 在此添加额外的初始化代码
	GameLog::Instance()->m_pWndLoginLog = &m_LogOutListBox;
	GameLog::Instance()->m_pWndRobortLog = &m_OutLog;

	// 设置程序默认路径
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	TCHAR *pResult = _tcsrchr(szPath, _T('\\'));	// 截去路径
	if(pResult)
		*pResult = 0;

	mSex.SetWindowText(_T("-1"));
	mClass.SetWindowText(_T("0"));

	SetCurrentDirectory(szPath);

	Tang::Net::InitNetwork();	

	new CoreLib;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
unsigned int WINAPI CLTRobortDlg::static_thread_rt(void* p)
{
	CLTRobortDlg* pThis = (CLTRobortDlg*)p;
	pThis->thread_rt( );
	_endthreadex(0);
	return 0;
}
// 监视线程是否运行的线程
unsigned int WINAPI CLTRobortDlg::thread_rt()
{
	while (m_bUpdate)
	{
		INT threadNum = 0;
		INT nConectNum = 0;
		for (int i = 0; i < m_nRobortNum; i++)
		{
			HANDLE hd = m_pListRobort[i].GetUpdataHandle();
			DWORD dwResult = 0;
			if( hd )
			{
				dwResult = ::WaitForSingleObject( hd, 0 );
				switch( dwResult )
				{
				case WAIT_TIMEOUT:
					threadNum++;
					break;

				default:
					break;
				}
			}
			if (m_pListRobort[i].IsConnect())
			{
				nConectNum++;
			}
		}
		nOnlineNum = nConectNum;
		TCHAR szTemp[X_SHORT_NAME] = _T("");
		_stprintf(szTemp, _T("%d"), threadNum);
		m_CEthreadNum.SetWindowText(szTemp);
		//GameLog::Instance()->GameLogOut(szTemp);

		Sleep(2000);
	}
	_endthreadex(0);
	return 0;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

//void CLTRobortDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // 用于绘制的设备上下文
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// 使图标在工作区矩形中居中
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// 绘制图标
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialog::OnPaint();
//	}
//}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
//HCURSOR CLTRobortDlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}

VOID	CLTRobortDlg::StartRobort(DWORD nRobortNum)
{
	m_pListRobort = new Robort[nRobortNum];
	
 	TCHAR const* lpFileName = _T(".\\RobortConfig.ini");
	
	for (DWORD i = 0; i < nRobortNum; ++i)
	{
		Robort* pRobort = &m_pListRobort[i];
		pRobort->Init();
		TCHAR szTemp[X_SHORT_NAME] = {0};
		GetPrivateProfileString(_T("robort"),_T("account"),_T(""),szTemp,X_SHORT_NAME,lpFileName);

		INT nBegin = GetPrivateProfileInt(_T("robort"),_T("beginNum"),0,lpFileName);
		TCHAR szAccountNum[32] = _T("");
		_stprintf_s(szTemp, _countof(szTemp), _T("%s%d"), szTemp, i+nBegin);
		pRobort->SetAccount(Tang::f_util::unicode_to_ansi(szTemp));
		
		//密码
		GetPrivateProfileString(_T("robort"),_T("password"),_T(""),szTemp,X_SHORT_NAME,lpFileName);
		pRobort->SetPassWord(Tang::f_util::unicode_to_ansi(szTemp));
		//serverIP
	
		GetPrivateProfileString(_T("robort"),_T("server"),_T(""),szTemp,X_SHORT_NAME,lpFileName);
		pRobort->SetLoginServer(Tang::f_util::unicode_to_ansi(szTemp));
		//name
		GetPrivateProfileString(_T("robort"),_T("serverName"),_T(""),szTemp,X_SHORT_NAME,lpFileName);
		pRobort->SetWorldName(Tang::f_util::unicode_to_ansi(szTemp));

		INT port = GetPrivateProfileInt(_T("robort"),_T("port"),0,lpFileName);
		pRobort->SetLoginServerProt(port);
		
		INT type = GetPrivateProfileInt(_T("robort"), _T("type"), 0, lpFileName);
		pRobort->SetType(type);
		
		TCHAR szLognTemp[X_LONG_NAME] = _T("");
		GetPrivateProfileString(_T("robort"),_T("map"),_T(""),szTemp,X_LONG_NAME,lpFileName);
		pRobort->SetMap(szTemp);

		pRobort->SetLoginRoleIndex(GetPrivateProfileInt(_T("robort"),_T("roleIndex"),0,lpFileName));

		pRobort->Connect();
		Sleep(10);
	}
	
	m_bUpdate = TRUE;
	m_hUpdate = (HANDLE)_beginthreadex(NULL, 0, &CLTRobortDlg::static_thread_rt, this, 0, NULL);

}

VOID CLTRobortDlg::EndRobort()
{
	m_bUpdate = false;

	WaitForSingleObject(m_hUpdate, INFINITE);

	for (int i = 0; i < m_nRobortNum; ++i)
	{
		Robort* pRobort = &m_pListRobort[i];
		if (pRobort != NULL)
		{
			pRobort->Quit();
		}
	}
	m_nRobortNum = 0;
	SAFE_DELETEA(m_pListRobort);
}
void CLTRobortDlg::OnBnClickedOk()
{
	UpdateData();
	StartRobort(m_nRobortNum);
	m_btnOK.EnableWindow(FALSE);
}

//void CLTRobortDlg::PostNcDestroy()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	for (int i = 0; i < m_nRobortNum; ++i)
//	{
//		Robort* pRobort = &m_pListRobort[i];
//		if (pRobort != NULL)
//		{
//			pRobort->Quit();
//		}
//	}
//
//	if (m_pListRobort != NULL)
//	{
//		delete[] m_pListRobort;
//	}
//	CDialog::PostNcDestroy();
//}

//void CLTRobortDlg::OnBnClickedCancel()
//{
//	for (int i = 0; i < m_nRobortNum; ++i)
//	{
//		Robort* pRobort = &m_pListRobort[i];
//		if (pRobort != NULL)
//		{
//			pRobort->Quit();
//		}
//	}
//
//	
//	OnCancel();
//}

void CLTRobortDlg::OnClose()
{
	CDialog::OnCancel();
}

void CLTRobortDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		TCHAR szTemp[X_SHORT_NAME] = _T("");
		_stprintf(szTemp, _T("%d"), nOnlineNum);
		m_CEonlineNum.SetWindowText(szTemp);

		DWORD dwCurTime = timeGetTime();

		if (dwCurTime - dwTime1 > /*10*1000*/ 30*60*1000)
		{
			if (nOnlineNum < m_nRobortNum * 0.5f)
			{
				bReConnect = TRUE;
				dwTime2 = dwCurTime;
			}
			
			dwTime1 = dwCurTime;
			
		}
		if (dwCurTime - dwTime2 >/* 10*1000*/5*60*1000 && bReConnect)
		{
			EndRobort();
			StartRobort(m_nRobortNum);
			bReConnect = FALSE;
		}

	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CDialog::OnTimer(nIDEvent);
}

void CLTRobortDlg::OnBnClickedCancel()
{
	if (m_bUpdate)
	{
		EndRobort();
		m_btnOK.EnableWindow(TRUE);
	}


	//OnCancel();
}
