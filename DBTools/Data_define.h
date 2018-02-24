#ifndef DATA_DEFINE
#define DATA_DEFINE

struct st_AccountData
{
	DWORD					dwClientID;			// 客户端ID
	CHAR					RoleName[X_SHORT_NAME];			//用户名
	BYTE					byPrivilege;		// 权限
	E_world_status		eLoginStatus;		// 登陆状态
	BOOL					bGuard;				// 防沉迷
	DWORD					dwPreLoginIP;		// 上次登录ip
	tagDWORDTime			dwPreLoginTime;		// 上次登录时间
};
#endif