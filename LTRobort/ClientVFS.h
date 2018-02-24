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
 *	@file		ClientVFS.h
 *	@author		zhaopeng
 *	@date		2011/03/11
 *	@version	
 *	@brief		
 */
#pragma once
namespace Tang {

class ClientPackage;

class ClientVFS : public IFS
{
public:
	// 设置当前工作的文件包
	virtual BOOL SetWorkingPackage(LPCTSTR szPackage);
	// 当前是否有包打开
	virtual BOOL HasWorkingPackage();

	virtual DWORD	Open(LPCTSTR szFileName);
	virtual BOOL	Close(DWORD dwHandle);
	virtual DWORD	Read(PVOID lpMemOut, DWORD dwSize, DWORD dwHandle);
	virtual DWORD	Seek(DWORD dwHandle, INT nOffset, DWORD dwOrigin);
	virtual DWORD	Tell(DWORD dwHandle);

	// 优化函数
	virtual DWORD	GetSize(LPCTSTR szFileName);	// 如果文件不存在，则返回INVALID
	virtual DWORD	LoadFile(LPVOID lpMemOut, LPCTSTR szFileName);

	ClientVFS();
	virtual ~ClientVFS();
private:
	ClientPackage*  m_package;
	StdFS			m_deffs;
};

}; // namespace Tang {