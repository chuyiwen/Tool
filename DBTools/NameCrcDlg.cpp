// NameCrcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBTools.h"
#include "NameCrcDlg.h"


// CNameCrcDlg 对话框

IMPLEMENT_DYNAMIC(CNameCrcDlg, CDialog)

CNameCrcDlg::CNameCrcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameCrcDlg::IDD, pParent)
	, m_NameStr(_T(""))
	, m_CrcStr(_T(""))
{

}

CNameCrcDlg::~CNameCrcDlg()
{
}

void CNameCrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_NameStr);
	DDX_Text(pDX, IDC_EDIT2, m_CrcStr);
}


BEGIN_MESSAGE_MAP(CNameCrcDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CNameCrcDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CNameCrcDlg 消息处理程序

void CNameCrcDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if(m_NameStr.GetLength() <= 0)
		return;

	tstring strTmp = m_NameStr;
	transform(strTmp.begin(), strTmp.end(), strTmp.begin(), tolower);

	DWORD dw_crc = get_tool()->crc32(strTmp.c_str());

	m_CrcStr.Format(_T("%u"), dw_crc);

	UpdateData(FALSE);
}
