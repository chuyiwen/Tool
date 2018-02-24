#ifndef _ROBORTSTATE_H_
#define _ROBORTSTATE_H_
#include "State.h"

class Robort;


//¿ÕÏÐ×´Ì¬
class IdleState : public State<Robort>
{
public:
	IdleState(){m_dwBeginTime = 0;}

	virtual void Enter(Robort* pRobort);

	virtual void Update(Robort* pRobort);

	virtual void Exit(Robort* pRobort);
protected:
	DWORD	m_dwBeginTime;
};


//×ÔÓÉÒÆ¶¯×´Ì¬
class FreeMoveState : public State<Robort>
{
public:
	FreeMoveState(){m_dwBeginTime = 0;}

	virtual void Enter(Robort* pRobort);

	virtual void Update(Robort* pRobort);

	virtual void Exit(Robort* pRobort);
protected:
	DWORD	m_dwBeginTime;
};

//¹¥»÷Ä¿±ê×´Ì¬
class AttackState: public State<Robort>
{
public:
	AttackState(){m_dwBeginTime = 0;}

	virtual void Enter(Robort* pRobort);

	virtual void Update(Robort* pRobort);

	virtual void Exit(Robort* pRobort);
protected:
	DWORD	m_dwBeginTime;

};
#endif