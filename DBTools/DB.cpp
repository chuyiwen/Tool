#include "StdAfx.h"
#include "DB.h"
#include "DBToolsDlg.h"

CDB::CDB(void)
{
	m_pDBGame = new odbc::db_interface;
}

CDB::~CDB(void)
{
	SAFE_DELETE(m_pDBGame);
}

BOOL CDB::InitDB(INT16 index)
{
	switch(index)
	{
	case 0:
		{
			if(!m_pDBGame->init_db(m_Ip, m_UserName, m_PassWord, m_DBName, _wtoi(m_Port)))
			{
				return FALSE;
			}
			if(m_pLoginDlg)
			{
				m_pLoginDlg->ShowWindow(FALSE);
				m_AccountDlg.SetDB(this);
				m_AccountDlg.DoModal();
			}
			break;
		}
	case 1:
		{
			if(!m_pDBGame->init_db(m_Ip, m_UserName, m_PassWord, m_DBName, _wtoi(m_Port)))
			{
				return FALSE;
			}
			if(m_pLoginDlg)
			{
				m_pLoginDlg->ShowWindow(FALSE);
				m_RoleDataDlg.SetDB(this);
				m_RoleDataDlg.DoModal();
			}
			break;
			break;
		}
	case 3:
		{
			if(!m_pDBGame->init_db(m_Ip, m_UserName, m_PassWord, m_DBName, _wtoi(m_Port)))
			{
				return FALSE;
			}
			if(m_pLoginDlg)
			{
				m_pLoginDlg->ShowWindow(FALSE);
				m_Add_Role_Dlg.SetDB(this);
				m_Add_Role_Dlg.DoModal();
			}
			break;
		}
	case 2:
		{
			if(!m_pDBGame->init_db(m_Ip, m_UserName, m_PassWord, m_DBName, _wtoi(m_Port)))
			{
				return FALSE;
			}
			if(m_pLoginDlg)
			{
				m_pLoginDlg->ShowWindow(FALSE);
				m_AddAccountDlg.SetDB(this);
				m_AddAccountDlg.DoModal();
			}
			break;
		}
	default:
		break;
	}
	return TRUE;
}

VOID CDB::Destroy()
{
	m_pDBGame->shut_down();
}

BOOL CDB::LoadRoleData(const CHAR RoleName[X_SHORT_NAME])
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("roled_ata",	
		"role_name," "role_name_crc," "display_set,"	"sex," "hair_model_id,"
		"hair_color_id," "face_model_id,"	"face_detail_id,"	"dress_model_id,"	"map_id,"	
		"x,"			"y,"			"z,"			"face_x,"		"face_y,"	
		"face_z,"		"class,"		"classex,"		"level,"		"exp_cur_level,"	
		"hp,"			"mp,"			"att_avail,"	"talent_avail," "physique_added,"	
		"strength_added," "pneuma_added," "innerforce_added," "technique_added," "agility_added,"		
		"injury,"		"vitality,"		"knowledge,"	"morality,"		"culture,"	
		"credit,"		"identity,"		"vip_point,"		"bag_size,"		"bag_gold,"	
		"bag_silver,"	"bag_yuanbao,"	"guild_id,"			"0,"			"0,"	
		"0,"			"create_time,"	"login_time,"	"logout_time,"	"online_time,"	
		"cur_online_time," "rage,"			"endurance,"	"safe_guard_flag,"		"close_safe_guard_time,"
		"talent_type1,"	"talent_type2,"	"talent_type3,"	"talent_type4,"	"talent_val1,"
		"talent_val2,"	"talent_val3,"	"talent_val4,"	"reborn_map_id,"	"total_tax,"	
		"morale,"		"get_mall_free_time,""remote_open_set," "cur_title_id,"	"exchange_volume,"
		"script_data,"	"treasure_sum,"	"stall_level,"	"stall_daily_exp," "stall_cur_exp,"	
		"stall_last_time");

	pStream->where_item();
	pStream->write_string("role_name like'%").write_string(RoleName);
	pStream->write_string("%'");
	pStream->write_string(" and remove_flag=") << 0;

	odbc::execute_result* pResult = m_pDBGame->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	if(pResult->get_row_count() > 0)
	{
		INT32 num = pResult->get_row_count();
		while(num)
		{
			//s_role_data_load* pRoleData = new s_role_data_load;
			//::ZeroMemory(pRoleData, sizeof(s_role_data_load));
			//s_role_data_const	*pRoleDataConst = &pRoleData->RoleDataConst;
			//s_role_data_save		*pRoleDataSave	= &pRoleData->RoleDataSave;
			//(*pResult)[0].get_tchar(pRoleDataConst->sz_role_name, X_SHORT_NAME);
			//pRoleDataConst->dw_role_name_crc				= (*pResult)[1].get_dword();
			//pRoleDataConst->avatar.bySex				= (*pResult)[3].get_byte();
			//pRoleDataConst->avatar.wHairMdlID			= (*pResult)[4].get_short();
			//pRoleDataConst->avatar.wHairTexID			= (*pResult)[5].get_short();
			//pRoleDataConst->avatar.wFaceMdlID			= (*pResult)[6].get_short();
			//pRoleDataConst->avatar.wFaceDetailTexID		= (*pResult)[7].get_short();
			//pRoleDataConst->avatar.wDressMdlID			= (*pResult)[8].get_short();

			//pRoleDataSave->display_set_					= (*pResult)[2].get_byte();
			//pRoleDataSave->dwMapID						= (*pResult)[9].get_dword();
			//pRoleDataSave->fCoordinate[0]				= (*pResult)[10].get_float();
			//pRoleDataSave->fCoordinate[1]				= (*pResult)[11].get_float();
			//pRoleDataSave->fCoordinate[2]				= (*pResult)[12].get_float();
			//pRoleDataSave->fFace[0]						= (*pResult)[13].get_float();
			//pRoleDataSave->fFace[1]						= (*pResult)[14].get_float();
			//pRoleDataSave->fFace[2]						= (*pResult)[15].get_float();

			//pRoleDataSave->eClass						= (EClassType)(*pResult)[16].get_int();
			//pRoleDataSave->eClassEx						= (EClassTypeEx)(*pResult)[17].get_int();
			//pRoleDataSave->nLevel						= (*pResult)[18].get_short();
			//pRoleDataSave->nCurExp						= (*pResult)[19].get_int();
			//pRoleDataSave->nHP							= (*pResult)[20].get_int();
			//pRoleDataSave->nMP							= (*pResult)[21].get_int();

			//pRoleDataSave->nAttPoint					= (*pResult)[22].get_int();
			//pRoleDataSave->nTalentPoint					= (*pResult)[23].get_int();

			//pRoleDataSave->nAttPointAdd[ERA_Physique]	= (*pResult)[24].get_int();
			//pRoleDataSave->nAttPointAdd[ERA_Strength]	= (*pResult)[25].get_int();
			//pRoleDataSave->nAttPointAdd[ERA_Pneuma]		= (*pResult)[26].get_int();
			//pRoleDataSave->nAttPointAdd[ERA_InnerForce]	= (*pResult)[27].get_int();
			//pRoleDataSave->nAttPointAdd[ERA_Technique]	= (*pResult)[28].get_int();
			//pRoleDataSave->nAttPointAdd[ERA_Agility]	= (*pResult)[29].get_int();

			//pRoleDataSave->nInjury						= (*pResult)[30].get_int();
			////pRoleDataSave->nVitality					= (*pResult)[31].GetInt();
			//pRoleDataSave->nKnowledge					= (*pResult)[32].get_int();
			//pRoleDataSave->nMorality					= (*pResult)[33].get_int();
			//pRoleDataSave->nCulture						= (*pResult)[34].get_int();
			//pRoleDataSave->nCredit						= (*pResult)[35].get_int();
			//pRoleDataSave->nIdentity					= (*pResult)[36].get_int();
			//pRoleDataSave->nVIPPoint					= (*pResult)[37].get_int();

			//pRoleDataSave->n16BagSize					= (*pResult)[38].get_short();
			//pRoleDataSave->nBagGold						= (*pResult)[39].get_int();
			//pRoleDataSave->nBagSilver					= (*pResult)[40].get_int();
			//pRoleDataSave->nBagYuanBao					= (*pResult)[41].get_int();

			//pRoleDataSave->dw_guild_id					= (*pResult)[42].get_dword();
			////pRoleDataSave->nWareGold					= (*pRes)[43].GetInt();
			////pRoleDataSave->nWareSilver					= (*pRes)[44].GetInt();
			////pRoleDataSave->nWareYuanBao					= (*pRes)[45].GetInt();

			//if(!DataTime2DwordTime(pRoleDataConst->CreateTime,	(*pResult)[46].get_string(), (*pResult)[46].get_length()))
			//{
			//	ASSERT(0);
			//}

			//DataTime2DwordTime(pRoleDataSave->LoginTime,	(*pResult)[47].get_string(), (*pResult)[47].get_length());
			//DataTime2DwordTime(pRoleDataSave->LogoutTime,	(*pResult)[48].get_string(), (*pResult)[48].get_length());

			//pRoleDataSave->nOnlineTime					= (*pResult)[49].get_dword();
			//pRoleDataSave->nCurOnlineTime				= (*pResult)[50].get_dword();

			//pRoleDataSave->nRage						= (*pResult)[51].get_int();
			//pRoleDataSave->nEndurance					= (*pResult)[52].get_int();
			//pRoleDataSave->bSafeGuard					= (*pResult)[53].get_int();

			////pRoleDataSave->CloseSafeGuardTime			= (*pRes)[54].GetDword();
			//DataTime2DwordTime(pRoleDataSave->CloseSafeGuardTime,	(*pResult)[54].get_string(), (*pResult)[54].get_length());

			//pRoleDataSave->talent[0].eType				= (ETalentType)(*pResult)[55].get_int();
			//pRoleDataSave->talent[1].eType				= (ETalentType)(*pResult)[56].get_int();
			//pRoleDataSave->talent[2].eType				= (ETalentType)(*pResult)[57].get_int();
			//pRoleDataSave->talent[3].eType				= (ETalentType)(*pResult)[58].get_int();
			//pRoleDataSave->talent[0].nPoint				= (*pResult)[59].get_int();
			//pRoleDataSave->talent[1].nPoint				= (*pResult)[60].get_int();
			//pRoleDataSave->talent[2].nPoint				= (*pResult)[61].get_int();
			//pRoleDataSave->talent[3].nPoint				= (*pResult)[62].get_int();

			//pRoleDataSave->dwRebornMapID				= (*pResult)[63].get_dword();
			//pRoleDataSave->nTotalTax					= (*pResult)[64].get_int();
			//pRoleDataSave->nMorale						= (*pResult)[65].get_int();

			//DataTime2DwordTime(*(tagDWORDTime*)&pRoleDataSave->dwTimeGetMallFree, (*pResult)[66].get_string(), (*pResult)[66].get_length());
			//pRoleDataSave->sRemoteOpenSet				= (*pResult)[67].get_dword();
			//pRoleDataSave->u16ActiveTitleID				= (*pResult)[68].get_int();
			//pRoleDataSave->nExVolume					= (*pResult)[69].get_int();
			////(*pResult)[70].GetBlob(pRoleDataSave->Data.dwData, (*pResult)[70].GetLen());
			//pRoleDataSave->nTreasureSum					= (*pResult)[71].get_int();

			//pRoleDataSave->byStallLevel					= (*pResult)[72].get_byte();
			//pRoleDataSave->nStallDailyExp				= (*pResult)[73].get_int();
			//pRoleDataSave->nStallCurExp					= (*pResult)[74].get_int();
			//pRoleDataSave->dwLastStallTime				= (*pResult)[75].get_dword();
			//m_mapRoleData.insert(std::make_pair(std::wstring(pRoleDataConst->sz_role_name), pRoleData));
			//CString str;
			//str.Format(_T("%s"), pRoleDataConst->sz_role_name);
			//m_RoleDataDlg.AddRoleData(str);
			//pResult->next_row();
			//num--;
		}
	}
	else
	{
		bRet = FALSE;
	}

exit:
	m_pDBGame->return_io(pStream);
	m_pDBGame->free_result_query(pResult);

	return bRet;
}

VOID CDB::CleanRoleData()
{
	/*std::map<std::wstring, tagRoleDataLoad*>::iterator iter;
	for(iter = m_mapRoleData.begin(); iter != m_mapRoleData.end(); iter++)
	{
		tagRoleDataLoad* pRoleData = (tagRoleDataLoad*)iter->second;
		SAFE_DEL(pRoleData);
	}
	m_mapRoleData.clear();*/
}

s_role_data_load* CDB::GetRoleData(const TCHAR RoleName[X_SHORT_NAME])
{
	/*std::map<std::wstring, tagRoleDataLoad*>::iterator iter = m_mapRoleData.find(RoleName);
	if(iter != m_mapRoleData.end())
	{
		return (tagRoleDataLoad*)iter->second;
	}*/
	return NULL;
}

BOOL CDB::LoadAccount(const CHAR RoleName[X_SHORT_NAME])
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("account", "id,name,privilege,login_status,guard,ip,time");
	pStream->where_item();
	pStream->write_string("name like'%").write_string(RoleName);
	pStream->write_string("%'");

	odbc::execute_result* pResult = m_pDBGame->sql_query(pStream);
	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	if(pResult->get_row_count() > 0)
	{
		INT32 num = pResult->get_row_count();
		while(num)
		{
			CHAR ip[X_IP_LEN] = "";
			CHAR time[X_DATATIME_LEN+1] = "";
			st_AccountData* pData = new st_AccountData;
			::ZeroMemory(pData, sizeof(st_AccountData));
			pData->dwClientID = (*pResult)[0].get_dword();
			memcpy(pData->RoleName, (*pResult)[1].get_string(), (*pResult)[1].get_length());
			pData->byPrivilege = (*pResult)[2].get_byte();
			pData->eLoginStatus = (E_world_status)(*pResult)[3].get_byte();
			pData->bGuard = (*pResult)[4].get_bool();
			if((*pResult)[5].get_length() > 0)
			{
				memcpy(ip, (*pResult)[5].get_string(), (*pResult)[5].get_length());
				pData->dwPreLoginIP = inet_addr(ip);
			}
			
			if((*pResult)[6].get_length() > 0)
			{
				memcpy(time, (*pResult)[6].get_string(), (*pResult)[6].get_length());
				DataTime2DwordTime(pData->dwPreLoginTime, time, (*pResult)[6].get_length());
			}
			
			m_mapAccount.insert(std::make_pair(std::string(pData->RoleName), pData));
			TCHAR wRoleName[X_SHORT_NAME];
			MultiByteToWideChar(CP_UTF8, 0, pData->RoleName, -1, wRoleName, sizeof(TCHAR)*X_SHORT_NAME);
			CString str;
			str.Format(_T("%s"), wRoleName);
			m_AccountDlg.AddAccount(str);
			num--;
			pResult->next_row();
		}
	}
	else
	{
		bRet = FALSE;
	}

exit:
	m_pDBGame->return_io(pStream);
	m_pDBGame->free_result_query(pResult);

	return bRet;
}

static DWORD n_rand = GetTickCount();
BOOL CDB::AddAccount(const CHAR Account[X_SHORT_NAME])
{

	DWORD n_result = ((n_rand = n_rand * 1103515245 + 12345) >> 1 ) & LONG_MAX;

	CHAR c_password[100];
	INT n_password = n_result % 99999999;
	sprintf_s(c_password, ",password=md5('%dssplay.password')", n_password);
	TCHAR sz_account[X_SHORT_NAME];

	MultiByteToWideChar(CP_UTF8,NULL,Account,-1,sz_account,X_SHORT_NAME);

	m_pLoginDlg->p_log->write_log(_T("account = %s, password = %d\r\n"), sz_account, n_password);

	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	odbc::tag_mysql_connect* pCon = m_pDBGame->get_idlesse_connect();

	pStream->insert_item("account");
	pStream->write_string("name='").write_string(Account, pCon);
	pStream->write_string("'");
	pStream->write_string(c_password);
	//pStream->write_string(",password='C636E38BB9F3447A01F171B8BFD66F4C'");
	pStream->write_string(",privilege=0");

	BOOL bRet = m_pDBGame->sql_execute(pStream);
	if(!bRet)
	{
		goto exit;
	}

exit:
	m_pDBGame->return_use_connect(pCon);
	m_pDBGame->return_io(pStream);
	
	return bRet;
}

BOOL CDB::UpdateAccount()
{
	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->update_item("account");
	pStream->write_string("password=ucase(password)");
	
	BOOL bRet = m_pDBGame->sql_execute(pStream);
	if(!bRet)
	{
		goto exit;
	}

exit:
	m_pDBGame->return_io(pStream);

	return bRet;
}

VOID CDB::CleanAccount()
{
	std::map<std::string, st_AccountData*>::iterator iter;

	for(iter = m_mapAccount.begin(); iter != m_mapAccount.end(); iter++)
	{
		st_AccountData* pData = (st_AccountData*)iter->second;
		SAFE_DELETE(pData);
	}

	m_mapAccount.clear();
}

st_AccountData* CDB::GetAccountData(const CHAR RoleName[X_SHORT_NAME])
{
	std::string str(RoleName);
	std::map<std::string, st_AccountData*>::iterator iter = m_mapAccount.find(str);
	if(iter != m_mapAccount.end())
	{
		return (st_AccountData*)iter->second;
	}
	return NULL;
}

VOID CDB::Get_Role_Max_ID(DWORD& dwMaxID)
{
	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();

	pStream->select_item("role_data", "count(role_id),max(role_id)");

	odbc::execute_result* p_result = m_pDBGame->sql_query(pStream);
	if(VALID_POINT(p_result) && p_result->get_row_count() > 0)
	{
		dwMaxID = (*p_result)[1].get_dword();
	}

	m_pDBGame->return_io(pStream);
	m_pDBGame->free_result_query(p_result);
}

BOOL CDB::create_role(DWORD& dw_account_id, DWORD& dw_max_role_id, s_create_role_info& role_info)
{
	char sz_time_buffer_[X_DATATIME_LEN + 1];
	TCHAR sz_role_name_buffer_[64];
	DWORD dw_role_name_crc = INVALID_VALUE;
	ZeroMemory(sz_time_buffer_, sizeof(sz_time_buffer_));
	ZeroMemory(sz_role_name_buffer_, sizeof(sz_role_name_buffer_));
	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();
	odbc::tag_mysql_connect* p_conn = m_pDBGame->get_idlesse_connect();

	pStream->insert_item("role_data");
	pStream->write_string("account_id=") << dw_account_id;
	pStream->write_string(",role_id=") << dw_max_role_id + 1;
	pStream->write_string(",role_name='").write_string(role_info.sz_role_name, p_conn);

	_tcscpy_s(sz_role_name_buffer_, _countof(sz_role_name_buffer_), role_info.sz_role_name);
	_tcslwr(sz_role_name_buffer_);
	dw_role_name_crc = get_tool()->crc32(sz_role_name_buffer_);
	pStream->write_string("',role_name_crc=") << dw_role_name_crc;

	pStream->write_string(",sex=") << role_info.avatar.bySex;
	pStream->write_string(",hair_model_id=") << role_info.avatar.wHairMdlID;
	pStream->write_string(",hair_color_id=") << role_info.avatar.wHairTexID;
	pStream->write_string(",face_model_id=") << role_info.avatar.wFaceMdlID;
	pStream->write_string(",face_detail_id=") << role_info.avatar.wFaceDetailTexID;
	pStream->write_string(",dress_model_id=") << role_info.avatar.wDressMdlID;
	pStream->write_string(",visualizeid=") << role_info.avatar.byVisualize;

	pStream->write_string(",map_id=") << role_info.dw_map_id_;
	pStream->write_string(",x=") << role_info.fX;			
	pStream->write_string(",y=") << role_info.fY;
	pStream->write_string(",z=") << role_info.fZ;
	pStream->write_string(",face_x=") << role_info.f_face_x_;	
	pStream->write_string(",face_y=") << role_info.f_face_y_;
	pStream->write_string(",face_z=") << role_info.f_face_z_;

	pStream->write_string(",level=") << role_info.by_level_;
	pStream->write_string(",class=") << role_info.e_class_type_;

	if(DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), role_info.create_time_))
	{
		pStream->write_string(",create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
	}
	else
	{
		print_message(_T("Error: Func DwordTime2DataTime() run error in db_handler::create_role()!!!!!\r\n"));
		ASSERT(0);
	}

	BOOL bRet = m_pDBGame->sql_execute(pStream);

	m_pDBGame->return_use_connect(p_conn);
	m_pDBGame->return_io(pStream);

	return bRet;
}

BOOL CDB::export_indagate()
{
	BYTE	dw_talk[255];
	ZeroMemory(dw_talk, sizeof(dw_talk));
	odbc::sql_language_disposal* pStream = m_pDBGame->get_io();

	pStream->select_item("role_data", "role_talk");
	pStream->where_item();
	pStream->write_string("level >= 30");

	odbc::execute_result* p_result = m_pDBGame->sql_query(pStream);
	if(VALID_POINT(p_result) && p_result->get_row_count() > 0)
	{
		INT n_num = p_result->get_row_count();

		while(n_num)
		{
			(*p_result)[0].get_blob(dw_talk, (*p_result)[0].get_length());

			m_pLoginDlg->p_log->write_log(_T("role_talk"));
			for(INT i = 0; i < 255; i++)
			{
				m_pLoginDlg->p_log->write_log(_T("%d\r\n"), dw_talk[i]);
			}

			m_pLoginDlg->p_log->write_log(_T("\r\n"));

			n_num--;
			p_result->next_row();
		}
		
	}

	m_pDBGame->return_io(pStream);
	m_pDBGame->free_result_query(p_result);

	return TRUE;
}

