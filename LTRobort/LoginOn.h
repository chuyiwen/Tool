#pragma once
#include "x_client.h"
#include "package_map.h"
#include "NetSession.h"
#include "net_define.h"
#include "select_role_protocol.h"
#include "RoleDefine.h"
#include "role_att_protocol.h"
#include "map_protocol.h"
#include "combat_protocol.h"
#include "dword_flag.h"
#include "gm_protocol.h"


enum ELoginState
{
	ELS_WaitInput,
	ELS_Connect,
	ELS_WaitProofResult,
	ELS_MiBao,
	ELS_Queue,
	ELS_ConnectZoneServer,		// �������������
	ELS_SentJoinGame,			// ����JoinGame��Ϣ
	ELS_JoinGame,				// ���յ�JoinGame��Ϣ��
	ELS_Launcher,				// �汾����,�������³���
};

class Robort;
struct RoleSimpleData
{
	int         m_nRoleID;
	TCHAR		m_szRoleName[X_SHORT_NAME];
	RoleSimpleData()
	{
		memset(this,0,sizeof(*this));
	}
};

class LoginOn
{
public:
	LoginOn();
	~LoginOn();

	void     Connect();
	//���͵�¼��Ϣ
    void     SendLoginMsg();

	tstring  GetWorkPath();

	void     GetMAC(std::string& strMAC);

    void  WaitProofResult();
	void  WaitQueue();
	void  TryIsConnectZoneSer();

    VOID SetState(DWORD status);

	VOID ShowUserPwdInfo(DWORD nInfo);

	BOOL Update();

	// �Ͽ���zone������������
	VOID CutOffZone();


	// ������ҵĽ�ɫ��Ϣ
	DWORD NetRecvEnumRole(NET_SIS_enum_role* pMsg, DWORD pPrama);

	// ������ҵ�ѡ���ɫ��Ϣ
	DWORD NetRecvSelectRole(NET_SIS_select_role* pMsg, DWORD pPrama);

	// �������ɾ����ɫ��Ϣ
	DWORD NetRecvDeleteRole(NET_SIS_delete_role* pMsg, DWORD pPrama);
	
	//��Ҵ�����ɫ
	DWORD NetRecvCreateRole(NET_SIS_create_role* pMsg, DWORD pPrama);
	
	BOOL Init(NetSession* pNetSession, Tang::NetCmdMgr* pNetCmdMgr, Robort* pOwner);
	BOOL Destroy();

	//�����ý�ɫ�б�
	void  GetEnumRole();

	//���������Ϸ
	DWORD NetRecvJoinGame(NET_SIS_join_game* pMsg, DWORD pPrama);

	//������ɫ
	//void CreateRole(TCHAR *pszRoleName);

	//void CreateRoleAuto(TCHAR *pszRoleName,int RoleIndex);

	//����ɾ����ɫ��Ϣ
	VOID SendDeleRoleMsg(int nSelectRoleID);

	//���ͽ�����Ϸ��Ϣ
	VOID SendEnterGameMsg(int nSelectRoleID);

	//���ͽ�����ɫ��Ϣ
	VOID SendCreateRoleMsg();
	//��ʾ������
	void ShowMainWnd();
	
	BYTE GetSexByClass(EClassType eClass);

	CHAR						m_LoginServerIP[17];
	DWORD						m_LoginServerPort;
	CHAR						m_szAccount[32];
	CHAR						m_szPwd[32];
	CHAR						m_szWorldName[32];

private:
	Tang::Net::XClient*			m_pStream;
	NetSession*					m_pSession;
	Tang::NetCmdMgr*			m_pCmdMgr;

	Robort*						m_pOwner;
	tstring						m_strLog;
	DWORD	                    m_dwAccountID;
	DWORD	                    m_dwVerifyCode;
	DWORD                       m_dwZoneIP;
	DWORD                       m_dwZonePort;
	DWORD                       m_dwSentJoinGame;
	int                         m_eState;
	DWORD						m_dwStateTime;

	RoleSimpleData              m_RoleSimpleData[20];
	int                         m_CurRoleIndex;
	int                         m_CurRoleID;
	TCHAR                       m_CurRoleName[32];     

	int							m_sex;
	int							m_class;
	
};