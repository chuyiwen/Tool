//-------------------------------------------------------------------------------
//��Name				:   dword_flag.h
//��Compiler			:	Microsoft Visual C++ 9.0aslan
//��Version				:	1.00
//��Create Date			:	2009-08-08
//��LastModified		:	
//��Brief				:	�޷�������λ��ʾ����
//-------------------------------------------------------------------------------
#pragma once

template<INT nSize>
struct tagDWORDFlagArray
{
public:
	tagDWORDFlagArray() : m_dwFlags(0) {}
	explicit tagDWORDFlagArray(DWORD dwFlags) : m_dwFlags(dwFlags) {}

	VOID	Init(DWORD dwFlags) { m_dwFlags = dwFlags; }

	VOID	SetFlag(INT nIndex);
	VOID	UnsetFlag(INT nIndex);
	BOOL	IsSet(INT nIndex);
	DWORD	GetFlags();

private:
	DWORD	m_dwFlags;		// �޷������ͱ�־λ����
};

//---------------------------------------------------------------------------------
// ���ñ�־λ
//---------------------------------------------------------------------------------
template<INT nSize>
inline VOID tagDWORDFlagArray<nSize>::SetFlag(INT nIndex)
{
	if( nIndex < 0 || nIndex >= nSize ) return;

	m_dwFlags |= (1 << nIndex);
}

//---------------------------------------------------------------------------------
// ȡ����־λ
//---------------------------------------------------------------------------------
template<INT nSize>
inline VOID tagDWORDFlagArray<nSize>::UnsetFlag(INT nIndex)
{
	if( nIndex < 0 || nIndex >= nSize ) return;

	m_dwFlags &= ~(1 << nIndex);
}

//---------------------------------------------------------------------------------
// ĳ����־λ�Ƿ��Ѿ�����
//---------------------------------------------------------------------------------
template<INT nSize>
inline BOOL tagDWORDFlagArray<nSize>::IsSet(INT nIndex)
{
	if( nIndex < 0 || nIndex >= nSize ) return FALSE;

	return m_dwFlags & (1 << nIndex);
}

//---------------------------------------------------------------------------------
// �õ���־λ����
//---------------------------------------------------------------------------------
template<INT nSize>
inline DWORD tagDWORDFlagArray<nSize>::GetFlags()
{
	return m_dwFlags;
}