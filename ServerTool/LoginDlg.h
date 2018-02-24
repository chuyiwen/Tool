#pragma once
#include "afxwin.h"
#include "event.h"

// LoginDlg 对话框

class LoginDlg : public CDialog
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mUser;
	CEdit mPwd;
	CString user;
	CString pwd;
	afx_msg void OnBnClickedOk();
};
