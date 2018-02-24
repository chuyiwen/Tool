#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include "State.h"

template<typename entity_type>
class StateMachine
{
public:
	StateMachine(entity_type* owner):m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pGlobalState(NULL)
	{}

	virtual ~StateMachine(){}

	void SetCurrentState(State<entity_type>* s){m_pCurrentState = s;}
	void SetGlobalState(State<entity_type>* s) {m_pGlobalState = s;}

	void  Update()const
	{
		if(m_pGlobalState)   m_pGlobalState->Update(m_pOwner);

		if (m_pCurrentState) m_pCurrentState->Update(m_pOwner);
	}

	void  ChangeState(State<entity_type>* pNewState)
	{
		assert(pNewState);

		m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = pNewState;

		m_pCurrentState->Enter(m_pOwner);
	}

 
	bool  isInState(const State<entity_type>& st)const
	{
		return typeid(*m_pCurrentState) == typeid(st);
	}

	State<entity_type>*  CurrentState()  const{return m_pCurrentState;}
	State<entity_type>*  GlobalState()   const{return m_pGlobalState;}

private:
	//状态机所有者
	entity_type*          m_pOwner;

	//当前状态
	State<entity_type>*   m_pCurrentState;
	//全局状态
	State<entity_type>*   m_pGlobalState;
};
#endif