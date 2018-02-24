// DBToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBTools.h"
#include "DBToolsDlg.h"
#include "NameCrcDlg.h"
#include "..\common\dump\zip_file.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDBToolsDlg dialog




CDBToolsDlg::CDBToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDB = new CDB;
}

void CDBToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_IPEdit);
	DDX_Control(pDX, IDC_EDIT2, m_PortEdit);
	DDX_Control(pDX, IDC_EDIT3, m_UserNameEdit);
	DDX_Control(pDX, IDC_EDIT4, m_PassWordEdit);
	DDX_Control(pDX, IDC_BUTTON1, m_LoginBT);
	DDX_Control(pDX, IDC_EDIT5, m_DBNameEdit);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_COMBO1, m_FindDataCB);
	DDX_Control(pDX, IDC_BUTTON2, m_AddAccountBT);
	DDX_Control(pDX, IDC_BUTTON3, m_Combination_bt);
	DDX_Control(pDX, IDC_BUTTON4, m_add_role_bt);
}

BEGIN_MESSAGE_MAP(CDBToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CDBToolsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDBToolsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDBToolsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDBToolsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDBToolsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CDBToolsDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDBToolsDlg message handlers

BOOL CDBToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	tagDWORDTime dwShutDownTime;
	ZeroMemory(&dwShutDownTime, sizeof(dwShutDownTime));
	dwShutDownTime.year = SHUT_DOWN_YEAY;
	dwShutDownTime.month = SHUT_DOWN_MONTH;

	DWORD dwCurTime = GetCurrentDWORDTime();

	if (dwCurTime > dwShutDownTime)
	{
		DestroyWindow();
		return TRUE;
	}

	serverbase::init_network();
	serverbase::init_serverbase();

	p_log = new log_file;
	p_log->create_log();

	InitStatic();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

VOID CDBToolsDlg::InitStatic()
{
	SetWindowText(_T("游戏数据库管理器v1.0"));
	m_LoginBT.SetWindowText(_T("登入"));
	m_Static1.SetWindowText(_T("查询数据"));
	m_FindDataCB.SetCurSel(0);
	m_AddAccountBT.SetWindowText(_T("批量添加账号"));
	m_Combination_bt.SetWindowText(_T("数据库合并工具"));
	m_add_role_bt.SetWindowText(_T("添加角色"));
}

void CDBToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDBToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDBToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDBToolsDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_pDB->Destroy();
	serverbase::destroy_serverbase();
	serverbase::destroy_network();
	OnCancel();
}

void CDBToolsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	INT16 index = m_FindDataCB.GetCurSel();
	if(m_pDB)
	{
		m_pDB->SetLoginDlg(this);
		ConnectDB(index);
	}
}

VOID CDBToolsDlg::ConnectDB(INT16 &index)
{
	CString str;
	m_IPEdit.GetWindowText(str);
	m_pDB->SetIP(str);

	m_PortEdit.GetWindowText(str);
	m_pDB->SetPort(str);

	m_UserNameEdit.GetWindowText(str);
	m_pDB->SetUserName(str);

	m_PassWordEdit.GetWindowText(str);
	m_pDB->SetPassWord(str);

	m_DBNameEdit.GetWindowText(str);
	m_pDB->SetDBName(str);

	if(!m_pDB->InitDB(index))
	{
		MessageBox(_T("数据库连接失败"));
	}
}

void CDBToolsDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pDB)
	{
		INT16 n16Index = 2;
		m_pDB->SetLoginDlg(this);
		ConnectDB(n16Index);
	}
}

void CDBToolsDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combinationdlg.DoModal();
}

void CDBToolsDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pDB)
	{
		INT16 n16Index = 3;
		m_pDB->SetLoginDlg(this);
		ConnectDB(n16Index);
	}
}

void CDBToolsDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CNameCrcDlg dlg;
	dlg.DoModal();
}
