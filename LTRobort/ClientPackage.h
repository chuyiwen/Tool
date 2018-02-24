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
 *	@file		ClientPackage.h
 *	@author		zhaopeng
 *	@date		2011/03/11
 *	@version	
 *	@brief		
 */
#pragma once

#include "PackageLib\IPackage.h"

namespace Tang {

class ClientPackage
{
public:
	BOOL	Load(LPCTSTR szZipFileName);
	BOOL	Unload();

	DWORD	Open(LPCTSTR szFileName);
	BOOL	Close(DWORD dwHandle);
	DWORD	Read(PVOID lpMemOut, DWORD dwSize, DWORD dwHandle);
	DWORD	Seek(DWORD dwHandle, INT nOffset, DWORD dwOrigin);
	DWORD	Tell(DWORD dwHandle);
	
	DWORD	GetSize(LPCTSTR szFileName);	// 如果文件不存在，则返回INVALID
	DWORD	LoadFile(LPVOID lpMemOut, LPCTSTR szFileName);

	ClientPackage();
	~ClientPackage();

private:
	Package::PackagePtr	m_pck;
	CRITICAL_SECTION m_cs;
	volatile long m_opennum;
};

}; // namespace Tang {