#include "stdafx.h"
#include "Console.h"

namespace Tang {

Console::Console()
: m_nMaxLine( 500 )
{
    ::InitializeCriticalSection( &m_Lock );
}

Console::~Console()
{
    DeleteCriticalSection( &m_Lock );
}

bool Console::RegisterCommand(TCHAR const* szCmd, FP0 fp, TCHAR const* szDesc)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP0.find(dwID) != m_mapCmdFP0.end() && m_mapCmdFP0[dwID] != fp )
    {
        Print( _T("warning!!!:\r\nCommand %s register twice use different handler..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP0[dwID] = fp;
    return true;
}

bool Console::RegisterCommand(TCHAR const* szCmd, FP1 fp, TCHAR const* szDesc)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP1.find(dwID) != m_mapCmdFP1.end() && m_mapCmdFP1[dwID] != fp )
    {
        Print( _T("warning!!!:\r\nCommand %s register twice use different handler..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP1[dwID] = fp;
    return true;
}

bool Console::RegisterCommand(TCHAR const* szCmd, FP2 fp, TCHAR const* szDesc)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP2.find(dwID) != m_mapCmdFP2.end() && m_mapCmdFP2[dwID] != fp )
    {
        Print( _T("warning!!!:\r\nCommand %s register twice use different handler..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP2[dwID] = fp;
    return true;
}

bool Console::RegisterCommand(TCHAR const* szCmd, FP3 fp, TCHAR const* szDesc)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP3.find(dwID) != m_mapCmdFP3.end() && m_mapCmdFP3[dwID] != fp )
    {
        Print( _T("warning!!!:\r\nCommand %s register twice use different handler..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP3[dwID] = fp;
    return true;
}

bool Console::RegisterCommand(TCHAR const* szCmd, FP4 fp, TCHAR const* szDesc)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP4.find(dwID) != m_mapCmdFP4.end() && m_mapCmdFP4[dwID] != fp )
    {
        Print( _T("warning!!!:\r\nCommand %s register twice use different handler..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP4[dwID] = fp;
    return true;
}

bool Console::UnRegisterCommand(TCHAR const* szCmd, FP0 fp)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP0.find(dwID) == m_mapCmdFP0.end() )
    {
        Print( _T("warning!!!:\r\nCommand %s has not register yet..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP0.erase(dwID);
    return true;
}
bool Console::UnRegisterCommand(TCHAR const* szCmd, FP1 fp)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP1.find(dwID) == m_mapCmdFP1.end() )
    {
        Print( _T("warning!!!:\r\nCommand %s has not register yet..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP1.erase(dwID);
    return true;
}
bool Console::UnRegisterCommand(TCHAR const* szCmd, FP2 fp)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP2.find(dwID) == m_mapCmdFP2.end() )
    {
        Print( _T("warning!!!:\r\nCommand %s has not register yet..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP2.erase(dwID);
    return true;
}
bool Console::UnRegisterCommand(TCHAR const* szCmd, FP3 fp)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP3.find(dwID) == m_mapCmdFP3.end() )
    {
        Print( _T("warning!!!:\r\nCommand %s has not register yet..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP3.erase(dwID);
    return true;
}
bool Console::UnRegisterCommand(TCHAR const* szCmd, FP4 fp)
{
    if ( !szCmd ) 
        return false;

    tstring strCmd = szCmd;
    transform( strCmd.begin(), strCmd.end(), strCmd.begin(), tolower );
	DWORD dwID = Tang::f_util::get_crc( strCmd.c_str() );	// 转为小写再运算

    if ( m_mapCmdFP4.find(dwID) == m_mapCmdFP4.end() )
    {
        Print( _T("warning!!!:\r\nCommand %s has not register yet..."), szCmd );
        SI_ASSERT(0);
    }
    
    m_mapCmdFP4.erase(dwID);
    return true;
}

DWORD Console::Execute(TCHAR const* szCommand)
{
	std::vector<tstring> command;
	Tang::f_util::token_string(command, szCommand);
	command.resize(10);	// 不可能超过10个参数
	std::vector<TCHAR const*> vp;

	if( command.size() == 0 )
		return INVALID;

	// 得到实际的参数
	for( int n=0; n<(int)command.size(); n++ )
		vp.push_back(command[n].c_str());

	transform(command[0].begin(), command[0].end(), command[0].begin(), tolower);	
	DWORD dwID = Tang::f_util::get_crc(command[0].c_str());	// 转为小写再运算

    DWORD dwRet = INVALID;
    if ( m_mapCmdFP0.find(dwID) != m_mapCmdFP0.end() )    
        dwRet = m_mapCmdFP0[dwID]();
    else if ( m_mapCmdFP1.find(dwID) != m_mapCmdFP1.end() )
    {
        if( vp.size() <= 2 )
            dwRet = m_mapCmdFP1[dwID]( vp[1] );
        else
        {
            tstring strParam;	// 组合所有参数成一个
            for(int n=1; n<(int)vp.size(); n++)
            {
                strParam += (TCHAR const*)(vp[n]);
                strParam += _T(" ");
            }
            dwRet = m_mapCmdFP1[dwID]( strParam.c_str() );            
        }        
    }        
    else if ( m_mapCmdFP2.find(dwID) != m_mapCmdFP2.end() )
        dwRet = m_mapCmdFP2[dwID]( vp[1], vp[2] );
    else if ( m_mapCmdFP3.find(dwID) != m_mapCmdFP3.end() )
        dwRet = m_mapCmdFP3[dwID]( vp[1], vp[2], vp[3] );
    else if ( m_mapCmdFP4.find(dwID) != m_mapCmdFP4.end() )
        dwRet = m_mapCmdFP4[dwID]( vp[1], vp[2], vp[3], vp[4] );
    else
    {
        if ( m_fpUnHandleCommand )
            return m_fpUnHandleCommand( szCommand );

        command[0].append( _T(" is unknow command\r\n"));
        Print( command[0].c_str() );
        return INVALID;
    }

    if( command[0] != _T("cls") )	// cls 不显示返回值
    {
        tstringstream stream;
        stream << command[0] << _T(" returned ") << dwRet << std::endl;
        Print( stream.str().c_str() );        
    }

    return dwRet;
}

void Console::Print(TCHAR const* szText, ...)
{
	if( !m_pUI )
		return;

    // 格式化字符串
	TCHAR szTextBuf[4096];
	memset( szTextBuf, 0, sizeof(szTextBuf) );
	va_list argptr = NULL;
	va_start( argptr, szText );
	_vstprintf_s( szTextBuf, sizeof(szTextBuf)/sizeof(TCHAR), szText, argptr );
	va_end( argptr );

	// 在此进入锁定区
	this->EnterLock();
	// ----------------------------------
	bool bShow = m_pUI->IsShowLastLine();
	m_pUI->AddText( szTextBuf );
	// 如果行数超过限制就删除前面的行，删除一半
	if( m_pUI->GetLineNum() > m_nMaxLine )
		m_pUI->DelFrontLine( m_nMaxLine / 2 );

	if( bShow )
		m_pUI->SetCurLine( 0xffffff );	// 卷到最后行
	// ----------------------------------
	this->LeaveLock();

}

void Console::Watch(TCHAR const* szName, DWORD dwValue)
{
    // 已有的记录则更新值
    for ( int i = 0; i < m_lstWatchItem.size(); ++i )
    {
        if ( m_lstWatchItem[i].strName == szName )
        {
            m_lstWatchItem[i].dwValue = dwValue;
            return;
        }
    }

    // 添加新项
    m_lstWatchItem.resize( m_lstWatchItem.size() + 1 );
    m_lstWatchItem.back().strName = szName;
    m_lstWatchItem.back().dwValue = dwValue;    
}

void Console::EnterLock()
{
    EnterCriticalSection( &m_Lock );
}

void Console::LeaveLock()
{
    LeaveCriticalSection( &m_Lock );
}

}; //namespace Tang