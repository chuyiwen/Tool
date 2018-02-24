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
 *	@file		ClientVFS.cpp
 *	@author		zhaopeng
 *	@date		2011/03/11
 *	@version	
 *	@brief		
 */
#include "stdafx.h"
#include "ClientVFS.h"
#include "ClientPackage.h"

namespace Tang {

ClientVFS::ClientVFS()
: m_package( NULL )
{
	
}

ClientVFS::~ClientVFS()
{
	SAFE_DELETE( m_package );
}

BOOL ClientVFS::SetWorkingPackage( LPCTSTR szPackage )
{
	if ( m_package )
	{
		m_package->Unload();
		SAFE_DELETE( m_package );
	}

	m_package = new ClientPackage;
	if ( !m_package->Load( szPackage ) )
	{
		SAFE_DELETE( m_package );
		return FALSE;
	}

	return TRUE;
}

BOOL ClientVFS::HasWorkingPackage()
{
	return m_package != NULL;
}

DWORD ClientVFS::Open( LPCTSTR szFileName )
{
	if ( m_package )
		return m_package->Open( szFileName );
	else
		return m_deffs.Open( szFileName );	
}

BOOL ClientVFS::Close( DWORD dwHandle )
{
	if ( m_package )
		return m_package->Close( dwHandle );
	else
		return m_deffs.Close( dwHandle );	
}

DWORD ClientVFS::Read( PVOID lpMemOut, DWORD dwSize, DWORD dwHandle )
{
	if ( m_package )
		return m_package->Read( lpMemOut, dwSize, dwHandle );
	else
		return m_deffs.Read( lpMemOut, dwSize, dwHandle );	
}

DWORD ClientVFS::Seek( DWORD dwHandle, INT nOffset, DWORD dwOrigin )
{
	if ( m_package )
		return m_package->Seek( dwHandle, nOffset, dwOrigin );
	else
		return m_deffs.Seek( dwHandle, nOffset, dwOrigin );	
}

DWORD ClientVFS::Tell( DWORD dwHandle )
{
	if ( m_package )
		return m_package->Tell( dwHandle );
	else
		return m_deffs.Tell( dwHandle );
}

DWORD ClientVFS::GetSize( LPCTSTR szFileName )
{
	if ( m_package )
		return m_package->GetSize( szFileName );
	else
		return m_deffs.GetSize( szFileName );
}

DWORD ClientVFS::LoadFile( LPVOID lpMemOut, LPCTSTR szFileName )
{
	if ( m_package )
		return m_package->LoadFile( lpMemOut, szFileName );
	else
		return m_deffs.LoadFile( lpMemOut, szFileName );
}

}; // namespace Tang {