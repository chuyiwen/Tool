#pragma once
#include "afxwin.h"




// BoardcastDlg �Ի���

class BoardcastDlg : public CDialog
{
	DECLARE_DYNAMIC(BoardcastDlg)

public:
	BoardcastDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BoardcastDlg();

// �Ի�������
	enum { IDD = IDD_BOARDCAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit mText;
	bool mBegin;
	std::vector<std::wstring> servernamelist;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CButton mStart;
	CButton mCkeck1;
	CButton mCheck2;
	CButton mCheck3;
	CButton mCheck4;
	CButton mCheck5;
	CEdit mMsg1;
	CEdit mMsg2;
	CEdit mMsg3;
	CEdit mMsg4;
	CEdit mMsg5;
	CEdit mTime1;
	CEdit mTime2;
	CEdit mTime3;
	CEdit mTime4;
	CEdit mTime5;
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
};
