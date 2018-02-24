#pragma once

template<class KeyType, class ValueType> class SMap
{
public:
	typedef typename std::map<KeyType, ValueType>::iterator SMapIterator;

public:
	//! add element
	VOID Add(KeyType key, ValueType value)
	{ m_map[key] = value; }
	
	//! get element
	ValueType Peek(KeyType key)
	{
		std::map<KeyType, ValueType>::iterator it = m_map.find(key);
		if( it == m_map.end() )
			return ValueType(INVALID);
		else
			return it->second;
	}
	
	//! change the value according to the key
	BOOL ChangeValue(KeyType key, ValueType new_value)
	{
		std::map<KeyType, ValueType>::iterator it = m_map.find(key);
		if( it == m_map.end() )
			return FALSE;

		it->second = new_value;
		return TRUE;
	}

	//! accumulate the values according to the key; if the key isn't exist,then append it(ValueType must have the ability to overload operator+ and operator=£©
	VOID ModifyValue(KeyType key, ValueType mod_value)
	{
		std::map<KeyType, ValueType>::iterator it = m_map.find(key);
		if( it == m_map.end() )
		{
			m_map.insert(std::make_pair(key, mod_value));
		}
		else
		{
			it->second = it->second + mod_value;
		}
	}

	//! check the element whether is exist
	BOOL IsExist(KeyType key)
	{
		std::map<KeyType, ValueType>::iterator it = m_map.find(key);
		if( it == m_map.end() )
			return FALSE;
		else
			return TRUE;
	}

	//! delete the element according to the key
	BOOL Erase(KeyType key)
	{ 
		std::map<KeyType, ValueType>::iterator it = m_map.find(key);
		if( it == m_map.end() )
			return FALSE;

        m_map.erase(it);
		return TRUE;
	}

	//! clear all elements
	VOID Clear() { m_map.clear(); }

	//! get the number of the element
	INT	Size() { return (INT)m_map.size(); }

	BOOL Empty() { return m_map.empty(); }

	//! initialize the inner iterator,reset the map
	VOID ResetIterator()
	{ m_it = m_map.begin(); }

	//! get the head of the map
	SMapIterator Begin()
	{ return m_map.begin(); }

	//! get the element according to the position of the inner iterator,then move back the iterator
	BOOL PeekNext(ValueType& value)
	{
		if( m_it == m_map.end() )
			return FALSE;
		value = m_it->second;
		++m_it;
		return TRUE;
	}

	//!  get the element according to the position of the specifing iterator,then move back the iterator
	BOOL PeekNext(SMapIterator& it, ValueType& value)
	{
		if( it == m_map.end() )
			return FALSE;
		value = it->second;
		++it;
		return TRUE;
	}

	//! //! get the element according to the position of the inner iterator,then move back the iterator
	BOOL PeekNext(KeyType& key, ValueType& value)
	{
		if( m_it == m_map.end() )
			return FALSE;
		key = m_it->first;
		value = m_it->second;
		++m_it;
		return TRUE;
	}

	//! get the element according to the position of the specifing iterator,then move back the iterator
	BOOL PeekNext(SMapIterator& it, KeyType& key, ValueType& value)
	{
		if( it == m_map.end() )
			return FALSE;
		key = it->first;
		value = it->second;
		++it;
		return TRUE;
	}

	//! get the element randomly from the list
	BOOL RandPeek(KeyType& key, ValueType& value)
	{
		INT nSize = m_map.size();
		if( nSize <= 0 )
			return FALSE;

		INT nRand = rand() % nSize;

		std::map<KeyType, ValueType>::iterator it = m_map.begin();
		for(INT n=0; n<nRand; n++)
			++it;

		key = it->first;
		value = it->second;
		return TRUE;
	}


	//! export all keys to the specifing list
	VOID ExportAllKey(std::list<KeyType>& listDest)
	{
		std::map<KeyType, ValueType>::iterator it;
		for(it = m_map.begin(); it != m_map.end(); ++it)
			listDest.push_back(it->first);
	}
	
	//! export all values to the specifing list
	VOID ExportAllValue(std::list<ValueType>& listDest)
	{
		std::map<KeyType, ValueType>::iterator it;
		for(it = m_map.begin(); it != m_map.end(); ++it)
			listDest.push_back(it->second);
	}


private:
	std::map<KeyType, ValueType>					m_map;
	typename std::map<KeyType, ValueType>::iterator m_it;
};
