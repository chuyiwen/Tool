#pragma once
template<typename Type> class SList
{
public:
	typedef typename std::list<Type>::iterator SListIterator;

public:
	// append the element to the tail
	VOID PushBack(Type val)
	{
		m_list.push_back(val);
		++m_nItemNum;
	}

	// get the element from the head
	Type PopFront()
	{
		Type val;
		if( m_nItemNum <= 0 )
			return Type(INVALID);

		val = m_list.front();
		m_list.pop_front();
		m_nItemNum--;
		return val;
	}

	// append the element to the head
	VOID PushFront(Type val)
	{
		m_list.push_front(val);
		++m_nItemNum;
	}

	// get the first element of the list and don't pop the element
	Type Front()
	{
		if( m_nItemNum <= 0 )
			return Type(INVALID);

		return m_list.front();
	}

	// delete the element
	BOOL Erase(Type& val)
	{
		std::list<Type>::iterator it;
		for(it=m_list.begin(); it!=m_list.end(); ++it)
		{
			if( val == *it )
			{
				m_list.erase(it);
				--m_nItemNum;	// need to deal with the nItemNum,so cann't use the list::remove directly
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL IsExist(Type& val)
	{
		std::list<Type>::iterator it;
		for(it=m_list.begin(); it!=m_list.end(); ++it)
		{
			if( val == *it )
				return TRUE;
		}
		return FALSE;
	}

	VOID Clear()
	{
		m_list.clear();
		m_nItemNum=0;
	}

	// get the number of the elements,
	// std::list.size() cann't assure thread-safe,
	// so we keep a records about the numbers
	INT	Size() { return m_nItemNum;	}
	BOOL Empty() { return (0 == m_nItemNum); }


	//! read a element randomly from the list
	BOOL RandPeek(Type& value, BOOL bPop=FALSE)
	{
		if( m_list.empty() )
			return FALSE;

		INT nRand = rand() % m_nItemNum;
		std::list<Type>::iterator it = m_list.begin();
		for(INT n=0; n<nRand; n++)
			++it;
       
		value = *it;
		if( bPop )
		{
			m_list.erase(it);
			m_nItemNum--;
		}
			
		return TRUE;
	}


	//! get the element according to the position of the inner iterator,then move back the iterator
	BOOL PeekNext(Type& value)
	{
		if( m_it == m_list.end() )
			return FALSE;
		value = *m_it;
		++m_it;
		return TRUE;
	}

	//! get the element according to the position of the external iterator,then move back the iterator
	BOOL PeekNext(SListIterator& it, Type& value)
	{
		if( it == m_list.end() )
			return FALSE;
		value = *it;
		++it;
		return TRUE;
	}

	//! initialize the inner iterator,reset the map
	VOID ResetIterator()
	{ m_it = m_list.begin();	}

	
	SListIterator Begin()
	{
		return m_list.begin();
	}

	std::list<Type>& GetList() { return m_list; }


	VOID operator=(std::list<Type>& list) { m_list = list;	}
	VOID operator=(SList<Type>& list) { m_list = list.GetList(); m_nItemNum = m_list.size(); m_it = m_list.end(); }


	SList():m_nItemNum(0) {}
	SList(std::list<Type>& list){ m_list = list; }
	~SList(){}

private:
	std::list<Type>						m_list;
	INT									m_nItemNum;
	typename std::list<Type>::iterator	m_it;
};