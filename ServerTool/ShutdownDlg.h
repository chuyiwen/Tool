#pragma once
#include "afxwin.h"


// ShutdownDlg 对话框

class ShutdownDlg : public CDialog
{
	DECLARE_DYNAMIC(ShutdownDlg)

public:
	ShutdownDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShutdownDlg();

// 对话框数据
	enum { IDD = IDD_SHUTDOWN };

	std::vector<std::wstring> servernamelist;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit mTime;
};
