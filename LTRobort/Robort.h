#ifndef _ROBORT_H_
#define _ROBORT_H_

#include "LoginOn.h"
#include "SimpleMap.h"
#include "StateMachine.h"
#include "RobortState.h"

//������״̬
enum StateType
{
	ST_IDLE, 		//����
	ST_FREEMOVE,	//�ƶ�
	ST_ATTACK,		//����

	ST_NUM
};

// �����˲���
enum RobortType
{
	RT_1,			//����������� �ƶ�
	RT_2,			//����ƶ�
	RT_3,			//��Χ�ƶ�
	RT_4,			//վ��ԭ��
	RT_5			//����
};
class Robort
{
public:
	Robort();
	~Robort();
	
	void	Init();
	static unsigned int WINAPI thread_update(void* p);
	void	Update();
	static unsigned int WINAPI thread_update_login(void* p);
	void	UpdateLogin();
	void	Quit();
	
	HANDLE	GetUpdataHandle() { return m_hUpdate; }
	void    Connect();
	void	RegisterCommand();
	void	UnregisterCommand();

	/** ��ʼ�������������
	*/
	DWORD NetInitLocalPlayerAtt(NET_SIS_get_role_init_state_att* pNetCmd, DWORD);
	DWORD NetRecvGotoMap(NET_SIS_goto_new_map* pMsg, DWORD pPrama);

	DWORD OnNS_GetRemoteRoleState( NET_SIS_get_remote_role_state *pNetCmd, DWORD );
	DWORD OnNS_GetMonsterState(NET_SIS_get_remote_creature_state* pNetCmd, DWORD);
	DWORD OnNET_SIS_remove_remote(NET_SIS_remove_remote* pNetCmd, DWORD);

	DWORD OnNS_SyncWalk(NET_SIS_synchronize_walk* pNetCmd, DWORD dwParam);	
	DWORD OnNS_SyncStand(NET_SIS_synchronize_stand* pNetCmd, DWORD dwParam);
	DWORD OnNS_MoveFailed(NET_SIS_move_failed* pNetCmd, DWORD dwParam);
	DWORD OnNS_RoleDead( NET_SIS_role_dead* pMsg, DWORD dwParam );
	
	DWORD OnNET_SIS_set_state(NET_SIS_set_state* pMsg, DWORD dwParam);
	DWORD OnNET_SIS_skill(NET_SIS_skill* pMsg, DWORD dwParam);
	void	OnGotoCommand(CPoint point);
	void	OnWalkCommand(CPoint point);
	void	AskRoleInitState();
	void	AskRemoteRoleState(DWORD dwRoldID);	
	//�ж�״̬
	bool IsInState(EState eState){ return m_state.IsSet(eState) != FALSE;}

	VOID	FreeMove(INT dwPatrolRadius, BOOL bInArea = FALSE);
	VOID	GoToRandPos(INT dwPatrolRadius, BOOL bInArea = FALSE);
	DWORD	MakeSkillMsgSerial();
	VOID	UseSkill(DWORD dwSKillID, DWORD dwTarget = 0);
	inline	void SaveLoginRoleID(DWORD dwID)	{ m_dwRoleID = dwID; }
	inline	Vector3 GetHeroPos()	{ return m_vHeroPos; }

	VOID	SetAccount(const char* szAccount);
	VOID	SetPassWord(const char* szPassWord);
	VOID	SetLoginServer(const char* szLoginServerIP);
	VOID	SetWorldName(const char* szWorldName);
	VOID	SetLoginServerProt(DWORD nPort);
		
	void	SetState(StateType ST);
	BOOL	IsInState(StateType ST) { return m_StateTyep == ST; }
	StateMachine<Robort>*	GetFMS(){return m_pStateMachine;}
	BOOL	InWorld() { return m_bFreeMove;}

	VOID	GMCommand(LPCTSTR szCommand);
	
	DWORD	GetRoleID() { return m_dwRoleID;}
	void	SetLoginRoleIndex(DWORD index) { m_nRoleIndex = index;}
	DWORD	GetLoginRoleIndex() { return m_nRoleIndex; }

	VOID	RandChangeMap();

	DWORD	GetTargetID() { return m_dwTargetID;}

	DWORD	GetNomalAttackID();

	VOID	SelRandTarget();

	VOID	RandGo();

	BOOL	IsConnect() 
	{ 
		if (VALID_POINT(m_pSession))
		{
			return m_pSession->IsConnect(); 
		}
		return false;
	}

	void	SetType(INT rt) { m_robortType = rt; }
	INT GetType() { return m_robortType; }
	
	void	SetMap(TCHAR * pStrMap) { _tcsncpy(m_szMap, pStrMap, X_LONG_NAME); }
private:
	//CClientDlg* m_pDlg;
	StateType				m_StateTyep;
	StateMachine<Robort>*	m_pStateMachine;	//������״̬��
	LoginOn					m_pLogin;							
	NetSession*				m_pSession;
	Tang::NetCmdMgr*		m_pCmdMgr;
	DWORD					m_nRoleIndex;//�����ɫ���
	
	
	SMap<DWORD, Vector3>	m_MonsterMap;
	SimpleMap*				m_pSimpleMap;
	DWORD					m_dwRoleID;
	Vector3					m_vHeroPos;
	Vector3					m_vRebornPos;
	EClassType				m_eClass;
	tagDWORDFlagArray<ES_End>	m_state;			// �������������Ľ�ɫ״̬
	
	DWORD					m_dwTargetID;
	BOOL					m_bFreeMove;
	BOOL					m_bUpdate;
	HANDLE					m_hUpdate;
	HANDLE					m_hUpdateLogin;
	BOOL					b;

	State<Robort>*			m_pState[ST_NUM];

	INT						m_robortType;		//����
	TCHAR					m_szMap[X_LONG_NAME];
	//bool					bChangeMap;
	//HANDLE m_hRecvGameMsg;
	//bool	m_bRecMsg;	
};

#endif