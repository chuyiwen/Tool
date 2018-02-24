// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "LoginDlg.h"
#include "../LogSystem/protocal.h"
#include "NetSession.h"

// LoginDlg 对话框


IMPLEMENT_DYNAMIC(LoginDlg, CDialog)

LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDlg::IDD, pParent)
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mUser);
	DDX_Control(pDX, IDC_EDIT2, mPwd);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// LoginDlg 消息处理程序

void LoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	mUser.GetWindowText(user);
	mPwd.GetWindowText(pwd);
	OnOK();
}
