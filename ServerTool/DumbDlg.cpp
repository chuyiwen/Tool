// DumbDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "DumbDlg.h"
#include "NetSession.h"
#include "../LogSystem/protocal.h"

// DumbDlg 对话框

IMPLEMENT_DYNAMIC(DumbDlg, CDialog)

DumbDlg::DumbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DumbDlg::IDD, pParent)
{
	dumb  = 0;
}

DumbDlg::~DumbDlg()
{
}

void DumbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mName);
	DDX_Control(pDX, IDC_EDIT2, mTime);
	DDX_Control(pDX, IDC_EDIT3, mBrief);
}


BEGIN_MESSAGE_MAP(DumbDlg, CDialog)
	ON_BN_CLICKED(IDC_ON, &DumbDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_OFF, &DumbDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK, &DumbDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// DumbDlg 消息处理程序
//on
void DumbDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	dumb = 1;
}
//off
void DumbDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	dumb = 2;
}
//ok
void DumbDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name;
	mName.GetWindowText(name);
	NET_C2GMS_ForbidTalk cmd;
	if(dumb == 1)
		cmd.bForbid = 1;
	else if(dumb == 2)
		cmd.bForbid = 0;
	else
	{
		::MessageBox(0 , _T("please check radio button") , _T("error") , 0);
		return;
	}
	_tcscpy_s(cmd.szRoleName , X_SHORT_NAME , name.GetBuffer());
	_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist.c_str());
	CString t;
	mTime.GetWindowText(t);
	cmd.dwSecond = _wtoi(t.GetBuffer())*60;
	CString bri;
	mBrief.GetWindowText(bri);
	_tcscpy_s(cmd.szReason , X_SHORT_NAME , bri);
	net_session::instance()->send_msg(&cmd , cmd.dw_size);
	OnOK();
}
