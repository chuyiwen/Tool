#include "stdafx.h"
#include "mem_pool.h"

namespace Tang {
namespace Net {

MemPool::MemPool(DWORD dwMaxPoolSize)
{
	m_dwMaxSize = dwMaxPoolSize;
	m_dwCurrentSize = 0;
	ZeroMemory(m_Pool, sizeof(m_Pool));
}


MemPool::~MemPool()
{
	for( int n=0; n<16; n++ )
	{
		while( m_Pool[n].pFirst )
		{
			tagNode* pNode = m_Pool[n].pFirst;
			m_Pool[n].pFirst = m_Pool[n].pFirst->pNext;
			free(pNode);
		}
	}
}

LPVOID MemPool::Alloc( DWORD dwBytes )
{
	DWORD dwRealSize = 0;
	INT nIndex = SizeToIndex(dwBytes, dwRealSize);
	if( INVALID != nIndex )
	{
		if( m_Pool[nIndex].pFirst )	// 池里有，就从池里分配
		{
			tagNode* pNode = m_Pool[nIndex].pFirst;
			m_Pool[nIndex].pFirst = m_Pool[nIndex].pFirst->pNext;
			if( m_Pool[nIndex].pFirst )
				m_Pool[nIndex].pFirst->pPrev = NULL;
			else
				m_Pool[nIndex].pLast = NULL;
			m_dwCurrentSize -= dwRealSize;
			++pNode->dwUseTime;
			return pNode->pMem;	
		}
	}

	tagNode* pNode = (tagNode*)malloc(dwRealSize + sizeof(tagNode) - sizeof(DWORD));
	if( !pNode )
		return NULL;

	pNode->nIndex = nIndex;
	pNode->dwSize = dwRealSize;
	pNode->pNext = NULL;
	pNode->pPrev = NULL;
	pNode->dwUseTime = 0;
	return pNode->pMem;	// 从实际内存中分配
}

VOID MemPool::Free( LPVOID pMem )
{
	tagNode* pNode = (tagNode*)(((LPBYTE)pMem) - sizeof(tagNode) + sizeof(DWORD));
	if( INVALID != pNode->nIndex )
	{
		if( pNode->dwSize + m_dwCurrentSize > m_dwMaxSize && pNode->dwUseTime > 0 )
			GarbageCollect(pNode->dwSize*2, pNode->dwUseTime);	// 垃圾收集

		if( pNode->dwSize + m_dwCurrentSize <= m_dwMaxSize ) // 内存池可以容纳
		{
			pNode->pPrev = NULL;
			pNode->pNext = m_Pool[pNode->nIndex].pFirst;
			if( m_Pool[pNode->nIndex].pFirst )
				m_Pool[pNode->nIndex].pFirst->pPrev = pNode;
			else
				m_Pool[pNode->nIndex].pLast = pNode;

			m_Pool[pNode->nIndex].pFirst = pNode;
			m_dwCurrentSize += pNode->dwSize;
			return;
		}
	}

	free(pNode);
}

VOID MemPool::GarbageCollect( DWORD dwExpectSize, DWORD dwUseTime )
{
	DWORD dwFreeSize = 0;
	for(INT n=15; n>=0; --n)	// 从最大的开始回收
	{
		if( !m_Pool[n].pFirst )
			continue;

		tagNode* pNode = m_Pool[n].pLast; // 从最后开始释放，因为后面的Node使用次数少
		while( pNode )
		{
			tagNode* pTempNode = pNode;
			pNode = pNode->pPrev;
			if( pTempNode->dwUseTime < dwUseTime )	// 释放此节点
			{
				if( pNode )
					pNode->pNext = pTempNode->pNext;
				if( pTempNode->pNext )
					pTempNode->pNext->pPrev = pNode;
				if( m_Pool[n].pLast == pTempNode )
					m_Pool[n].pLast = pNode;
				if( m_Pool[n].pFirst == pTempNode )
					m_Pool[n].pFirst = pTempNode->pNext;

				m_dwCurrentSize -= pTempNode->dwSize;
				dwFreeSize += pTempNode->dwSize;
				free(pTempNode);
			}

			if( dwFreeSize >= dwExpectSize )
				return;
		}
	}
}

INT MemPool::SizeToIndex( DWORD dwSize, DWORD& dwRealSize )
{
	if( dwSize<=32 )		{ dwRealSize = 32;			return 0; }
	if( dwSize<=64 )		{ dwRealSize = 64;			return 1; }
	if( dwSize<=128 )		{ dwRealSize = 128;			return 2; }
	if( dwSize<=256 )		{ dwRealSize = 256;			return 3; }
	if( dwSize<=512 )		{ dwRealSize = 512;			return 4; }
	if( dwSize<=1024 )		{ dwRealSize = 1024;		return 5; }
	if( dwSize<=2*1024 )	{ dwRealSize = 2*1024;		return 6; }
	if( dwSize<=4*1024 )	{ dwRealSize = 4*1024;		return 7; }
	if( dwSize<=8*1024 )	{ dwRealSize = 8*1024;		return 8; }
	if( dwSize<=16*1024 )	{ dwRealSize = 16*1024;		return 9; }
	if( dwSize<=32*1024 )	{ dwRealSize = 32*1024;		return 10; }
	if( dwSize<=64*1024 )	{ dwRealSize = 64*1024;		return 11; }
	if( dwSize<=128*1024 )	{ dwRealSize = 128*1024;	return 12; }
	if( dwSize<=256*1024 )	{ dwRealSize = 256*1024;	return 13; }
	if( dwSize<=512*1024 )	{ dwRealSize = 512*1024;	return 14; }
	if( dwSize<=1024*1024 )	{ dwRealSize = 1024*1024;	return 15; }
	dwRealSize = dwSize;
	return INVALID;
}

} // namespace Net {
} // namespace Tang {
