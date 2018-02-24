#pragma once
#include "afxwin.h"


// DumbDlg 对话框

class DumbDlg : public CDialog
{
	DECLARE_DYNAMIC(DumbDlg)

public:
	DumbDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DumbDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mName;
	int dumb;
	std::wstring servernamelist;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	CEdit mTime;
	CEdit mBrief;
};
