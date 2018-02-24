#pragma once

#include "resource.h"
// CNameCrcDlg 对话框

class CNameCrcDlg : public CDialog
{
	DECLARE_DYNAMIC(CNameCrcDlg)

public:
	CNameCrcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNameCrcDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_NameStr;
	CString m_CrcStr;
	afx_msg void OnBnClickedButton1();
};
