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
	// ���õ�ǰ�������ļ���
	virtual BOOL SetWorkingPackage(LPCTSTR szPackage);
	// ��ǰ�Ƿ��а���
	virtual BOOL HasWorkingPackage();

	virtual DWORD	Open(LPCTSTR szFileName);
	virtual BOOL	Close(DWORD dwHandle);
	virtual DWORD	Read(PVOID lpMemOut, DWORD dwSize, DWORD dwHandle);
	virtual DWORD	Seek(DWORD dwHandle, INT nOffset, DWORD dwOrigin);
	virtual DWORD	Tell(DWORD dwHandle);

	// �Ż�����
	virtual DWORD	GetSize(LPCTSTR szFileName);	// ����ļ������ڣ��򷵻�INVALID
	virtual DWORD	LoadFile(LPVOID lpMemOut, LPCTSTR szFileName);

	ClientVFS();
	virtual ~ClientVFS();
private:
	ClientPackage*  m_package;
	StdFS			m_deffs;
};

}; // namespace Tang {