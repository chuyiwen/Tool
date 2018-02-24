#pragma once

#include "FastDelegate.h"

namespace Tang {

typedef fastdelegate::FastDelegate0<DWORD>                                  FP0;
typedef fastdelegate::FastDelegate1<TCHAR const*,DWORD>                          FP1;
typedef fastdelegate::FastDelegate2<TCHAR const*,TCHAR const*,DWORD>                  FP2;
typedef fastdelegate::FastDelegate3<TCHAR const*,TCHAR const*,TCHAR const*,DWORD>          FP3;
typedef fastdelegate::FastDelegate4<TCHAR const*,TCHAR const*,TCHAR const*,TCHAR const*,DWORD>  FP4;

typedef fastdelegate::FastDelegate1<TCHAR const*,DWORD> UnHandleCommandExecuteFP;

struct IConsoleUI
{    
    virtual void    ClearText()             = 0;
    virtual void    DelFrontLine(int nLine) = 0;    
    virtual void    AddText(TCHAR const* szText) = 0;
    virtual int     GetLineNum()            = 0;
    virtual bool    IsShowLastLine()        = 0;
    virtual void    SetCurLine(int nLine)   = 0;    
};

class Console : public Tang::Singleton<Console>
{
public:
    Console();
    ~Console();
public:    
    bool RegisterCommand(TCHAR const* szCmd, FP0 fp, TCHAR const* szDesc);
    bool RegisterCommand(TCHAR const* szCmd, FP1 fp, TCHAR const* szDesc);
    bool RegisterCommand(TCHAR const* szCmd, FP2 fp, TCHAR const* szDesc);
    bool RegisterCommand(TCHAR const* szCmd, FP3 fp, TCHAR const* szDesc);
    bool RegisterCommand(TCHAR const* szCmd, FP4 fp, TCHAR const* szDesc);

    bool UnRegisterCommand(TCHAR const* szCmd, FP0 fp);
    bool UnRegisterCommand(TCHAR const* szCmd, FP1 fp);
    bool UnRegisterCommand(TCHAR const* szCmd, FP2 fp);
    bool UnRegisterCommand(TCHAR const* szCmd, FP3 fp);
    bool UnRegisterCommand(TCHAR const* szCmd, FP4 fp);

    DWORD Execute(TCHAR const* szCommand);
    void  Print(TCHAR const* szText, ...);
    void  Watch(TCHAR const* szName, DWORD dwValue);

    void  SetUIInterface(IConsoleUI* pUI) { m_pUI = pUI; }
    void  SetUnHandleCommandProc(UnHandleCommandExecuteFP fp) { m_fpUnHandleCommand = fp; }
    
    struct WatchItem
    {
        tstring strName;
        DWORD   dwValue;
    };
    typedef std::vector<WatchItem> WatchItemList;
    const WatchItemList& GetWatchItemList() { return m_lstWatchItem; }
private:
    void  EnterLock();
    void  LeaveLock();
private:

    std::map<DWORD,FP0> m_mapCmdFP0;
    std::map<DWORD,FP1> m_mapCmdFP1;
    std::map<DWORD,FP2> m_mapCmdFP2;
    std::map<DWORD,FP3> m_mapCmdFP3;
    std::map<DWORD,FP4> m_mapCmdFP4;

    std::list<tstring>  m_lstAllCmd;

    UnHandleCommandExecuteFP m_fpUnHandleCommand;
private:
    IConsoleUI*         m_pUI;
    int                 m_nMaxLine;

    CRITICAL_SECTION    m_Lock;
    WatchItemList       m_lstWatchItem;
};

}; //namespace Tang

#define CONSOLE_TRACE Tang::Console::GetSingleton().Print