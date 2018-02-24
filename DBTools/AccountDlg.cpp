// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBTools.h"
#include "AccountDlg.h"
#include "DBToolsDlg.h"
#include "DB.h"


// CAccountDlg dialog

IMPLEMENT_DYNAMIC(CAccountDlg, CDialog)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{

}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_RoleNameEdit);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_BUTTON1, m_SelectBT);
	DDX_Control(pDX, IDC_LIST1, m_AccountList);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_EDIT2, m_dwClientID);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_EDIT3, m_RoleNameEdit1);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_EDIT4, m_byPrivilegeEdit);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_EDIT5, m_eLoginStatusEdit);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);
	DDX_Control(pDX, IDC_EDIT6, m_bGuardEdit);
	DDX_Control(pDX, IDC_STATIC7, m_Static7);
	DDX_Control(pDX, IDC_EDIT7, m_dwPreLoginIPEdit);
	DDX_Control(pDX, IDC_STATIC8, m_Static8);
	DDX_Control(pDX, IDC_EDIT8, m_dwPreLoginTimeEdit);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAccountDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAccountDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CAccountDlg message handlers

BOOL CAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitStatic();
	InitAccount();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

VOID CAccountDlg::InitStatic()
{
	SetWindowText(_T("账号数据"));
	m_Static1.SetWindowText(_T("账号查询"));
	m_SelectBT.SetWindowText(_T("查询"));
	m_Static2.SetWindowText(_T("客户端ID"));
	m_Static3.SetWindowText(_T("用户名"));
	m_Static4.SetWindowText(_T("权限"));
	m_Static5.SetWindowText(_T("登陆状态"));
	m_Static6.SetWindowText(_T("防沉迷"));
	m_Static7.SetWindowText(_T("上次登录ip"));
	m_Static8.SetWindowText(_T("上次登录时间"));
}

void CAccountDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pDB)
	{
		m_pDB->GetDataBase()->shut_down();
		m_pDB->GetDBToolsDlg()->ShowWindow(TRUE);
		m_pDB = NULL;
	}
	
	CDialog::OnCancel();
}

void CAccountDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_RoleNameEdit.GetWindowText(str);
	if(m_pDB)
	{
		m_pDB->CleanAccount();
		m_AccountList.ResetContent();
		CHAR RoleName[X_SHORT_NAME];
		WideCharToMultiByte(CP_ACP, 0, str, -1, RoleName, sizeof(CHAR)*X_SHORT_NAME, NULL, NULL);
		m_pDB->LoadAccount(RoleName);
	}
}

VOID CAccountDlg::AddAccount(CString &str)
{
	m_AccountList.AddString(str);
}

VOID CAccountDlg::InitAccount()
{
	m_dwClientID.SetWindowText(_T(""));
	m_RoleNameEdit1.SetWindowText(_T(""));
	m_byPrivilegeEdit.SetWindowText(_T(""));
	m_eLoginStatusEdit.SetWindowText(_T(""));
	m_bGuardEdit.SetWindowText(_T(""));
	m_dwPreLoginIPEdit.SetWindowText(_T(""));
	m_dwPreLoginTimeEdit.SetWindowText(_T(""));
}

VOID CAccountDlg::SetAccount(st_AccountData* pData)
{
	CString str;
	str.Format(_T("%d"), pData->dwClientID);
	m_dwClientID.SetWindowText(str);

	TCHAR RoleName[X_SHORT_NAME];
	MultiByteToWideChar(CP_UTF8, 0, pData->RoleName, -1, RoleName, sizeof(TCHAR)*X_SHORT_NAME);
	str.Format(_T("%s"), RoleName);
	m_RoleNameEdit1.SetWindowText(str);

	str.Format(_T("%d"), pData->byPrivilege);
	m_byPrivilegeEdit.SetWindowText(str);

	str.Format(_T("%d"), pData->eLoginStatus);
	m_eLoginStatusEdit.SetWindowText(str);

	str.Format(_T("%d"), pData->bGuard);
	m_bGuardEdit.SetWindowText(str);

	TCHAR ip[X_IP_LEN] = _T("");
	in_addr addr;
	addr.S_un.S_addr = pData->dwPreLoginIP;
	MultiByteToWideChar(CP_UTF8, 0, inet_ntoa(addr), -1, ip, sizeof(TCHAR)*X_IP_LEN);
	m_dwPreLoginIPEdit.SetWindowText(ip);

	CHAR time[X_DATATIME_LEN+1] = "";
	TCHAR wtime[X_DATATIME_LEN+1] = _T("");
	DwordTime2DataTime(time, sizeof(time), pData->dwPreLoginTime);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wtime, sizeof(TCHAR)*(X_DATATIME_LEN+1));
	m_dwPreLoginTimeEdit.SetWindowText(wtime);
	UpdateData();
}

void CAccountDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	if(m_pDB)
	{
		InitAccount();
		CString str;
		INT32 index = m_AccountList.GetCurSel();
		if(index != -1)
		{
			m_AccountList.GetText(index, str);
			CHAR RoleName[X_SHORT_NAME];
			WideCharToMultiByte(CP_ACP, 0, str, -1, RoleName, sizeof(CHAR)*X_SHORT_NAME, NULL, NULL);
			st_AccountData* pData = m_pDB->GetAccountData(RoleName);
			if(pData)
			{
				SetAccount(pData);
			}
		}
	}
}
