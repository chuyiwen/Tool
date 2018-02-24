// LTRobortDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class Robort;
// CLTRobortDlg 对话框
class CLTRobortDlg : public CDialog
{
// 构造
public:
	CLTRobortDlg(CWnd* pParent = NULL);	// 标准构造函数

	virtual ~CLTRobortDlg();
// 对话框数据
	enum { IDD = IDD_LTROBORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 监视线程是否运行的线程
	static unsigned int WINAPI static_thread_rt(void* p);
	unsigned int WINAPI thread_rt();
// 实现
protected:
	HICON m_hIcon;
	Robort*	m_pListRobort;
	BOOL m_bUpdate;
	HANDLE m_hUpdate;
	// 生成的消息映射函数
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

	DWORD	dwTime1;			//重连条件计时
	DWORD	dwTime2;			//重连倒计时
	BOOL	bReConnect;			//是否需要重连
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_btnOK;
	afx_msg void OnBnClickedCancel();
	CEdit mClass;
	CEdit mSex;
};
