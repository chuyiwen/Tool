// LTRobortDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class Robort;
// CLTRobortDlg �Ի���
class CLTRobortDlg : public CDialog
{
// ����
public:
	CLTRobortDlg(CWnd* pParent = NULL);	// ��׼���캯��

	virtual ~CLTRobortDlg();
// �Ի�������
	enum { IDD = IDD_LTROBORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// �����߳��Ƿ����е��߳�
	static unsigned int WINAPI static_thread_rt(void* p);
	unsigned int WINAPI thread_rt();
// ʵ��
protected:
	HICON m_hIcon;
	Robort*	m_pListRobort;
	BOOL m_bUpdate;
	HANDLE m_hUpdate;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	VOID	StartRobort(DWORD nRobortNum);
	VOID	EndRobort();
public:
	afx_msg void OnBnClickedOk();
	int m_nRobortNum;
//protected:
//	virtual void PostNcDestroy();
//	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();

private:
	BOOL	m_bQuit;
	IFS*	m_pFS;
public:
	CEdit	m_CEthreadNum;
	CListBox	m_LogOutListBox;
	CListBox	m_OutLog;
	CEdit m_CEonlineNum;
	INT		nOnlineNum;

	DWORD	dwTime1;			//����������ʱ
	DWORD	dwTime2;			//��������ʱ
	BOOL	bReConnect;			//�Ƿ���Ҫ����
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_btnOK;
	afx_msg void OnBnClickedCancel();
	CEdit mClass;
	CEdit mSex;
};
