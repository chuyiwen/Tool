#ifndef ADDACCOUNT
#define ADDACCOUNT
#include "resource.h"
#include "afxwin.h"
#include <string>
class CDB;

// CAddAccount �Ի���

class CAddAccount : public CDialog
{
	DECLARE_DYNAMIC(CAddAccount)

public:
	CAddAccount(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddAccount();

// �Ի�������
	enum { IDD = IDD_ADDACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	VOID SetDB(CDB *pDB)
	{
		m_pDB = pDB;
	}
private:
	VOID InitControl();
private:
	CDB *m_pDB;
public:
	CEdit m_AccountET;
	CEdit m_AccountNumET;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
protected:
	virtual void OnCancel();
};
#endif
