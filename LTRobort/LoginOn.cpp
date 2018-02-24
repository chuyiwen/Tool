#include "stdafx.h"
#include "package_map.h"
#include "LoginOn.h"
#include "GameLog.h"
#include "login_protocol.h"
#include "select_role_protocol.h"
#include <process.h>
#include "SimpleMap.h"
#include <Iphlpapi.h>
#include "Robort.h"
#include "resource.h"
#include "LTRobortDlg.h"
#include "LTRobort.h"


LoginOn::LoginOn()
{	
    memset(m_LoginServerIP,0,sizeof(m_LoginServerIP));
	m_LoginServerPort = 0;
	memset(m_szAccount,0,sizeof(m_szAccount));
	memset(m_szPwd,0,sizeof(m_szPwd));
	memset(m_szWorldName,0,sizeof(m_szWorldName));
	m_eState=0;
	m_strLog.empty();

	m_dwStateTime	= timeGetTime();


	//m_pRoleListBox =NULL;
	m_CurRoleIndex =0;
	m_CurRoleID =0;
	//m_pWndMain = NULL;
	memset(m_CurRoleName,0,sizeof(m_CurRoleName));	

	m_pSession = NULL;
	m_pCmdMgr = NULL;
	m_dwAccountID = -1;
}

LoginOn::~LoginOn()
{

}

//开始登录
void LoginOn::Connect()
{
	if( m_pStream->IsConnected() )
	{
		this->SendLoginMsg();
		return;
	}

	if( m_pStream->IsTryingToConnect() )
		return;	// 仍然在尝试连接

	if( m_eState == ELS_Connect )	// 连接失败
	{
		SetState(ELS_WaitInput);
		GameLog::Instance()->GameLogOut(_T("无法连接LoginServer服务器"));
		return;
	}


	// 尝试连接
	m_pStream->TryToConnect(m_LoginServerIP, m_LoginServerPort);

	SetState(ELS_Connect);

	//HANDLE m_hRecvLoginMsg = (HANDLE)_beginthreadex(NULL, 0, (THREADPROC)m_Trunk.sfp0(&LoginOn::Update), NULL, 0, NULL);
	//m_pStream->Init(FALSE);

	//m_pStream->TryToConnect(m_LoginServerIP, m_LoginServerPort);
 //   int i=0;
	//while(i<500)
	//{
	//	if(m_pStream->IsConnected())
	//	{
	//		SendLoginMsg();
	//		break;
	//	}
	//	i++;
	//	Sleep(20);
	//}
	//if(i==500)
	//{
	//	GameLog::Instance()->GameLogOut(_T("无法连接LoginServer服务器"));
	//	return;
	//}

	// 启动线程 处理接收loginServer结果线程

	
	CString Sex, Class;
	((CLTRobortDlg*)theApp.GetMainWnd())->mSex.GetWindowText(Sex);
	((CLTRobortDlg*)theApp.GetMainWnd())->mClass.GetWindowText(Class);

	m_sex = _ttoi(Sex.GetBuffer());
	m_class = _ttoi(Class.GetBuffer());
}

//发送登录消息
void  LoginOn::SendLoginMsg()
{

    //发送nlc_proof
 	TCHAR szIniFileName[X_LONG_NAME] = _T(".\\RobortConfig.ini");
	TCHAR szTemp[X_LONG_NAME*2];
	//TCHAR szTemp1[X_LONG_NAME*2];

	//tstring strAppPath =GetWorkPath() ;

	//tstring strIniFileFullName = strAppPath + szIniFileName;
	::GetPrivateProfileString(_T("Launcher"), _T("LocalGameVersion"), NULL,  szTemp, X_LONG_NAME*2, szIniFileName);
	//::GetPrivateProfileString(_T("Launcher"), _T("version"), NULL,  szTemp1, X_LONG_NAME*2, szIniFileName);

	tstring version = szTemp;

    DWORD m_nPolicy =1;
	NET_C2L_proof send;
	send.dwType = m_nPolicy;		//验证方式
	tstring szWorldName =Tang::f_util::ansi_to_unicode(m_szWorldName);

	send.dw_world_name_crc = Tang::f_util::get_crc(szWorldName.c_str());
	send.dwCurVersionID = Tang::f_util::get_crc(version.c_str());
	
	Tang::f_md5 md5;
	switch(m_nPolicy)
	{
	case 0:					//内部使用
		{
			strncpy( send.szUserName, m_szAccount, X_SHORT_NAME );
			if( strcmp(m_szPwd,"")!=0 )
			{
				string pass = m_szPwd;
				//密钥
				pass += "ssplay.password";
				BYTE digest[16];
				md5.md5_for_string( (char*)pass.c_str(), digest );
				string strPswMD5;
				md5.md5_to_string( strPswMD5, digest );
				char szBuff[X_LONG_NAME] = {0};
				strncpy( szBuff, strPswMD5.c_str(), MAX_MD5_ARRAY );
				strupr( szBuff );
				strncpy( send.szPsd, szBuff, MAX_MD5_ARRAY );
			}
		}
		break;
	case 1:					//中心激活
		{
			strncpy( send.szUserName, m_szAccount, X_SHORT_NAME );
			string pass =m_szPwd;
			//密钥
			pass += "ssplay.password";
			BYTE digest[16];
			md5.md5_for_string( (char*)pass.c_str(), digest );
			string strPswMD5;
			md5.md5_to_string( strPswMD5, digest );
			char szBuff1[X_LONG_NAME] = {0};
			strncpy( szBuff1, strPswMD5.c_str(), MAX_MD5_ARRAY );
			strupr( szBuff1 );
			strncpy( send.szPsd, szBuff1, MAX_MD5_ARRAY );

			//MAC地址+C盘的序列号
			string strMAC;
			GetMAC(strMAC);
			DWORD Volue ;
			//API获得某个特定驱动器的序列号,这个程序中是获得C盘的序列号
			::GetVolumeInformation(_T("c:\\"), NULL, 12, &Volue, NULL, NULL, NULL, 10);
			char szBuff[64];
			std::string strTemp(_itoa(Volue, szBuff, 16));
			strMAC += strTemp;
			BYTE digest1[16];
			md5.md5_for_string( (char*)strMAC.c_str(), digest1 );
			string strGUIDMD5;
			md5.md5_to_string( strGUIDMD5, digest1 );
			strncpy( send.szGUID, strGUIDMD5.c_str(), MAX_MD5_ARRAY );
		}
		break;	
	
	}
	
	m_pStream->Send(&send, sizeof(send));

	SetState(ELS_WaitProofResult);    
}


//得到工作路径
tstring LoginOn::GetWorkPath()
{
	TCHAR szPathName[256];
	memset(szPathName,0,sizeof(szPathName));

   	GetModuleFileName(NULL,szPathName,sizeof(szPathName)/sizeof(TCHAR));
	TCHAR *find=::_tcsrchr(szPathName,_T('\\'));
	if(find!=NULL)
	{
		*find=0;
		find=::_tcsrchr(szPathName,_T('\\'));
		if(find!=NULL)
		{
			*(find+1)=0;
			_tcslwr_s(szPathName,sizeof(szPathName)/sizeof(TCHAR));
		}
	}
	tstring strPath = szPathName;
	return strPath;

}
//获得本机mac地址
void LoginOn::GetMAC(std::string& strMAC)   
{
	DWORD   Err;     
	PIP_ADAPTER_INFO   pAdapterInfo,   pAdapt;   
	DWORD   AdapterInfoSize;   

	AdapterInfoSize = 0;   
	if((Err = ::GetAdaptersInfo(NULL,&AdapterInfoSize))!=0)   
	{   
		if(Err != ERROR_BUFFER_OVERFLOW)   
		{   
			GameLog::Instance()->GameLogOut(_T("GetAdaptersInfo sizing failed with error: %u\n"));   
			strMAC = "";
			return;   
		}   
	}   

	if((pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize))==NULL)   
	{   
		GameLog::Instance()->GameLogOut(_T("Memory   allocation   error\n"));   
		strMAC = "";
		return;   
	}   

	//   Get   actual   adapter   information   
	if((Err = ::GetAdaptersInfo(pAdapterInfo,  &AdapterInfoSize))!= 0)   
	{   
		GameLog::Instance()->GameLogOut(_T("GetAdaptersInfo failed with error %u\n"));   
		strMAC = "";
		return;   
	}   

	pAdapt = pAdapterInfo;
	char szBuff[128] = {0};
	std::string str("");   
	if(pAdapt) 
	{
		int  i=1;   	
		for(int i=0; i<6; i++)   
		{      
			INT64 n64Value = INT64(pAdapt->Address[i]);
			std::string strTemp(_i64toa(n64Value, szBuff, 16));
			transform(strTemp.begin(), strTemp.end(), strTemp.begin(), toupper);
			str = str + strTemp;
		}   
	}
	strMAC = str;
}


//接收登录消息线程函数
void LoginOn::WaitProofResult()
{	
	if(timeGetTime() - m_dwStateTime > 30000)
	{
		m_pStream->Disconnect();
		SetState(ELS_WaitInput);
		GameLog::Instance()->GameLogOut(_T("连接超时"));
		return;
	}
    LPBYTE pMsg = NULL;
	DWORD dwMsgSize = 0;

	pMsg = m_pStream->Recv(dwMsgSize);
	if( IS_VALID_PTR(pMsg))
	{
		NET_L2C_proof_result* pRecv = (NET_L2C_proof_result*)pMsg;
		if( pRecv->dw_message_id == Tang::f_util::get_crc("NET_L2C_proof_result"))
		{
			if( pRecv->dw_error_code != E_Success )
			{
				ShowUserPwdInfo(pRecv->dw_error_code);					
				return ;
			}

			m_dwZoneIP		= pRecv->dw_ip;
			m_dwZonePort	= pRecv->dwPort;
			m_dwAccountID	= pRecv->dw_account_id;
			m_dwVerifyCode	= pRecv->dwVerifyCode;
			if (pRecv->dw_error_code == 0)
			{
				BOOL m_bGuard = pRecv->bGuard;
			}									
			CHAR* szIP = m_pStream->IP2String(m_dwZoneIP);
			m_pSession->Connect(Tang::f_util::utf8_to_unicode(szIP), m_dwZonePort);		//与zone服务器建立连接
			SetState(ELS_ConnectZoneServer);	
			m_pStream->FreeRecved(pMsg); 

			return;
		}
		m_pStream->FreeRecved(pMsg);
		Sleep(10);
	}


}

void LoginOn::WaitQueue()
{
	if ( !m_pStream->IsConnected() )
	{
		SetState(ELS_WaitInput);
		GameLog::Instance()->GameLogOut(_T("连接断开"));
		return;
	}

	unsigned char* pMsg = NULL;
	DWORD dwMsgSize = 0;

	pMsg = m_pStream->Recv(dwMsgSize);
	if( IS_VALID_PTR(pMsg) )
	{
		NET_L2C_queue* pRecv = (NET_L2C_queue*)pMsg;
		if( pRecv->dw_message_id == Tang::f_util::get_crc("NET_L2C_queue") )
		{
			TCHAR szBuff[X_LONG_NAME] = {0};
			_stprintf(szBuff, _T("账号:%u   排队位置:%u"), m_dwAccountID, pRecv->dwPosition);

			GameLog::Instance()->GameLogOut(szBuff);
			if( pRecv->dwPosition==0 )
			{
				SetState(ELS_WaitProofResult);
			}
		}

		m_pStream->FreeRecved(pMsg);
		Sleep(10);
	}
}
VOID LoginOn::SetState(DWORD status)
{
	if( m_eState == status )
		return;

    m_eState = status;

	m_dwStateTime = timeGetTime();
}

// 显示用户名\密码错误信息
VOID LoginOn::ShowUserPwdInfo(DWORD nInfo)
{
	switch(nInfo)
	{
	case E_ProofResult_Account_No_Match:
		GameLog::Instance()->GameLogOut(_T("此帐号非法(帐户不存在或者密码不对,密保错误)"));
		break;
	case E_ProofResult_Account_In_Use:
		GameLog::Instance()->GameLogOut(_T("此帐号当前已经在使用"));
		break;
	case E_ProofResult_Account_Freezed:
		GameLog::Instance()->GameLogOut(_T("此帐号被停用"));
		break;
	case E_ProofResult_Wrong_Type:
		GameLog::Instance()->GameLogOut(_T("非法验证策略"));
		break;
	case E_ProofResult_Mibao_Error:
		GameLog::Instance()->GameLogOut(_T("密保错误"));
		break;
	case E_ProofResult_Wrong_Build_Number:
		GameLog::Instance()->GameLogOut(_T("版本号不对"));
		break;
	case E_ProofResult_Disabled:
		GameLog::Instance()->GameLogOut(_T("此帐号已经被封停"));
		break;
	case E_SelectWorld_Server_Full:
		GameLog::Instance()->GameLogOut(_T("该服务器当前拥挤"));
		break;
	case E_SelectWorld_Server_Suspended:
		GameLog::Instance()->GameLogOut(_T("该服务器当前阻塞"));
		break;
	case E_SelectWorld_Server_Maintenance:
		GameLog::Instance()->GameLogOut(_T("该服务器当前维护"));
		break;
	case E_SelectWorld_Failed:
		GameLog::Instance()->GameLogOut(_T("出现异常，选择失败"));
		break;
	case E_SelectWorld_Short_Time:
		GameLog::Instance()->GameLogOut(_T("间隔时间太短,请稍候重试"));
		break;
	case E_SelectWorld_No_Select:
		GameLog::Instance()->GameLogOut(_T("你已经选择成功,不可再选"));
		break;
	case E_SelectWorld_GameWorldName_Wrong:
		GameLog::Instance()->GameLogOut(_T("非法的游戏世界名"));
		break;
	case E_SystemError:
		GameLog::Instance()->GameLogOut(_T("系统错误"));
		break;
	case E_ProofResult_Forbid_MemberCenter:
		GameLog::Instance()->GameLogOut(_T("您的会员中心账号已被封停，请联系客服"));
		break;
	case E_ProofResult_Forbid_GMTool:
		GameLog::Instance()->GameLogOut(_T("您的游戏账号已被封停，请联系客服"));
		break;
	case E_ProofResult_Forbid_CellPhone:
		GameLog::Instance()->GameLogOut(_T("您的账号已被锁定，请联系客服"));
		break;
	case E_ProofResult_Forbid_MiBao:
		GameLog::Instance()->GameLogOut(_T("您的账号已经挂失密保卡，请完成解绑后登录"));
		break;
	case E_ProofResult_Queue:
		{
			GameLog::Instance()->GameLogOut(_T("进入排队"));
			SetState(ELS_Queue);            
			return;
		}
		break;
	default:
		GameLog::Instance()->GameLogOut(_T("未知错误"));
		break;
	}
}
BOOL LoginOn::Update()
{
	switch(m_eState)
	{
	case ELS_WaitInput:
		break;
	case ELS_Connect:
		this->Connect();
		break;
	case ELS_WaitProofResult:
		this->WaitProofResult();
		break;
	case ELS_Queue:
		this->WaitQueue();
		break;
	case ELS_ConnectZoneServer:
		this->TryIsConnectZoneSer();
		break;
	case ELS_SentJoinGame:							//在发送join后,如果与zone服务器断开,则让玩家重新连接
		{
			if(!m_pSession->IsConnect())
				CutOffZone();
			if(timeGetTime() - m_dwSentJoinGame >= 10000)
				CutOffZone();
		}
		break;
	case ELS_JoinGame:
		{
			return FALSE;
		}
		break;
	case ELS_Launcher:
		//{
		//	if(timeGetTime() - m_dwStateTime >= 1000)
		//	{
		//		m_pClient->ExitThreadLoad();
		//		PostQuitMessage(0);
		//	}
		//}
		break;
	}
	
	Sleep(200);
	return TRUE;
	
	
}
// 断开与zone服务器的连接
VOID LoginOn::CutOffZone()
{
	SetState(ELS_WaitInput);
	m_pSession->Disconnect();
}


void  LoginOn::TryIsConnectZoneSer()
{
	if(m_pSession->IsConnect())
	{
		m_pStream->Disconnect();		
		//发送加入GameServer申请
		NET_SIC_join_game joinGameMsg;
		joinGameMsg.dw_account_id = m_dwAccountID;
		joinGameMsg.dwVerifyCode = m_dwVerifyCode;
		m_pSession->Send(&joinGameMsg);
		m_dwSentJoinGame = timeGetTime();
		SetState(ELS_SentJoinGame);
	}
	else if(timeGetTime() - m_dwStateTime > 10000)
	{
		//如果超时
		m_pStream->Disconnect();
		SetState(ELS_WaitInput);
		GameLog::Instance()->GameLogOut(_T("无法连接GameServer服务器"));
	}
}


//-----------------------------------------------------------------------------
// init
//-----------------------------------------------------------------------------
BOOL LoginOn::Init(NetSession* pNetSession, Tang::NetCmdMgr* pNetCmdMgr, Robort* pOwner)
{   

	//stringstream stream;
	//stream << "XClient_Login" << this;
	//m_pStream = CreateObj(stream.str().c_str(), "XClient");
	m_pStream = new Tang::Net::XClient;
	m_pStream->Init(FALSE);
	
	m_pSession = pNetSession;
	m_pCmdMgr = pNetCmdMgr;

	m_pOwner = pOwner;

	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_enum_role", LoginOn, NetRecvEnumRole, _T("NET_SIS_enum_role"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_select_role", LoginOn, NetRecvSelectRole, _T("NET_SIS_select_role"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_delete_role", LoginOn, NetRecvDeleteRole, _T("NET_SIS_delete_role"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_create_role", LoginOn, NetRecvCreateRole, _T("NET_SIS_create_role"));
	REGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_join_game", LoginOn, NetRecvJoinGame, _T("NET_SIS_join_game"));
	
	return TRUE;
}

//-----------------------------------------------------------------------------
// destroy
//-----------------------------------------------------------------------------
BOOL LoginOn::Destroy()
{
	
	//--注销网络消息
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_enum_role", LoginOn, NetRecvEnumRole);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_select_role", LoginOn, NetRecvSelectRole);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_delete_role", LoginOn, NetRecvDeleteRole);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_create_role", LoginOn, NetRecvCreateRole);
	UNREGISTER_NET_MSG(m_pCmdMgr, "NET_SIS_join_game", LoginOn, NetRecvJoinGame);

	return TRUE;
}


// 接收玩家的角色信息
DWORD LoginOn::NetRecvEnumRole(NET_SIS_enum_role* pMsg, DWORD pPrama)
{
	if(pMsg->dw_error_code == E_Success)
	{	
		//手动创建角色
		m_CurRoleIndex =0;
		memset(m_RoleSimpleData,0,sizeof(m_RoleSimpleData));
		//m_pRoleListBox->ResetContent();
		
		//如果没角色就自动建立一个
		if (pMsg->n_num == 0)
		{
			SendCreateRoleMsg();
		}
		tagSimRole* pRole = (tagSimRole *)pMsg->bySimpleInfo;
		for(int i=0; i<pMsg->n_num; i++)
		{
			//m_pRoleListBox->AddString(pRole->szRoleName);
			m_RoleSimpleData[m_CurRoleIndex].m_nRoleID = pRole->dw_role_id;
			lstrcpyn(m_RoleSimpleData[m_CurRoleIndex].m_szRoleName,pRole->szRoleName,sizeof(m_RoleSimpleData[m_CurRoleIndex].m_szRoleName)-1);
			m_CurRoleIndex++;				
			pRole++;				
		}
		if (pMsg->n_num > 0 && m_pOwner->GetLoginRoleIndex() < pMsg->n_num)
		{
			SendEnterGameMsg(m_RoleSimpleData[m_pOwner->GetLoginRoleIndex()].m_nRoleID);
		}

		//}

	}
	else
	{
		switch(pMsg->dw_error_code)
		{
		case E_EnumRole_RoleEnumed:
			GameLog::Instance()->GameLogOut(_T("EnumRole_RoleEnumed"));
			break;
		case E_EnumRole_RoleEnuming:
			GameLog::Instance()->GameLogOut(_T("EnumRole_RoleEnuming"));
			break;
		case E_EnumRole_InWorld:
			GameLog::Instance()->GameLogOut(_T("EnumRole_InWorld"));
			break;
		default:
			GameLog::Instance()->GameLogOut(_T("SystemError"));
			break;
		}

	}
	return 0;
}




//发送删除角色消息
VOID LoginOn::SendDeleRoleMsg(int nSelectRoleID)
{
	if(m_pSession->IsConnect())
	{
		NET_SIC_delete_role msgDelRole;
		msgDelRole.dw_role_id = nSelectRoleID;
		tstring szSafeCode =_T("");
		msgDelRole.dwSafeCodeCrc = Tang::f_util::get_crc(szSafeCode.c_str());
		m_pSession->Send(&msgDelRole);
	}
}


//接收服务器删除角色消息
DWORD LoginOn::NetRecvDeleteRole(NET_SIS_delete_role* pMsg, DWORD pPrama)
{
	//CString strMsg;
	TCHAR strMsg[MAX_PATH] = _T("");
	if(pMsg->dw_error_code == E_Success)
	{



		for(int i=0;i<20;i++)
		{
			if(m_RoleSimpleData[i].m_nRoleID==pMsg->dw_role_id)
			{			
				_stprintf_s(strMsg, _countof(strMsg), _T("删除\"%s\"成功"), m_RoleSimpleData[i].m_szRoleName);
				//strMsg.Format(_T("删除\"%s\"成功"),m_RoleSimpleData[i].m_szRoleName);
				GameLog::Instance()->GameLogOut(strMsg);
				memset(&m_RoleSimpleData[i],0,sizeof(m_RoleSimpleData[i]));
				for(int j= i;j<20;j++)
				{
					if(m_RoleSimpleData[j+1].m_nRoleID!=0)
					{
						m_RoleSimpleData[j].m_nRoleID = m_RoleSimpleData[j+1].m_nRoleID;
						memcpy(m_RoleSimpleData[j].m_szRoleName,m_RoleSimpleData[j+1].m_szRoleName,sizeof(m_RoleSimpleData[j].m_szRoleName));
						memset(&m_RoleSimpleData[j+1],0,sizeof(m_RoleSimpleData[j]));
					}
				}
				break;
			}
		}
		// 		m_pRoleListBox->ResetContent();
		// 		for(int i=0;i<20;i++)
		// 		{
		// 			if(m_RoleSimpleData[i].m_szRoleName)
		// 			{
		// 				m_pRoleListBox->AddString(m_RoleSimpleData[i].m_szRoleName);
		// 			}
		// 		}


	}
	else
	{
		switch(pMsg->dw_error_code)
		{
		case E_DelRole_RoleNotExist:		//角色不存在
			GameLog::Instance()->GameLogOut(_T("DelRole_RoleNotExist"));
			break;
		case E_DelRole_RoleDeleting:		//正在删除
			GameLog::Instance()->GameLogOut(_T("DelRole_RoleDeleting"));
			break;
		case E_DelRole_RoleEnumNotDone:		//初始化错误
			GameLog::Instance()->GameLogOut(_T("DelRole_RoleEnumNotDone"));
			break;
		case E_DelRole_RoleCreating:		//正在创建
			GameLog::Instance()->GameLogOut(_T("DelRole_RoleCreating"));
			break;
		case E_DelRole_SafeCodeIncorrect:	//安全码错误
			GameLog::Instance()->GameLogOut(_T("DelRole_SafeCodeIncorrect"));
			break;
		case E_DelRole_InWorld:				//角色已进入游戏世界，无法删除
			GameLog::Instance()->GameLogOut(_T("DelRole_InWorld"));
			break;
		case E_DelRole_RoleLoading:
			GameLog::Instance()->GameLogOut(_T("DeleRole_RoleLoading"));
			break;
		case E_DelRole_LeaveGuild1st:
			GameLog::Instance()->GameLogOut(_T("DeleRole_LeaveGuild1st"));
			break;
		}
	}
	return 0;
}

//创建角色
//void LoginOn::CreateRole(TCHAR *pszRoleName)
//{
//	NET_SIC_create_role msgCreateRole;
//	_tcscpy(msgCreateRole.szRoleName, pszRoleName);
//	msgCreateRole.eStatus = EPCS_OutKungSword;
//	tagAvatarAtt m_avatarAtt;
//	memset(&m_avatarAtt,0,sizeof(tagAvatarAtt));
//	m_avatarAtt.bySex =1;
//	msgCreateRole.AvatarAtt		= m_avatarAtt;
//	m_pSession->Send(&msgCreateRole);
//}

//创建角色
//void LoginOn::CreateRoleAuto(TCHAR *pszRoleName,int RoleIndex)
//{
//	NET_SIC_create_role msgCreateRole;
//	_tcscpy(msgCreateRole.szRoleName, pszRoleName);
//	msgCreateRole.eStatus = EPCS_OutKungSword;
//	tagAvatarAtt m_avatarAtt;
//	memset(&m_avatarAtt,0,sizeof(tagAvatarAtt));
//	m_avatarAtt.bySex =RoleIndex%2;
//	msgCreateRole.AvatarAtt		= m_avatarAtt;
//	m_pSession->Send(&msgCreateRole);
//}


//发送获取角色列表申请
void  LoginOn::GetEnumRole()
{
	NET_SIC_enum_role enumRoleMsg;
	m_pSession->Send(&enumRoleMsg);
}


//接收服务器创建角色消息
DWORD LoginOn::NetRecvCreateRole(NET_SIS_create_role* pMsg, DWORD pPrama)
{
	if( pMsg->dw_message_id != Tang::f_util::get_crc("NET_SIS_create_role") )
		return 0;

	//创建角色成功后
	if( pMsg->dw_error_code == E_Success )
	{
		//手动创建角色
		tagSimRole* pRole = (tagSimRole *)pMsg->bySimRoleInfo;
		// 		if(g_bAutoCreateFlag)
		// 		{
		// 			//自动创建角色成功，开始下个账号登录
		// 			m_pSession->Disconnect();  //断开连接
		// 			InterlockedExchange((LONG*)&g_bTerminateRecv,TRUE);  //退出线程
		// 			g_pAutoCreateRole->CreateRole();
		// 
		// 		}else
		// 		{		
		//手动创建角色成功
		//m_pRoleListBox->AddString(pRole->szRoleName);			
		m_RoleSimpleData[m_CurRoleIndex].m_nRoleID = pRole->dw_role_id;
		lstrcpyn(m_RoleSimpleData[m_CurRoleIndex].m_szRoleName,pRole->szRoleName,sizeof(m_RoleSimpleData[m_CurRoleIndex].m_szRoleName)-1);
		m_CurRoleIndex++;					
		//Player* pPlayer = new Player;
		//SeleRoleMgr::Inst()->CreateRole(*pRole, pPlayer);
		//}
		TCHAR strMsg[MAX_PATH] = _T("") ;
		_stprintf_s(strMsg, _countof(strMsg), _T("创建角色：\"%s\" 成功"), pRole->szRoleName);
		//strMsg.Format(_T("创建角色：\"%s\" 成功"),pRole->szRoleName);
		GameLog::Instance()->GameLogOut(strMsg);
	
		SendEnterGameMsg(m_RoleSimpleData[0].m_nRoleID);
	}
	else
	{
		CString strMsg;
		switch(pMsg->dw_error_code)
		{
		case E_CreateRole_RoleCreating:
			//strMsg.Format(_T("%s,CreateRole_RoleCreating"),m_pUtil->AnsiToUnicode(g_pLoginOn->m_szAccount));
			//GameLog::Instance()->GameLogOut(strMsg);
			break;
		case E_CreateRole_RoleEnumNotDone:
			GameLog::Instance()->GameLogOut(_T("CreateRole_RoleEnumNotDone"));
			break;
		case E_CreateRole_RoleDeleting:
			GameLog::Instance()->GameLogOut(_T("CreateRole_RoleDeleting"));
			break;
		case E_CreateRole_RoleNumFull:
			GameLog::Instance()->GameLogOut(_T("CreateRole_RoleNumFull"));
			break;
		case E_CreateRole_NameExist:
			//strMsg.Format(_T("%s,CreateRole_NameExist"),m_pUtil->AnsiToUnicode(g_pLoginOn->m_szAccount));
			//GameLog::Instance()->GameLogOut(strMsg);
			break;
		case E_CreateRole_NameInvalid:
			GameLog::Instance()->GameLogOut(_T("CreateRole_NameInvalid"));
			break;
		case E_CreateRole_SafeCodeInvalid:
			GameLog::Instance()->GameLogOut(_T("CreateRole_SafeCodeInvalid"));
			break;
		case E_CreateRole_InWorld:
			GameLog::Instance()->GameLogOut(_T("CreateRole_InWorld"));
			break;
		case E_CreateRole_RoleLoading:
			GameLog::Instance()->GameLogOut(_T("CreateRole_RoleLoading"));
			break;
		case E_SystemError:
			GameLog::Instance()->GameLogOut(_T("SystemError"));
			break;
		case E_Filter_Name_TooLong:
			GameLog::Instance()->GameLogOut(_T("Common_Error30"));
			break;
		case E_Filter_Name_Null:
			GameLog::Instance()->GameLogOut(_T("Common_Error31"));
			break;
		case E_Filter_Name_Illegal:
		case E_Filter_Name_InFilterFile:
			GameLog::Instance()->GameLogOut(_T("CreateRole_NameInvalid"));
			break;
		default:
			GameLog::Instance()->GameLogOut(_T("SystemError"));
			break;
		}

		// 		if(g_bAutoCreateFlag)
		// 		{
		// 			//自动创建角色成功，开始下个账号登录
		// 			m_pSession->Disconnect();  //断开连接
		// 			InterlockedExchange((LONG*)&g_bTerminateRecv,TRUE);  //退出线程
		// 			g_pAutoCreateRole->CreateRole();
		// 
		// 		}


	}

	return 0;
}

//收到加入游戏成功消息
DWORD LoginOn::NetRecvJoinGame(NET_SIS_join_game* pMsg, DWORD pPrama)
{
	if( pMsg->dw_message_id != Tang::f_util::get_crc("NET_SIS_join_game") )
		return 0;
	switch(pMsg->dw_error_code)
	{
	case E_Success:
		{		
			SetState(ELS_JoinGame);
			//申请获得角色列表
			GetEnumRole();

			break;
		}
	case E_JoinGame_AccountOnline:
		GameLog::Instance()->GameLogOut(_T("JoinGame_AccountOnline"));
		break;
	case E_JoinGame_VerifyCodeError:
		GameLog::Instance()->GameLogOut(_T("JoinGame_VerifyCodeError"));
		break;
	}
	return 0;

}

//发送玩家的选择角色
VOID LoginOn::SendEnterGameMsg(int nSelectRoleID)
{
	if(m_pSession->IsConnect())
	{
		NET_SIC_select_role seleRoleMsg;
		seleRoleMsg.dw_role_id = nSelectRoleID;
		m_pSession->Send(&seleRoleMsg);		

		m_pOwner->SaveLoginRoleID(nSelectRoleID);
	}
}

BYTE LoginOn::GetSexByClass(EClassType eClass)
{
	switch(eClass)
	{
	case EV_Warrior:
	case EV_knight:
		return 1;
	case EV_Apothecary:
	case EV_Assassin:
		return 0;
	case EV_defend: 
		return Tang::f_util::GetSingleton().tool_rand()%2;
	}
	return 0;
}
//发送建立角色消息
VOID LoginOn::SendCreateRoleMsg()
{
	NET_SIC_create_role msgCreateRole;
	_tcscpy(msgCreateRole.szRoleName, Tang::f_util::ansi_to_unicode(m_szAccount));
	msgCreateRole.eStatus		= EPCS_OutKungSword;
	tagAvatarAtt m_avatarAtt;
	memset(&m_avatarAtt,0,sizeof(tagAvatarAtt));
	msgCreateRole.AvatarAtt		= m_avatarAtt;
	msgCreateRole.eClassType    = (EClassType)( m_class ? m_class : ((Tang::f_util::GetSingleton().tool_rand()%3)+1));
	msgCreateRole.AvatarAtt.bySex = GetSexByClass(msgCreateRole.eClassType);
	//msgCreateRole.AvatarAtt.bySex = m_sex >= 0 ? m_sex : (Tang::f_util::GetSingleton().tool_rand()%2);  // GetSexByClass(msgCreateRole.eClassType);
	m_pSession->Send(&msgCreateRole);
}
// 接收玩家的选择角色信息
DWORD LoginOn::NetRecvSelectRole(NET_SIS_select_role* pMsg, DWORD pPrama)
{
	switch(pMsg->dw_error_code)
	{
	case E_Success:
		{
			m_CurRoleID = pMsg->dw_role_id;
			for(int i=0;i<20;i++)
			{
				if( m_RoleSimpleData[i].m_nRoleID == m_CurRoleID)
				{
					lstrcpyn(m_CurRoleName,m_RoleSimpleData[i].m_szRoleName,sizeof(m_CurRoleName)-1);
					break;
				}
			}			

			//m_pWndMain->SendNotifyMessage(WM_SHOWMAINWND,0,0);			
		}
		break;
	case E_SelectRole_RoleEnumNotDone:
		GameLog::Instance()->GameLogOut(_T("SelectRole_RoleEnumNotDone"));
		break;
	case E_SelectRole_RoleCreating:
		GameLog::Instance()->GameLogOut(_T("SelectRole_RoleCreating"));
		break;
	case E_SelectRole_RoleDeleting:
		GameLog::Instance()->GameLogOut(_T("SelectRole_RoleDeleting"));
		break;
	case E_SelectRole_RoleNotExist:
		GameLog::Instance()->GameLogOut(_T("SelectRole_RoleNotExist"));
		break;
	case E_SelectRole_InWorld:
		GameLog::Instance()->GameLogOut(_T("SelectRole_InWorld"));
		break;
	case E_SelectRole_RoleLoading:
		GameLog::Instance()->GameLogOut(_T("SelectRole_RoleLoading"));
		break;
	default:

		break;
	}

	return 0;
}
