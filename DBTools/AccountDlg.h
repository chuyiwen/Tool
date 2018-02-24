#ifndef ACCOUNTDLG
#define ACCOUNTDLG

#include "resource.h"
#include "afxwin.h"
#include <string>
class CDB;

// CAccountDlg dialog

class CAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAccountDlg();

// Dialog Data
	enum { IDD = IDD_ACCOUNTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	VOID SetDB(CDB *pDB)
	{
		m_pDB = pDB;
	}

	VOID AddAccount(CString &str);

	VOID InitAccount();

	VOID SetAccount(st_AccountData* pData);

private:
	VOID InitStatic();

private:
	CDB *m_pDB;
protected:
	virtual void OnCancel();
public:
	CEdit m_RoleNameEdit;
	CStatic m_Static1;
	CButton m_SelectBT;
	afx_msg void OnBnClickedButton1();
	CListBox m_AccountList;
	afx_msg void OnLbnSelchangeList1();
	CStatic m_Static2;
	CEdit m_dwClientID;
	CStatic m_Static3;
	CEdit m_RoleNameEdit1;
	CStatic m_Static4;
	CEdit m_byPrivilegeEdit;
	CStatic m_Static5;
	CEdit m_eLoginStatusEdit;
	CStatic m_Static6;
	CEdit m_bGuardEdit;
	CStatic m_Static7;
	CEdit m_dwPreLoginIPEdit;
	CStatic m_Static8;
	CEdit m_dwPreLoginTimeEdit;
};
#endif
