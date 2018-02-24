#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>

namespace Util 
{
#ifdef _UNICODE
    typedef std::wstring tstring;
#else
    typedef std::string tstring;
#endif

class IniReader
{
public:
	BOOL Load(PBYTE pRawData, DWORD dwDataLen);
	VOID Unload();

	PBYTE Read(DWORD& dwSize, LPCTSTR szKeyName, LPCTSTR szSectionName);

	IniReader();
    ~IniReader();

private:
	typedef std::vector<DWORD>	VEC_DWORD;
	typedef	std::map<DWORD, VEC_DWORD>	MAP_VEC_DWORD;

	std::map<DWORD, MAP_VEC_DWORD>	m_mapOffset;
	std::map<DWORD, tstring>		m_mapSectionName;
	PBYTE							m_pData; //!< ini 数据块
	DWORD							m_dwDataSize; //!< ini 数据块大小

};

}	// namespace Util
