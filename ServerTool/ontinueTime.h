#pragma once
#include "afxwin.h"


// ContinueTime �Ի���

class ContinueTime : public CDialog
{
	DECLARE_DYNAMIC(ContinueTime)

public:
	ContinueTime(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ContinueTime();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit mT;
	afx_msg void OnBnClickedCheck1();
	CButton mCk;
	CEdit mFromHour;
	CEdit mFromMinute;
	CEdit mToHour;
	CEdit mToMinute;
	std::vector<std::wstring> servernamelist;
	int index;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CString temp[3];
	CString temp1[3];
	CString temp2[3];
	CString temp3[3];
	bool mCheck[3];
};
