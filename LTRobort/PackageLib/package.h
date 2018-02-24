//-----------------------------------------------------------------------------
// File: package
// Time: 2004-2-20
// Auth: CTCRST
//
//-----------------------------------------------------------------------------
#pragma once
namespace vEngine{
//-----------------------------------------------------------------------------
// ���ִ���ļ���ͳһ�ӿ�
//-----------------------------------------------------------------------------
class Package
{
public:
	virtual BOOL	Load(LPCTSTR szZipFileName)=0;
	virtual BOOL	Unload()=0;

	// ��԰��ڵ����ļ��Ĳ���
	virtual DWORD	Open(LPCTSTR szFileName)=0;	// return handle
	virtual BOOL	Close(DWORD dwHandle)=0;
	virtual DWORD	Read(PVOID lpMemOut, DWORD dwSize, DWORD dwHandle)=0;
	virtual DWORD	Seek(DWORD dwHandle, INT nOffset, DWORD dwOrigin)=0;
	virtual	DWORD	Tell(DWORD dwHandle)=0;


	// �����е����ļ���Ŀ���ڴ棬����ԭ�ļ��ֽڴ�С��
	// ��Open+Read�����Ϊֱ�Ӷ���ָ���ڴ棬����һ��Memcpy
	// ����ڴ�Ŀ��lpMemOutΪ�գ��ͽ�����ԭ�ļ�(δѹ��ʱ)��С
	virtual DWORD	LoadFile(LPVOID lpMemOut, LPCTSTR szFileName)=0;
	virtual ~Package(){};

protected:
	TObjRef<DiscIOMgr>	m_pDiscIOMgr;
	TObjRef<FilterMgr>	m_pFilterMgr;
	TObjRef<Util>		m_pUtil;
};

}