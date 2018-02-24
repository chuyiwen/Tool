#include "stdafx.h"
#include "GameLog.h"

GameLog* GameLog::Instance()
{
	static GameLog gameLog;
	return &gameLog;
}

GameLog::GameLog():m_pWndLoginLog(NULL)
{
    InitializeCriticalSection(&m_Lock);
	InitializeCriticalSection(&m_Lock2);
}

GameLog::~GameLog()
{
    DeleteCriticalSection(&m_Lock);
	DeleteCriticalSection(&m_Lock2);
}

// void GameLog::GameLogOut(TCHAR *pText)
// {
// 	EnterCriticalSection(&m_Lock);
//     if(!m_pWndLoginLog)
// 	{
// 	    return;
// 	}
// 	tstring strText(pText);
// 	tstring strFeedLine(_T("\r\n"));
// 	strText+=strFeedLine;
// 	m_strLog +=strText;
// 
// 	m_pWndLoginLog->SetWindowTextW(m_strLog.c_str());
//     ((CEdit*)m_pWndLoginLog)->SetSel(m_strLog.length(),m_strLog.length(),FALSE);
// 	LeaveCriticalSection(&m_Lock);
// }

void GameLog::GameLogOut(TCHAR *pText)
{
    EnterCriticalSection(&m_Lock);
    if(!m_pWndLoginLog)
	{
	    return;
	}
	//tstring strText(pText);
	//tstring strFeedLine(_T("\r\n"));
	//strText+=strFeedLine;
	//m_strLog +=strText;

	m_pWndLoginLog->AddString(pText);
	LeaveCriticalSection(&m_Lock);
}

void GameLog::GameLogOut2(TCHAR* pText)
{
	EnterCriticalSection(&m_Lock2);
	if(!m_pWndRobortLog)
	{
		return;
	}
	//tstring strText(pText);
	//tstring strFeedLine(_T("\r\n"));
	//strText+=strFeedLine;
	//m_strLog +=strText;

	m_pWndRobortLog->AddString(pText);
	LeaveCriticalSection(&m_Lock2);
}
// void GameLog::GameLogOut(CString strTextLine)
// {
// 	EnterCriticalSection(&m_Lock);
//     if(!m_pWndLoginLog)
// 	{
// 	    return;
// 	}
// 	tstring strText(strTextLine.GetBuffer());
// 	tstring strFeedLine(_T("\r\n"));
// 	strText+=strFeedLine;
// 	m_strLog +=strText;
// 
// 	m_pWndLoginLog->SetWindowTextW(m_strLog.c_str());
//     ((CEdit*)m_pWndLoginLog)->SetSel(m_strLog.length(),m_strLog.length(),FALSE);
// 	LeaveCriticalSection(&m_Lock);
// }
// 
// void GameLog::GameLogOut(CString strTextLine)
// {
//     EnterCriticalSection(&m_Lock);
//     if(!m_pWndLoginLog)
// 	{
// 	    return;
// 	}
// 	tstring strText(strTextLine.GetBuffer());
// 	tstring strFeedLine(_T("\r\n"));
// 	strText+=strFeedLine;
// 	m_strLog +=strText;
// 
// 	m_pWndGameLog->SetWindowTextW(m_strLog.c_str());
//     ((CEdit*)m_pWndLoginLog)->SetSel(m_strLog.length(),m_strLog.length(),FALSE);
// 	LeaveCriticalSection(&m_Lock);
// }