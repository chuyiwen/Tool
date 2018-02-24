#include "stdafx.h"
#include "msg_queue_ts.h"
#include "safe_mem_pool.h"

namespace Tang {
namespace Net {

MsgQueueTS::MsgQueueTS(BOOL bActiveEvent, BOOL bAddSizeAhead)
{
	m_bEvent = bActiveEvent;
	m_bAddSizeAhead = bAddSizeAhead;
	
	m_nMsg = 0;
	m_hEvent = NULL;
	m_pQueueBegin = NULL;
	m_pQueueEnd = NULL;
	
	InitializeCriticalSection(&m_Lock);

	if( m_bEvent )
		m_hEvent = ::CreateEvent(NULL, FALSE, TRUE, NULL);	// 自动激活

	m_pMemPool = new SafeMemPool(256*1024);	// 256KB 缓存
}

MsgQueueTS::~MsgQueueTS()
{
	MsgItem* pMsg = m_pQueueBegin; 
	while( m_pQueueBegin )
	{
		pMsg = m_pQueueBegin->pNext;
		m_pMemPool->Free(m_pQueueBegin->pData);
		m_pMemPool->Free(m_pQueueBegin);
		m_pQueueBegin = pMsg;
	}

	if( m_bEvent )
		CloseHandle(m_hEvent);

	DeleteCriticalSection(&m_Lock);
	SAFE_DELETE(m_pMemPool);
}

BOOL MsgQueueTS::AddMsg( LPCVOID pMsg, DWORD dwSize )
{
	DWORD dwOriginSize = dwSize;
	if( m_bAddSizeAhead ) // 此成员在对象创建后就不会改变
		dwSize += sizeof(DWORD);

	// 申请新的单元
	MsgItem* pMsgItem = (MsgItem*)m_pMemPool->Alloc(sizeof(MsgItem));
	if( pMsgItem == NULL )
		return FALSE;

	// 初始化
	pMsgItem->dwDataSize = dwSize;
	pMsgItem->pData = NULL;
	pMsgItem->pNext = NULL;

	// 申请内容空间
	pMsgItem->pData = (LPBYTE)m_pMemPool->Alloc(dwSize);
	if( pMsgItem->pData == NULL )
	{
		delete(pMsgItem);
		return FALSE;
	}

	// 进入互斥区
	EnterCriticalSection(&m_Lock);	

	// 拷贝内容
	if( m_bAddSizeAhead )
	{
		*(DWORD*)(pMsgItem->pData) = dwOriginSize;
		memcpy(pMsgItem->pData+sizeof(dwOriginSize), pMsg, dwOriginSize);
	}
	else
	{
		memcpy(pMsgItem->pData, pMsg, dwSize);
	}

	if( m_pQueueBegin == NULL )	// 队列空
	{
		m_pQueueBegin = pMsgItem;
		m_pQueueEnd = pMsgItem;
	}
	else
	{
		m_pQueueEnd->pNext = pMsgItem;
		m_pQueueEnd = pMsgItem;
	}

	m_nMsg++;

	if( m_bEvent )	// 激活线程
		::SetEvent(m_hEvent);	

	LeaveCriticalSection(&m_Lock);
	return TRUE;
}

LPBYTE MsgQueueTS::GetMsg( DWORD &dwMsgSize )
{
	dwMsgSize = 0;
	if( m_nMsg <= 0 )	// 预先检查，以免不必要的进入critical section
		return NULL;	// no msg

	EnterCriticalSection(&m_Lock);

	if( m_nMsg <= 0 )	// 内部再行检查
	{
		LeaveCriticalSection(&m_Lock);
		return NULL;	// no msg
	}

	// 取出消息
	LPBYTE pMsg = m_pQueueBegin->pData;
	dwMsgSize = m_pQueueBegin->dwDataSize;

	MsgItem* pMsgItem = m_pQueueBegin;
	m_pQueueBegin = m_pQueueBegin->pNext;

	m_nMsg--;
	LeaveCriticalSection(&m_Lock);

	m_pMemPool->Free(pMsgItem);
	return pMsg;
}

VOID MsgQueueTS::FreeMsg( LPVOID pMsg )
{
	m_pMemPool->Free(pMsg);
}

} //namespace Net {
} //namespace Tang {