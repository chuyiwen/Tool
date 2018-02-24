#pragma once
namespace Tang {
namespace Net {
//-----------------------------------------------------------------------------
// �ڴ��(ע�⣺�ڴ�صĴ�С��ʾ:�ڴ�ص�ǰ�����ڴ�Ĵ�С)
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
class SafeMemPool
{
public:
	LPVOID		Alloc(DWORD dwBytes);
	VOID		Free(LPVOID pMem);
	LPVOID		TryAlloc(DWORD dwBytes);	// ���Խ�����������
	BOOL		TryFree(LPVOID pMem);		// ���Խ�����������
	VOID		SetMaxSize(DWORD dwSize) { m_dwMaxSize = dwSize; }
	DWORD		GetSize() { return m_dwCurrentSize; }
	DWORD		GetMalloc() { return m_dwMalloc; }
	DWORD		GetGC() { return m_dwGCTimes; }

	SafeMemPool(DWORD dwMaxPoolSize=16*1024*1024);
	~SafeMemPool();

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
	DWORD m_dwMalloc;			// ͳ���ã�ʵ��Malloc����
	DWORD m_dwGCTimes;		// ͳ���ã�ʵ�������ռ�����

	DWORD volatile 	m_dwCurrentSize;	// �ڴ���п����ڴ�����
	LONG volatile 	m_lLock;

	VOID Lock() { while(InterlockedCompareExchange((LPLONG)&m_lLock, 1, 0)!= 0) Sleep(0); }
	VOID Unlock() { InterlockedExchange((LPLONG)(&m_lLock), 0); }
	bool TryLock() { return InterlockedCompareExchange((LPLONG)(&m_lLock), 1, 0) == 0;	}

	// �����ռ�
	VOID GarbageCollect(DWORD dwExpectSize, DWORD dwUseTime);
	// ������ƥ��Ĵ�С
	INT SizeToIndex(DWORD dwSize, DWORD& dwRealSize);
};

} // namespace Net {
} // namespace Tang {
