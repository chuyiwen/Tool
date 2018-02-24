#pragma once
#include "resource.h"

class CDB;
// AddRoleDlg 对话框

class AddRoleDlg : public CDialog
{
	DECLARE_DYNAMIC(AddRoleDlg)

public:
	AddRoleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddRoleDlg();

// 对话框数据
	enum { IDD = IDD_ADDROLEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	VOID	SetDB(CDB* pDB);

	VOID	Get_Role_Max_id();

private:

	CDB*	m_pDB;
public:
	// 账号区间基数
	DWORD m_min_account_id;
	// 账号区间大编号
	DWORD m_max_account_id;
	CString m_role_name;
	int m_class;
	int m_sex;
	afx_msg void OnBnClickedButton1();
	DWORD	m_dw_max_role_id;
protected:
	virtual void OnCancel();
};
