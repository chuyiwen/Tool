/*******************************************************************************

	Copyright 2010 by Shengshi Interactive Game Co., Ltd.
	All rights reserved.
	
	This software is the confidential and proprietary information of
	Shengshi Interactive Game Co., Ltd. ('Confidential Information'). You shall
	not disclose such Confidential Information and shall use it only in
	accordance with the terms of the license agreement you entered into with
	Shengshi Interactive  Co., Ltd.

*******************************************************************************/
/**
 *	@file		ClientPackage.cpp
 *	@author		zhaopeng
 *	@date		2011/03/11
 *	@version	
 *	@brief		
 */
#include "stdafx.h"
#include "ClientPackage.h"

#if defined(_DEBUG)
	#pragma comment(lib,"..\\..\\..\\vsout\\PackageLib\\Debug\\PackageLib.lib")
#else
	#pragma comment(lib,"..\\..\\..\\vsout\\PackageLib\\Release\\PackageLib.lib")
#endif

namespace Tang {

struct __FileTrack
{
	char*  data;
	size_t cur;
	size_t size;
};

ClientPackage::ClientPackage()
: m_opennum( 0 )
{
	InitializeCriticalSection( &m_cs );
}

ClientPackage::~ClientPackage()
{
	DeleteCriticalSection( &m_cs );
}

BOOL ClientPackage::Load( LPCTSTR szZipFileName )
{
	Package::PackagePtr pck = 
		Package::GetPackageInterface( Package::EPT_TPK );

	if ( !pck->Open( szZipFileName ) )
		return FALSE;

	m_pck = pck;
	return TRUE;
}

BOOL ClientPackage::Unload()
{
	SI_ASSERT( m_opennum == 0 );

	m_pck.reset();
	return TRUE;
}

DWORD ClientPackage::Open( LPCTSTR szFileName )
{
	if ( !m_pck )
		return INVALID;

	Package::FileSizeResult ret = m_pck->GetFileSize( szFileName );
	if ( !ret.first )
		return INVALID;

	__FileTrack* track = new __FileTrack;
	track->size = ret.second;
	track->cur  = 0;
	track->data = new char[track->size];

	EnterCriticalSection( &m_cs );
	if ( !m_pck->GetFileData( szFileName, track->data, track->size ) )
	{
		Close( (DWORD)track );
		LeaveCriticalSection( &m_cs );
		return INVALID;
	}
	LeaveCriticalSection( &m_cs );

	::InterlockedIncrement( &m_opennum );
	return (DWORD)track;
}

BOOL ClientPackage::Close( DWORD dwHandle )
{
	if ( !IS_VALID_PTR(dwHandle) )
		return FALSE;

	__FileTrack* track = (__FileTrack*)dwHandle;
	delete[] track->data;
	delete track;

	::InterlockedDecrement( &m_opennum );
	return TRUE;
}

DWORD ClientPackage::Read( PVOID lpMemOut, DWORD dwSize, DWORD dwHandle )
{
	if ( !IS_VALID_PTR(dwHandle) )
		return INVALID;

	__FileTrack* track = (__FileTrack*)dwHandle;
	if ( track->cur >= track->size )
		return 0;
	
	if ( track->cur + dwSize > track->size )
		dwSize = track->size - track->cur;

	memcpy( lpMemOut, track->data + track->cur, dwSize );
	track->cur += dwSize;

	// 返回实际"成功"读取的字节数
	return dwSize;
}

DWORD ClientPackage::Seek( DWORD dwHandle, INT nOffset, DWORD dwOrigin )
{
	if ( !IS_VALID_PTR(dwHandle) )
		return INVALID;

	__FileTrack* track = (__FileTrack*)dwHandle;
	switch( dwOrigin )
	{
	case SEEK_SET:
		track->cur = nOffset;
		break;
	case SEEK_CUR:
		track->cur += nOffset;
		break;
	case SEEK_END:
		track->cur = track->size + nOffset;
		break;
	default:
		SI_ASSERT(0);
		return (DWORD)INVALID;
	}

	return track->cur;
}

DWORD ClientPackage::Tell( DWORD dwHandle )
{
	if ( !IS_VALID_PTR(dwHandle) )
		return INVALID;

	return ((__FileTrack*)dwHandle)->cur;
}

DWORD ClientPackage::GetSize( LPCTSTR szFileName )
{
	SI_ASSERT( szFileName );

	if ( !m_pck )
		return INVALID;

	Package::FileSizeResult ret = m_pck->GetFileSize( szFileName );
	if ( !ret.first ) 
		return INVALID;

	return (DWORD)ret.second;
}

DWORD ClientPackage::LoadFile( LPVOID lpMemOut, LPCTSTR szFileName )
{
	SI_ASSERT( szFileName );

	DWORD dwSize = GetSize( szFileName );
	if ( INVALID == dwSize )
		return INVALID;
	
	EnterCriticalSection( &m_cs );
	if ( !m_pck->GetFileData( szFileName, lpMemOut, dwSize ) )
	{		
		LeaveCriticalSection( &m_cs );
		return INVALID;
	}
	LeaveCriticalSection( &m_cs );

	return dwSize;
}

}; // namespace Tang {