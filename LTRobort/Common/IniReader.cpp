#include "IniReader.h"
#include "Util.h"
#include <assert.h>

namespace Util {
#define GT_INVALID -1
//-----------------------------------------------------------------------------
//!	construction
//-----------------------------------------------------------------------------
IniReader::IniReader()
{
	m_mapOffset.clear();
	m_mapSectionName.clear();
	m_pData = NULL;
	m_dwDataSize = 0;
}

//-----------------------------------------------------------------------------
//!	destruction
//-----------------------------------------------------------------------------
IniReader::~IniReader()
{
	Unload();
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL IniReader::Load(PBYTE pRawData, DWORD dwDataLen)
{
	if( m_pData )
		Unload();

	if( -1 == dwDataLen || 0 == dwDataLen )
		return FALSE;

    LPCTSTR szText = Util::Unicode8ToUnicode( (const char*)pRawData );
    pRawData = (PBYTE)szText;
    dwDataLen = _tcslen(szText)*sizeof(TCHAR);

    m_dwDataSize = dwDataLen;
	m_pData = (BYTE*)malloc(dwDataLen+sizeof(TCHAR)*2);
	if( NULL == m_pData )
		return FALSE;

    memcpy( m_pData, pRawData, m_dwDataSize );

	// ���ļ������ӻس����з�(�ܶ��ļ���������0d0a����)
	*(DWORD*)( m_pData + m_dwDataSize ) = 0x0a000d00; // little-endian

	// ���濪ʼ��������INI,��¼�����м��ͼ�ֵ��ƫ��,������m_mapOffset
	std::map<DWORD, VEC_DWORD> mapOneSection;
	tstring strTemp, strSectionName;
	INT nSectionOffset = GT_INVALID, nValueOffset = GT_INVALID, nKeyOffset = 0; 
	INT	nKeySize = 0;
	INT nCommentStart = GT_INVALID;
	TCHAR* pChar = (TCHAR*)m_pData;

	for( DWORD n=0; n<(m_dwDataSize+4)/sizeof(TCHAR); n++ )
	{
		switch( *(pChar+n) )
		{
		case _T('['):	// ������Ϣ��ʼ
			if( GT_INVALID != nCommentStart )
				continue;
			if( false == strSectionName.empty() )
			{
				// ����һ�������Ϣ��������
                DWORD dwID = Util::Crc32( strSectionName.c_str() );
				// ����û���ظ���ID(���ʷǳ��ǳ�С������Ϊ������������Ǽ��һ��)
				assert( m_mapSectionName.find( dwID ) == m_mapSectionName.end() );
				m_mapSectionName.insert(
					std::pair<DWORD,tstring>(dwID, strSectionName) );
				m_mapOffset.insert( 
					std::pair<DWORD, MAP_VEC_DWORD>(dwID, mapOneSection) );
				mapOneSection.clear();
			}
			nSectionOffset = n+1;
			nKeyOffset = GT_INVALID;
			nValueOffset = GT_INVALID;
			break;

		case _T(']'):	// ������Ϣ����
			if( GT_INVALID != nCommentStart )
				continue;

			// ��¼���������
			if( nSectionOffset != GT_INVALID && n - nSectionOffset > 0 )
				strSectionName.assign(pChar+nSectionOffset,n-nSectionOffset);

			nSectionOffset = GT_INVALID;
			break;

		case _T('='):	// ����ֵ�ļ��
			if( GT_INVALID != nCommentStart )
				continue;
			if( GT_INVALID != nKeyOffset )
			{
				if( n - nKeyOffset > 0 )	// key�ĳ��Ȳ���Ϊ��
				{
					nKeySize = n - nKeyOffset;
					nValueOffset = n+1;
				}
				else
					nKeyOffset = GT_INVALID;
			}
			break;

		case _T(';'):	// ����ע��
			nCommentStart = n;
			break;

		case 0x0a:	// ��β
			if( GT_INVALID != nKeyOffset && GT_INVALID != nValueOffset )
			{
				// ��¼���еļ���ֵ��ƫ����
				std::vector<DWORD> vecTemp;	// �洢һ���е����е�Ԫ���ƫ��
				vecTemp.push_back( nKeyOffset );
				vecTemp.push_back( nKeySize );
				vecTemp.push_back( nValueOffset );
				if( GT_INVALID != nCommentStart )
					vecTemp.push_back( nCommentStart - nValueOffset );
				else
					vecTemp.push_back( n-1 - nValueOffset );
				// ��
				strTemp.assign(pChar+nKeyOffset, nKeySize);
				// tab���ɿո�
				while( strTemp.find(_T('\t')) != strTemp.npos )
					strTemp.replace(strTemp.find(_T('\t')), 1, 1, _T(' '));
				// ȥ��ͷβ�Ŀո����id
				if( strTemp.find_first_not_of(_T(' ')) != -1 )
					strTemp.assign(strTemp,strTemp.find_first_not_of(_T(' ')),
						strTemp.find_last_not_of(_T(' '))-strTemp.find_first_not_of(_T(' '))+1);
                DWORD dwID = Util::Crc32((LPCTSTR)strTemp.c_str());
				// ����û���ظ���ID(���ʷǳ��ǳ�С������Ϊ������������Ǽ��һ��)
				assert( mapOneSection.find( dwID ) == mapOneSection.end() );
				mapOneSection.insert(std::pair<DWORD, VEC_DWORD>(dwID, vecTemp));
			}

			nSectionOffset = nValueOffset = GT_INVALID;
			nKeyOffset = n+1;
			nCommentStart = GT_INVALID;
			break;
		}
	}

	if( false == strSectionName.empty() )
	{
		// ����һ�������Ϣ��������
		DWORD dwID = Util::Crc32( strSectionName.c_str() );
		m_mapSectionName.insert(std::pair<DWORD,tstring>(dwID, strSectionName));
		m_mapOffset.insert(std::pair<DWORD, MAP_VEC_DWORD>(dwID, mapOneSection));
	}

	return TRUE;
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
VOID IniReader::Unload()
{
	free(m_pData);

	m_mapOffset.clear();
	m_mapSectionName.clear();
	m_pData = NULL;
	m_dwDataSize = 0;
}


//-----------------------------------------------------------------------------
//!\param dwSize ����value���ݴ�С
//!\return ָ��value���ݵ�PBYTEָ��
//-----------------------------------------------------------------------------
PBYTE IniReader::Read(DWORD& dwSize, LPCTSTR szKeyName, LPCTSTR szSectionName)
{
	assert( szKeyName );
	assert( szSectionName );

	if( NULL == m_pData )
		return NULL;

	std::map<DWORD, MAP_VEC_DWORD>::iterator it = m_mapOffset.begin();
	it = m_mapOffset.find(Util::Crc32(szSectionName));
	if( it == m_mapOffset.end() )
		return NULL;

	std::map<DWORD, VEC_DWORD>::iterator real_it;
	real_it = it->second.find(Util::Crc32(szKeyName));
	if( real_it == it->second.end() )
			return NULL;

	if( real_it->second.size() < 4 )	// ���������
		return NULL;

	// (real_it->second)[0]: key name offset
	// (real_it->second)[1]: key name size
	dwSize = (real_it->second)[3]*sizeof(TCHAR);	// (real_it->second)[3]: value size
	return (m_pData+(real_it->second)[2]*sizeof(TCHAR)); // (real_it->second)[2]: value offset
}

}	// namespace Util {
