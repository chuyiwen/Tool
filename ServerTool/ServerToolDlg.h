// ServerToolDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "../LogSystem/protocal.h"
#include "BoardcastDlg.h"
#include "mForbid.h"
#include "mKickDlg.h"
#include "event.h"
#include "afxwin.h"
#include "ontinueTime.h"
#include "DumbDlg.h"
#include "ShutdownDlg.h"
#include "LoginDlg.h"
// CServerToolDlg 对话框
class CServerToolDlg : public CDialog
{
// 构造
public:
	CServerToolDlg(CWnd* pParent = NULL);	// 标准构造函数

	virtual ~CServerToolDlg();

// 对话框数据
	enum { IDD = IDD_SERVERTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	struct com{
		short port;
		int line;
		std::string ip;
	};

	c_event m_event;

	std::map<std::wstring , com> m_ipport;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mAreaList;
	CListCtrl mServerList;
	BoardcastDlg mBoardcast;
	mKickDlg mKick;
	DumbDlg dlg;
	mForbid mfor;
	LoginDlg mLogin;
	ContinueTime  mCTime;
	int mTotal;
public:
	void onLoginStatus(NP_NET_CMD* mdg);
	void onLoginOK(NP_NET_CMD* msg);
	void onUpdateServerList(NP_NET_CMD* msg);

private:
	void connect_all();
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton3();
	CEdit mNumber;
	afx_msg void OnBnClickedButton6();
	CEdit mEXP;
	CEdit mITEM;
	CStatic mOnline;
	CStatic mServerTip;
	CEdit mTrain;
	ShutdownDlg mShutdown;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton5();


private:
	LPCSTR unicode_to_ansi(LPCTSTR sz_src_);
	LPCTSTR ansi_to_unicode(LPCSTR sz_src_);
	void md5_init();
	void md5_update(BYTE *p_in_, UINT n_in_length_);
	void encode(BYTE* p_out_, DWORD* p_in_, unsigned int n_length_);
	void md5_final(BYTE by_digest_[16]);
	VOID md5_for_buffer(BYTE* p_buffer_, UINT n_buffer_length_, BYTE by_digest_[16]);
	VOID md5_for_string(CHAR* sz_string_, BYTE by_digest_[16]);
	void md5_transform (DWORD[4], unsigned char[64]);
	void decode(DWORD* p_out_, BYTE* p_in_, unsigned int);
	VOID md5_to_string(std::string& string_, BYTE by_digest_[16]);
	CStatic tip;
	CEdit mUser;
	CEdit mPWD;
	CHAR* p_char_buffer;
	TCHAR* p_tchar_buffer;
	typedef struct 
	{
		DWORD _state[4];		
		DWORD _count[2];		
		BYTE _buffer[64];		
	} MD5_CONTEXT;
	MD5_CONTEXT	st_context;
public:
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
public:
	bool mTrainCheck;
	bool mExpCheck;
	bool mItemCheck;
};
