#pragma once
#include "afxwin.h"


// mForbid �Ի���

class mForbid : public CDialog
{
	DECLARE_DYNAMIC(mForbid)

public:
	mForbid(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~mForbid();

// �Ի�������
	enum { IDD = IDD_FORBID };
	std::vector<std::wstring> servernamelist;
	bool forbid;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	virtual BOOL OnInitDialog();
	CButton mbt1;
	CEdit mText;
};
