// BoardcastDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "BoardcastDlg.h"
#include "NetSession.h"
#include "../LogSystem/protocal.h"
// BoardcastDlg 对话框

IMPLEMENT_DYNAMIC(BoardcastDlg, CDialog)

BoardcastDlg::BoardcastDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BoardcastDlg::IDD, pParent)
{
	mBegin = false;
}

BoardcastDlg::~BoardcastDlg()
{
}

void BoardcastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mText);
	DDX_Control(pDX, IDOK, mStart);
	DDX_Control(pDX, IDC_CHECK1, mCkeck1);
	DDX_Control(pDX, IDC_CHECK2, mCheck2);
	DDX_Control(pDX, IDC_CHECK3, mCheck3);
	DDX_Control(pDX, IDC_CHECK4, mCheck4);
	DDX_Control(pDX, IDC_CHECK5, mCheck5);
	DDX_Control(pDX, IDC_EDIT12, mMsg1);
	DDX_Control(pDX, IDC_EDIT5, mMsg2);
	DDX_Control(pDX, IDC_EDIT6, mMsg3);
	DDX_Control(pDX, IDC_EDIT7, mMsg4);
	DDX_Control(pDX, IDC_EDIT8, mMsg5);
	DDX_Control(pDX, IDC_EDIT3, mTime1);
	DDX_Control(pDX, IDC_EDIT4, mTime2);
	DDX_Control(pDX, IDC_EDIT9, mTime3);
	DDX_Control(pDX, IDC_EDIT10, mTime4);
	DDX_Control(pDX, IDC_EDIT11, mTime5);
}


BEGIN_MESSAGE_MAP(BoardcastDlg, CDialog)
	ON_BN_CLICKED(IDOK, &BoardcastDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &BoardcastDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// BoardcastDlg 消息处理程序
//!循环消息播放
void BoardcastDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	mBegin = !mBegin;
	net_session::instance2()->start = mBegin;
	if(mBegin)
	{
		mStart.SetWindowText(_T("Stop"));
		//!1
		if(mCkeck1.GetCheck())
		{
			for(int i = 0 ; i < servernamelist.size() ; ++i)
			{
				NET_C2GMS_Affiche_Periodicity cmd;
				cmd.dwIndex = 0;
				CString t;
				mTime1.GetWindowText(t);
				cmd.dwSecond = _wtoi(t.GetBuffer())*60;
				CString msg;
				mMsg1.GetWindowText(msg);
				_tcscpy(cmd.szAfficheMsg , msg.GetBuffer());
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
		//!2
		if(mCheck2.GetCheck())
		{
			for(int i = 0 ; i < servernamelist.size() ; ++i)
			{
				NET_C2GMS_Affiche_Periodicity cmd;
				cmd.dwIndex = 1;
				CString t;
				mTime2.GetWindowText(t);
				cmd.dwSecond = _wtoi(t.GetBuffer())*60;
				CString msg;
				mMsg2.GetWindowText(msg);
				_tcscpy(cmd.szAfficheMsg , msg.GetBuffer());
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
		//!3
		if(mCheck3.GetCheck())
		{
			for(int i = 0 ; i < servernamelist.size() ; ++i)
			{
				NET_C2GMS_Affiche_Periodicity cmd;
				cmd.dwIndex = 2;
				CString t;
				mTime3.GetWindowText(t);
				cmd.dwSecond = _wtoi(t.GetBuffer())*60;
				CString msg;
				mMsg3.GetWindowText(msg);
				_tcscpy(cmd.szAfficheMsg , msg.GetBuffer());
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
		//!4
		if(mCheck4.GetCheck())
		{
			for(int i = 0 ; i < servernamelist.size() ; ++i)
			{
				NET_C2GMS_Affiche_Periodicity cmd;
				cmd.dwIndex = 3;
				CString t;
				mTime4.GetWindowText(t);
				cmd.dwSecond = _wtoi(t.GetBuffer())*60;
				CString msg;
				mMsg4.GetWindowText(msg);
				_tcscpy(cmd.szAfficheMsg , msg.GetBuffer());
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
		//!5
		if(mCheck5.GetCheck())
		{
			for(int i = 0 ; i < servernamelist.size() ; ++i)
			{
				NET_C2GMS_Affiche_Periodicity cmd;
				cmd.dwIndex = 4;
				CString t;
				mTime5.GetWindowText(t);
				cmd.dwSecond = _wtoi(t.GetBuffer())*60;
				CString msg;
				mMsg5.GetWindowText(msg);
				_tcscpy(cmd.szAfficheMsg , msg.GetBuffer());
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
	}
	else
	{
		mStart.SetWindowText(_T("Start"));
		for(int i = 0 ; i < servernamelist.size() ; ++i)
		{
			{
				NET_C2GMS_Cancel_Affiche_Periodicity cmd;
				cmd.dwIndex = 0;
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}

			{
				NET_C2GMS_Cancel_Affiche_Periodicity cmd;
				cmd.dwIndex = 1;
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}

			{
				NET_C2GMS_Cancel_Affiche_Periodicity cmd;
				cmd.dwIndex = 2;
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}

			{
				NET_C2GMS_Cancel_Affiche_Periodicity cmd;
				cmd.dwIndex = 3;
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}

			{
				NET_C2GMS_Cancel_Affiche_Periodicity cmd;
				cmd.dwIndex = 4;
				_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
	}
}

//!一次性公告
void BoardcastDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = 0 ; i < servernamelist.size() ; ++i)
	{
		CString text;
		mText.GetWindowText(text);
		CString time;
		NET_C2GMS_Affiche cmd;
		int sec = 20;
		cmd.dwSecond = time.IsEmpty() ? 120 : _ttoi(time.GetBuffer());
		_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
		_tcscpy_s(cmd.szAfficheMsg, GMAFFICHELEN, text.GetBuffer());
		net_session::instance()->send_msg(&cmd , cmd.dw_size);
	}
}
//!保存
void BoardcastDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
	//1
	{
		net_session::instance2()->info[0].checked = (bool)mCkeck1.GetCheck();
		CString msg;
		mMsg1.GetWindowText(msg);
		net_session::instance2()->info[0].msg = msg.GetBuffer();
		msg.Empty();
		mTime1.GetWindowText(msg);
		net_session::instance2()->info[0].time = msg.GetBuffer();
	}
	//2
	{
		net_session::instance2()->info[1].checked = (bool)mCheck2.GetCheck();
		CString msg;
		mMsg2.GetWindowText(msg);
		net_session::instance2()->info[1].msg = msg.GetBuffer();
		msg.Empty();
		mTime2.GetWindowText(msg);
		net_session::instance2()->info[1].time = msg.GetBuffer();
	}
	//3
	{
		net_session::instance2()->info[2].checked = (bool)mCheck3.GetCheck();
		CString msg;
		mMsg3.GetWindowText(msg);
		net_session::instance2()->info[2].msg = msg.GetBuffer();
		msg.Empty();
		mTime3.GetWindowText(msg);
		net_session::instance2()->info[2].time = msg.GetBuffer();
	}
	//4
	{
		net_session::instance2()->info[3].checked = (bool)mCheck4.GetCheck();
		CString msg;
		mMsg4.GetWindowText(msg);
		net_session::instance2()->info[3].msg = msg.GetBuffer();
		msg.Empty();
		mTime4.GetWindowText(msg);
		net_session::instance2()->info[3].time = msg.GetBuffer();
	}
	//5
	{
		net_session::instance2()->info[4].checked = (bool)mCheck5.GetCheck();
		CString msg;
		mMsg5.GetWindowText(msg);
		net_session::instance2()->info[4].msg = msg.GetBuffer();
		msg.Empty();
		mTime5.GetWindowText(msg);
		net_session::instance2()->info[4].time = msg.GetBuffer();
	}
}

BOOL BoardcastDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(net_session::instance2()->start)
		mStart.SetWindowText(L"Stop");
	else
		mStart.SetWindowText(L"Start");

	// TODO:  在此添加额外的初始化
	//1
	{
		mCkeck1.SetCheck(net_session::instance2()->info[0].checked);
		mMsg1.SetWindowText(net_session::instance2()->info[0].msg.c_str());
		mTime1.SetWindowText(net_session::instance2()->info[0].time.c_str());
	}
	//2
	{
		mCheck2.SetCheck(net_session::instance2()->info[1].checked);
		mMsg2.SetWindowText(net_session::instance2()->info[1].msg.c_str());
		mTime2.SetWindowText(net_session::instance2()->info[1].time.c_str());
	}
	//3
	{
		mCheck3.SetCheck(net_session::instance2()->info[2].checked);
		mMsg3.SetWindowText(net_session::instance2()->info[2].msg.c_str());
		mTime3.SetWindowText(net_session::instance2()->info[2].time.c_str());
	}
	//4
	{
		mCheck4.SetCheck(net_session::instance2()->info[3].checked);
		mMsg4.SetWindowText(net_session::instance2()->info[3].msg.c_str());
		mTime4.SetWindowText(net_session::instance2()->info[3].time.c_str());
	}
	//5
	{
		mCheck5.SetCheck(net_session::instance2()->info[4].checked);
		mMsg5.SetWindowText(net_session::instance2()->info[4].msg.c_str());
		mTime5.SetWindowText(net_session::instance2()->info[4].time.c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
