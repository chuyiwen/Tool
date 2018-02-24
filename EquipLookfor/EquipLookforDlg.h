// EquipLookforDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEquipLookforDlg 对话框
class CEquipLookforDlg : public CDialog
{
// 构造
public:
	CEquipLookforDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EQUIPLOOKFOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void OnCancel( );

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit mDatabaseIP;
	CEdit mDatabasePort;
	CEdit mDatabaseUser;
	CEdit mDatabaseName;
	CEdit mDatabasePassword;
	CButton mConnectDB;
	CButton mQuery;
	CButton mQueryFromDel;
	afx_msg void OnBnClickedButtionGet();
	afx_msg void OnBnClickedButtionConnect();
	CEdit mItemSerial;
	CListCtrl mListProperty;
	odbc::db_interface*	mDBSession;
private:
	void DisableButton(BOOL Success);
	void ShowEquip(VOID* p, INT i = 0);	
};
