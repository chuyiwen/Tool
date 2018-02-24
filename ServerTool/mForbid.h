#pragma once
#include "afxwin.h"


// mForbid 对话框

class mForbid : public CDialog
{
	DECLARE_DYNAMIC(mForbid)

public:
	mForbid(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~mForbid();

// 对话框数据
	enum { IDD = IDD_FORBID };
	std::vector<std::wstring> servernamelist;
	bool forbid;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	virtual BOOL OnInitDialog();
	CButton mbt1;
	CEdit mText;
};
