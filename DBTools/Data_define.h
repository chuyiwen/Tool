#ifndef DATA_DEFINE
#define DATA_DEFINE

struct st_AccountData
{
	DWORD					dwClientID;			// �ͻ���ID
	CHAR					RoleName[X_SHORT_NAME];			//�û���
	BYTE					byPrivilege;		// Ȩ��
	E_world_status		eLoginStatus;		// ��½״̬
	BOOL					bGuard;				// ������
	DWORD					dwPreLoginIP;		// �ϴε�¼ip
	tagDWORDTime			dwPreLoginTime;		// �ϴε�¼ʱ��
};
#endif