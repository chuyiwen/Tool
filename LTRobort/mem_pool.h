#pragma once
namespace Tang {
namespace Net {
//-----------------------------------------------------------------------------
// 内存池(注意：内存池的大小表示:内存池当前空闲内存的大小)
// lookaside list
// 初始化时：
// 1 外部设定内存池的最大允许大小
// 2 内存池不做任何内存预分配
//
// 外部申请内存时,依次判断：
// 1 如果内存池有对应尺寸的空闲块,使用空闲块返回
// 2 没有空闲块时,直接申请内存并在内存前加入tagMemItem,然后返回
//
// 外部释放内存时,依次判断:
// 1 如果释放内存块大小>内存池最大大小,直接释放到系统内存
// 2 如果当前内存池大小+释放内存块大小<内存池最大大小,直接放入内存池
// 3 进行垃圾收集：垃圾收集后重新检查上面的第2步，如果不通过，则进行第4步
// 4 否则直接释放入系统内存
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
	struct tagNode	// 内存块头描述
	{
		tagNode*	pNext;
		tagNode*	pPrev;
		INT			nIndex;
		DWORD		dwSize;
		DWORD		dwUseTime;
		DWORD		pMem[1];	// 实际内存空间
	};

	struct
	{
		tagNode*	pFirst;
		tagNode*	pLast;
	} m_Pool[16];

	DWORD m_dwMaxSize;		// 外部设定的最大允许空闲内存
	DWORD m_dwCurrentSize;	// 内存池中空闲内存总数

	// 垃圾收集
	VOID GarbageCollect(DWORD dwExpectSize, DWORD dwUseTime);
	// 返回最匹配的大小
	INT SizeToIndex(DWORD dwSize, DWORD& dwRealSize);
};

} // namespace Net {
} // namespace Tang {
