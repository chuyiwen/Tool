// ShutdownDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerTool.h"
#include "ShutdownDlg.h"
#include "../LogSystem/protocal.h"
#include "NetSession.h"
// ShutdownDlg �Ի���

IMPLEMENT_DYNAMIC(ShutdownDlg, CDialog)

ShutdownDlg::ShutdownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ShutdownDlg::IDD, pParent)
{

}

ShutdownDlg::~ShutdownDlg()
{
}

void ShutdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mTime);
}


BEGIN_MESSAGE_MAP(ShutdownDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ShutdownDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ShutdownDlg ��Ϣ�������

//!�ط�����
void ShutdownDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = 0 ; i < servernamelist.size() ; ++i)
	{
		CString str;
		mTime.GetWindowText(str);
		NET_C2GMS_ShutDown cmd;
		cmd.nTime = _wtoi(str.GetBuffer());
		_tcscpy_s(cmd.szServerName, X_SHORT_NAME, servernamelist[i].c_str());
		net_session::instance()->send_msg(&cmd , cmd.dw_size);
	}
	OnOK();
}
