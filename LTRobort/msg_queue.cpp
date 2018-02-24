#include "stdafx.h"
#include "msg_queue.h"
#include "mem_pool.h"

namespace Tang {
namespace Net {

MsgQueue::MsgQueue()
{
	m_nMsg = 0;
	m_pQueueBegin = NULL;
	m_pQueueEnd = NULL;
	m_pCurrentItem = NULL;

	m_pMemPool = new MemPool(16*1024);	// 默认 16KB 缓存
}

MsgQueue::~MsgQueue()
{
	Clear();
	SAFE_DELETE(m_pMemPool);
}

BOOL MsgQueue::AddMsg( LPCVOID pMsg, DWORD dwSize )
{
	// 申请新的单元
	MsgItem* pNewMsg = (MsgItem*)m_pMemPool->Alloc(sizeof(MsgItem));
	if( pNewMsg == NULL )
		return FALSE;

	// 初始化
	pNewMsg->dwDataSize = dwSize;
	pNewMsg->pData = NULL;
	pNewMsg->pPrev = NULL;
	pNewMsg->pNext = NULL;

	// 申请内容空间
	pNewMsg->pData = (LPBYTE)m_pMemPool->Alloc(dwSize);
	if( pNewMsg->pData == NULL )
	{
		delete(pNewMsg);
		return FALSE;
	}

	// 拷贝内容
	memcpy(pNewMsg->pData, pMsg, dwSize);

	if( m_pQueueBegin == NULL )	// 队列空
	{
		m_pQueueBegin = pNewMsg;
		m_pQueueEnd = pNewMsg;
		m_pCurrentItem = pNewMsg;
	}
	else
	{
		m_pQueueEnd->pNext = pNewMsg;
		pNewMsg->pPrev = m_pQueueEnd;
		m_pQueueEnd = pNewMsg;

	}

	m_nMsg++;
	return TRUE;
}

LPBYTE MsgQueue::GetMsg( DWORD &dwMsgSize )
{
	dwMsgSize = 0;
	if( m_nMsg <= 0 )
		return NULL;	// no msg

	// 取出消息
	LPBYTE pMsg = m_pQueueBegin->pData;
	dwMsgSize = m_pQueueBegin->dwDataSize;

	MsgItem* pItem = m_pQueueBegin;
	m_pQueueBegin = m_pQueueBegin->pNext;
	if( m_pQueueBegin )
		m_pQueueBegin->pPrev = NULL;
	m_pMemPool->Free(pItem);

	m_nMsg--;
	return pMsg;
}

VOID MsgQueue::FreeMsg( LPVOID pMsg )
{
	m_pMemPool->Free(pMsg);
}

VOID MsgQueue::ResetIterator()
{
	m_pCurrentItem = m_pQueueBegin;
}

VOID MsgQueue::IncIterator()
{
	if( !m_pCurrentItem )
		return;

	m_pCurrentItem = m_pCurrentItem->pNext;
}

LPBYTE MsgQueue::PeekMsg( DWORD& dwMsgSize )
{
	dwMsgSize = 0;
	if( !m_pCurrentItem || m_nMsg <= 0 )
		return NULL;

	dwMsgSize = m_pCurrentItem->dwDataSize;
	return m_pCurrentItem->pData;
}

VOID MsgQueue::RemoveMsg()
{
	if( !m_pCurrentItem )
		return;

	MsgItem* pItem = m_pCurrentItem;
	if( m_pCurrentItem == m_pQueueBegin )
	{
		m_pQueueBegin = m_pQueueBegin->pNext;
		if( m_pQueueBegin )
			m_pQueueBegin->pPrev = NULL;
		m_pCurrentItem = m_pQueueBegin;

	}
	else if( m_pCurrentItem == m_pQueueEnd )
	{
		m_pQueueEnd = m_pQueueEnd->pPrev;
		if( m_pQueueEnd )
			m_pQueueEnd->pNext = NULL;

		m_pCurrentItem = NULL;
	}
	else
	{
		m_pCurrentItem->pPrev->pNext = m_pCurrentItem->pNext;
		m_pCurrentItem->pNext->pPrev = m_pCurrentItem->pPrev;
		m_pCurrentItem = m_pCurrentItem->pNext;
	}

	m_pMemPool->Free(pItem->pData);
	m_pMemPool->Free(pItem);
	m_nMsg--;
	if( 0 == m_nMsg )
	{
		m_pQueueBegin = m_pQueueEnd = m_pCurrentItem = NULL;
	}
}

VOID MsgQueue::Clear()
{
	MsgItem* pMsg = m_pQueueBegin; 
	while( m_pQueueBegin )
	{
		pMsg = m_pQueueBegin->pNext;
		m_pMemPool->Free( m_pQueueBegin->pData);
		m_pMemPool->Free(m_pQueueBegin);
		m_pQueueBegin = pMsg;
	}
	m_nMsg = 0;
	m_pQueueBegin = NULL;
	m_pQueueEnd = NULL;
	m_pCurrentItem = NULL;
}

} // namespace Net {
} // namespace Tang {

