#pragma once
#include "afxwin.h"


// ShutdownDlg �Ի���

class ShutdownDlg : public CDialog
{
	DECLARE_DYNAMIC(ShutdownDlg)

public:
	ShutdownDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShutdownDlg();

// �Ի�������
	enum { IDD = IDD_SHUTDOWN };

	std::vector<std::wstring> servernamelist;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit mTime;
};
