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
		m_hEvent = ::CreateEvent(NULL, FALSE, TRUE, NULL);	// �Զ�����

	m_pMemPool = new SafeMemPool(256*1024);	// 256KB ����
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
	if( m_bAddSizeAhead ) // �˳�Ա�ڶ��󴴽���Ͳ���ı�
		dwSize += sizeof(DWORD);

	// �����µĵ�Ԫ
	MsgItem* pMsgItem = (MsgItem*)m_pMemPool->Alloc(sizeof(MsgItem));
	if( pMsgItem == NULL )
		return FALSE;

	// ��ʼ��
	pMsgItem->dwDataSize = dwSize;
	pMsgItem->pData = NULL;
	pMsgItem->pNext = NULL;

	// �������ݿռ�
	pMsgItem->pData = (LPBYTE)m_pMemPool->Alloc(dwSize);
	if( pMsgItem->pData == NULL )
	{
		delete(pMsgItem);
		return FALSE;
	}

	// ���뻥����
	EnterCriticalSection(&m_Lock);	

	// ��������
	if( m_bAddSizeAhead )
	{
		*(DWORD*)(pMsgItem->pData) = dwOriginSize;
		memcpy(pMsgItem->pData+sizeof(dwOriginSize), pMsg, dwOriginSize);
	}
	else
	{
		memcpy(pMsgItem->pData, pMsg, dwSize);
	}

	if( m_pQueueBegin == NULL )	// ���п�
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

	if( m_bEvent )	// �����߳�
		::SetEvent(m_hEvent);	

	LeaveCriticalSection(&m_Lock);
	return TRUE;
}

LPBYTE MsgQueueTS::GetMsg( DWORD &dwMsgSize )
{
	dwMsgSize = 0;
	if( m_nMsg <= 0 )	// Ԥ�ȼ�飬���ⲻ��Ҫ�Ľ���critical section
		return NULL;	// no msg

	EnterCriticalSection(&m_Lock);

	if( m_nMsg <= 0 )	// �ڲ����м��
	{
		LeaveCriticalSection(&m_Lock);
		return NULL;	// no msg
	}

	// ȡ����Ϣ
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