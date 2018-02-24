//-----------------------------------------------------------------------------
// File: CPKFast.cpp
// Desc: game resource file system 1.0
// Time: 2003-1-2
// Auth: CTCRST
//
//-----------------------------------------------------------------------------
#include "..\stdafx.h"
#include "cpkdefine.h"
// ��̳�(�����ӿ�)
#include "package.h"
#include "cpkfast.h"

// ʹ����������
#include "..\filter\filtermgr.h"
#include "..\system\disciomgr.h"
#include "..\memory\mem_pool.h"

struct CPKFile
{
	tagCPKTable* pTableItem;	// ָ��������

	// memory
	PVOID	lpMapAddress;	// Map��ʼλ��
	PVOID	lpStartAddress;	// Map�е��ļ���ʼλ��
	DWORD	dwOffset;		// ʵ��Map��ʼ��ַ���ļ���ʼ��ַ��ƫ��
	PVOID	lpMem;			// ָ���ļ�ʵ������

	// for seek/tell
	DWORD	dwFileSize;		// �ļ�ʵ�����ݴ�С
	DWORD	dwPointer;		// �ļ�ָ��

	BOOL	bCompressed;	// �ļ��Ƿ�ѹ��
	BOOL	bValid;			// �Ƿ���Ч
};


//-----------------------------------------------------------------------------
// CPK construction / destruction
//-----------------------------------------------------------------------------
CPK::CPK()
{
	ZeroMemory(&m_CPKHeader, sizeof(m_CPKHeader));

	m_pCPKTable = NULL;	// ʹ��ָ��,���⹹�캯��ѹ������
	m_bLoaded = FALSE;
	m_dwAllocGranularity = 0;
	m_dwCPKHandle = INVALID_FILE_HANDLE;
	m_dwCPKMappingHandle = INVALID_FILEMAP_HANDLE;
	m_nOpenedFileNum = 0;

	SYSTEM_INFO si;
	::GetSystemInfo(&si);
	m_dwAllocGranularity = si.dwAllocationGranularity;

	m_pMemPool = new SafeMemPool(8*1024*1024);
}

CPK::~CPK()
{
	Unload();
	SAFE_DEL(m_pMemPool);
}


//-----------------------------------------------------------------------------
// ����ѹ����
//-----------------------------------------------------------------------------
BOOL CPK::Load(LPCTSTR szFileName)
{
	SI_ASSERT(szFileName);
	m_strCPKFileName = szFileName;

	if( m_bLoaded )	// �������ͷ�������
		this->Unload();

	m_dwCPKHandle = m_pDiscIOMgr->Create(szFileName, GENERIC_READ,	// ֻ��
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);

	if( m_dwCPKHandle == INVALID_FILE_HANDLE )
		return FALSE;

	// �����ļ�ͷ
	m_pDiscIOMgr->Read(m_dwCPKHandle, &m_CPKHeader, sizeof(m_CPKHeader));
	
	// ����ļ���־
	if( m_CPKHeader.dwLable != GT_CPK_LABEL )
	{
		ERR(_T("Unknow file format %s"), szFileName);
		m_pDiscIOMgr->Close(m_dwCPKHandle);
		m_dwCPKHandle = INVALID_FILE_HANDLE;
		return FALSE;
	}

	// ����ļ��汾��
	if( m_CPKHeader.dwVersion != GT_CPK_VERSION )
	{
		ERR(_T("Wrong file version %lu"), m_CPKHeader.dwVersion);
		m_pDiscIOMgr->Close(m_dwCPKHandle);
		m_dwCPKHandle = INVALID_FILE_HANDLE;
		return FALSE;
	}

	// ����Table�ռ�
	m_pCPKTable = (tagCPKTable*)malloc(sizeof(tagCPKTable)*m_CPKHeader.dwMaxTableNum);

	if( !m_pCPKTable )
	{
		m_pDiscIOMgr->Close(m_dwCPKHandle);
		m_dwCPKHandle = INVALID_FILE_HANDLE;
		return FALSE;
	}

	// �����ļ�Table
	//��λ����λ��
	if( FALSE == m_pDiscIOMgr->Seek(m_dwCPKHandle, m_CPKHeader.dwTableStart) )
	{
		ERR(_T("Could not seek table from the CPK %s, seekpos=%ld"), \
			szFileName, m_CPKHeader.dwTableStart);

		return FALSE;
	}


	if( sizeof(tagCPKTable)*m_CPKHeader.dwMaxTableNum
		!= m_pDiscIOMgr->Read(m_dwCPKHandle, m_pCPKTable,
		sizeof(tagCPKTable)*m_CPKHeader.dwMaxTableNum) )
	{
		ERR(_T("could not load cpk %s table"), szFileName);
		m_pDiscIOMgr->Close(m_dwCPKHandle);
		m_dwCPKHandle = INVALID_FILE_HANDLE;
		free(m_pCPKTable);
		return FALSE;
	}


	// �����ļ�ӳ��
	m_dwCPKMappingHandle = m_pDiscIOMgr->CreateMapping(m_dwCPKHandle, NULL,
		PAGE_READONLY, 0, NULL);
	
	if( m_dwCPKMappingHandle == NULL )
	{
		//�޷�ӳ���ļ�,���ǽ���ȡ��ͨ��ʽ�����ļ�
		ERR(_T("couldn't create file mapping %s"), szFileName);
		//ת��Ϊ�ڲ�ר����Чӳ������ʶ
		m_dwCPKMappingHandle = INVALID_FILEMAP_HANDLE;
	}
	else
	{
		// �ļ�ӳ���Ѿ�����
		if( ::GetLastError() == ERROR_ALREADY_EXISTS )
		{
			ERR(_T("File mapping %s has already exist"), szFileName);
			m_pDiscIOMgr->CloseMappingHandle(m_dwCPKMappingHandle);
			m_dwCPKMappingHandle = INVALID_FILEMAP_HANDLE;
			m_pDiscIOMgr->Close(m_dwCPKHandle);
			m_dwCPKHandle = INVALID_FILE_HANDLE;
			free(m_pCPKTable);
			return FALSE;
		}
	}


	m_bLoaded = TRUE;
	return TRUE;
}




//-----------------------------------------------------------------------------
// ж��ѹ����
//-----------------------------------------------------------------------------
BOOL CPK::Unload()
{
	if( m_bLoaded )
	{
		SI_ASSERT(m_nOpenedFileNum == 0);	// ȷ�������ļ��Ѿ��ر�
	
		// �ر��ļ�ӳ����
		if( m_dwCPKMappingHandle != INVALID_FILEMAP_HANDLE )
		{
			m_pDiscIOMgr->CloseMappingHandle(m_dwCPKMappingHandle);
			m_dwCPKMappingHandle = INVALID_FILEMAP_HANDLE;
		}
		
		// �ر�CPK�ļ����
		m_pDiscIOMgr->Close(m_dwCPKHandle);
		m_dwCPKHandle = INVALID_FILE_HANDLE;

		ZeroMemory(&m_CPKHeader, sizeof(m_CPKHeader));
		free(m_pCPKTable);
		m_pCPKTable = NULL;

		m_strCPKFileName.clear();
		m_nOpenedFileNum = 0;

		m_bLoaded = FALSE;
		return TRUE;	// unload succeed
	}

	return FALSE; // nothing to unload
}




//-----------------------------------------------------------------------------
// �򿪰��еĵ����ļ�, ���ҽ����ļ�ӳ�䣬���ص����ļ����
//-----------------------------------------------------------------------------
DWORD CPK::Open(LPCTSTR szFileName)
{
	SI_ASSERT(szFileName);

	// û���κ�CPK�ļ�����
	if( FALSE == m_bLoaded )
		return GT_INVALID;

	// �ҵ��ļ���Ӧ��CPK�еı���
	INT nTableIndex = this->GetTableIndex(szFileName);
	if( nTableIndex == GT_INVALID )
		return GT_INVALID;

	if( m_dwCPKMappingHandle != INVALID_FILEMAP_HANDLE )
	{
		DWORD dwHandle = OpenForMap(nTableIndex, szFileName);
		if( dwHandle )
			return dwHandle;
	}

	return OpenForCommon(nTableIndex, szFileName);
}



//-----------------------------------------------------------------------------
//�ļ�ӳ�䷽ʽ�򿪵����ļ�
//-----------------------------------------------------------------------------
DWORD CPK::OpenForMap(INT nTableIndex, LPCTSTR szFileName)
{
	// ����ļ�ӳ����
	SI_ASSERT(m_dwCPKMappingHandle != INVALID_FILEMAP_HANDLE); 

	// ����ʵ�ʿ�ʼӳ���λ��
	DWORD dwRealStartPos = m_pCPKTable[nTableIndex].dwStartPos;
	dwRealStartPos = dwRealStartPos - (dwRealStartPos % m_dwAllocGranularity);

	// ʵ��ӳ������Ҫӳ��λ�õ�ƫ��
	DWORD dwOffset = m_pCPKTable[nTableIndex].dwStartPos - dwRealStartPos;

	// ������Ҫӳ����ֽ�
	DWORD dwBytesToRead = m_pCPKTable[nTableIndex].dwPackedSize
		+ m_pCPKTable[nTableIndex].dwExtraInfoSize + dwOffset;

	// �����ļ�����
	CPKFile* fp = (CPKFile*)m_pMemPool->Alloc(sizeof(CPKFile));
	if( !fp )
	{
		ERR(_T("could not malloc for fp in %s"), m_strCPKFileName.c_str());
		return NULL;
	}

	fp->bValid = TRUE;
	fp->lpMapAddress = NULL;

	// ӳ��
	fp->lpMapAddress = m_pDiscIOMgr->MapFile
			(m_dwCPKMappingHandle, FILE_MAP_READ, dwRealStartPos, dwBytesToRead);
	
	if( fp->lpMapAddress == NULL )
	{
		ERR(_T("could not map file %s\r\ncpk:%s, start pos:%lu, bytes:%lu"), 
			szFileName, m_strCPKFileName.c_str(), dwRealStartPos, dwBytesToRead);

		fp->bValid = FALSE;
		m_pMemPool->Free(fp);
		return NULL;
	}


	// ��дfp������Ϣ
	fp->pTableItem = &m_pCPKTable[nTableIndex];
	fp->lpStartAddress = (LPVOID)((BYTE*)fp->lpMapAddress + dwOffset);
	fp->bCompressed = IS_COMPRESSED( m_pCPKTable[nTableIndex].dwFlag );
	fp->dwFileSize = m_pCPKTable[nTableIndex].dwOriginSize;
	fp->dwOffset = dwOffset;
	fp->dwPointer = 0;	// �ļ�ָ���ʼ

	SI_ASSERT( fp->dwFileSize>= 0 && fp->dwFileSize<0x40000000 );

	// �����ѹ���ļ�������Ҫ�Ƚ�ѹ��
	if( fp->bCompressed == TRUE && fp->dwFileSize > 0 )
	{
		// Ϊ��ѹ�����ڴ�
		fp->lpMem = m_pMemPool->Alloc(fp->dwFileSize);
		if( fp->lpMem == NULL )
		{
			m_pDiscIOMgr->UnMapFile(fp->lpMapAddress);
			fp->bValid = FALSE;
			m_pMemPool->Free(fp);
			return NULL;
		}

		// �����ˣ���ѹ���ļ�
		tagFilterParam param;
		param.bCompress = FALSE;
		param.bSuccess = FALSE;
		param.dwInBufferSize = m_pCPKTable[nTableIndex].dwPackedSize;
		param.dwInDataSize = m_pCPKTable[nTableIndex].dwPackedSize;
		param.dwOutBufferSize = m_pCPKTable[nTableIndex].dwOriginSize;
		param.dwOutDataSize = m_pCPKTable[nTableIndex].dwOriginSize;
		param.eFilter = GET_FILTER(m_pCPKTable[nTableIndex].dwFlag);
		param.lpMemIn = fp->lpStartAddress;
		param.lpMemOut = fp->lpMem;

		// ���й����ļ���Ϣ
		m_pFilterMgr->Filter(&param);

		if( FALSE == param.bSuccess )
		{
			ERR(_T("could not decompress"));
			m_pDiscIOMgr->UnMapFile(fp->lpMapAddress);
			m_pMemPool->Free(fp->lpMem);
			fp->bValid = FALSE;
			m_pMemPool->Free(fp);
			return NULL;
		}
	}
	else	// ����ļ�û�б�ѹ����
	{
		// ����ָ��Map�е��ļ�ʵ����ʼ��ַ
		fp->lpMem = fp->lpStartAddress;
	}

	::InterlockedIncrement((LONG*)&m_nOpenedFileNum);

	return (DWORD)fp;
}



//-----------------------------------------------------------------------------
//��ͨ��ʽ�򿪵����ļ�
//-----------------------------------------------------------------------------
DWORD CPK::OpenForCommon(INT nTableIndex, LPCTSTR szFileName)
{
	// �����ļ�����
	CPKFile* fp = (CPKFile*)m_pMemPool->Alloc(sizeof(CPKFile));
	if( !fp )
	{
		ERR(_T("could not malloc for fp in %s"), m_strCPKFileName.c_str());
		return NULL;
	}

	// ��дfp������Ϣ
	fp->bValid = TRUE;
	fp->lpMapAddress = NULL;
	fp->pTableItem = &m_pCPKTable[nTableIndex];
	fp->lpStartAddress = NULL;
	fp->bCompressed = IS_COMPRESSED( m_pCPKTable[nTableIndex].dwFlag );
	fp->dwFileSize = m_pCPKTable[nTableIndex].dwOriginSize;
	fp->dwOffset = 0;
	fp->dwPointer = 0;	// �ļ�ָ���ʼ

	SI_ASSERT( fp->dwFileSize>= 0 && fp->dwFileSize<0x40000000 );

	//�����ڴ�洢��ʼѹ���ļ�����
	LPVOID lpPackMem = m_pMemPool->Alloc(m_pCPKTable[nTableIndex].dwPackedSize);
	if( lpPackMem == NULL )
	{
		fp->bValid = FALSE;
		m_pMemPool->Free(fp);
		return NULL;
	}

	if( 0 == m_pDiscIOMgr->Seek(m_dwCPKHandle, m_pCPKTable[nTableIndex].dwStartPos) )
	{
		ERR(_T("could not read cpk file"));

		m_pMemPool->Free(lpPackMem);
		fp->bValid = FALSE;
		m_pMemPool->Free(fp);
		return NULL;
	}
	if( 0 == m_pDiscIOMgr->Read(m_dwCPKHandle, lpPackMem, m_pCPKTable[nTableIndex].dwPackedSize) )
	{
		ERR(_T("could not read cpk file"));

		m_pMemPool->Free(lpPackMem);
		fp->bValid = FALSE;
		m_pMemPool->Free(fp);
		return NULL;
	}

	// �����ѹ���ļ�������Ҫ�Ƚ�ѹ��
	if( fp->bCompressed == TRUE && fp->dwFileSize > 0 )
	{

		// Ϊ��ѹ���������ļ����������ڴ�
		fp->lpMem = m_pMemPool->Alloc(fp->dwFileSize);
		if( fp->lpMem == NULL )
		{
			fp->bValid = FALSE;
			m_pMemPool->Free(lpPackMem);
			m_pMemPool->Free(fp);
			return NULL;
		}

		// �����ˣ���ѹ���ļ�
		tagFilterParam param;
		param.bCompress = FALSE;
		param.bSuccess = FALSE;
		param.dwInBufferSize = m_pCPKTable[nTableIndex].dwPackedSize;
		param.dwInDataSize = m_pCPKTable[nTableIndex].dwPackedSize;
		param.dwOutBufferSize = m_pCPKTable[nTableIndex].dwOriginSize;
		param.dwOutDataSize = m_pCPKTable[nTableIndex].dwOriginSize;
		param.eFilter = GET_FILTER(m_pCPKTable[nTableIndex].dwFlag);
		param.lpMemIn = lpPackMem;
		param.lpMemOut = fp->lpMem;

		// ���й����ļ���Ϣ
		m_pFilterMgr->Filter(&param);

		//�ͷų�ʼѹ���ļ�����֮�ڴ�
		m_pMemPool->Free(lpPackMem);


		if( FALSE == param.bSuccess )
		{
			ERR(_T("could not decompress"));
			m_pMemPool->Free(fp->lpMem);
			fp->bValid = FALSE;
			m_pMemPool->Free(fp);
			return NULL;
		}
	}
	else	// ����ļ�û�б�ѹ����
	{
		// ����ָ���ʼ�ļ����ݴ洢�ĵ�ַ
		fp->lpMem = lpPackMem;
	}

	::InterlockedIncrement((LONG*)&m_nOpenedFileNum);

	return (DWORD)fp;
}


//-----------------------------------------------------------------------------
// �رհ��еĵ����ļ�, ����ȡ���ļ�ӳ�䣬�������ļ����
//-----------------------------------------------------------------------------
BOOL CPK::Close(DWORD dwHandle)
{
	CPKFile* fp = (CPKFile*)dwHandle;
	SI_ASSERT(fp != NULL);
	SI_ASSERT(fp->bValid == TRUE);

	if( fp->lpMapAddress == 0 )
	{
		if( fp->lpMem != NULL )
		{
			//����ͨ�ļ���ȡ��ʽ
			m_pMemPool->Free(fp->lpMem);
		}
		else
		{
			ERR(_T("invalid address in cpk close"));
			return FALSE;
		}
	}
	else 
	{
		BOOL bResult = m_pDiscIOMgr->UnMapFile(fp->lpMapAddress);
		if( FALSE == bResult )
		{
			ERR(_T("could not unmap file in cpk close"));
			fp->bValid = FALSE;
			return FALSE;
		}
		
		if( fp->bCompressed && fp->dwFileSize > 0 )
			m_pMemPool->Free(fp->lpMem);
	}

	m_pMemPool->Free(fp);
	::InterlockedDecrement((LONG*)&m_nOpenedFileNum);

	return TRUE;
}



//-----------------------------------------------------------------------------
// �����е����ļ�������
//-----------------------------------------------------------------------------
DWORD CPK::Read(LPVOID lpMemOut, DWORD dwSize, DWORD dwHandle)
{
	CPKFile* fp = (CPKFile*)dwHandle;
	SI_ASSERT(fp != NULL);
	SI_ASSERT(fp->bValid);

	if( fp->dwPointer >= fp->dwFileSize )	// �ļ�ָ���Ѿ����ļ�β
		return 0;
	
	if( fp->dwPointer + dwSize > fp->dwFileSize )
		dwSize = fp->dwFileSize -  fp->dwPointer;

	memcpy(lpMemOut, (BYTE*)fp->lpMem + fp->dwPointer, dwSize);
	fp->dwPointer += dwSize;

	// ���뷵��ʵ��"�ɹ�"��ȡ���ֽ���
	return dwSize;
}



//-----------------------------------------------------------------------------
// ��λ���е����ļ���ָ��,���ص�ǰ�ļ�ָ��λ��
//-----------------------------------------------------------------------------
DWORD CPK::Seek(DWORD dwHandle, INT nOffset, DWORD dwOrigin)
{
	CPKFile* fp = (CPKFile*)dwHandle;
	SI_ASSERT( fp != NULL );
	SI_ASSERT( fp->bValid );

	switch( dwOrigin )
	{
	case GT_SEEK_SET:
		fp->dwPointer = nOffset;
		break;
	case GT_SEEK_CUR:
		fp->dwPointer += nOffset;
		break;
	case GT_SEEK_END:
		fp->dwPointer = fp->dwFileSize + nOffset;
		break;
	default:
		SI_ASSERT(0);
		return (DWORD)GT_INVALID;		
	}

	return fp->dwPointer;
}


//-----------------------------------------------------------------------------
// ���ص�ǰ�ļ�ָ��λ��
//-----------------------------------------------------------------------------
DWORD CPK::Tell(DWORD dwHandle)
{ 
	return ((CPKFile*)dwHandle)->dwPointer; 
}


//-----------------------------------------------------------------------------
// �����е����ļ���ȫ�����ݣ�������Ŀ���ڴ��С������ԭ�ļ��ֽڴ�С
//-----------------------------------------------------------------------------
DWORD CPK::LoadFile(LPVOID lpMemOut, LPCTSTR szFileName)
{
	SI_ASSERT(szFileName);

	// û���κ�CPK�ļ�����
	if( m_bLoaded == FALSE )
	{
		ERR(_T("no cpk loaded"));
		return (DWORD)GT_INVALID;
	}
	
	// �ҵ��ļ���Ӧ��CPK�еı���
	INT nTableIndex = this->GetTableIndex(szFileName);
	if( nTableIndex == GT_INVALID )
	{
		if( NULL != lpMemOut )	// �ⲿֻ����ȡ���ļ���С���򲻲���������ʾ
		{
			ERR(_T("could not find file %s in cpk"), szFileName);
		}

		return (DWORD)GT_INVALID;
	}

	// ����ڴ�Ŀ��Ϊ�գ��ͽ�����ԭ�ļ���С
	if( lpMemOut == NULL )
		return m_pCPKTable[nTableIndex].dwOriginSize;

	BOOL bCompressed = IS_COMPRESSED( m_pCPKTable[nTableIndex].dwFlag );


	// �ļ�ӳ�����Ƿ�
	if( m_dwCPKMappingHandle != INVALID_FILEMAP_HANDLE)
	{
		// ����ʵ�ʿ�ʼӳ���λ��
		DWORD dwRealStartPos = m_pCPKTable[nTableIndex].dwStartPos;
		dwRealStartPos = dwRealStartPos - (dwRealStartPos % m_dwAllocGranularity);

		// ʵ��ӳ������Ҫӳ��λ�õ�ƫ��
		DWORD dwOffset = m_pCPKTable[nTableIndex].dwStartPos - dwRealStartPos;
		
		// ������Ҫӳ����ֽ�
		DWORD dwBytesToRead = m_pCPKTable[nTableIndex].dwPackedSize
			+ m_pCPKTable[nTableIndex].dwExtraInfoSize + dwOffset;
		
		// ӳ��
		VOID* lpMapAddress = m_pDiscIOMgr->MapFile
			(m_dwCPKMappingHandle, FILE_MAP_READ, dwRealStartPos, dwBytesToRead);

		if( lpMapAddress == NULL )
			goto __DiscIOMgr;
		
		// �����ˣ���ѹ���ļ�
		tagFilterParam param;
		param.bCompress = FALSE;
		param.bSuccess = FALSE;
		param.dwInBufferSize = m_pCPKTable[nTableIndex].dwPackedSize;
		param.dwInDataSize = m_pCPKTable[nTableIndex].dwPackedSize;
		param.dwOutBufferSize = m_pCPKTable[nTableIndex].dwOriginSize;
		param.dwOutDataSize = m_pCPKTable[nTableIndex].dwOriginSize;
		param.eFilter = GET_FILTER( m_pCPKTable[nTableIndex].dwFlag );
		param.lpMemIn = (BYTE*)lpMapAddress + dwOffset;
		param.lpMemOut = lpMemOut;

		// �����ļ���Ϣ
		m_pFilterMgr->Filter(&param);
		if( param.bSuccess == FALSE )
		{
			ERR(_T("decompress failed in cpk loadfile"));
			m_pDiscIOMgr->UnMapFile(lpMapAddress);
			return (DWORD)GT_INVALID;
		}

		// ���ӳ��
		if( m_pDiscIOMgr->UnMapFile(lpMapAddress) == FALSE )
		{
			ERR(_T("ummap failed in cpk loadfile"));
			return (DWORD)GT_INVALID;
		}
	}
	else
	{
__DiscIOMgr:
		if( 0 == m_pDiscIOMgr->Seek(m_dwCPKHandle, m_pCPKTable[nTableIndex].dwStartPos) )
		{
			ERR(_T("could not read cpk file"));
			return (DWORD)GT_INVALID;
		}

		// �����ѹ���ļ�������Ҫ�Ƚ�ѹ��
		if( bCompressed == TRUE && m_pCPKTable[nTableIndex].dwOriginSize > 0 )
		{

			// Ϊ��ѹ���������ļ����������ڴ�
			LPVOID lpPackMem = m_pMemPool->Alloc(m_pCPKTable[nTableIndex].dwPackedSize);
			if( lpPackMem == NULL )
			{
				return (DWORD)GT_INVALID;
			}

			if( 0 == m_pDiscIOMgr->Read(m_dwCPKHandle, lpPackMem, 
						m_pCPKTable[nTableIndex].dwPackedSize) )
			{
				ERR(_T("could not read cpk file"));
				m_pMemPool->Free(lpPackMem);

				return (DWORD)GT_INVALID;
			}

			// �����ˣ���ѹ���ļ�
			tagFilterParam param;
			param.bCompress = FALSE;
			param.bSuccess = FALSE;
			param.dwInBufferSize = m_pCPKTable[nTableIndex].dwPackedSize;
			param.dwInDataSize = m_pCPKTable[nTableIndex].dwPackedSize;
			param.dwOutBufferSize = m_pCPKTable[nTableIndex].dwOriginSize;
			param.dwOutDataSize = m_pCPKTable[nTableIndex].dwOriginSize;
			param.eFilter = GET_FILTER(m_pCPKTable[nTableIndex].dwFlag);
			param.lpMemIn = lpPackMem;
			param.lpMemOut = lpMemOut;

			// ���й����ļ���Ϣ
			m_pFilterMgr->Filter(&param);

			//�ͷų�ʼѹ���ļ�����֮�ڴ�
			m_pMemPool->Free(lpPackMem);


			if( FALSE == param.bSuccess )
			{
				ERR(_T("could not decompress"));
				return (DWORD)GT_INVALID;
			}
		}
		else	// ����ļ�û�б�ѹ����
		{
			if( 0 == m_pDiscIOMgr->Read(m_dwCPKHandle, lpMemOut, 
				m_pCPKTable[nTableIndex].dwPackedSize) )
			{
				ERR(_T("could not read cpk file"));
				return (DWORD)GT_INVALID;
			}
		}

	}

	return m_pCPKTable[nTableIndex].dwOriginSize;
}




//-----------------------------------------------------------------------------
// �����ļ����ҵ���Ӧ�ı���
//-----------------------------------------------------------------------------
INT CPK::GetTableIndex(LPCTSTR pFullName)
{
	TCHAR szFullName[MAX_PATH];

	// ���ļ���ת��ΪСд�ټ���CRC
	lstrcpy(szFullName, pFullName);
	_tcslwr(szFullName);
	
	INT i = 0;
	while( i<MAX_PATH && szFullName[i] != _T('\0') )
	{
		if( szFullName[i] == _T('/') )
			szFullName[i] = _T('\\');
		i++;
	}


	CHAR szFullName8[MAX_PATH];
	INT nLen = WideCharToMultiByte(CP_ACP, 0, szFullName, -1, szFullName8, MAX_PATH, NULL, NULL);

	DWORD dwCRC = m_pUtil->Crc32((LPBYTE)szFullName8, nLen-1);
	return GetTableIndexFromCRC(dwCRC);
}


//-----------------------------------------------------------------------------
// ��CRC�ҵ���Ӧ����
//-----------------------------------------------------------------------------
INT CPK::GetTableIndexFromCRC(DWORD dwCRC)
{
	// ��һ����ͬ��CRC����Ч��CRC�϶������
	// ���ֲ���
	INT nStart = 0, nEnd = m_CPKHeader.dwValidTableNum;
	INT nPos = 0;
	
	while( nEnd != nStart )
	{
		nPos = nStart + (nEnd-nStart)/2;
		if( dwCRC == m_pCPKTable[nPos].dwCRC
			&& IS_FILE_OR_DIR_VALID(m_pCPKTable[nPos].dwFlag) ) 
			return nPos;

		if( nEnd == nStart+1 )
			return GT_INVALID;

		if( dwCRC >=  m_pCPKTable[nPos].dwCRC )
			nStart = nPos;
		else
			nEnd = nPos;
	}

	return GT_INVALID;
}