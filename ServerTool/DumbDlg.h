#pragma once
#include "afxwin.h"


// DumbDlg �Ի���

class DumbDlg : public CDialog
{
	DECLARE_DYNAMIC(DumbDlg)

public:
	DumbDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DumbDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
