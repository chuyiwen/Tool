// EquipLookforDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEquipLookforDlg �Ի���
class CEquipLookforDlg : public CDialog
{
// ����
public:
	CEquipLookforDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EQUIPLOOKFOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void OnCancel( );

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
