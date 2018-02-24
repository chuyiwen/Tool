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
*	@file		sigslot.h
*	@author		slash
*	@date		2011/02/12	initial
*	@version	0.0.1.0
*	@brief		
*/

#ifndef SIGSLOT_H_INCLUDE
#define SIGSLOT_H_INCLUDE
#include "fastdelegate.h"
#include "fastdelegatebind.h"
#include <list>
#define signals public
#define slots
//! null class
class Nil;	
//! params = 8
template <typename TR , typename T1 = Nil , typename T2 = Nil , typename T3 = Nil , typename T4 = Nil , typename T5 = Nil , typename T6 = Nil , typename T7 = Nil , typename T8 = Nil>
class Signal
{
public:
	typedef fastdelegate::FastDelegate8<T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2 , T3 p3 , T4 p4 , T5 p5 , T6 p6 , T7 p7 , T8 p8) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2 , p3 , p4 , p5 , p6 , p7 , p8);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 0
template <typename TR>
class Signal<TR , Nil , Nil , Nil , Nil , Nil , Nil , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate0<TR> BaseType;
	Signal(){}
	void Emit() const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()();
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 1
template <typename TR , typename T1>
class Signal<TR , T1 , Nil , Nil , Nil , Nil , Nil , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate1<T1 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 2
template <typename TR , typename T1 , typename T2>
class Signal<TR , T1 , T2 , Nil , Nil, Nil , Nil , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate2<T1 , T2 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 3
template <typename TR , typename T1 , typename T2 , typename T3>
class Signal<TR , T1 , T2 , T3 , Nil, Nil , Nil , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate3<T1 , T2 , T3 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2, T3 p3) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2 , p3);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 4
template <typename TR , typename T1 , typename T2 , typename T3 , typename T4>
class Signal<TR , T1 , T2 , T3 , T4 , Nil , Nil , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate4<T1 , T2 , T3 , T4 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2 , T3 p3 , T4 p4) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2 , p3 , p4);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 5
template <typename TR , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
class Signal<TR , T1 , T2 , T3 , T4 , T5 , Nil , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate5<T1 , T2 , T3 , T4 , T5 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2 , T3 p3 , T4 p4 , T5 p5) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2 , p3 , p4 , p5);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 6
template <typename TR , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
class Signal<TR , T1 , T2 , T3 , T4 , T5 , T6 , Nil , Nil>
{
public:
	typedef fastdelegate::FastDelegate6<T1 , T2 , T3 , T4 , T5 , T6 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2 , T3 p3 , T4 p4 , T5 p5 , T6 p6) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2 , p3 , p4 , p5 , p6);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
//! params = 7
template <typename TR , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
class Signal<TR , T1 , T2 , T3 , T4 , T5 , T6 , T7 , Nil>
{
public:
	typedef fastdelegate::FastDelegate7<T1 , T2 , T3 , T4 , T5 , T6 , T7 , TR> BaseType;
	Signal(){}
	void Emit(T1 p1 , T2 p2 , T3 p3 , T4 p4 , T5 p5 , T6 p6 , T7 p7) const
	{
		std::list<BaseType>::const_iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			(*p).operator()(p1 , p2 , p3 , p4 , p5 , p6);
		}
	}
	template <typename TObj , typename TFunc>
	void Connect(TObj Obj , TFunc func)
	{
		m_list.push_back(fastdelegate::MakeDelegate(Obj , func));
	}
	template <typename TObj , typename TFunc>
	void Disconnect(TObj Obj , TFunc func)
	{
		BaseType temp = fastdelegate::MakeDelegate(Obj , func);
		std::list<BaseType>::iterator p = m_list.begin();
		for(;p!=m_list.end() ; ++p)
		{
			if((*p) == temp)
			{
				m_list.erase(p);
				break;
			}
		}
	}
private:
	std::list<BaseType> m_list;
};
#endif