#pragma once
#include "afxwin.h"


// mKickDlg �Ի���

class mKickDlg : public CDialog
{
	DECLARE_DYNAMIC(mKickDlg)

public:
	mKickDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~mKickDlg();

// �Ի�������
	enum { IDD = IDD_KICK };

	std::vector<std::wstring> servernamelist;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit nName;
};
