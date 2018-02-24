// mKickDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "mKickDlg.h"
#include "NetSession.h"
#include "../LogSystem/protocal.h"


// mKickDlg 对话框

IMPLEMENT_DYNAMIC(mKickDlg, CDialog)

mKickDlg::mKickDlg(CWnd* pParent /*=NULL*/)
	: CDialog(mKickDlg::IDD, pParent)
{

}

mKickDlg::~mKickDlg()
{
}

void mKickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, nName);
}


BEGIN_MESSAGE_MAP(mKickDlg, CDialog)
	ON_BN_CLICKED(IDOK, &mKickDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// mKickDlg 消息处理程序

void mKickDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = 0 ; i < servernamelist.size() ; ++i)
	{
		NET_C2GMS_Kick cmd;
		_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
		CString text;
		nName.GetWindowText(text);
		_tcscpy_s(cmd.szRoleName, X_SHORT_NAME, text.GetBuffer());
		net_session::instance()->send_msg(&cmd , cmd.dw_size);
	}
	OnOK();
}
