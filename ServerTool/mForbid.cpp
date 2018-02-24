// mForbid.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "mForbid.h"
#include "NetSession.h"
#include "../LogSystem/protocal.h"

// mForbid 对话框

IMPLEMENT_DYNAMIC(mForbid, CDialog)

mForbid::mForbid(CWnd* pParent /*=NULL*/)
	: CDialog(mForbid::IDD, pParent)
{
	forbid = true;

}

mForbid::~mForbid()
{
}

void mForbid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, mbt1);
	DDX_Control(pDX, IDC_EDIT1, mText);
}


BEGIN_MESSAGE_MAP(mForbid, CDialog)
	ON_BN_CLICKED(IDOK, &mForbid::OnBnClickedOk)
	ON_BN_CLICKED(IDC_FORBID, &mForbid::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_UNFORBID, &mForbid::OnBnClickedRadio2)
END_MESSAGE_MAP()


// mForbid 消息处理程序

void mForbid::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


	for(int i = 0 ; i < servernamelist.size() ; ++i)
	{
		CString str;
		mText.GetWindowText(str);
		NET_C2GMS_ForbidAccount send;
		send.bForbid = forbid;
		_tcscpy_s(send.szAccount, X_SHORT_NAME, str.GetBuffer());
		_tcscpy_s(send.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
		net_session::instance()->send_msg(&send , send.dw_size);
	}
	OnOK();
}

void mForbid::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	forbid = true;
}

void mForbid::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	forbid = false;
}

BOOL mForbid::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(forbid)
		CheckRadioButton(IDC_FORBID , IDC_UNFORBID , IDC_FORBID);
	else
		CheckRadioButton(IDC_FORBID , IDC_UNFORBID , IDC_UNFORBID);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
