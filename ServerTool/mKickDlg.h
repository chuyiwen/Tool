#pragma once
#include "afxwin.h"


// mKickDlg 对话框

class mKickDlg : public CDialog
{
	DECLARE_DYNAMIC(mKickDlg)

public:
	mKickDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~mKickDlg();

// 对话框数据
	enum { IDD = IDD_KICK };

	std::vector<std::wstring> servernamelist;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit nName;
};
