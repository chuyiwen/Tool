#pragma once

class GameLog
{
private:
	CRITICAL_SECTION m_Lock;
	CRITICAL_SECTION m_Lock2;
	tstring m_strLog;
public:
	//CWnd *m_pWndLoginLog;
	//CWnd *m_pWndGameLog;
	CListBox* m_pWndRobortLog;
	CListBox* m_pWndLoginLog;
	GameLog();
	~GameLog();

	static GameLog* Instance();
    void GameLogOut(TCHAR *pText);
	void GameLogOut2(TCHAR* pText);
};