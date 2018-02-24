#pragma once
namespace Tang {
namespace Net {
class MemPool;
//-----------------------------------------------------------------------------
// MsgQueue: �ṩ�򵥵��Ƚ��ȳ���Ϣ���й���
// ��ȡ��Ϣ��ʱ��ʹ���ڲ�������ڴ�,����踺���ͷ��ڴ�
//-----------------------------------------------------------------------------
class MsgQueue
{
public:
	// �����Ϣ������β�������Ƿ���ӳɹ�
	BOOL AddMsg(LPCVOID pMsg, DWORD dwSize);
	// �Ӷ���ͷȡ��Ϣ������踺���ͷ��ڴ�
	LPBYTE GetMsg(DWORD& dwMsgSize);
	// ��Ӧ��GetMsg(),��Ϊ�ڴ����ڲ�����ģ�����Ӧ�ý����ڲ����ͷ�
	VOID FreeMsg(LPVOID pMsg);

	//-----------------------------------------------------------------------------
	// �������
	//-----------------------------------------------------------------------------
	// ���ڲ�ָ��ָ�����ͷ
	VOID ResetIterator();
	// ���ڲ�ָ�����
	VOID IncIterator();
	// ��õ�ǰ�ڲ�ָ��ָ����Ϣ��������ȡ��
	LPBYTE PeekMsg(DWORD& dwMsgSize);
	// �Ƴ���ǰ�ڲ�ָ��ָ����Ϣ��������ָ��
	VOID RemoveMsg();
	// ���������Ϣ
	VOID Clear();

	// �õ������е���Ϣ��Ŀ
	INT GetMsgNum() { return m_nMsg; }
	
	MsgQueue();
	~MsgQueue();

private:
	struct MsgItem
	{
		DWORD			dwDataSize;
		BYTE*			pData;
		MsgItem*		pPrev;
		MsgItem*		pNext;
	};

	INT					m_nMsg;
	MsgItem*			m_pQueueBegin;
	MsgItem*			m_pQueueEnd;
	MsgItem*			m_pCurrentItem;

	MemPool*			m_pMemPool;
};

} // namespace Net {
} // namespace Tang {