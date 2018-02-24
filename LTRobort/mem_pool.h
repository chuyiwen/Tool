#pragma once
namespace Tang {
namespace Net {
//-----------------------------------------------------------------------------
// �ڴ��(ע�⣺�ڴ�صĴ�С��ʾ:�ڴ�ص�ǰ�����ڴ�Ĵ�С)
// lookaside list
// ��ʼ��ʱ��
// 1 �ⲿ�趨�ڴ�ص���������С
// 2 �ڴ�ز����κ��ڴ�Ԥ����
//
// �ⲿ�����ڴ�ʱ,�����жϣ�
// 1 ����ڴ���ж�Ӧ�ߴ�Ŀ��п�,ʹ�ÿ��п鷵��
// 2 û�п��п�ʱ,ֱ�������ڴ沢���ڴ�ǰ����tagMemItem,Ȼ�󷵻�
//
// �ⲿ�ͷ��ڴ�ʱ,�����ж�:
// 1 ����ͷ��ڴ���С>�ڴ������С,ֱ���ͷŵ�ϵͳ�ڴ�
// 2 �����ǰ�ڴ�ش�С+�ͷ��ڴ���С<�ڴ������С,ֱ�ӷ����ڴ��
// 3 ���������ռ��������ռ������¼������ĵ�2���������ͨ��������е�4��
// 4 ����ֱ���ͷ���ϵͳ�ڴ�
//-----------------------------------------------------------------------------
class MemPool
{
public:
	LPVOID Alloc(DWORD dwBytes);
	VOID  Free(LPVOID pMem);
	DWORD GetSize() { return m_dwCurrentSize; }

	MemPool(DWORD dwMaxPoolSize=16*1024*1024);
	~MemPool();

private:
	struct tagNode	// �ڴ��ͷ����
	{
		tagNode*	pNext;
		tagNode*	pPrev;
		INT			nIndex;
		DWORD		dwSize;
		DWORD		dwUseTime;
		DWORD		pMem[1];	// ʵ���ڴ�ռ�
	};

	struct
	{
		tagNode*	pFirst;
		tagNode*	pLast;
	} m_Pool[16];

	DWORD m_dwMaxSize;		// �ⲿ�趨�������������ڴ�
	DWORD m_dwCurrentSize;	// �ڴ���п����ڴ�����

	// �����ռ�
	VOID GarbageCollect(DWORD dwExpectSize, DWORD dwUseTime);
	// ������ƥ��Ĵ�С
	INT SizeToIndex(DWORD dwSize, DWORD& dwRealSize);
};

} // namespace Net {
} // namespace Tang {
