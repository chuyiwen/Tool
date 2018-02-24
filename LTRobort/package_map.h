/*******************************************************************************

Copyright 2010 by Shengshi Interactive Game Co., Ltd.
All rights reserved.

This software is the confidential and proprietary information of
Shengshi Interactive Game Co., Ltd. ('Confidential Information'). You shall
not disclose such Confidential Information and shall use it only in
accordance with the terms of the license agreement you entered into with
Shengshi Interactive  Co., Ltd.

*******************************************************************************/

/**
*	@file		package_map.h
*	@author		wmr
*	@date		2011/02/17	initial
*	@version	0.0.1.0
*	@brief		
*/


#pragma once
namespace serverframe {


template<class KeyType, class ValueType> class package_map
{
public:
	typedef typename std::map<KeyType, ValueType>::iterator map_iter;

public:
	
	VOID add(KeyType key_, ValueType value_)
	{ 
		_map.insert(std::make_pair(key_, value_)); 
	}
	
	ValueType find(KeyType key_)
	{
		std::map<KeyType, ValueType>::iterator iter = _map.find(key_);
		if( iter == _map.end() )
			return ValueType(GT_INVALID);
		else
			return iter->second;
	}
	
	BOOL change_value(KeyType key_, ValueType value_)
	{
		std::map<KeyType, ValueType>::iterator iter = _map.find(key_);
		if( iter == _map.end() )
			return FALSE;

		iter->second = value_;
		return TRUE;
	}

	VOID modify_value(KeyType key_, ValueType value_)
	{
		std::map<KeyType, ValueType>::iterator iter = _map.find(key_);
		if( iter == _map.end() )
		{
			_map.insert(std::make_pair(key_, value_));
		}
		else
		{
			iter->second = iter->second + value_;
		}
	}

	BOOL is_exist(KeyType key_)
	{
		std::map<KeyType, ValueType>::iterator iter = _map.find(key_);
		if( iter == _map.end() )
			return FALSE;
		else
			return TRUE;
	}

	BOOL erase(KeyType key_)
	{ 
		std::map<KeyType, ValueType>::iterator iter = _map.find(key_);
		if( iter == _map.end() )
			return FALSE;

        _map.erase(iter);
		return TRUE;
	}

	VOID clear() { _map.clear(); }

	INT	size() { return (INT)_map.size(); }

	BOOL empty() { return _map.empty(); }

	VOID reset_iterator()
	{ _iter = _map.begin(); }

	map_iter begin()
	{ 
		return _map.begin(); 
	}

	BOOL find_next(ValueType& value_)
	{
		if( _iter == _map.end() )
			return FALSE;
		value_ = _iter->second;
		++_iter;
		return TRUE;
	}

	BOOL find_next(map_iter& iter_, ValueType& value_)
	{
		if( iter_ == _map.end() )
			return FALSE;
		value_ = iter_->second;
		++iter_;
		return TRUE;
	}

	BOOL find_next(KeyType& key_, ValueType& value_)
	{
		if( _iter == _map.end() )
			return FALSE;
		key_ = _iter->first;
		value_ = _iter->second;
		++_iter;
		return TRUE;
	}

	BOOL find_next(map_iter& iter_, KeyType& key_, ValueType& value_)
	{
		if( iter_ == _map.end() )
			return FALSE;
		key_ = iter_->first;
		value_ = iter_->second;
		++iter_;
		return TRUE;
	}

	BOOL rand_find(KeyType& key_, ValueType& value_)
	{
		INT n_size = _map.size();
		if( n_size <= 0 )
			return FALSE;

		INT n_rand = rand() % n_size;

		std::map<KeyType, ValueType>::iterator it = _map.begin();
		for(INT n=0; n<n_rand; n++)
			++it;

		key_ = it->first;
		value_ = it->second;
		return TRUE;
	}

	VOID copy_key_to_list(std::list<KeyType>& list_out_)
	{
		std::map<KeyType, ValueType>::iterator iter;
		for(iter = _map.begin(); iter != _map.end(); ++iter)
			list_out_.push_back(iter->first);
	}
	
	VOID copy_value_to_list(std::list<ValueType>& list_out_)
	{
		std::map<KeyType, ValueType>::iterator iter;
		for(iter = _map.begin(); iter != _map.end(); ++iter)
			list_out_.push_back(iter->second);
	}


private:
	std::map<KeyType, ValueType>					_map;
	typename std::map<KeyType, ValueType>::iterator _iter;
};


}