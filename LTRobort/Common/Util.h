#pragma once
#include <tchar.h>
#include <string>
#include <vector>

namespace Util
{
typedef unsigned int	uint32_t;
typedef int				int32_t;
typedef unsigned short  uint16_t;
typedef short			int16_t;
typedef unsigned char	uint8_t;
typedef char			int8_t;

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

// ����32λCRC,�㷨����
uint32_t	Crc32(char const* lpData);	// ר���������ַ���
uint32_t	Crc32(wchar_t const* pData);	// ר���������ַ���
uint32_t	Crc32(uint8_t* pData, int32_t nByteCount);

// unicode��unicode8ת��
// ʹ��ʱע��ʹ�õ��ǹ���buff,�����ε��ú����ݸ���
char    const*	UnicodeToUnicode8(wchar_t const* szSrc, char* szOut=NULL);
wchar_t const*	Unicode8ToUnicode(char const* szSrc, wchar_t* szOut=NULL);
char    const*	UnicodeToAnsi(wchar_t const* szSrc);
wchar_t const*	AnsiToUnicode(char const* szSrc);

// ȥ��tstring��β�Ŀո�
void CutSpaceOfStringHeadAndTail(tstring& string);
// �������ַ�תΪtoken;
void StringToToken(std::vector<tstring>& token, TCHAR const* szString, TCHAR chSeparator=_T(' '));

enum ECurDirMode
{
	ECDM_Exe,
	ECDM_Parent
};
void SetCurDir(ECurDirMode mode);
TCHAR const* GetCurDir();

void MakeDirForFile(tstring const& path);

void ThrowException(TCHAR const* szText, ...);

}; // namespace Util