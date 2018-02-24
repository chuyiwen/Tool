// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerTool.h"
#include "LoginDlg.h"
#include "../LogSystem/protocal.h"
#include "NetSession.h"

// LoginDlg �Ի���


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


// LoginDlg ��Ϣ�������

void LoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mUser.GetWindowText(user);
	mPwd.GetWindowText(pwd);
	OnOK();
}
