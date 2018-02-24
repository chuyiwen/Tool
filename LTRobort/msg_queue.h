#pragma once
namespace Tang {
namespace Net {
class MemPool;
//-----------------------------------------------------------------------------
// MsgQueue: 提供简单的先进先出信息队列管理
// 在取消息的时候使用内部分配的内存,外边需负责释放内存
//-----------------------------------------------------------------------------
class MsgQueue
{
public:
	// 添加消息到队列尾，返回是否添加成功
	BOOL AddMsg(LPCVOID pMsg, DWORD dwSize);
	// 从队列头取消息，外边需负责释放内存
	LPBYTE GetMsg(DWORD& dwMsgSize);
	// 对应于GetMsg(),因为内存是内部分配的，所以应该交还内部来释放
	VOID FreeMsg(LPVOID pMsg);

	//-----------------------------------------------------------------------------
	// 特殊操作
	//-----------------------------------------------------------------------------
	// 将内部指针指向队列头
	VOID ResetIterator();
	// 将内部指针后移
	VOID IncIterator();
	// 获得当前内部指针指向消息，但并不取出
	LPBYTE PeekMsg(DWORD& dwMsgSize);
	// 移除当前内部指针指向消息，并后移指针
	VOID RemoveMsg();
	// 清除所有消息
	VOID Clear();

	// 得到队列中的消息数目
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