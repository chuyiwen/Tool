#pragma once
#include "resource.h"

class CDB;
// AddRoleDlg �Ի���

class AddRoleDlg : public CDialog
{
	DECLARE_DYNAMIC(AddRoleDlg)

public:
	AddRoleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddRoleDlg();

// �Ի�������
	enum { IDD = IDD_ADDROLEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:

	VOID	SetDB(CDB* pDB);

	VOID	Get_Role_Max_id();

private:

	CDB*	m_pDB;
public:
	// �˺��������
	DWORD m_min_account_id;
	// �˺��������
	DWORD m_max_account_id;
	CString m_role_name;
	int m_class;
	int m_sex;
	afx_msg void OnBnClickedButton1();
	DWORD	m_dw_max_role_id;
protected:
	virtual void OnCancel();
};
