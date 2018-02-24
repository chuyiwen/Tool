#pragma once
namespace Tang {
namespace Net {
class SafeMemPool;
//-----------------------------------------------------------------------------
// MsgQueueTS: �ṩ�̰߳�ȫ���Ƚ��ȳ���Ϣ���й���
// ��ȡ��Ϣ��ʱ��ʹ���ڲ�������ڴ�,����踺���ͷ��ڴ�
// ������Ϣ����ʱ�����Լ���һ��Event���ʺ�������߳��շ�
// ��������Ϣǰ�������Ϣ���ȣ��ʺ����紫��
//-----------------------------------------------------------------------------
class MsgQueueTS
{
public:

	// bActiveEvent: ������Ϣ����ʱ���Ƿ񼤻�һ���ڽ�event
	// bAddSizeAhead: �Ƿ�����Ϣͷ��ǰ������Ϣ���ȣ���ҪΪ����ͨ��׼��
	MsgQueueTS(BOOL bActiveEvent, BOOL bAddSizeAhead);
	~MsgQueueTS();

	// �����Ϣ������β�������Ƿ���ӳɹ�
	BOOL AddMsg(LPCVOID pMsg, DWORD dwSize);

	// �Ӷ���ͷȡ��Ϣ������踺���ͷ��ڴ�
	LPBYTE GetMsg(DWORD& dwMsgSize);

	// ��Ӧ��GetMsg(),��Ϊ�ڴ����ڲ�����ģ�����Ӧ�ý����ڲ����ͷ�
	VOID FreeMsg(LPVOID pMsg);

	// ȡ���¼����������м�����Ϣʱ�����¼�������
	HANDLE GetEvent() { return m_hEvent; }

	// �õ������е���Ϣ��Ŀ
	INT GetMsgNum() { return m_nMsg; }
private:
	struct MsgItem
	{
		DWORD			dwDataSize;
		BYTE*			pData;
		MsgItem*		pNext;
	};

	SafeMemPool*		m_pMemPool;
	CRITICAL_SECTION	m_Lock;
	HANDLE				m_hEvent;
	INT					m_nMsg;
	BOOL				m_bEvent;
	BOOL				m_bAddSizeAhead;	

	MsgItem*			m_pQueueBegin;
	MsgItem*			m_pQueueEnd;
};

} //namespace Net {
} //namespace Tang {