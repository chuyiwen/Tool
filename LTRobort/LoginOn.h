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
	ELS_ConnectZoneServer,		// 连接区域服务器
	ELS_SentJoinGame,			// 发送JoinGame消息
	ELS_JoinGame,				// 接收到JoinGame消息后
	ELS_Launcher,				// 版本不对,启动更新程序
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
	//发送登录消息
    void     SendLoginMsg();

	tstring  GetWorkPath();

	void     GetMAC(std::string& strMAC);

    void  WaitProofResult();
	void  WaitQueue();
	void  TryIsConnectZoneSer();

    VOID SetState(DWORD status);

	VOID ShowUserPwdInfo(DWORD nInfo);

	BOOL Update();

	// 断开与zone服务器的连接
	VOID CutOffZone();


	// 接收玩家的角色信息
	DWORD NetRecvEnumRole(NET_SIS_enum_role* pMsg, DWORD pPrama);

	// 接收玩家的选择角色信息
	DWORD NetRecvSelectRole(NET_SIS_select_role* pMsg, DWORD pPrama);

	// 接收玩家删除角色信息
	DWORD NetRecvDeleteRole(NET_SIS_delete_role* pMsg, DWORD pPrama);
	
	//玩家创建角色
	DWORD NetRecvCreateRole(NET_SIS_create_role* pMsg, DWORD pPrama);
	
	BOOL Init(NetSession* pNetSession, Tang::NetCmdMgr* pNetCmdMgr, Robort* pOwner);
	BOOL Destroy();

	//申请获得角色列表
	void  GetEnumRole();

	//申请加入游戏
	DWORD NetRecvJoinGame(NET_SIS_join_game* pMsg, DWORD pPrama);

	//创建角色
	//void CreateRole(TCHAR *pszRoleName);

	//void CreateRoleAuto(TCHAR *pszRoleName,int RoleIndex);

	//发送删除角色消息
	VOID SendDeleRoleMsg(int nSelectRoleID);

	//发送进入游戏消息
	VOID SendEnterGameMsg(int nSelectRoleID);

	//发送建立角色消息
	VOID SendCreateRoleMsg();
	//显示主窗体
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