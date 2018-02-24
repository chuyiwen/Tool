#ifndef ADDACCOUNT
#define ADDACCOUNT
#include "resource.h"
#include "afxwin.h"
#include <string>
class CDB;

// CAddAccount 对话框

class CAddAccount : public CDialog
{
	DECLARE_DYNAMIC(CAddAccount)

public:
	CAddAccount(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddAccount();

// 对话框数据
	enum { IDD = IDD_ADDACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
