#pragma once
#include "afxwin.h"
#include "event.h"

// LoginDlg �Ի���

class LoginDlg : public CDialog
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit mUser;
	CEdit mPwd;
	CString user;
	CString pwd;
	afx_msg void OnBnClickedOk();
};
