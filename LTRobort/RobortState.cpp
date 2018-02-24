#include "stdafx.h"
#include "RobortState.h"
#include "Robort.h"

void IdleState::Enter(Robort* pRobort)
{
	m_dwBeginTime = timeGetTime();
	//pRobort->FreeMove(1500, TRUE);
}

void IdleState::Update(Robort* pRobort)
{
	//if (!pRobort->InWorld())
	//	return;

	if (pRobort->GetType() == RT_4 || pRobort->GetType() == RT_5)
	{
		return;
	}
	DWORD dwCurTime = timeGetTime();
	if (dwCurTime - m_dwBeginTime > 2000)
	{
		pRobort->SetState(ST_FREEMOVE);
		m_dwBeginTime = dwCurTime;
	}
	if (dwCurTime - m_dwBeginTime > 200000)
	{
		/*srand( (unsigned)time( NULL ) );
		CString str;
		INT n_x = rand() % 1024;
		INT n_z = rand() % 1024;
		str.Format(_T("gm goto %d %d"), n_x, n_z);
		pRobort->GMCommand(str);*/
	}
}

void IdleState::Exit(Robort* pRobort)
{

}

// ÒÆ¶¯×´Ì¬ [4/6/2011 Administrator]
void FreeMoveState::Enter(Robort* pRobort)
{
	m_dwBeginTime = timeGetTime();
	BOOL bInArea = (pRobort->GetType() == RT_3);
	
	pRobort->FreeMove(240, bInArea);
	
}

void FreeMoveState::Update(Robort* pRobort)
{
	DWORD dwCurTime = timeGetTime();
	if (dwCurTime - m_dwBeginTime > 3000)
	{
		m_dwBeginTime = dwCurTime;
		if (pRobort->GetType() == RT_1)
		{
			pRobort->SetState(ST_ATTACK);
		}
		else
		{
			pRobort->SetState(ST_IDLE);
		}
		
	}
	
}

void FreeMoveState::Exit(Robort* pRobort)
{

}

// ¹¥»÷×´Ì¬ [4/6/2011 Administrator]
void AttackState::Enter(Robort* pRobort)
{
	m_dwBeginTime = timeGetTime();
	pRobort->SelRandTarget();
}

void AttackState::Update(Robort* pRobort)
{
	DWORD dwCurTime = timeGetTime();
	if (dwCurTime - m_dwBeginTime > 2000)
	{
		//pRobort->UseSkill(pRobort->GetNomalAttackID(), pRobort->GetTargetID());
		pRobort->UseSkill(3000101, pRobort->GetTargetID());
		m_dwBeginTime = dwCurTime;
	}
}

void AttackState::Exit(Robort* pRobort)
{

}