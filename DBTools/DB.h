#ifndef _DB_
#define _DB_
#include "AccountDlg.h"
#include "RoleDataDlg.h"
#include "AddAccount.h"
#include "AddRoleDlg.h"
#include <map>
#include <utility>

class CDBToolsDlg;

class CDB
{
	typedef std::map<std::string, st_AccountData*> MAP_ACCOUNT;
	typedef std::map<std::wstring, s_role_data_load*> MAP_ROLDDATA;

public:
	CDB(void);
	~CDB(void);
public:
	BOOL InitDB(INT16 index);
	VOID Destroy();

	VOID SetIP(CString &str)
	{
		m_Ip = str;
	}

	VOID SetPort(CString &str)
	{
		m_Port = str;
	}

	VOID SetUserName(CString &str)
	{
		m_UserName = str;
	}

	VOID SetPassWord(CString &str)
	{
		m_PassWord = str;
	}

	VOID SetDBName(CString &str)
	{
		m_DBName = str;
	}

	VOID SetLoginDlg(CDBToolsDlg* pLoginDlg)
	{
		m_pLoginDlg = pLoginDlg;
	}

	CDBToolsDlg* GetDBToolsDlg()
	{
		return m_pLoginDlg;
	}

	odbc::db_interface* GetDataBase()
	{
		return m_pDBGame;
	}

	BOOL LoadAccount(const CHAR RoleName[X_SHORT_NAME]);

	VOID CleanAccount();

	st_AccountData* GetAccountData(const CHAR RoleName[X_SHORT_NAME]);

	BOOL LoadRoleData(const CHAR RoleName[X_SHORT_NAME]);

	VOID CleanRoleData();

	s_role_data_load* GetRoleData(const TCHAR RoleName[X_SHORT_NAME]);

	BOOL AddAccount(const CHAR Account[X_SHORT_NAME]);

	BOOL UpdateAccount();

	VOID	Get_Role_Max_ID(DWORD& dwMaxID);

	BOOL	create_role(DWORD& dw_account_id, DWORD& dw_max_role_id, s_create_role_info& role_info);

	BOOL	export_indagate();
	
private:
	odbc::db_interface*	m_pDBGame;

	CString m_Ip;
	CString m_Port;
	CString m_UserName;
	CString m_PassWord;
	CString m_DBName;

	CDBToolsDlg* m_pLoginDlg;
	CAccountDlg  m_AccountDlg;
	CRoleDataDlg m_RoleDataDlg;
	CAddAccount m_AddAccountDlg;
	AddRoleDlg	m_Add_Role_Dlg;

	MAP_ACCOUNT m_mapAccount;
	MAP_ROLDDATA m_mapRoleData;


};
#endif
