#pragma once

#include "resource.h"
// CNameCrcDlg �Ի���

class CNameCrcDlg : public CDialog
{
	DECLARE_DYNAMIC(CNameCrcDlg)

public:
	CNameCrcDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNameCrcDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_NameStr;
	CString m_CrcStr;
	afx_msg void OnBnClickedButton1();
};
