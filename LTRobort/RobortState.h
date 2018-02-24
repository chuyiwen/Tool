#ifndef _ROBORTSTATE_H_
#define _ROBORTSTATE_H_
#include "State.h"

class Robort;


//����״̬
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


//�����ƶ�״̬
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

//����Ŀ��״̬
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