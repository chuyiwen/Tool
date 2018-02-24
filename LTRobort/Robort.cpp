#include "stdafx.h"
#include "Robort.h"
#include "GameLog.h"

const TCHAR sz_map_name[11][32] = {_T("s01"), _T("s02"), _T("s03"), _T("s04"), _T("s05"), _T("s06"), _T("s07"), _T("s08"), _T("s09"), _T("13"), _T("s20")};

unsigned int Robort::thread_update_login(void* p)
{
	Robort* pThis = (Robort*)p;
	pThis->UpdateLogin( );

	_endthreadex(0);
	return 0;
}


unsigned int Robort::thread_update(void* p)
{
	Robort* pThis = (Robort*)p;
	pThis->Update( );
	_endthreadex(0);
	return 0;
}

Robort::Robort() : m_dwRoleID(-1), m_hUpdate(0), m_dwTargetID(0)
{
	//m_pCmdMgr = TObjRef<NetCmdMgr>();
	m_pStateMachine = new StateMachine<Robort>(this);
	m_pStateMachine->SetCurrentState(new IdleState);
	
	m_bFreeMove = FALSE;
	m_bUpdate = TRUE;
	m_nRoleIndex = 0;
	b = TRUE;
	
	m_pState[0]	= new IdleState();

	m_pState[1] = new FreeMoveState();

	m_pState[2] = new AttackState();
	
	m_robortType = RT_1;

	memset(m_szMap, 0, sizeof(m_szMap));
	//bChangeMap = TRUE;
}

Robort::~Robort()
{
	WaitForSingleObject(m_hUpdate, INFINITE);

	if (m_pSimpleMap != NULL)
	{
		delete m_pSimpleMap;
	}
	if (m_pStateMachine)
	{
		delete m_pStateMachine;
	}
	if (m_pSession)
	{
		delete m_pSession;
	}
	SAFE_DEL(m_pState[0]);
	SAFE_DEL(m_pState[1]);
	SAFE_DEL(m_pState[2]);
}

void Robort::Init()
{	
	m_pSession = new NetSession;
	m_pSimpleMap = new SimpleMap;
	m_pCmdMgr = new Tang::NetCmdMgr;
	m_pSession->Init(m_pCmdMgr);

	m_pLogin.Init(m_pSession, m_pCmdMgr, this);

	AskRoleInitState();
	//m_bRecMsg = true;	
	
	MapLogicData::Inst()->load();		
	
	RegisterCommand();
}

void Robort::Quit()
{
	m_bUpdate = FALSE;
	UnregisterCommand();
	//m_bRecMsg = false;

}

void Robort::UseSkill(DWORD dwSkillID, DWORD dwTarget)
{
	NET_SIC_skill cmd;
	cmd.dwSkillID		= dwSkillID;
	cmd.dwSerial		= MakeSkillMsgSerial();
	cmd.dwTargetRoleID	= dwTarget;
	cmd.vSrcPos			= GetHeroPos();
	m_pSession->Send(&cmd);
}

VOID Robort::GMCommand(LPCTSTR szCommand)
{
	if( m_pSession->IsConnect() )
	{
		NET_SIC_gm_command cmd;
		lstrcpyn(cmd.szCommand, szCommand, MAX_GM_COMMAND_LEN-1);
		m_pSession->Send(&cmd);

	}

}

void Robort::SetState(StateType ST)
{
// 	if (m_StateTyep == ST)
// 		return;

	m_StateTyep = ST;

	State<Robort>* pNewState = m_pState[m_StateTyep];	
	State<Robort>* pOldState = NULL;

	pOldState = m_pStateMachine->CurrentState();
	m_pStateMachine->ChangeState(pNewState);

}
void Robort::RegisterCommand()
{
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_goto_new_map",				Robort, NetRecvGotoMap,			_T("NET_SIS_goto_new_map"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_get_role_init_state_att",	Robort, NetInitLocalPlayerAtt,	_T("NET_SIS_get_role_init_state_att"));	

	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_synchronize_walk",			Robort,OnNS_SyncWalk,			_T("NET_SIS_synchronize_walk"));	
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_synchronize_stand",		Robort, OnNS_SyncStand,			_T("NET_SIS_synchronize_stand"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_move_failed",				Robort, OnNS_MoveFailed,		_T("NET_SIS_move_failed"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_role_dead",				Robort, OnNS_RoleDead,			_T("NET_SIS_role_dead"));

	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_get_remote_role_state",	Robort, OnNS_GetRemoteRoleState,_T("NET_SIS_get_remote_role_state"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_get_remote_creature_state",Robort, OnNS_GetMonsterState,			_T("NET_SIS_get_remote_creature_state"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_set_state",				Robort, OnNET_SIS_set_state,			_T("NET_SIS_set_state"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_skill",					Robort, OnNET_SIS_skill,			_T("NET_SIS_skill"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_remove_remote",			Robort, OnNET_SIS_remove_remote,			_T("NET_SIS_remove_remote"));
}

void Robort::UnregisterCommand()
{
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_goto_new_map",				Robort, NetRecvGotoMap);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_get_role_init_state_att",	Robort, NetInitLocalPlayerAtt);	

	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_synchronize_walk",			Robort, OnNS_SyncWalk);	
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_synchronize_stand",			Robort, OnNS_SyncStand);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_move_failed",				Robort, OnNS_MoveFailed);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_role_dead",					Robort, OnNS_RoleDead);

	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_get_remote_role_state",		Robort, OnNS_GetRemoteRoleState);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_get_remote_creature_state",	Robort, OnNS_GetMonsterState);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_set_state",					Robort, OnNET_SIS_set_state);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_skill",						Robort, OnNET_SIS_skill);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_remove_remote",				Robort, OnNET_SIS_remove_remote);
}

void Robort::Connect()
{
	m_pLogin.Connect();

	m_hUpdate = (HANDLE)_beginthreadex(NULL, 0, &Robort::thread_update, this, 0, NULL);

	m_hUpdateLogin = (HANDLE)_beginthreadex(NULL, 0, &Robort::thread_update_login, this, 0, NULL);
}

void Robort::UpdateLogin()
{
	while (m_bUpdate)
	{
		if(!m_pLogin.Update())
			break;

		Sleep(10);
	}

	return;
}


void Robort::Update()
{
	while (m_bUpdate)
	{
		//m_pLogin.Update();
		m_pSession->Update();
		if (m_bFreeMove)
		{
			m_pStateMachine->Update();
		}
		
		Sleep(20);
	}

	return;
}
static DWORD n_rand_seed = 0;
DWORD Robort::NetInitLocalPlayerAtt( NET_SIS_get_role_init_state_att* pNetCmd, DWORD )
{
	DWORD dwMapID = pNetCmd->dwRebornMapID;	
	m_state.Init(pNetCmd->dwState);
	
	m_eClass = pNetCmd->eClassType;

	const tagMapLogicData* pData = MapLogicData::Inst()->FindMapLogicData(dwMapID);
	if(VALID_POINT(pData))
	{
		m_pSimpleMap->SetMapLogicData(*pData);

		AskRemoteRoleState(m_dwRoleID);
	}
	m_bFreeMove = TRUE;
	if(IsInState(ES_Dead))
	{
		GMCommand(_T("silver 100"));
		NET_SIC_role_revive cmd;
		cmd.eType = ERRT_Locus;
		cmd.n64ItemID = 0;
		m_pSession->Send(&cmd);
	}
	//GMCommand(_T("invincible"));
	if(b && ( m_robortType == RT_1 || m_robortType == RT_2) )
	{
		((n_rand_seed = n_rand_seed * 1103515245 + 12345) >> 1 ) & LONG_MAX;
		INT n_map_rand = n_rand_seed%12;
		INT n_map_x = n_rand_seed%700;
		INT n_map_y = n_rand_seed%700;

		CString str;
		str.Format(_T("goto %s %d %d"), sz_map_name[n_map_rand], n_map_x, n_map_y);
		GMCommand(str);
		m_vHeroPos.x = n_map_x * 50;
		m_vHeroPos.z = n_map_y * 50;

		GMCommand(_T("addskill 3000101"));
		SetState(ST_IDLE);

		b = false;
	}
	else if(b && m_robortType == RT_3)
	{

		TCHAR temp[X_SHORT_NAME] = _T("");
		_stprintf(temp, _T("goto %s"), m_szMap);

		GMCommand(temp);
		b = false;
		
		_stscanf(temp, _T("%s %s %f %f"), temp ,temp, &m_vRebornPos.x, &m_vRebornPos.z);
		m_vRebornPos.x *= 50;
		m_vRebornPos.z *= 50;
	}
	else if(b && m_robortType == RT_4)
	{
		TCHAR temp[X_SHORT_NAME] = _T("");
		_stprintf(temp, _T("goto %s"), m_szMap);

		GMCommand(temp);

		_stscanf(temp, _T("%s %s %f %f"), temp ,temp, &m_vRebornPos.x, &m_vRebornPos.z);
		m_vRebornPos.x *= 50;
		m_vRebornPos.z *= 50;

		GoToRandPos(1000, true);

		SetState(ST_IDLE);
		
		b = false;
	}
	else if(b && m_robortType == RT_5)
	{
		TCHAR temp[X_SHORT_NAME] = _T("");
		_stprintf(temp, _T("att 26 10000"));

		GMCommand(temp);
		
		memset(temp, 0, sizeof(temp));
		_stprintf(temp, _T("goto %s"), m_szMap);

		GMCommand(temp);

		_stscanf(temp, _T("%s %s %f %f"), temp ,temp, &m_vRebornPos.x, &m_vRebornPos.z);
		m_vRebornPos.x *= 50;
		m_vRebornPos.z *= 50;

		GoToRandPos(1000, true);

		SetState(ST_IDLE);
	
		NET_SIC_practice_begin send;
		send.dw_speed_item_data_id = INVALID_VALUE;
		m_pSession->Send(&send);
		b = false;
	}

// 	if (bChangeMap)
// 	{
// 		RandChangeMap();
// 		bChangeMap = FALSE;
// 	}
	
	return 0;
}

VOID	Robort::RandChangeMap()
{
	INT mapID = Tang::f_util::GetSingleton().tool_rand()%30;
	TCHAR szGmCmd[X_SHORT_NAME] = _T("");

	_stprintf_s(szGmCmd, _countof(szGmCmd), _T("%s%d%s"), _T("goto TestMap"), mapID, _T(" 16 16"));
	GMCommand(szGmCmd);
}

DWORD Robort::OnNS_GetRemoteRoleState( NET_SIS_get_remote_role_state *pNetCmd, DWORD )
{
	if (pNetCmd->RoleData.dwID == m_dwRoleID)
	{
		m_eClass = pNetCmd->RoleData.eClassType;
		m_vHeroPos.x = pNetCmd->RoleData.fPos[0];
		m_vHeroPos.y = pNetCmd->RoleData.fPos[1];
		m_vHeroPos.z = pNetCmd->RoleData.fPos[2];
	}

	//m_bFreeMove = TRUE;
	return 0;
}

DWORD Robort::OnNS_GetMonsterState(NET_SIS_get_remote_creature_state* pNetCmd, DWORD)
{
	if (pNetCmd->CreatureData.eCreType == ECT_Monster && !IsInState(ST_ATTACK) && m_robortType == RT_1)
	{
		m_dwTargetID = pNetCmd->CreatureData.dwID;

		TCHAR szTemp[X_SHORT_NAME] = _T("");
		INT x = (INT)pNetCmd->CreatureData.fPos[0]/50;
		INT z = (INT)pNetCmd->CreatureData.fPos[2]/50;
		_stprintf(szTemp, _T("goto map %d %d"), x, z);
		GMCommand(szTemp);
		m_vHeroPos.x = pNetCmd->CreatureData.fPos[0];
		m_vHeroPos.y = pNetCmd->CreatureData.fPos[1];
		m_vHeroPos.z = pNetCmd->CreatureData.fPos[2];
		SetState(ST_ATTACK);
	}
	return 0;
}

DWORD Robort::OnNET_SIS_remove_remote(NET_SIS_remove_remote* pNetCmd, DWORD)
{
	int num = ( pNetCmd->dw_size - sizeof(NET_SIS_remove_remote) ) / sizeof(DWORD) + 1;
	for(int i=0;i<num;i++)
	{
		m_MonsterMap.Erase(pNetCmd->dw_role_id[i]);
	}

	return 0;
}

DWORD Robort::NetRecvGotoMap(NET_SIS_goto_new_map* pMsg, DWORD pPrama)
{	
	ASSERT(pMsg);
	const tagMapLogicData* pMapLogicData=MapLogicData::Inst()->FindMapLogicData(pMsg->dwMapID);
	if(VALID_POINT(pMapLogicData))
	{

		m_pSimpleMap->SetMapLogicData(*pMapLogicData);
		m_vHeroPos = pMsg->pos;
	}	
	AskRoleInitState();
	return 0;
}

DWORD Robort::OnNS_SyncWalk(NET_SIS_synchronize_walk* pNetCmd, DWORD dwParam)
{	
	if( pNetCmd->dw_role_id == m_dwRoleID )
	{

	}
	return 0;
}

DWORD Robort::OnNS_SyncStand(NET_SIS_synchronize_stand* pNetCmd, DWORD dwParam)
{	
	if( pNetCmd->dw_role_id == m_dwRoleID )
	{
		m_vHeroPos = pNetCmd->curPos;
		m_bFreeMove = TRUE;
	}
	else
	{
		if (IS_CREATURE(pNetCmd->dw_role_id))
		{
			m_MonsterMap.Add(pNetCmd->dw_role_id, pNetCmd->curPos);
		}

	}
	return 0;
}

DWORD Robort::OnNS_MoveFailed( NET_SIS_move_failed* pNetCmd, DWORD dwParam )
{	
	m_vHeroPos = pNetCmd->curPos;		
	//GameLog::Instance()->GameLogOut(_T("Move Failed"));
	m_bFreeMove = TRUE;
	return 0;
}

DWORD Robort::OnNS_RoleDead( NET_SIS_role_dead* pMsg, DWORD dwParam )
{
	if (pMsg->dw_role_id == m_dwRoleID)
	{
		NET_SIC_role_revive cmd;
		cmd.eType = ERRT_Locus;
		cmd.n64ItemID = 0;
		m_pSession->Send(&cmd);
	}
	return 0;
}

DWORD Robort::OnNET_SIS_set_state(NET_SIS_set_state* pMsg, DWORD dwParam)
{
	if (pMsg->dw_role_id == m_dwTargetID && pMsg->eState == ES_Dead && m_robortType == RT_1)
	{
		RandGo();
		SetState(ST_IDLE);
		m_dwTargetID = 0;
	}
	return 0;
}

DWORD Robort::OnNET_SIS_skill(NET_SIS_skill* pMsg, DWORD dwParam)
{
	if (pMsg->dw_error_code != E_Success)
	{
		SetState(ST_IDLE);
		m_dwTargetID = 0;
	}
	return 0;
}
void Robort::OnWalkCommand(CPoint point)
{
	Vector3 vWorldPos;
	m_pSimpleMap->ScreenPosToWorldPos(point, vWorldPos);

	NET_SIC_mouse_walk cmd;
	cmd.srcPos=m_vHeroPos;
	cmd.dstPos=vWorldPos;
	cmd.bSwim=false;
	m_pSession->Send(&cmd);	
}

void Robort::OnGotoCommand(CPoint point)
{
	//TCHAR szCommand[50];

	Vector3 vWorldPos;
	m_pSimpleMap->ScreenPosToWorldPos(point, vWorldPos);

	point.x = int(vWorldPos.x/50);
	point.y = int(vWorldPos.z/50);

	//swprintf(szCommand, _T("goto %s %d %d"), m_pDlg->m_szSelectMapName, point.x, point.y);

	//TObjRef<GameConsole>()->GMCommand(szCommand);
}

void Robort::AskRoleInitState()
{
	NET_SIC_get_role_init_state cmd;
	cmd.eType = ERIT_Att;
	m_pSession->Send(&cmd);
}

void Robort::AskRemoteRoleState(DWORD dwRoldID)
{
	BYTE byTemp[sizeof(NET_SIC_get_remote_role_state)+sizeof(DWORD)*50];
	NET_SIC_get_remote_role_state* pSend = (NET_SIC_get_remote_role_state*)byTemp;
	pSend->dw_message_id = pSend->message_id_crc("NET_SIC_get_remote_role_state");
	pSend->nRoleNum = 1;
	pSend->dw_role_id[0] = dwRoldID;

	if( pSend->nRoleNum > 0 )
	{
		pSend->dw_size = sizeof(NET_SIC_get_remote_role_state)
			+ sizeof(DWORD) * (pSend->nRoleNum - 1);
		m_pSession->Send(pSend);		
	}
}

VOID Robort::FreeMove(INT dwPatrolRadius, BOOL bInArea /*= FALSE*/)
{
	INT nRange = dwPatrolRadius * 2;
	

	Vector3 vWorldPos;
	
	Vector3 vCent;
	vCent = m_vHeroPos;
	if (bInArea)
	{
		vCent = m_vRebornPos;
	}
	vWorldPos.x = float(Tang::f_util::GetSingleton().tool_rand() % nRange - dwPatrolRadius) + vCent.x;//m_vHeroPos.x;
	vWorldPos.z = float(Tang::f_util::GetSingleton().tool_rand() % nRange - dwPatrolRadius) + vCent.z;//m_vHeroPos.z;
	
	float nWidth = 0.0f;
	float nHeight = 0.0f;
	if (m_pSimpleMap != NULL)
	{
		m_pSimpleMap->GetSimpleMapSize(nWidth, nHeight);
		vWorldPos.x = vWorldPos.x > nWidth ? vWorldPos.x : nWidth;
		vWorldPos.z = vWorldPos.z > nHeight ? vWorldPos.z : nHeight;
	}
	
	NET_SIC_mouse_walk cmd;
	cmd.srcPos=m_vHeroPos;
	cmd.dstPos=vWorldPos;
	cmd.bSwim=false;
	m_pSession->Send(&cmd);
	
	
	m_vHeroPos = vWorldPos;
	
}

VOID Robort::GoToRandPos(INT dwPatrolRadius, BOOL bInArea)
{
	INT nRange = dwPatrolRadius * 2;


	Vector3 vWorldPos;

	Vector3 vCent;
	vCent = m_vHeroPos;
	if (bInArea)
	{
		vCent = m_vRebornPos;
	}
	vWorldPos.x = float(Tang::f_util::GetSingleton().tool_rand() % nRange - dwPatrolRadius) + vCent.x;//m_vHeroPos.x;
	vWorldPos.z = float(Tang::f_util::GetSingleton().tool_rand() % nRange - dwPatrolRadius) + vCent.z;//m_vHeroPos.z;

	float nWidth = 0.0f;
	float nHeight = 0.0f;
	if (m_pSimpleMap != NULL)
	{
		m_pSimpleMap->GetSimpleMapSize(nWidth, nHeight);
		vWorldPos.x = vWorldPos.x > nWidth ? vWorldPos.x : nWidth;
		vWorldPos.z = vWorldPos.z > nHeight ? vWorldPos.z : nHeight;
	}
	
	TCHAR temp[X_SHORT_NAME] = _T("");
	INT nx = vWorldPos.x / 50;
	INT nz = vWorldPos.z / 50;
	_stprintf(temp, _T("goto sss %d %d"), nx, nz);


	GMCommand(temp);

	//NET_SIC_mouse_walk cmd;
	//cmd.srcPos=m_vHeroPos;
	//cmd.dstPos=vWorldPos;
	//cmd.bSwim=false;
	//m_pSession->Send(&cmd);


	m_vHeroPos = vWorldPos;
}
DWORD	Robort::MakeSkillMsgSerial()
{
	static DWORD serial=1;
	return serial++;
}

VOID Robort::SetAccount(const char* szAccount)
{
	sprintf_s(m_pLogin.m_szAccount,32,"%s", szAccount);
}
VOID Robort::SetPassWord(const char* szPassWord)
{
	sprintf_s(m_pLogin.m_szPwd,32,"%s", szPassWord);
}
VOID Robort::SetLoginServer(const char* szLoginServerIP)
{
	sprintf_s(m_pLogin.m_LoginServerIP, 17,"%s", szLoginServerIP);
}
VOID Robort::SetWorldName(const char* szWorldName)
{
	sprintf_s(m_pLogin.m_szWorldName, 32, "%s", szWorldName);
}
VOID Robort::SetLoginServerProt(DWORD nPort)
{
	m_pLogin.m_LoginServerPort = nPort;
}

DWORD Robort::GetNomalAttackID()
{
	switch(m_eClass)
	{
	case EV_Null: return 1000001;
	case EV_Warrior: return 1010001;
	case EV_defend: return 1020001;
	case EV_knight: return 1030001;
	case EV_Assassin: return 1040001;
	case EV_Apothecary: return 1050001;
	}
}

VOID Robort::SelRandTarget()
{
	DWORD dwTargetID = 0;
	Vector3 vPos;

	INT nSize = m_MonsterMap.Size();
	if( nSize <= 0 )
	{
		SetState(ST_FREEMOVE);
		return;
	}
	INT nRand = Tang::f_util::GetSingleton().tool_rand() % nSize;

	std::map<DWORD, Vector3>::iterator it = m_MonsterMap.Begin();
	for(INT n=0; n<nRand; n++)
		++it;

	dwTargetID = it->first;
	vPos = it->second;


	m_dwTargetID = dwTargetID;

	TCHAR szTemp[X_SHORT_NAME] = _T("");
	INT x = (INT)vPos.x/50;
	INT z = (INT)vPos.z/50;
	_stprintf(szTemp, _T("goto map %d %d"), x, z);
	GMCommand(szTemp);
	m_vHeroPos = vPos;
	
}

VOID Robort::RandGo()
{
	//INT n_map_rand = Tang::f_util::GetSingleton().tool_rand()%12;
	INT n_map_x = Tang::f_util::GetSingleton().tool_rand()%700;
	INT n_map_y = Tang::f_util::GetSingleton().tool_rand()%700;

	CString str;
	str.Format(_T("goto map %d %d"), n_map_x, n_map_y);
	GMCommand(str);
	m_vHeroPos.x = n_map_x * 50;
	m_vHeroPos.z = n_map_y * 50;
}