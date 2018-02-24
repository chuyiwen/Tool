// DBToolsDlg.h : header file
//

#ifndef DBTOOLSDLG
#define DBTOOLSDLG
#include "afxwin.h"
#include "resource.h"
#include "DB.h"

#include "CombinationDlg.h"



// CDBToolsDlg dialog
class CDBToolsDlg : public CDialog
{
// Construction
public:
	CDBToolsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DBTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CDB *m_pDB;
private:

	VOID InitStatic();

	VOID ConnectDB(INT16 &index);

public:

	afx_msg void OnBnClickedCancel();
	CEdit m_IPEdit;
	CEdit m_PortEdit;
	CEdit m_UserNameEdit;
	CEdit m_PassWordEdit;
	afx_msg void OnBnClickedButton1();
	CButton m_LoginBT;
	CEdit m_DBNameEdit;
	CStatic m_Static1;
	CComboBox m_FindDataCB;
	afx_msg void OnBnClickedButton2();
	CButton m_AddAccountBT;
	afx_msg void OnBnClickedButton3();

private:

	CombinationDlg m_combinationdlg;
public:
	CButton m_Combination_bt;
	CButton m_add_role_bt;
	afx_msg void OnBnClickedButton4();

	log_file*	p_log;
	afx_msg void OnBnClickedButton6();
};
#endif

