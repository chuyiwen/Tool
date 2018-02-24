//-----------------------------------------------------------------------------
// File: CPKFast.h
// Desc: game resource file system 1.0
// Time: 2003-1-2
// Auth: CTCRST
//
//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
/*	CPK �ļ���װ���Ŀ�꣺
 1.	����
 2.	���ݶ���ѹ������
 3.	Ŀ¼ʽ����
 4.	��������ɾ�������ļ���Ŀ¼

	��ƹ���
 1.	�ñ�������¼�����ļ�����Ϣ����CRC(ͨ���ļ�������)��־�������ļ���
 2.	CRC�ǰ����ļ���ȫ��(����������·��)����ģ�
 3.	�����ļ���(������·��)�Լ�ExtraInfo�����ڸ��ļ�������Ϣ֮��
 4.	һ��ʼ�ͷ���һЩ�������ļ�ʱ�Ϳ��Բ���Ҫ�ƶ������ļ���Ϣ��
 5.	��������֮���ٷ���һ�������
 6.	ɾ���ļ�ʱֻ��������Ϊ��Ч��
 7.	����ļ�ʱ��Ѱ�ҿ��б����Լ������ļ��ռ���룬���û�к��ʵĿ���
    �ļ��ռ䣬����ӵ����ļ�ĩβ��
 8.	����Ŀ���е�һ���׶�ʱ�����Զ԰�����һ����Ƭ���������ų�������
	������ӡ�ɾ�����޸��ļ���ɵĿռ���Ƭ�����һ����ԶԱ������һ��
	���������Ա�ӿ��ļ������ٶȣ�
 9.	���ù�������˼�룬ѹ������ѹ�����ܡ����ܡ������ļ���ʽ��ת������
	�Կ����ǹ��ˣ�ֻҪ��ͨ�õĽӿڣ��Ϳ�����ܶ���ѹ����ʽ���ݣ�
 11.����Ӱ����ɾ�ļ��������Գ��Խ��лָ�
 12.���ڴ���8MB���ļ�����Ϊ��һ�㶼�Ƕ��������֣����Բ������κ�ѹ����
	ʽ��ֱ�Ӵ��ڰ��С�
 13.֧��Ƕ�װ�����cpk�ļ�����԰���cpk�ļ���֧�ֽ���
*/
//-----------------------------------------------------------------------------
// ���ٵ�������
//-----------------------------------------------------------------------------
class CPK:public Package
{
public:
	// ��԰��Ĳ���
	BOOL Load(LPCTSTR szFileName);
	BOOL Unload();

	// ��԰��ڵ����ļ��Ĳ���
	DWORD	Open(LPCTSTR szFileName);	// return handle
	BOOL	Close(DWORD dwHandle);
	DWORD	Read(PVOID lpMemOut, DWORD dwSize, DWORD dwHandle);
	DWORD	Seek(DWORD dwHandle, INT nOffset, DWORD dwOrigin);
	DWORD	Tell(DWORD dwHandle);
	
	// �����е����ļ���Ŀ���ڴ棬����ԭ�ļ��ֽڴ�С��
	// ��Open+Read�����Ϊֱ�Ӷ���ָ���ڴ棬����һ��Memcpy
	// ����ڴ�Ŀ��lpMemOutΪ�գ��ͽ�����ԭ�ļ�(δѹ��ʱ)��С
	DWORD	LoadFile(LPVOID lpMemOut, LPCTSTR szFileName);


	CPK();~CPK();

private:
	tagCPKHeader	m_CPKHeader;
	tstring			m_strCPKFileName;
	tagCPKTable*	m_pCPKTable;
	
	BOOL			m_bLoaded;	// �Ƿ���CPK����
	DWORD			m_dwAllocGranularity;
	DWORD			m_dwCPKHandle;
	DWORD			m_dwCPKMappingHandle;
	volatile INT	m_nOpenedFileNum;


	SafeMemPool*	m_pMemPool;

	// �����ļ����ҵ���Ӧ�ı���
	INT GetTableIndex(LPCTSTR pFullName);
	INT GetTableIndexFromCRC(DWORD dwCRC);

	//�ļ�ӳ�䷽ʽ�򿪵����ļ�
	DWORD OpenForMap(INT nTableIndex, LPCTSTR szFileName);
	//��ͨ��ʽ�򿪵����ļ�
	DWORD OpenForCommon(INT nTableIndex, LPCTSTR szFileName);

};