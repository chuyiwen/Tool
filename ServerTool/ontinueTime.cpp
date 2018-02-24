// ontinueTime.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "ontinueTime.h"
#include "NetSession.h"

// ContinueTime 对话框

IMPLEMENT_DYNAMIC(ContinueTime, CDialog)

ContinueTime::ContinueTime(CWnd* pParent /*=NULL*/)
	: CDialog(ContinueTime::IDD, pParent)
{
	mCheck[0] = false;
	mCheck[1] = false;
	mCheck[2] = false;
}

ContinueTime::~ContinueTime()
{
}

void ContinueTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mT);
	DDX_Control(pDX, IDC_CHECK1, mCk);
	DDX_Control(pDX, IDC_EDIT2, mFromHour);
	DDX_Control(pDX, IDC_EDIT3, mFromMinute);
	DDX_Control(pDX, IDC_EDIT4, mToHour);
	DDX_Control(pDX, IDC_EDIT5, mToMinute);
}


BEGIN_MESSAGE_MAP(ContinueTime, CDialog)
	ON_BN_CLICKED(IDOK, &ContinueTime::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &ContinueTime::OnBnClickedCheck1)
	ON_BN_CLICKED(IDCANCEL, &ContinueTime::OnBnClickedCancel)
END_MESSAGE_MAP()


// ContinueTime 消息处理程序

void ContinueTime::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	mFromHour.GetWindowText(temp[index]);
	mFromMinute.GetWindowText(temp1[index]);
	mToHour.GetWindowText(temp2[index]);
	mToMinute.GetWindowText(temp3[index]);
	mCheck[index] = mCk.GetCheck();


	CString str;
	mT.GetWindowText(str);
	int mini = _wtoi(str.GetBuffer());
	if(mini<=0||mini>=60*24*7)
	{
		net_session::instance2()->continueTime = 0;
		::MessageBox(0 , _T("input time is invalid") , _T("error") , 0);
	}
	net_session::instance2()->continueTime = mini*60;
	OnOK();
}

void ContinueTime::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	bool check = mCk.GetCheck();
	if(check)
	{
		for(int i = 0 ; i < servernamelist.size() ; ++i)
		{
			mFromHour.GetWindowText(temp[index]);
			int hs = _wtoi(temp[index].GetBuffer());
			net_session::instance2()->mDoublePolicy[servernamelist[i]].hourStart[index] = hs;
			mFromMinute.GetWindowText(temp1[index]);
			int ms = _wtoi(temp1[index].GetBuffer());
			net_session::instance2()->mDoublePolicy[servernamelist[i]].minuteStart[index] = ms;
			mToHour.GetWindowText(temp2[index]);
			int he = _wtoi(temp2[index].GetBuffer());
			net_session::instance2()->mDoublePolicy[servernamelist[i]].hourEnd[index] = he;
			mToMinute.GetWindowText(temp3[index]);
			int me = _wtoi(temp3[index].GetBuffer());
			net_session::instance2()->mDoublePolicy[servernamelist[i]].minuteEnd[index] = me;
			net_session::instance2()->mDoublePolicy[servernamelist[i]].continueMinutes[index] = 
				(he - hs)*60 + me - ms;
		}
		mCheck[index] = true;
	}
	else
		mCheck[index] = false;
}

void ContinueTime::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	net_session::instance2()->continueTime = 0;
	mFromHour.GetWindowText(temp[index]);
	mFromMinute.GetWindowText(temp1[index]);
	mToHour.GetWindowText(temp2[index]);
	mToMinute.GetWindowText(temp3[index]);
	mCheck[index] = mCk.GetCheck();
	OnCancel();
}

BOOL ContinueTime::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mFromHour.SetWindowText(temp[index]);
	mFromMinute.SetWindowText(temp1[index]);
	mToHour.SetWindowText(temp2[index]);
	mToMinute.SetWindowText(temp3[index]);
	mCk.SetCheck(mCheck[index]);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
