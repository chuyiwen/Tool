// AddAccount.cpp : 实现文件
//

#include "stdafx.h"
#include "DBTools.h"
#include "AddAccount.h"
#include "DBToolsDlg.h"
#include "DB.h"


// CAddAccount 对话框

IMPLEMENT_DYNAMIC(CAddAccount, CDialog)

CAddAccount::CAddAccount(CWnd* pParent /*=NULL*/)
	: CDialog(CAddAccount::IDD, pParent)
{

}

CAddAccount::~CAddAccount()
{
}

void CAddAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_AccountET);
	DDX_Control(pDX, IDC_EDIT2, m_AccountNumET);
}


BEGIN_MESSAGE_MAP(CAddAccount, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddAccount::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAddAccount 消息处理程序

BOOL CAddAccount::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

VOID CAddAccount::InitControl()
{
	m_AccountET.SetWindowText(_T(""));
	m_AccountNumET.SetWindowText(_T(""));
}

void CAddAccount::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_Account;
	CString str_Num;

	m_AccountET.GetWindowText(str_Account);
	m_AccountNumET.GetWindowText(str_Num);
	if(str_Account.IsEmpty() || str_Num.IsEmpty())
		return;

	DWORD n16Num = _wtoi(str_Num);
	for(DWORD i = 0; i < n16Num; i++)
	{
		if(m_pDB)
		{
			CString str = str_Account;
			str.Format(_T("%s%d"), str, i+1);
			CHAR Account[X_SHORT_NAME];
			WideCharToMultiByte(CP_ACP, 0, str, -1, Account, sizeof(CHAR)*X_SHORT_NAME, NULL, NULL);
			if(!m_pDB->AddAccount(Account)/* || !m_pDB->UpdateAccount()*/)
			{
				MessageBox(_T("账号添加失败！！！"));
				OnCancel();
				return;
			}
			
		}
	}

	if(!m_pDB->UpdateAccount())
	{
		MessageBox(_T("账号添加失败！！！"));
		OnCancel();
		return;
	}

	MessageBox(_T("账号添加完成"));
	OnCancel();
}

void CAddAccount::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pDB)
	{
		m_pDB->GetDataBase()->shut_down();
		m_pDB->GetDBToolsDlg()->ShowWindow(TRUE);
		m_pDB = NULL;
	}
	CDialog::OnCancel();
}
