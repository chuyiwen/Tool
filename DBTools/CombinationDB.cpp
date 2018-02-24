#include "StdAfx.h"
#include "CombinationDB.h"
#include "CombinationDlg.h"

CombinationDB::CombinationDB(void)
{
	m_pdb = new odbc::db_interface;
}

CombinationDB::~CombinationDB(void)
{
	m_pdb->shut_down();
	SAFE_DELETE(m_pdb);
}

BOOL CombinationDB::InitDB(LPCTSTR ip, LPCTSTR port, LPCTSTR user, LPCTSTR psd, LPCTSTR name, CombinationDlg* pCombin_Dlg)
{
	if(!VALID_POINT(pCombin_Dlg))
	{
		return FALSE;
	}
	m_pCombin_Dlg = pCombin_Dlg;
	return m_pdb->init_db(ip, user, psd, name, _wtoi(port));
}

VOID CombinationDB::ShutDown()
{
	m_pdb->shut_down();
}

// 初始化角色共用数据
BOOL CombinationDB::InitAccountCommon(MAP_ACCOUNT_COMMON& map_account_common)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("account_common", 
		"safecode_crc,reset_time,bag_password_crc,baibao_yuanbao,	\
		ware_size,ware_silver,warestep,yuanbao_recharge,			\
		IsReceive,total_recharge,receive_type,		\
		account_id,account_name,receive_type_ex,web_type,\
		score");

	// 差receive_type_ex,web_type
	
	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	while(nNum)
	{
		tag_account_common* pAccount_Common = new tag_account_common;
		ZeroMemory(pAccount_Common, sizeof(tag_account_common));

		pAccount_Common->s_safe_code_.dw_safe_code_crc	= (*pResult)[0].get_dword();
		pAccount_Common->s_safe_code_.dw_reset_time	= (*pResult)[1].get_dword();
		pAccount_Common->dw_bag_password_crc_				= (*pResult)[2].get_dword();
		pAccount_Common->n_baibao_yuanbao_			= (*pResult)[3].get_int();
		pAccount_Common->n16_ware_size_				= (*pResult)[4].get_int();
		pAccount_Common->n64_ware_silver_			= (*pResult)[5].get_long();
		pAccount_Common->n16_ware_step			= (*pResult)[6].get_short();
		pAccount_Common->n_yuanbao_recharge		= (*pResult)[7].get_int();
		pAccount_Common->b_receive				= (*pResult)[8].get_int();
		pAccount_Common->dw_total_recharge		= (*pResult)[9].get_dword();
		pAccount_Common->n16_receive_type			= (*pResult)[10].get_short();
		
		pAccount_Common->dw_account_id			= (*pResult)[11].get_dword();
		memcpy(pAccount_Common->sz_account_name, (*pResult)[12].get_string(), sizeof(CHAR)*16);
		pAccount_Common->dw_receive_type			= (*pResult)[13].get_dword();
		pAccount_Common->dw_web_type				= (*pResult)[14].get_dword();
		pAccount_Common->n32_score					= (*pResult)[15].get_int();
		
		map_account_common.insert(std::make_pair(pAccount_Common->dw_account_id, pAccount_Common));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化角色ID对照表
BOOL CombinationDB::InitRoleID(MAP_ROLE_ID& map_role_id, DWORD& dw_role_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("role_data", "role_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{

		DWORD dw_role_id = (*pResult)[0].get_dword();

		dw_role_max_id++;

		map_role_id.insert(make_pair(dw_role_id, dw_role_max_id));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitItemID(MAP_ITEM_ID& map_item_id, INT64& dw_item_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("item", "serial");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{

		INT64 serial = (*pResult)[0].get_long();

		dw_item_max_id++;

		map_item_id.insert(make_pair(serial, dw_item_max_id));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitBankID(MAP_BANK_ID& map_bank_id, DWORD& dw_bank_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("bank", "id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{

		DWORD	dw_bank_id = (*pResult)[0].get_dword();

		dw_bank_max_id++;

		map_bank_id.insert(make_pair(dw_bank_id, dw_bank_max_id));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitMailID(MAP_MAIL_ID& map_mail_id, DWORD& dw_mail_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("mail", "mail_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	//if(nNum <= 0)
	//{
	//	bRet = FALSE;
	//	goto exit;
	//}

	while(nNum)
	{

		DWORD	dw_mail_id = (*pResult)[0].get_dword();

		dw_mail_max_id++;

		map_mail_id.insert(make_pair(dw_mail_id, dw_mail_max_id));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitPetID(MAP_PET_ID& map_pet_id,	DWORD& dw_pet_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("pet_data", "pet_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{

		DWORD	dw_pet_id = (*pResult)[0].get_dword();

		dw_pet_max_id++;

		map_pet_id.insert(make_pair(dw_pet_id, dw_pet_max_id));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitPaimaiID(MAP_PAIMAI_ID& map_paimai_id, DWORD& dw_paimai_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("paimai", "id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{

		DWORD	dw_paimai_id = (*pResult)[0].get_dword();

		dw_paimai_max_id++;

		map_paimai_id.insert(make_pair(dw_paimai_id, dw_paimai_max_id));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化角色名称对照表
BOOL CombinationDB::InitRoleName(MAP_ROLE_NAME& map_role_name)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("role_data", "role_id,"	"role_name");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();
	
	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{
		DWORD dwRoleID = (*pResult)[0].get_dword();
		TCHAR szRoleName[X_SHORT_NAME];
		ZeroMemory(szRoleName, sizeof(szRoleName));
		(*pResult)[1].get_tchar(szRoleName, X_SHORT_NAME);

		tstring str = szRoleName;

		map_role_name.insert(std::make_pair(dwRoleID, str));

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化角色名称crc
BOOL CombinationDB::InitRoleNameCrc(MAP_ROLE_NAME_CRC& list_role_name_crc)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("role_data", "role_name_crc");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	/*if(nNum <= 0)
	{
		bRet = FALSE;
		goto exit;
	}*/

	while(nNum)
	{
		DWORD	dw_name_crc = (*pResult)[0].get_dword();
		list_role_name_crc.insert(std::make_pair(dw_name_crc, dw_name_crc));
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化帮会id
BOOL CombinationDB::InitGuildID(MAP_GUILD_ID& list_guild_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild", "id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count();

	//if(nNum <= 0)
	//{
	//	bRet = FALSE;
	//	goto exit;
	//}

	while(nNum)
	{
		DWORD	dw_guild_id = (*pResult)[0].get_dword();
		list_guild_id.insert(std::make_pair(dw_guild_id, dw_guild_id));
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化成就
BOOL CombinationDB::InitAchievement(LIST_ACHIEVEMENT& list_achievement)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("achievement", "role_id,id,date");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_achievement* p_achievement = new tag_achievement;
		ZeroMemory(p_achievement, sizeof(tag_achievement));

		p_achievement->dw_role_id = (*pResult)[0].get_dword();
		p_achievement->dw_id = (*pResult)[1].get_dword();
		tagDWORDTime st_Time;
		ZeroMemory(&st_Time, sizeof(st_Time));
		DataTime2DwordTime(st_Time,	(*pResult)[2].get_string(), (*pResult)[2].get_length());
		p_achievement->dw_date = st_Time;

		list_achievement.push_back(p_achievement);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化成就进度
BOOL CombinationDB::InitAchievementProcess(LIST_ACHIEVEMENT_PROCESS& list_achievement_process)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("achievement_progress", "role_id,id,counter");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_achievement_process* p_achievement_process = new tag_achievement_process;
		ZeroMemory(p_achievement_process, sizeof(tag_achievement_process));

		p_achievement_process->dw_role_id = (*pResult)[0].get_dword();
		p_achievement_process->dw_id = (*pResult)[1].get_dword();
		p_achievement_process->dw_count = (*pResult)[2].get_dword();

		list_achievement_process.push_back(p_achievement_process);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化黑名单列表
BOOL CombinationDB::InitBlackList(LIST_BLACK& list_black)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("blacklist", "role_id," "black_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_black_list* p_black = new tag_black_list;
		ZeroMemory(p_black, sizeof(*p_black));

		p_black->dwRoleID = (*pResult)[0].get_dword();
		p_black->dwBlackID = (*pResult)[1].get_dword();

		list_black.push_back(p_black);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化buffer列表
BOOL CombinationDB::InitBufferList(LIST_BUFFER& list_buffer)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("buff", "role_id,"
		"src_unit_id,"		"src_skill_id,"			"item_type_id,"		"item_serial_id,"		"buff_id,"
		"cur_tick,"			"level,"				"cur_lap_times,"		"effect_skill_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_buffer_list* pbuffer = new tag_buffer_list;
		//ZeroMemory(pbuffer, sizeof(*pbuffer));

		pbuffer->dwRoleID					= (*pResult)[0].get_dword();
		pbuffer->dw_src_unit_id_			= (*pResult)[1].get_dword();
		pbuffer->dw_src_skill_id_			= (*pResult)[2].get_dword();
		pbuffer->dw_item_type_id_			= (*pResult)[3].get_dword();
		pbuffer->n_serial_					= (*pResult)[4].get_long();

		pbuffer->dw_buff_id_				= (*pResult)[5].get_dword();
		pbuffer->n_persist_tick_			= (*pResult)[6].get_int();
		pbuffer->n_level_				= (INT8)(*pResult)[7].get_int();
		pbuffer->n_cur_lap_times_		= (INT8)(*pResult)[8].get_int();


		pbuffer->n_modifier_num_		= (INT8)((*pResult)[9].get_length()/sizeof(DWORD));

		if(pbuffer->n_modifier_num_ > 0)
		{
			INT n_size = pbuffer->n_modifier_num_ * sizeof(DWORD);
			BYTE* pTemp = new BYTE[n_size];
			ZeroMemory(pTemp, sizeof(*pTemp));

			(*pResult)[9].get_blob(pTemp, (*pResult)[9].get_length());

			INT n_num = pbuffer->n_modifier_num_;
			BYTE* p_buff = pTemp;

			while(n_num)
			{
				DWORD dw_skill_id = INVALID_VALUE;
				memcpy(&dw_skill_id, p_buff, sizeof(DWORD));
				pbuffer->list_skill_id.push_back(dw_skill_id);
				p_buff += sizeof(DWORD);
				n_num--;
			}

			SAFE_DELETE_ARRAY(pTemp);
		}

		list_buffer.push_back(pbuffer);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化敌人列表
BOOL CombinationDB::InitEnemyList(LIST_ENEMY& list_enemy)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("enemy", "role_id,"	"enemy_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_enemy_list* pEnemy = new tag_enemy_list;
		ZeroMemory(pEnemy, sizeof(*pEnemy));

		pEnemy->dwRoleID = (*pResult)[0].get_dword();
		pEnemy->dwEnemyID = (*pResult)[1].get_dword();
		
		list_enemy.push_back(pEnemy);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化好友列表
BOOL CombinationDB::InitFriendList(LIST_FRIEND& list_friend)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("friend", "role_id,"	"friend_id,"	"group_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_friend_list* pFriend = new tag_friend_list;
		ZeroMemory(pFriend, sizeof(*pFriend));

		pFriend->dwRoleID = (*pResult)[0].get_dword();
		pFriend->dw_friend_id_ = (*pResult)[1].get_dword();
		pFriend->n_group_id_ = (*pResult)[2].get_int();

		list_friend.push_back(pFriend);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化好友度列表
BOOL CombinationDB::InitFriendShipList(LIST_FRIENDSHIP& list_friendship)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("friendship", "role_id,"	"friend_id,"	"friend_val");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_friendship_list* pFriendShip = new tag_friendship_list;
		ZeroMemory(pFriendShip, sizeof(*pFriendShip));

		pFriendShip->dwRoleID = (*pResult)[0].get_dword();
		pFriendShip->dw_friend_id_ = (*pResult)[1].get_dword();
		pFriendShip->n_frival_ = (*pResult)[2].get_int();

		list_friendship.push_back(pFriendShip);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化帮会列表
BOOL CombinationDB::InitGuildList(LIST_GUILD& list_guild)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild", 
		"id,"			"name,"			"creater_name_id,"	"special_state,"		"level,"
		"hold_city0,"	"hold_city1,"	"hold_city2,"		"fund,"				"material,"
		"reputation,"	"daily_cost,"	"peace,"			"rank,"				"tenet,"
		"symbol,"		"group_purchase," "leader_id,"		"remain_spread_times,"	"commendation,"
		"formal,"		"sign_num,"		 "sign_data,"		"create_time,"		"enemy_data,"
		"league_id,"	"unleague_time," "prosperity,"		"uplevel_time,"		"pos_name,"      
		"pos_power,"	"dkp,"			 "change_dkp,"		"symbol_value,"		"script_data,"	
		"text,"			"family_name,"	 "npc_name");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_guild_load* p = new s_guild_load;
		ZeroMemory(p, sizeof(s_guild_load));

		p->dwID				= (*pResult)[0].get_dword();
		p->dwFounderNameID	= (*pResult)[2].get_dword();
		p->dwSpecState		= (*pResult)[3].get_dword();
		p->byLevel			= (*pResult)[4].get_byte();
		p->byHoldCity[0]	= (*pResult)[5].get_byte();
		p->byHoldCity[1]	= (*pResult)[6].get_byte();
		p->byHoldCity[2]	= (*pResult)[7].get_byte();
		p->nFund			= (*pResult)[8].get_int();
		p->nMaterial		= (*pResult)[9].get_int();
		p->nReputation		= (*pResult)[10].get_int();
		p->nDailyCost		= (*pResult)[11].get_int();
		p->n16Peace			= (INT16)(*pResult)[12].get_int();
		p->n16Rank			= (INT16)(*pResult)[13].get_int();
		p->nGroupPurchase	= (*pResult)[16].get_int();
		p->dwLeaderRoleID	= (*pResult)[17].get_dword();
		p->byAffairRemainTimes = (BYTE)(*pResult)[18].get_dword();
		p->bCommendation	= (*pResult)[19].get_bool();
		p->bFormal			= (*pResult)[20].get_bool();
		p->bySignatoryNum	= (*pResult)[21].get_byte();
		p->dwLeagueID		= (*pResult)[25].get_dword();
		p->nProsperity		= (*pResult)[27].get_int();
		p->bSignUpAttact	= (*pResult)[32].get_bool();
		p->dwValue			= (*pResult)[33].get_dword();


		(*pResult)[1].get_blob(p->sz_name, sizeof(p->sz_name));
		(*pResult)[14].get_blob(p->sz_tenet, sizeof(p->sz_tenet));

		(*pResult)[22].get_blob(p->dwSignRoleID, sizeof(p->dwSignRoleID));
		DataTime2DwordTime(p->dwCreateTime,	(*pResult)[23].get_string(), (*pResult)[23].get_length());
		(*pResult)[24].get_blob(p->dwEnemyID, sizeof(p->dwEnemyID));
		DataTime2DwordTime(p->dwUnLeagueBeginTime, (*pResult)[26].get_string(), (*pResult)[26].get_length());
		DataTime2DwordTime(p->dwMianzhanTime, (*pResult)[28].get_string(), (*pResult)[28].get_length());
		(*pResult)[29].get_blob(p->szPosName, sizeof(p->szPosName));	
		(*pResult)[30].get_blob(p->dwPosPower, sizeof(p->dwPosPower));	
		(*pResult)[31].get_blob(p->n16DKP, sizeof(p->n16DKP));
		(*pResult)[34].get_blob(p->n32ScriptData, sizeof(p->n32ScriptData));
		(*pResult)[35].get_blob(p->szText, sizeof(p->szText));
		(*pResult)[36].get_blob(p->n_family_name, (*pResult)[36].get_length());
		(*pResult)[37].get_blob(p->n_name, (*pResult)[37].get_length());

		list_guild.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化帮会跑商
BOOL CombinationDB::InitGuildCommerceList(LIST_GUILD_COMMERCE& list_guild_commerce)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild_commodity", "role_id," "guild_id," "role_level," "tael," "goods");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_guild_commerce* pInfo = new tag_guild_commerce;
		ZeroMemory(pInfo, sizeof(*pInfo));

		pInfo->dw_role_id		= (*pResult)[0].get_dword();
		pInfo->dwGuildID		= (*pResult)[1].get_dword();
		pInfo->n_level		= (*pResult)[2].get_int();
		pInfo->n_tael		= (int)(*pResult)[3].get_int();
		(*pResult)[4].get_blob(pInfo->s_good_info, (*pResult)[4].get_length());

		list_guild_commerce.push_back(pInfo);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化帮会弹劾
BOOL CombinationDB::InitGuildDelateList(LIST_GUILD_DELATE& list_guild_delate)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild_delate", 
		"guild_id,"		"initiate_role_id,"		"be_delate_role_id,"		"agree_num,"
		"oppose_num,"	"delate_begin_time,"	"delate_end_time,"		"b_succeed,"
		"content");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_guild_delate_load* p = new s_guild_delate_load;
		ZeroMemory(p, sizeof(*p));

		p->dwGuildID = (*pResult)[0].get_dword();
		p->dwInitiateRoleID = (*pResult)[1].get_dword();
		p->dwBeDelateRoleID = (*pResult)[2].get_dword();
		p->nAgreeNum		= (*pResult)[3].get_int();
		p->nOpposeNum		= (*pResult)[4].get_int();
		DataTime2DwordTime(p->dwDelateBeginTime, (*pResult)[5].get_string(), (*pResult)[5].get_length());
		DataTime2DwordTime(p->dwDelateEneTime, (*pResult)[6].get_string(), (*pResult)[6].get_length());
		p->bSucceed			= (*pResult)[7].get_int();

		(*pResult)[8].get_blob(p->sz_content, (*pResult)[8].get_length());

		list_guild_delate.push_back(p);
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;

}

// 初始化帮会成员
BOOL CombinationDB::InitGuildMemberList(LIST_GUILD_MEMBER& list_guild_member)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild_member", 
		"role_id,"	"guild_id,"  "guild_pos,"  "total_contribution," "cur_contribution,"
		"exploit,"	"salary,"  "can_use_guild_ware," "ballot,"	"dkp," "join_time," "total_fund");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_guild_member_load* p = new s_guild_member_load;
		ZeroMemory(p, sizeof(*p));

		p->s_guild_member_.dw_role_id			= (*pResult)[0].get_dword();
		p->dw_guild_id_						= (*pResult)[1].get_dword();
		p->s_guild_member_.eGuildPos		= (EGuildMemberPos)(*pResult)[2].get_int();
		p->s_guild_member_.nTotalContribution	= (*pResult)[3].get_int();
		p->s_guild_member_.nContribution	= (*pResult)[4].get_int();
		p->s_guild_member_.nExploit			= (*pResult)[5].get_int();
		p->s_guild_member_.nSalary			= (*pResult)[6].get_int();
		p->s_guild_member_.bUseGuildWare	= (*pResult)[7].get_bool();
		p->s_guild_member_.bBallot			= (*pResult)[8].get_int();
		p->s_guild_member_.nDKP				= (*pResult)[9].get_int();	
		DataTime2DwordTime(p->s_guild_member_.dwJoinTime, (*pResult)[10].get_string(), (*pResult)[10].get_length());
		p->s_guild_member_.nTotalFund		= (*pResult)[11].get_int();

		list_guild_member.push_back(p);
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;

}

// 初始化帮会建筑
BOOL CombinationDB::InitGuildUpgradeList(LIST_GUILD_UPGRADE& list_guild_upgrade)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild_upgrade",	"guild_id,"		"type,"	"level,"	"progress,"
		"item_type_1,"	"item_neednum_1,"	
		"item_type_2,"	"item_neednum_2,"
		"item_type_3,"	"item_neednum_3,"
		"item_type_4,"	"item_neednum_4,"
		"max_level,"		"b_up_level,"			"up_begin_time,"
		"b_dead,"		"dead_begin_time,"	"relive_time,"
		"use_type,"		"use_num,"		"use_time,"
		"holiness_step");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_facilities_load* p = new s_facilities_load;
		ZeroMemory(p, sizeof(*p));

		p->dw_guild_id	= (*pResult)[0].get_dword();
		p->e_type		= (EFacilitiesType)(*pResult)[1].get_int();
		p->by_level		= (*pResult)[2].get_byte();
		p->n16_progress	= (*pResult)[3].get_short();
		p->by_max_level	= (*pResult)[12].get_byte();
		p->b_up_level		= (*pResult)[13].get_byte();
		DataTime2DwordTime(p->dw_begin_up_time, (*pResult)[14].get_string(), (*pResult)[14].get_length());
		p->b_dead		= (*pResult)[15].get_byte();
		DataTime2DwordTime(p->dw_dead_begin_time, (*pResult)[16].get_string(), (*pResult)[16].get_length());
		p->dw_relive_time_limit = (*pResult)[17].get_dword();
		p->byUseType = (*pResult)[18].get_int();
		p->byUseNum = (*pResult)[19].get_int();
		DataTime2DwordTime(p->dwUseTime, (*pResult)[20].get_string(), (*pResult)[20].get_length());
		p->byStep = (*pResult)[21].get_byte();

		for (int n=0; n<MAX_UPGRADE_NEED_ITEM_TYPE; n++)
		{
			p->dw_item_type_id[n]	= (*pResult)[n*2+4].get_dword();
			p->n_item_need[n]		= (*pResult)[n*2+5].get_int();
		}

		list_guild_upgrade.push_back(p);
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;

}

// 初始化物品
BOOL CombinationDB::InitItem(LIST_ITEM& list_item, DWORD dw_read)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("select ");
	pStream->write_string(
		"serial,"	"num,"				"type_id,"		"bind,"				"lock_state,"
		"use_times,"		"first_gain_time,"	"creator_id,"	"create_time,"		"owner_id,"
		"account_id,"	"container_type_id,"	"suffix,"		"quality,"			"potval_used,"
		"min_use_level,"	"max_use_level,"		"min_dmg_in,"		"min_dmg,"			"max_dmg,"		
		"armor,"		"potval,"			"role_att_effect," "posy_times," "posy_effect,"
		"engrave_times,"	"engrave_att,"		"hole_num,"		"hole_gem_id,"		"brand_level,"
		"derate_val,"	"x_ful_level,"		"hole_gem_ness,"		"can_cut,"			"xer_in_id,"
		"xer_out_id,"	"0,"				"0,"			"special_att,"			"appearance,"
		"rein,"			"savvy,"			"fortune,"		"color_id,"			"quality_mod_pct,"
		"quality_mod_pct_ex,"	"create_mode,"		"create_id,"		"att_a_lim_mod," "att_a_lim_mod_pct,"
		"flare_val,"		"name_id,"			"pot_val_mod_pct,"	"consolidate_level," "exp," "level," 
		"max_dmg_in,"		"armor_in,"			"equip_add_att,"	"talent_point,"		"max_talent_point,"
		"skill_list,"	"bind_time,"			"rating,"			"script_data1,"		"script_data2, " 
		"create_bind,"	"consolidate_level_star,"	"add_talent_point," "equip_rel_att");
	pStream->write_string(" from item left join equip using(serial)");
	if(dw_read > 0) pStream->write_string("where bRead = 0 limit ") << dw_read;
	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tagEquip* pItem = new tagEquip;
		ZeroMemory(pItem, sizeof(*pItem));

		pItem->n64_serial 					= (*pResult)[0].get_long();
		pItem->n16Num 						= (*pResult)[1].get_short();
		pItem->dw_data_id 					= (*pResult)[2].get_dword();
		pItem->byBind 						= (*pResult)[3].get_int();
		pItem->bCreateBind					= (*pResult)[66].get_bool();
		pItem->bLock 						= (*pResult)[4].get_bool();

		pItem->nUseTimes 					= (*pResult)[5].get_int();
		pItem->dwCreatorID 					= (*pResult)[7].get_dword();
		pItem->dwOwnerID 					= (*pResult)[9].get_dword();
		pItem->dw_account_id 					= (*pResult)[10].get_dword();

		pItem->eConType 					= (EItemConType)(*pResult)[11].get_int();
		pItem->n16Index 					= (*pResult)[12].get_short();
		pItem->eCreateMode					= (EItemCreateMode)(*pResult)[46].get_int();
		pItem->dwCreateID					= (*pResult)[47].get_dword();

		pItem->dwNameID						=(*pResult)[51].get_dword();

		DataTime2DwordTime(pItem->dw1stGainTime, (*pResult)[6].get_string(), (*pResult)[6].get_length());

		DataTime2DwordTime(pItem->dwCreateTime, (*pResult)[8].get_string(), (*pResult)[8].get_length());

		DataTime2DwordTime(pItem->dwBindTime, (*pResult)[62].get_string(), (*pResult)[62].get_length());

		pItem->dw_script_data[0] = (*pResult)[64].get_dword();
		pItem->dw_script_data[1] = (*pResult)[65].get_dword();

		if(!MIsEquipment(pItem->dw_data_id))
		{
			tagItem* pTempItem = new tagItem;
			memcpy(pTempItem, pItem, sizeof(tagItem));
			list_item.push_back(pTempItem);
			SAFE_DELETE(pItem);
			nNum--;
			pResult->next_row();
			continue;
		}

		// 装备附加属性
		pItem->equipSpec.byQuality 		= (*pResult)[13].get_byte();
		//pItem->equipSpec.nPotValUsed 		= (*pResult)[14].get_int();
		//pItem->equipSpec.byMinUseLevel 	= (*pResult)[15].get_byte();
		//pItem->equipSpec.byMaxUseLevel 	= (*pResult)[16].get_byte();
		//pItem->equipSpec.n16MinDmg 		= (*pResult)[18].get_short();
		//pItem->equipSpec.n16MaxDmg 		= (*pResult)[19].get_short();
		//pItem->equipSpec.n16Armor 		= (*pResult)[20].get_short();
		//pItem->equipSpec.nPotVal 			= (*pResult)[21].get_int();
		//pItem->equipSpec.byPosyTimes 		= (*pResult)[23].get_byte();
		//pItem->equipSpec.byEngraveTimes 	= (*pResult)[25].get_byte();
		pItem->equipSpec.byHoleNum 		= (*pResult)[27].get_byte();
		//pItem->equipSpec.byTriggerCount 	= (*pResult)[29].get_byte();
		//pItem->equipSpec.byLongfuLevel	= (*pResult)[31].get_byte();
		//pItem->equipSpec.bCanCut 			= (*pResult)[33].get_bool();
		pItem->equipSpec.byLuck			= (*pResult)[38].get_int();//装备幸运

		// 时装附加属性
		//pItem->equipSpec.n16Appearance				= (*pResult)[39].get_int();
		//pItem->equipSpec.byRein					= (*pResult)[40].get_byte();
		//pItem->equipSpec.bySavvy					= (*pResult)[41].get_byte();
		//pItem->equipSpec.byFortune					= (*pResult)[42].get_byte();
		//pItem->equipSpec.n8ColorID					= (INT8)(*pResult)[43].get_int();

		//pItem->equipSpec.n16QltyModPct				= (*pResult)[44].get_short();
		//pItem->equipSpec.n16QltyModPctEx			= (*pResult)[45].get_short();
		//pItem->equipSpec.n16PotValModPct			= (*pResult)[52].get_short();
		//pItem->equipSpec.n16AttALimMod				= (*pResult)[48].get_int();
		//pItem->equipSpec.n16AttALimModPct			= (*pResult)[49].get_int();
		//pItem->equipSpec.byFlareVal				= (*pResult)[50].get_byte();
		pItem->equipSpec.byConsolidateLevel		= (*pResult)[53].get_byte();
		//pItem->equipSpec.nCurLevelExp				= (*pResult)[54].get_int();
		//pItem->equipSpec.nLevel					= (*pResult)[55].get_int();
		//pItem->equipSpec.byTalentPoint				= (*pResult)[59].get_int();
		//pItem->equipSpec.byMaxTalentPoint			= (*pResult)[60].get_int();
		pItem->equipSpec.nRating					= (*pResult)[63].get_int();

		//(*pResult)[22].get_blob(pItem->equipSpec.nRoleAttEffect, min((*pResult)[22].get_length(), sizeof(pItem->equipSpec.nRoleAttEffect)));
		//(*pResult)[24].get_blob(pItem->equipSpec.PosyEffect, min((*pResult)[24].get_length(), sizeof(pItem->equipSpec.PosyEffect)));
		//(*pResult)[26].get_blob(pItem->equipSpec.nEngraveAtt, min((*pResult)[26].get_length(), sizeof(pItem->equipSpec.nEngraveAtt)));
		(*pResult)[28].get_blob(pItem->equipSpec.dwHoleGemID, min((*pResult)[28].get_length(), sizeof(pItem->equipSpec.dwHoleGemID)));
		//(*pResult)[30].get_blob(pItem->equipSpec.nBrandAtt, min((*pResult)[30].get_length(), sizeof(pItem->equipSpec.nBrandAtt)));
		//(*pResult)[32].get_blob(pItem->equipSpec.byHoleGemNess, min((*pResult)[32].get_length(), sizeof(pItem->equipSpec.byHoleGemNess)));
		(*pResult)[58].get_blob(pItem->equipSpec.EquipAttitionalAtt, min((*pResult)[58].get_length(), sizeof(pItem->equipSpec.EquipAttitionalAtt)));
		//(*pResult)[61].get_blob(pItem->equipSpec.dwSkillList, min((*pResult)[61].get_length(), sizeof(pItem->equipSpec.dwSkillList)));

		//pItem->equipSpec.byConsolidateLevelStar		= (*pResult)[67].get_byte();
		//pItem->equipSpec.byAddTalentPoint			= (*pResult)[68].get_byte();
		(*pResult)[69].get_blob(pItem->equipSpec.EquipAttitional, min((*pResult)[69].get_length(), sizeof(pItem->equipSpec.EquipAttitional)));

		list_item.push_back(pItem);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化物品CD
BOOL CombinationDB::InitItemCD(LIST_ITEM_CD& list_item_cd)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("item_cd_time", "role_id,"		"cd_time");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_item_cd* p = new tag_item_cd;
		//ZeroMemory(p, sizeof(*p));

		p->dw_role_id = (*pResult)[0].get_dword();

		p->n_num = (*pResult)[1].get_length() / sizeof(tagCDTime);

		if(p->n_num > 0)
		{
			INT n_size = p->n_num * sizeof(tagCDTime);
			BYTE* p_buffer = new BYTE[n_size];
			ZeroMemory(p_buffer, sizeof(*p_buffer));

			BYTE* p_Temp = p_buffer;

			(*pResult)[1].get_blob(p_Temp, (*pResult)[1].get_length());	

			for(INT i = 0; i < p->n_num; i++)
			{
				tagCDTime p_cd_time;
				ZeroMemory(&p_cd_time, sizeof(p_cd_time));
				memcpy(&p_cd_time, p_Temp, sizeof(tagCDTime));
				p->list_cd_time.push_back(p_cd_time);
				p_Temp += sizeof(tagCDTime);
			}

			SAFE_DELETE_ARRAY(p_buffer);
		}

		list_item_cd.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;

}

// 初始化邮件
BOOL CombinationDB::InitMail(LIST_MAIL& list_mail)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("mail",
		"mail_id,"		"mail_name,"	"mail_content,"	"send_role_id,"	"recv_role_id,"
		"is_send,"		"is_read,"	"is_withdrawal,"	"solve,"		"give_money,"
		"item_serial,"	"send_time,"	"recv_time,"	"is_at_once,"	"moneytype,"
		"yuanbao_type");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_load_mail* p = new tag_load_mail;
		ZeroMemory(p, sizeof(*p));

		p->s_mail_base_.dwID					= (*pResult)[0].get_dword();
		p->s_mail_base_.dwSendRoleID			= (*pResult)[3].get_dword();
		p->s_mail_base_.dwRecvRoleID			= (*pResult)[4].get_dword();
		p->s_mail_base_.bSend					= (*pResult)[5].get_int();
		p->s_mail_base_.bReed					= (*pResult)[6].get_int();
		p->s_mail_base_.bWithdrawal			= (*pResult)[7].get_int();
		p->s_mail_base_.dwSolve				= (*pResult)[8].get_int();
		p->s_mail_base_.dwGiveMoney			= (*pResult)[9].get_int();
		DataTime2DwordTime(p->s_mail_base_.dwSendTime, (*pResult)[11].get_string(), (*pResult)[11].get_length());
		DataTime2DwordTime(p->s_mail_base_.dwRecvTime, (*pResult)[12].get_string(), (*pResult)[12].get_length());
		p->s_mail_base_.bAtOnce				= (*pResult)[13].get_int();
		p->s_mail_base_.byType				= (*pResult)[14].get_short();
		p->s_mail_base_.n_yuanbao_type		= (*pResult)[15].get_short();

		(*pResult)[1].get_blob(p->str_name, sizeof(p->str_name));
		(*pResult)[2].get_blob(p->sz_content_, sizeof(p->sz_content_));
		(*pResult)[10].get_blob(p->s_mail_base_.n64ItemSerial, sizeof(p->s_mail_base_.n64ItemSerial));

		list_mail.push_back(p);
		
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化地图限制
BOOL CombinationDB::InitMapLimit(LIST_MAP_LIMIT& list_map_limit)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("map_limit",
		"role_id,"	"map_id,"	"enter_num," "type");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_map_limit* p = new tag_map_limit;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id = (*pResult)[0].get_dword();
		p->dw_map_id_ = (*pResult)[1].get_dword();
		p->dw_enter_num_ = (*pResult)[2].get_dword();
		p->e_enter_limit_ = (*pResult)[3].get_int();

		list_map_limit.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitInstanceProcess(LIST_INTS_PROCESS& list_inst_process)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("inst_process",
		"role_id,"	"map_id,"	"mode," "door_process," "creature_process," "type");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_ints_process* p = new tag_ints_process;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id = (*pResult)[0].get_dword();
		p->dw_map_id = (*pResult)[1].get_dword();
		p->n_mode = (INT16)(*pResult)[2].get_dword();
		(*pResult)[3].get_blob(p->st_door_state,(*pResult)[3].get_length( ));
		(*pResult)[4].get_blob(p->dw_creature_id,(*pResult)[4].get_length( ));
		p->n_type = (INT16)(*pResult)[5].get_dword();

		list_inst_process.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}
//初始化人物奖励信息
BOOL CombinationDB::InitRoleRewardData(LIST_ROLE_REWARD_DATA& list_reward_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("reward","role_id," "reward_data");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_reward_data* p = new tag_reward_data;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id = (*pResult)[0].get_dword();
		(*pResult)[1].get_blob(p->st_role_reward_data,min((*pResult)[1].get_length(),sizeof(p->st_role_reward_data)));

		list_reward_data.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}
//add 2013.11.11坐骑数据
BOOL CombinationDB::InitRoleMountData(LIST_MOUNT_DATA& list_mount_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("mounts", "role_id,step,grade,exp");

	odbc::execute_result* p_result = m_pdb->sql_query(pStream);

	if(!p_result)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = p_result->get_row_count() ;

	while(nNum)
	{
		tag_mount_data* p = new tag_mount_data;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id		= (*p_result)[0].get_int();
		p->nStep			= (*p_result)[1].get_int();
		p->nGrade			= (*p_result)[2].get_int();
		p->nExp				= (*p_result)[3].get_int();

		list_mount_data.push_back(p);

		nNum--;
		p_result->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(p_result);

	return bRet;
}
BOOL CombinationDB::InitRoleVCardData(LIST_ROLE_VCARD_DATA& list_vcard_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("visiting_card", "level,job,mate_role_id,guild_id,position,visibility,"
		"sex,constellation,chinesezodiac,area,province,city,head_url,signature, role_id");

	odbc::execute_result* p_result = m_pdb->sql_query(pStream);

	if(!p_result)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = p_result->get_row_count() ;

	while(nNum)
	{
		byte* pData = new byte[2048];
		memset(pData, 0, 2048);
		tagVCardData* p = (tagVCardData*)pData;
		ZeroMemory(p, sizeof(*p));

		p->dwLevel			= (*p_result)[0].get_int();
		p->dwJob			= (*p_result)[1].get_int();
		p->dwMateRoleID		= (*p_result)[2].get_int();
		p->dwFactionID		= (*p_result)[3].get_int();
		p->dwPosition		= (*p_result)[4].get_int();

		//p->customVCardData.bVisibility		= (*p_result)[5].get_bool();
		//p->customVCardData.bySex			= (*p_result)[6].get_byte();
		p->customVCardData.byConstellation	= (*p_result)[7].get_byte();
		//p->customVCardData.byChineseZodiac	= (*p_result)[8].get_byte();
		//p->customVCardData.byArea			= (*p_result)[9].get_byte();
		//p->customVCardData.byProvince		= (*p_result)[10].get_byte();
		(*p_result)[11].get_tchar(p->customVCardData.chCity, LEN_CITY_NAME);
		//p->customVCardData.byHeadUrlSize	= (*p_result)[12].get_tchar(reinterpret_cast<TCHAR *>(p->customVCardData.byData), 200) * sizeof(TCHAR);
		p->customVCardData.bySignatureSize	= (*p_result)[13].get_tchar(reinterpret_cast<TCHAR *>(&(p->customVCardData.byData)), 200) * sizeof(TCHAR);

		p->dw_role_id		= (*p_result)[14].get_int();

		list_vcard_data.push_back(p);

		nNum--;
		p_result->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(p_result);

	return bRet;
}
// 初始化师徒关系
BOOL CombinationDB::InitMaster(LIST_MASTER& list_master)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("master_prentice",
							"master," "graduates," "master_moral," "show_in_panel," "prentices" );

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_master* p = new tag_master;
		//ZeroMemory(p, sizeof(*p));

		p->dw_master = (*pResult)[0].get_dword( );
		p->dw_graduates = (UINT32)(*pResult)[1].get_dword( );
		p->dw_master_moral = (UINT32)(*pResult)[2].get_dword( );
		p->b_show_in_panel = (*pResult)[3].get_byte( );
		p->by_number =(BYTE)((*pResult)[4].get_length( ) / sizeof(DWORD) );

		if(p->by_number > 0)
		{
			INT n_size = p->by_number * sizeof(DWORD);

			BYTE* p_buffer = new BYTE[n_size];
			ZeroMemory(p_buffer, sizeof(*p_buffer));
			BYTE* p_Temp = p_buffer;

			(*pResult)[4].get_blob(p_Temp,(*pResult)[4].get_length( ));

			for(INT i = 0; i < p->by_number; i++)
			{
				DWORD dw_role;
				memcpy(&dw_role, p_Temp, sizeof(DWORD));
				p->list_role.push_back(dw_role);
				p_Temp += sizeof(DWORD);
			}

			SAFE_DELETE_ARRAY(p_buffer);
		}

		list_master.push_back(p);
		
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化拍卖行
BOOL CombinationDB::InitPaiMai(LIST_PAIMAI& list_paimai)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("paimai", 
		"id,"		"bidup,"		"bidup_id,"		"maxbidup,"
		"chaw,"		"sell_id,"		"begintime,"	"timetype,"
		"show_name");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_paimai* p = new tag_paimai;
		ZeroMemory(p, sizeof(*p));
		p->dw_paimai_id		= (*pResult)[0].get_dword();
		p->dw_bidup			= (*pResult)[1].get_dword();
		p->dw_bidup_id		= (*pResult)[2].get_dword();
		p->dw_chaw			= (*pResult)[4].get_dword();
		p->dw_sell_id		= (*pResult)[5].get_dword();
		DataTime2DwordTime(p->dw_beigin_time, (*pResult)[6].get_string(), (*pResult)[6].get_length());
		p->by_time_type		= (*pResult)[7].get_byte();
		p->b_show_name		= (BOOL)(*pResult)[8].get_byte();

		list_paimai.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化宠物
BOOL CombinationDB::InitPet(LIST_PET& list_pet)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("pet_data", "pet_id,	pet_name,	master_id,	type_id,"
		"quality,	aptitude,	potential,	cur_spirit,"
		"cur_exp,	step,	grade,	talent_count,"
		"wuxing_energy,	pet_state,	pet_lock, rename_count,"
		"happy_value, color, strength, agility,"
		"innerforce, attpoint,time_type,mode_type,"
		"xiulian_time");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_db_pet_att* pPetAtt = new s_db_pet_att;
		ZeroMemory(pPetAtt, sizeof(*pPetAtt));
		pPetAtt->dw_pet_id_	= (*pResult)[0].get_dword();
		(*pResult)[1].get_tchar(pPetAtt->sz_name_, X_SHORT_NAME);

		pPetAtt->dw_master_id_	= (*pResult)[2].get_dword();				
		pPetAtt->dw_proto_id_	= (*pResult)[3].get_dword();	
		pPetAtt->n_quality_	= (*pResult)[4].get_int();
		pPetAtt->n_aptitude_	= (*pResult)[5].get_int();
		pPetAtt->n_potential_	= (*pResult)[6].get_int();
		pPetAtt->n_spirit_	= (*pResult)[7].get_int();
		pPetAtt->n_exp_cur_	= (*pResult)[8].get_int();
		pPetAtt->n_step_		= (*pResult)[9].get_int();
		pPetAtt->n_grade_		= (*pResult)[10].get_int();
		pPetAtt->n_talent_count_= (*pResult)[11].get_int();
		pPetAtt->n_wuxing_energy_= (*pResult)[12].get_int();
		pPetAtt->by_pet_state_	= (*pResult)[13].get_int();
		pPetAtt->b_locked_	= (*pResult)[14].get_bool();
		pPetAtt->n_rename_count_=(*pResult)[15].get_int();
		pPetAtt->n_happy_value_ = (*pResult)[16].get_int();
		pPetAtt->n_color		= (*pResult)[17].get_int();
		pPetAtt->n_strength		= (*pResult)[18].get_int();
		pPetAtt->n_agility		= (*pResult)[19].get_int();
		pPetAtt->n_innerForce	= (*pResult)[20].get_int();
		pPetAtt->n_att_point	= (*pResult)[21].get_int();
		pPetAtt->dw_time_type	= (*pResult)[22].get_dword();
		pPetAtt->dw_mode_type	= (*pResult)[23].get_dword();
		pPetAtt->dw_xiulian_time = (*pResult)[24].get_dword();

		list_pet.push_back(pPetAtt);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化宠物技能
BOOL CombinationDB::InitPetSkill(LIST_PET_SKILL& list_pet_skill)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("pet_skill", "pet_id,pet_skill_type_id,para1,para2");
	
	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_pet_skill* p = new tag_pet_skill;
		ZeroMemory(p, sizeof(*p));

		p->dw_pet_id_		= (*pResult)[0].get_dword();
		p->dw_data_id		= (*pResult)[1].get_dword();
		p->n_para1_		= (*pResult)[2].get_dword();
		p->n_para2_		= (*pResult)[3].get_dword();

		list_pet_skill.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化宠物sns
BOOL CombinationDB::InitPetSns(LIST_PET_SNS& list_pet_sns)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("pet_sns", "pet_id,master_id,friend_id,begintime");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tagPetSNSInfo* pPetSns = new tagPetSNSInfo;
		ZeroMemory(pPetSns, sizeof(*pPetSns));

		pPetSns->dw_pet_id = (*pResult)[0].get_dword();
		pPetSns->dw_master_id = (*pResult)[1].get_dword();
		pPetSns->dw_friend_id = (*pResult)[2].get_dword();
		tagDWORDTime time;
		DataTime2DwordTime(time, (*pResult)[3].get_string(), (*pResult)[3].get_length());
		pPetSns->dw_begin_time = time;

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化任务
BOOL CombinationDB::InitQuest(LIST_QUEST& list_quest)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("quest", "role_id,quest_id,start_time,quest_flag,monster0_num,monster1_num,monster2_num,"
		"monster3_num,monster4_num,monster5_num,script_data, dynamic_target, dynamic_reward, scriptQuest_var,new_flag");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_quest* p = new tag_quest;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id	= (*pResult)[0].get_dword();
		p->u16QuestID	= (UINT16)(*pResult)[1].get_dword();
		p->dwAcceptTime	= (*pResult)[2].get_dword();
		p->dwQuestFlag	= (*pResult)[3].get_dword();

		for(int j=0; j<QUEST_CREATURES_COUNT; ++j)
		{
			p->n16MonsterNum[j] = (INT16)(*pResult)[j+4].get_int();
		}

		(*pResult)[QUEST_CREATURES_COUNT+3].get_blob(p->Data.dwData, (*pResult)[QUEST_CREATURES_COUNT+4].get_length());
		if((*pResult)[QUEST_CREATURES_COUNT+4].get_length() > 0)
			(*pResult)[QUEST_CREATURES_COUNT+4].get_blob(&p->DynamicTarget, (*pResult)[QUEST_CREATURES_COUNT+5].get_length());

		if((*pResult)[QUEST_CREATURES_COUNT+5].get_length() > 0)
			(*pResult)[QUEST_CREATURES_COUNT+5].get_blob(&p->DynamicReward, (*pResult)[QUEST_CREATURES_COUNT+6].get_length());

		if((*pResult)[QUEST_CREATURES_COUNT+6].get_length() > 0)
			(*pResult)[QUEST_CREATURES_COUNT+6].get_blob(&p->ScriptQuestVar, (*pResult)[QUEST_CREATURES_COUNT+7].get_length());
		
		p->u16Quest_NewFlag = (*pResult)[14].get_int();//add
		list_quest.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化任务完成
BOOL CombinationDB::InitQuestDone(LIST_QUEST_DONE& list_quest_done, DWORD dw_read_num /*= 0*/)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("quest_done", "role_id,quest_id,times,start_time,new_flag");
	if(dw_read_num > 0)
	{
		pStream->where_item();
		pStream->write_string("bRead = 0 limit ") << dw_read_num;
	}

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_quest_done* p = new tag_quest_done;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id = (*pResult)[0].get_dword();
		p->u16QuestID = (UINT16)(*pResult)[1].get_dword();
		p->dwStartTime = (*pResult)[3].get_dword();
		p->nTimes = (*pResult)[2].get_int();
		p->u16QuestFalg = (*pResult)[4].get_int();//add
		list_quest_done.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化人物数据
BOOL CombinationDB::InitRoleData(LIST_ROLE_DATA& list_role_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("role_data",		
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
		"stall_last_time," "pk_value,"		"team_id,"		"leave_guild_time," "send_mail_num," 
		"master_id," "masterprentice_forbid_time," "map_limit_num,"	 "own_instance_id,"	"own_instance_map_id,"	
		"instance_create_time," "hang_num," "is_exp,"		"is_brotherhood,"	"leave_exp,"		
		"leave_brotherhood,"	  "vigour," "bag_copper,"	"pet_packet_num,"	"role_help,"			
		"role_talk,"			  "key_info," "kill_num,"		"gift_step,"			"gift_id,"		
		"gift_leaving_time,"	  "gift_get," "gift_group_id," "total_mastermoral,"	"visualizeid,"		
		"bag_bind_gold,"		  "bag_bind_silver," "bag_bind_copper,"	"role_camp,"		"paimailimit,"  
		"banklimit," "today_online_tick," "history_vigour_cost," "exbagstep,"		"exwarestep,"	
		"ware_size,"	"ware_gold,"	"ware_silver,"		"ware_copper," "signature_name,"
		"circle_quest,"	"yuanbao_exchange_num," "achievemetn_point," "forbid_talk_start," "forbid_talk_end," "graduate_num," "destory_equip_count,"	
		"cur_1v1_score," "day_1v1_score," "day_1v1_num," "score_1v1_award," "exploits," "circle_quest_refresh,"	"exploitslimit,"
		"active_num,"	"active_data,"	"active_receive,"	"justice," "purpuredec," "circle_quest_perdaynumber," "day_clear," "cooldownrevive_cd,"
		"circle_quest_refresh_daymax," "perday_hang_getexp_timems," "shihun," "achievemetn_num,"
		"role_id,"			"account_id,"		"remove_flag,"		"avatar_equip,"		"change_name,"
		"last_change_name_time,"	"delete_role_guard_time," "pet_xiulian_size," "perday_vigour_get_total,"
		"guild_active_num," "guild_active_data," "guild_active_receive,"
		"cur_title_id2," "cur_title_id3," "instance_pass," "shaodang_begin_time," 
		"shaodang_index," "spouse_id," "vip_level," "vip_deadline");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_role_data* p = new tag_role_data;
		ZeroMemory(p, sizeof(*p));

		s_role_data_const	*p_role_data_const = &p->role_data_const_;
		s_role_data_save		*p_role_data_save	= &p->role_data_save_;

		(*pResult)[0].get_tchar(p_role_data_const->sz_role_name, X_SHORT_NAME);
		p_role_data_const->dw_role_name_crc				= (*pResult)[1].get_dword();
		p_role_data_const->avatar.bySex				= (*pResult)[3].get_byte();
		p_role_data_const->avatar.wHairMdlID			= (*pResult)[4].get_short();
		p_role_data_const->avatar.wHairTexID			= (*pResult)[5].get_short();
		p_role_data_const->avatar.wFaceMdlID			= (*pResult)[6].get_short();
		p_role_data_const->avatar.wFaceDetailTexID		= (*pResult)[7].get_short();
		p_role_data_const->avatar.wDressMdlID			= (*pResult)[8].get_short();

		p_role_data_save->display_set_					= (*pResult)[2].get_byte();
		p_role_data_save->dw_map_id_						= (*pResult)[9].get_dword();
		p_role_data_save->f_coordinate_[0]				= (*pResult)[10].get_float();
		p_role_data_save->f_coordinate_[1]				= (*pResult)[11].get_float();
		p_role_data_save->f_coordinate_[2]				= (*pResult)[12].get_float();
		p_role_data_save->f_face_[0]						= (*pResult)[13].get_float();
		p_role_data_save->f_face_[1]						= (*pResult)[14].get_float();
		p_role_data_save->f_face_[2]						= (*pResult)[15].get_float();

		p_role_data_save->e_class_						= (EClassType)(*pResult)[16].get_int();
		p_role_data_save->e_class_ex_						= (EClassTypeEx)(*pResult)[17].get_int();
		p_role_data_save->n_level_						= (*pResult)[18].get_short();
		p_role_data_save->n_cur_exp_						= (*pResult)[19].get_int();
		p_role_data_save->n_hp_							= (*pResult)[20].get_int();
		p_role_data_save->n_mp_							= (*pResult)[21].get_int();

		p_role_data_save->n_att_point_					= (*pResult)[22].get_int();
		p_role_data_save->n_talent_point_					= (*pResult)[23].get_int();

		p_role_data_save->n_att_point_add_[ERA_Physique]	= (*pResult)[24].get_int();
		p_role_data_save->n_att_point_add_[ERA_Strength]	= (*pResult)[25].get_int();
		p_role_data_save->n_att_point_add_[ERA_Pneuma]		= (*pResult)[26].get_int();
		p_role_data_save->n_att_point_add_[ERA_InnerForce]	= (*pResult)[27].get_int();
		p_role_data_save->n_att_point_add_[ERA_Technique]	= (*pResult)[28].get_int();
		p_role_data_save->n_att_point_add_[ERA_Agility]	= (*pResult)[29].get_int();

		p_role_data_save->n_injury_						= (*pResult)[30].get_int();
		p_role_data_save->n_brotherhood_					= (*pResult)[31].get_int();
		p_role_data_save->n_knowledge_					= (*pResult)[32].get_int();
		p_role_data_save->n_morality_					= (*pResult)[33].get_int();
		p_role_data_save->n_luck_						= (*pResult)[34].get_int();
		p_role_data_save->n_credit_						= (*pResult)[35].get_int();
		p_role_data_save->n_identity_					= (*pResult)[36].get_int();
		p_role_data_save->n_vip_point_					= (*pResult)[37].get_int();

		p_role_data_save->n16_bag_size_					= (*pResult)[38].get_short();
		p_role_data_save->n_bag_gold_						= (*pResult)[39].get_int();
		p_role_data_save->n_bag_silver_					= (*pResult)[40].get_int();
		p_role_data_save->n_bag_tuanbao_					= (*pResult)[41].get_int();

		p_role_data_save->dw_guild_id					= (*pResult)[42].get_dword();
		//p_role_data_save->nWareGold					= (*pResult)[43].GetInt();
		//p_role_data_save->nWareSilver					= (*pResult)[44].GetInt();
		//p_role_data_save->nWareYuanBao					= (*pResult)[45].GetInt();

		DataTime2DwordTime(p_role_data_const->create_time_,	(*pResult)[46].get_string(), (*pResult)[46].get_length());

		DataTime2DwordTime(p_role_data_save->login_time_,	(*pResult)[47].get_string(), (*pResult)[47].get_length());
		DataTime2DwordTime(p_role_data_save->logout_time_,	(*pResult)[48].get_string(), (*pResult)[48].get_length());

		p_role_data_save->n_online_time_					= (*pResult)[49].get_dword();
		p_role_data_save->n_cur_online_time_				= (*pResult)[50].get_dword();

		p_role_data_save->n_rage_						= (*pResult)[51].get_int();
		p_role_data_save->n_endurance_					= (*pResult)[52].get_int();
		p_role_data_save->b_safe_guard_					= (*pResult)[53].get_int();

		//p_role_data_save->CloseSafeGuardTime			= (*pResult)[54].GetDword();
		DataTime2DwordTime(p_role_data_save->close_safe_guard_time_,	(*pResult)[54].get_string(), (*pResult)[54].get_length());

		p_role_data_save->talent_[0].eType				= (ETalentType)(*pResult)[55].get_int();
		p_role_data_save->talent_[1].eType				= (ETalentType)(*pResult)[56].get_int();
		p_role_data_save->talent_[2].eType				= (ETalentType)(*pResult)[57].get_int();
		p_role_data_save->talent_[3].eType				= (ETalentType)(*pResult)[58].get_int();
		p_role_data_save->talent_[0].nPoint				= (*pResult)[59].get_int();
		p_role_data_save->talent_[1].nPoint				= (*pResult)[60].get_int();
		p_role_data_save->talent_[2].nPoint				= (*pResult)[61].get_int();
		p_role_data_save->talent_[3].nPoint				= (*pResult)[62].get_int();

		p_role_data_save->dw_reborn_map_id_				= (*pResult)[63].get_dword();
		p_role_data_save->n_total_tax_					= (*pResult)[64].get_int();
		p_role_data_save->n_morale_						= (*pResult)[65].get_int();

		DataTime2DwordTime(*(tagDWORDTime*)&p_role_data_save->dw_time_get_mall_free_, (*pResult)[66].get_string(), (*pResult)[66].get_length());
		p_role_data_save->s_remote_open_set_				= (*pResult)[67].get_dword();
		p_role_data_save->u16_active_title_id[0]				= (*pResult)[68].get_int();
		p_role_data_save->u16_active_title_id[1]				= (*pResult)[158].get_int();//modify
		p_role_data_save->u16_active_title_id[2]				= (*pResult)[159].get_int();//modify


		p_role_data_save->n_ex_volume_					= (*pResult)[69].get_int();
		(*pResult)[70].get_blob(p_role_data_save->data_.dwData, (*pResult)[70].get_length());
		p_role_data_save->n_treasure_sum_					= (*pResult)[71].get_int();

		p_role_data_save->by_stall_level_					= (*pResult)[72].get_byte();
		p_role_data_save->n_stall_daily_exp_				= (*pResult)[73].get_int();
		p_role_data_save->n_stall_cur_exp_					= (*pResult)[74].get_int();
		p_role_data_save->dw_last_stall_time_				= (*pResult)[75].get_dword();
		p_role_data_save->n_pk_value_						= (*pResult)[76].get_int();
		p_role_data_save->dw_team_id_						= (*pResult)[77].get_dword();
		DataTime2DwordTime(p_role_data_save->leave_guild_time_,	(*pResult)[78].get_string(), (*pResult)[78].get_length());
		p_role_data_save->n_send_mail_num_					= (*pResult)[79].get_int();
		p_role_data_save->dw_master_id_ = (*pResult)[80].get_dword();
		p_role_data_save->dw_master_prentice_forbid_time_ = (*pResult)[81].get_dword();
		p_role_data_save->n_map_limit_num_ = (*pResult)[82].get_int();
		p_role_data_save->dw_own_instance_id_ = (*pResult)[83].get_dword();
		p_role_data_save->dw_own_instance_map_id_ = (*pResult)[84].get_dword();
		DataTime2DwordTime(p_role_data_save->dw_instance_create_time_, (*pResult)[85].get_string(), (*pResult)[85].get_length());
		p_role_data_save->n16_hang_num_ = (*pResult)[86].get_int();
		p_role_data_save->b_exp_ = (*pResult)[87].get_int();
		p_role_data_save->b_brotherhood_ = (*pResult)[88].get_int();
		p_role_data_save->n_leave_exp_ = (*pResult)[89].get_int();
		p_role_data_save->n_leave_brotherhood_ = (*pResult)[90].get_int();
		p_role_data_save->n_vigour_ = (*pResult)[91].get_int();
		p_role_data_save->n_bag_copper_ = (*pResult)[92].get_int();
		p_role_data_save->n16_pet_packet_size_ = (*pResult)[93].get_int();
		(*pResult)[94].get_blob(p_role_data_save->by_role_help_, (*pResult)[94].get_length());
		(*pResult)[95].get_blob(p_role_data_save->by_talk_data_, (*pResult)[95].get_length());
		(*pResult)[96].get_blob(&p_role_data_save->st_key_info_, (*pResult)[96].get_length());
		p_role_data_save->n_kill_num_ = (*pResult)[97].get_int();
		p_role_data_save->n_gift_step_ = (*pResult)[98].get_short();
		p_role_data_save->dw_gift_id_ = (*pResult)[99].get_dword();
		p_role_data_save->dw_gift_leave_time_ = (*pResult)[100].get_dword();
		p_role_data_save->b_gift_get_ = (BOOL)(*pResult)[101].get_short();
		p_role_data_save->n_gift_id_ = (*pResult)[102].get_short();
		p_role_data_save->n_total_mater_moral_ = (*pResult)[103].get_int();
		p_role_data_const->avatar.byVisualize = (*pResult)[104].get_byte();
		p_role_data_save->n_bag_bind_gold_ = (*pResult)[105].get_int();
		p_role_data_save->n_bag_bind_silver_ = (*pResult)[106].get_int();
		p_role_data_save->n_bag_bind_copper_ = (*pResult)[107].get_int();
		p_role_data_save->e_role_camp = (ECamp)(*pResult)[108].get_short();
		p_role_data_save->n_paimai_limit = (*pResult)[109].get_int();
		p_role_data_save->n_bank_limit = (*pResult)[110].get_int();
		p_role_data_save->dw_today_online_tick_ = (*pResult)[111].get_dword();
		p_role_data_save->dw_history_vigour_cost_ = (*pResult)[112].get_dword();
		p_role_data_save->n16_exbag_step = (*pResult)[113].get_short();
		p_role_data_save->n16_exware_step = (*pResult)[114].get_short();
		p_role_data_save->n16WareSize = (*pResult)[115].get_int();
		p_role_data_save->nWareGold = (*pResult)[116].get_int();
		p_role_data_save->nWareSilver = (*pResult)[117].get_int();
		p_role_data_save->nWareCopper = (*pResult)[118].get_int();

		(*pResult)[119].get_tchar(p_role_data_save->sz_signature_name, X_SHORT_NAME);

		// 环随机任务
		if((*pResult)[120].get_length()) 
			(*pResult)[120].get_blob(&p_role_data_save->circle_quest_man_, (*pResult)[120].get_length());

		p_role_data_save->n_yuanbao_exchange_num = (*pResult)[121].get_int();

		p_role_data_save->n_achievement_point = (*pResult)[122].get_int();

		p_role_data_save->dw_forbid_talk_start_ = (*pResult)[123].get_dword();
		p_role_data_save->dw_forbid_talk_end_ = (*pResult)[124].get_dword();

		p_role_data_save->n_graduates_num = (*pResult)[125].get_int();

		p_role_data_save->dw_destory_equip_count = (*pResult)[126].get_dword();

		p_role_data_save->st_1v1_score.n_cur_score = (*pResult)[127].get_int();
		p_role_data_save->st_1v1_score.n_day_max_score = (*pResult)[128].get_int();
		p_role_data_save->st_1v1_score.n_day_scroe_num = (*pResult)[129].get_int();
		p_role_data_save->st_1v1_score.n16_score_award = (*pResult)[130].get_short();
/**/
		p_role_data_save->n32_exploits = (*pResult)[131].get_int();
		p_role_data_save->n_circle_quest_fresh = (*pResult)[132].get_int();

		p_role_data_save->n_shop_exploits_limit = (*pResult)[133].get_int();

		p_role_data_save->n32_active_num = (*pResult)[134].get_int();
		if((*pResult)[135].get_length())
			(*pResult)[135].get_blob(&p_role_data_save->n32_active_data, (*pResult)[135].get_length());
		if((*pResult)[136].get_length())
			(*pResult)[136].get_blob(&p_role_data_save->b_active_receive, (*pResult)[136].get_length());

		p_role_data_save->n32_rating = (*pResult)[137].get_int();
		p_role_data_save->b_PurpureDec = (*pResult)[138].get_bool();
		p_role_data_save->n_circle_quest_perdaynum = (*pResult)[139].get_int();

		(*pResult)[140].get_blob(p_role_data_save->by_role_day_clear, (*pResult)[140].get_length());

		p_role_data_save->n_CoolDownReviveCD = (*pResult)[141].get_int();
		p_role_data_save->n_circle_quest_freshMax = (*pResult)[142].get_int();
		p_role_data_save->n_PerDayHangGetExpTimeMS = (*pResult)[143].get_int();
		p_role_data_save->dw_shihun = (*pResult)[144].get_dword();
		p_role_data_save->n_achievement_num = (*pResult)[145].get_int();

		p->dw_role_id = (*pResult)[146].get_dword();
		p->dw_account_id = (*pResult)[147].get_dword();
		p->b_remove = (*pResult)[148].get_int();
		if(!(*pResult)[149].is_null())
			(*pResult)[149].get_blob(&p->role_data_save_.avatar_equip_, min((*pResult)[149].get_length(), SIZE_AVATAR_EQUIP));
		p->b_change_name = (*pResult)[150].get_short();
		p->dwChangeNameTime = (*pResult)[151].get_dword();
		p->dwDelGuardTime = (*pResult)[152].get_dword();
		p_role_data_save->n16_pet_xiulian_size= (*pResult)[153].get_int();
		p_role_data_save->dw_perday_get_vigour_total = (*pResult)[154].get_dword();
		p_role_data_save->n32_guild_active_num = (*pResult)[155].get_int();
		if((*pResult)[156].get_length())
			(*pResult)[156].get_blob(&p_role_data_save->n32_guild_active_data, (*pResult)[156].get_length());
		if((*pResult)[157].get_length())
			(*pResult)[157].get_blob(&p_role_data_save->b_guild_active_receive, (*pResult)[157].get_length());

		//gx add 2013.10.14
		p_role_data_save->nInstanceData = (*pResult)[160].get_dword();
		p_role_data_save->nInstanceShaodang = (*pResult)[161].get_dword();
		p_role_data_save->nSaodangIndex = (*pResult)[162].get_dword();
		p_role_data_save->dwSpouseID = (*pResult)[163].get_dword();

		//vip
		p_role_data_save->dwVIPLevel = (*pResult)[164].get_int();
		DataTime2DwordTime(p_role_data_save->dwVIP_Deadline, (*pResult)[165].get_string(), (*pResult)[165].get_length());
		//end

		list_role_data.push_back(p);


		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化人物技能
BOOL CombinationDB::InitRoleSkill(LIST_ROLE_SKILL& list_role_skill)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("skill", "role_id,id,bidden_level,self_level,cooldown,proficiency");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_role_skill* p = new tag_role_skill;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id		= (*pResult)[0].get_dword();
		p->dw_id			= (*pResult)[1].get_dword();
		p->n_self_level_	= (*pResult)[3].get_int();
		p->n_learn_level_	= (*pResult)[2].get_int();
		p->n_cool_down_	    = (*pResult)[4].get_int();
		p->n_proficiency_	= (*pResult)[5].get_int();

		list_role_skill.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化称号
BOOL CombinationDB::InitTitle(LIST_TITLE& list_title)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("title", "role_id,id,count,time");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_title* p = new tag_title;
		ZeroMemory(p, sizeof(*p));

		p->dw_role_id		= (*pResult)[0].get_dword();
		p->n_title_id_		= (UINT16)(*pResult)[1].get_dword();
		p->dw_state_mark_	= (*pResult)[2].get_dword();

		tagDWORDTime time;
		DataTime2DwordTime(time, (*pResult)[3].get_string(), (*pResult)[3].get_length());
		p->dw_time	= time;

		list_title.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化钱庄
BOOL CombinationDB::InitBank(LIST_BANK& list_bank)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("bank",
		"id,"		"bidup,"		"bidup_id,"		"type,"
		"sell,"		"chaw,"			"sell_id,"		"begintime,"
		"timetype");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_bank* p = new tag_bank;
		ZeroMemory(p, sizeof(*p));

		p->dw_id = (*pResult)[0].get_dword();
		p->dw_bidup = (*pResult)[1].get_dword();
		p->dw_bidup_id = (*pResult)[2].get_dword();
		p->by_type = (*pResult)[3].get_byte();
		p->dw_sell = (*pResult)[4].get_dword();
		p->dw_chaw = (*pResult)[5].get_dword();
		p->dw_sell_id = (*pResult)[6].get_dword();
		DataTime2DwordTime(p->dw_begin_time, (*pResult)[7].get_string(), (*pResult)[7].get_length());
		p->by_time_type = (*pResult)[8].get_byte();

		list_bank.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 初始化悬赏
BOOL CombinationDB::InitGuerdonQuest(LIST_GUERDON_QUEST& list_guerdon_quest)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guerdon_quest", "serial,sender,reciver,quest_id,guild_fix,state,yuanbao,end_time");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		guerdon_quest* pGuerdon_Quest = new guerdon_quest;
		ZeroMemory(pGuerdon_Quest, sizeof(*pGuerdon_Quest));

		pGuerdon_Quest->n64Serial = (*pResult)[0].get_long( );
		pGuerdon_Quest->dwSender = (*pResult)[1].get_dword();
		pGuerdon_Quest->dwReciver = (*pResult)[2].get_dword();
		pGuerdon_Quest->u16QuestID = (UINT16)(*pResult)[3].get_int( );
		pGuerdon_Quest->bGuildFix = (BOOL)(*pResult)[4].get_byte( );
		pGuerdon_Quest->eState = (EGuerdonQuestState)(*pResult)[5].get_byte( );
		pGuerdon_Quest->u16YuanBao = (UINT16)(*pResult)[6].get_int( );
		pGuerdon_Quest->dwEndTime = (*pResult)[7].get_dword();

		list_guerdon_quest.push_back(pGuerdon_Quest);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InitAccount(LIST_ACCOUNT_DATA&	list_main_account)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("account", "id, name, password");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		tag_account_data* p = new tag_account_data;
		ZeroMemory(p, sizeof(*p));

		p->dw_account_id = (*pResult)[0].get_dword();
		memcpy(p->sz_account_name, (*pResult)[1].get_string(), (*pResult)[1].get_length());
		memcpy(p->sz_password, (*pResult)[2].get_string(), (*pResult)[2].get_length());

		list_main_account.push_back(p);
		
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;

}
BOOL CombinationDB::InitThirdAccount(MAP_THIRD_ACCOUNT_DATA& map_main_account)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("account_third", "account_id, code, third_type, third_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;
	int sameid_num = 0;

	while(nNum)
	{
		//可能出现一个平台账号对应多个
		tag_third_key tmpKey;
		tmpKey.n_thirdtype = (*pResult)[2].get_int();
		tmpKey.dw_thirdid = (*pResult)[3].get_dword();
		MAP_THIRD_ACCOUNT_DATA::iterator iter = map_main_account.find(tmpKey);
		if (iter != map_main_account.end())//已经存在的平台账号，不再考虑
		{
			sameid_num++;
		}
		else
		{
			tag_third_account_data* p = new tag_third_account_data;
			ZeroMemory(p, sizeof(*p));

			p->dw_account_id = (*pResult)[0].get_dword();
			memcpy(p->sz_password, (*pResult)[1].get_string(), (*pResult)[1].get_length());
			p->n_thirdtype = (*pResult)[2].get_int();
			p->dw_thirdid = (*pResult)[3].get_dword();

			map_main_account.insert(std::make_pair(tmpKey,p));
		}
		nNum--;
		pResult->next_row();
	}
	
	//二次处理，获取account_name与pass_word
	MAP_THIRD_ACCOUNT_DATA::iterator iter = map_main_account.begin();
	while (iter != map_main_account.end())
	{
		if (!GetThirdAccount_Name(iter->second))
		{
			bRet = FALSE;
			goto exit;
		}
		iter++;
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::GetThirdAccount_Name(tag_third_account_data* pThirdAccountData)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("account", "name, password,forbid_mask,ip");
	pStream->where_item();
	pStream->write_string("id='")<<pThirdAccountData->dw_account_id;
	pStream->write_string("'");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;
	if (nNum != 1)
	{
		bRet = FALSE;
		goto exit;
	}

	memcpy(pThirdAccountData->sz_account_name, (*pResult)[0].get_string(), (*pResult)[0].get_length());
	memcpy(pThirdAccountData->sz_account_password, (*pResult)[1].get_string(), (*pResult)[1].get_length());
	pThirdAccountData->dw_forbid_mask = (*pResult)[2].get_dword();//add 2013.12.03
	memcpy(pThirdAccountData->sz_account_ip,(*pResult)[3].get_string(),(*pResult)[3].get_length());

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}
VOID CombinationDB::CheckAccount(tag_account_data* pAccountData, DWORD& dw_account_max_id)
{
	INT nNum = 0;
	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return ;
	}

	pStream->clear();

	tag_mysql_connect* p_con = m_pdb->get_idlesse_connect();

	pStream->select_item("account", "id");
	pStream->where_item();
	pStream->write_string("name='").write_string(pAccountData->sz_account_name, p_con).write_string("'");

	m_pdb->return_use_connect(p_con);

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	/*if(!pResult)
	{
		goto exit;
	}*/

	nNum = pResult->get_row_count() ;

	if(nNum <= 0)
	{
		dw_account_max_id++;
		tag_account_data* p = new tag_account_data;
		ZeroMemory(p, sizeof(*p));
		memcpy(p, pAccountData, sizeof(tag_account_data));
		p->dw_change_account_id = dw_account_max_id;
		m_pCombin_Dlg->get_list_no_exist_account().push_back(p);
		goto exit;
	}

	while(nNum)
	{
		DWORD dw_account_id = (*pResult)[0].get_dword();

		if(dw_account_id != pAccountData->dw_account_id)
		{
			tag_account_data* p = new tag_account_data;
			ZeroMemory(p, sizeof(*p));
			memcpy(p, pAccountData, sizeof(tag_account_data));
			p->dw_change_account_id = dw_account_id;
			m_pCombin_Dlg->get_list_change_account().push_back(p);
		}
		
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);
}
VOID CombinationDB::CheckThirdAccount(tag_third_account_data* pThirdAccountData,DWORD& dw_account_max_id)
{
	INT nNum = 0;
	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return ;
	}

	pStream->clear();


	pStream->select_item("account_third", "account_id");//平台类型与平台id对应相等才是同一个账号
	pStream->where_item();
	pStream->write_string("third_type='")<<pThirdAccountData->n_thirdtype;
	pStream->write_string("' AND third_id='")<<pThirdAccountData->dw_thirdid;
	pStream->write_string("'");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	/*if(!pResult)
	{
		goto exit;
	}*/

	nNum = pResult->get_row_count() ;

	if(nNum <= 0)
	{
		dw_account_max_id++;
		tag_third_account_data* p = new tag_third_account_data;
		ZeroMemory(p, sizeof(*p));
		memcpy(p, pThirdAccountData, sizeof(tag_third_account_data));
		p->dw_change_account_id = dw_account_max_id;

		tag_third_key tmpKey;
		tmpKey.n_thirdtype = p->n_thirdtype;
		tmpKey.dw_thirdid = p->dw_thirdid;
		m_pCombin_Dlg->get_map_no_exist_third_account().insert(std::make_pair(tmpKey,p));
		goto exit;
	}

	while(nNum)
	{
		DWORD dw_account_id = (*pResult)[0].get_dword();

		if(dw_account_id != pThirdAccountData->dw_account_id)
		{
			tag_third_account_data* p = new tag_third_account_data;
			ZeroMemory(p, sizeof(*p));
			memcpy(p, pThirdAccountData, sizeof(tag_third_account_data));
			p->dw_change_account_id = dw_account_id;

			tag_third_key tmpKey;
			tmpKey.n_thirdtype = p->n_thirdtype;
			tmpKey.dw_thirdid = p->dw_thirdid;
			m_pCombin_Dlg->get_map_change_third_account().insert(std::make_pair(tmpKey,p));
		}
		
		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);
}
BOOL CombinationDB::ChangeAccountCommonIndex()
{
	BOOL bRet = TRUE;
	
	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("alter table account_common drop primary key");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();

	pStream->write_string("alter table account_common add index account_id(account_id)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();

	pStream->write_string("alter table account_common add column bChange tinyint unsigned not null default '0'");

	bRet = m_pdb->sql_execute(pStream);

	
	m_pdb->return_io(pStream);

}

BOOL CombinationDB::ChangeAccountCommonID(tag_account_data* pAccountData)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->update_item("account_common");
	pStream->write_string("account_id = ") << pAccountData->dw_change_account_id;
	pStream->write_string(",bChange = 1");
	pStream->where_item();
	pStream->write_string("account_id = ") << pAccountData->dw_account_id;
	pStream->write_string(" and ");
	pStream->write_string("bChange = 0");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
BOOL CombinationDB::ChangeAccountCommonID(tag_third_account_data* pThirdAccountData)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->update_item("account_common");
	pStream->write_string("account_id = ") << pThirdAccountData->dw_change_account_id;
	pStream->write_string(",bChange = 1");
	pStream->where_item();
	pStream->write_string("account_id = ") << pThirdAccountData->dw_account_id;
	pStream->write_string(" and ");
	pStream->write_string("bChange = 0");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
BOOL CombinationDB::ChangeRoleDataAccountID(tag_account_data* pAccountData)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->update_item("role_data");
	pStream->write_string("account_id = ") << pAccountData->dw_change_account_id;
	pStream->write_string(",bChange = 1");
	pStream->where_item();
	pStream->write_string("account_id = ") << pAccountData->dw_account_id;
	pStream->write_string(" and ");
	pStream->write_string("bChange = 0");

		bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
BOOL CombinationDB::ChangeRoleDataAccountID(tag_third_account_data* pThirdAccountData)
{
	BOOL bRet = TRUE;
	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}
	pStream->clear();

	pStream->update_item("role_data");
	pStream->write_string("account_id = ") << pThirdAccountData->dw_change_account_id;
	pStream->write_string(",bChange = 1");
	pStream->where_item();
	pStream->write_string("account_id = ") << pThirdAccountData->dw_account_id;
	pStream->write_string(" and ");
	pStream->write_string("bChange = 0");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
BOOL CombinationDB::InsertAccount(tag_account_data* pAccountData)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	tag_mysql_connect* p_con = m_pdb->get_idlesse_connect();

	pStream->insert_item("account");
	pStream->write_string("id=") << pAccountData->dw_change_account_id;
	pStream->write_string(",name='").write_string(pAccountData->sz_account_name, p_con).write_string("'");
	pStream->write_string(",password='").write_string(pAccountData->sz_password, p_con).write_string("'");

	m_pdb->return_use_connect(p_con);

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
BOOL CombinationDB::InsertAccount(tag_third_account_data* pAccountThird)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	tag_mysql_connect* p_con = m_pdb->get_idlesse_connect();

	pStream->insert_item("account");
	pStream->write_string("id=") << pAccountThird->dw_change_account_id;
	pStream->write_string(",name='").write_string(pAccountThird->sz_account_name, p_con).write_string("'");
	pStream->write_string(",password='").write_string(pAccountThird->sz_account_password, p_con).write_string("'");
	pStream->write_string(",forbid_mask=") << pAccountThird->dw_forbid_mask;//add 2013.12.03
	pStream->write_string(",ip='").write_string(pAccountThird->sz_account_ip,p_con).write_string("'");
	m_pdb->return_use_connect(p_con);

	bRet = m_pdb->sql_execute(pStream);
	m_pdb->return_io(pStream);
	//可能存在不同大区之间不同平台账号对应相同的account_name
	if (!bRet)
	{
		strcat(pAccountThird->sz_account_name,"_");
		pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		tag_mysql_connect* p_con_temp = m_pdb->get_idlesse_connect();

		pStream->insert_item("account");
		pStream->write_string("id=") << pAccountThird->dw_change_account_id;
		pStream->write_string(",name='").write_string(pAccountThird->sz_account_name, p_con_temp).write_string("'");
		pStream->write_string(",password='").write_string(pAccountThird->sz_account_password, p_con_temp).write_string("'");

		m_pdb->return_use_connect(p_con_temp);

		bRet = m_pdb->sql_execute(pStream);
		m_pdb->return_io(pStream);
	}
	//
}
BOOL CombinationDB::InsertThirdAccount(tag_third_account_data* pAccountThird)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	tag_mysql_connect* p_con = m_pdb->get_idlesse_connect();

	pStream->insert_item("account_third");
	pStream->write_string("account_id=") << pAccountThird->dw_change_account_id;
	pStream->write_string(",code='").write_string(pAccountThird->sz_password, p_con).write_string("'");
	pStream->write_string(",third_type=") << pAccountThird->n_thirdtype;
	pStream->write_string(",third_id=") << pAccountThird->dw_thirdid;

	m_pdb->return_use_connect(p_con);

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
BOOL CombinationDB::AddRoleDataChange()
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("alter table role_data add column bChange tinyint unsigned not null default '0'");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}
// 初始化悬赏
//BOOL CombinationDB::InitXuanShang(LIST_XUANSHANG& list_xuanshang)
//{
//	BOOL bRet = TRUE;
//	INT nNum = 0;
//
//	odbc::sql_language_disposal* pStream = m_pdb->get_io();
//	if(!pStream)
//	{
//		return FALSE;
//	}
//
//	pStream->clear();
//
//	pStream->select_item("xuanshang_quest", "serial," "sender_id," "reciver_id," "quest_id,"
//		"delete_time," "quest_state," "complete_data");
//
//	odbc::execute_result* pResult = m_pdb->sql_query(pStream);
//
//	if(!pResult)
//	{
//		bRet = FALSE;
//		goto exit;
//	}
//
//	nNum = pResult->get_row_count() ;
//
//	while(nNum)
//	{
//		tagXuanShangQuestLoad* p = new tagXuanShangQuestLoad;
//		ZeroMemory(p, sizeof(*p));
//
//		p->dwSerial		= (*pResult)[0].get_dword( );
//		p->dwSenderID	= (*pResult)[1].get_dword( ); 
//		p->dwReciverID	= (*pResult)[2].get_dword( );
//		p->u16QuestID	= (UINT16)(*pResult)[3].get_int( );
//		p->dwDeleteTime = (DWORD)(*pResult)[4].get_dword( );
//		p->eState		= (EXuanShangQuestState)(*pResult)[5].get_byte( );
//		(*pResult)[6].get_blob( &p->sCompleteData, (*pResult)[6].get_length( ));
//
//		list_xuanshang.push_back(p);
//
//		nNum--;
//		pResult->next_row();
//	}
//
//exit:
//	m_pdb->return_io(pStream);
//	m_pdb->free_result_query(pResult);
//
//	return bRet;
//}

// 获得角色最大ID
BOOL CombinationDB::GetMaxRoleID(DWORD&	dw_role_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("role_data", "max(role_id)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_role_max_id = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::GetMaxPaimaiID(DWORD&	dw_paimai_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("paimai", "max(id)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_paimai_max_id = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 获取钱庄最大ID
BOOL CombinationDB::GetMaxBankID(DWORD&	dw_bank_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("bank", "max(id)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_bank_max_id = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 获取物品最大编号
BOOL CombinationDB::GetMaxItemID(INT64&	n64_item_max_id, LPCSTR sz_table_name)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item(sz_table_name, "max(serial)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		n64_item_max_id = (INT64)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 获取邮件最大编号
BOOL CombinationDB::GetMaxMailID(DWORD&	dw_mail_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("mail", "max(mail_id)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_mail_max_id = (INT64)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 获得最大宠物编号
BOOL CombinationDB::GetMaxPetID(DWORD&		dw_pet_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("pet_data", "max(pet_id)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_pet_max_id = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 获取悬赏最大ID
BOOL CombinationDB::GetMaxGuerdonID(DWORD& dw_guerdon_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guerdon_quest", "max(serial)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_guerdon_max_id = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::GetMaxAccountID(DWORD& dw_account_max_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("account", "max(id)");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_account_max_id = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

// 插入角色公有数据
BOOL CombinationDB::InsertAccountCommon(MAP_ACCOUNT_COMMON& map_main_account_common, BOOL bDel/* = FALSE*/)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	if(bDel)
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->write_string("delete from account_common");

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
		return bRet;
		}*/

		m_pdb->return_io(pStream);
	}

	MAP_ACCOUNT_COMMON::iterator iter_account_common = map_main_account_common.begin();
	while(iter_account_common != map_main_account_common.end())
	{
		tag_account_common* pAccount_Common = iter_account_common->second;
		if(!VALID_POINT(pAccount_Common))
		{
			iter_account_common++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		tag_mysql_connect* p_con = m_pdb->get_idlesse_connect();

		pStream->clear();

		pStream->replace_item("account_common");
		pStream->write_string("account_id=") << pAccount_Common->dw_account_id;
		pStream->write_string(",account_name='").write_string(pAccount_Common->sz_account_name, p_con).write_string("'");
		pStream->write_string(",bag_password_crc=") << pAccount_Common->dw_bag_password_crc_;
		pStream->write_string(",baibao_yuanbao=") << pAccount_Common->n_baibao_yuanbao_;
		pStream->write_string(",score=") << pAccount_Common->n32_score;
		pStream->write_string(",yuanbao_recharge=") << pAccount_Common->n_yuanbao_recharge;
		pStream->write_string(",total_recharge=") << pAccount_Common->dw_total_recharge;
		/*pStream->write_string(",IsReceive=") << pAccount_Common->b_receive;
		pStream->write_string(",receive_type=") << pAccount_Common->n16_receive_type;
		pStream->write_string(",receive_type_ex=") << pAccount_Common->dw_receive_type;
		pStream->write_string(",web_type=") << pAccount_Common->dw_web_type;*/

		m_pdb->return_use_connect(p_con);


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_account_common++;
	}

	return bRet;
}

// 插入成就称号
BOOL CombinationDB::InsertAchievement(LIST_ACHIEVEMENT& list_achievement)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ACHIEVEMENT::iterator iter_achievement = list_achievement.begin();
	while(iter_achievement != list_achievement.end())
	{
		if(!VALID_POINT(*iter_achievement))
		{
			iter_achievement++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("achievement");
		pStream->write_string("role_id=") << (*iter_achievement)->dw_role_id;
		pStream->write_string(",id=") << (*iter_achievement)->dw_id;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), (*iter_achievement)->dw_date);
		pStream->write_string(",date='").write_string(sz_time_buffer_);
		pStream->write_string("'");


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_achievement++;
	}

	return bRet;
}

// 插入成就进度
BOOL CombinationDB::InsertAchievement(LIST_ACHIEVEMENT_PROCESS& list_achievement_process)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ACHIEVEMENT_PROCESS::iterator iter_achievement_process = list_achievement_process.begin();
	while(iter_achievement_process != list_achievement_process.end())
	{
		if(!VALID_POINT(*iter_achievement_process))
		{
			iter_achievement_process++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->replace_item("achievement_progress");
		pStream->write_string("role_id=") << (*iter_achievement_process)->dw_role_id;
		pStream->write_string(",id=") << (*iter_achievement_process)->dw_id;
		pStream->write_string(",counter=") << (*iter_achievement_process)->dw_count;


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_achievement_process++;
	}

	return bRet;
}

// 插入黑名单数据
BOOL CombinationDB::InsertBlackList(LIST_BLACK& list_black)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_BLACK::iterator iter_black = list_black.begin();
	while(iter_black != list_black.end())
	{
		if(!VALID_POINT(*iter_black))
		{
			iter_black++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("blacklist");
		pStream->write_string("role_id=") << (*iter_black)->dwRoleID;
		pStream->write_string(",black_id=") << (*iter_black)->dwBlackID;


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_black++;
	}

	return bRet;
}

// 插入buffer数据
BOOL CombinationDB::InsertBufferList(LIST_BUFFER& list_buffer)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_BUFFER::iterator iter_buffer = list_buffer.begin();
	while(iter_buffer != list_buffer.end())
	{
		if(!VALID_POINT(*iter_buffer))
		{
			iter_buffer++;
			continue;
		}

		tag_buffer_list* p = *iter_buffer;

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("buff");
		pStream->write_string("role_id=") << p->dwRoleID;
		pStream->write_string(",src_unit_id=") << p->dw_src_unit_id_;
		pStream->write_string(",src_skill_id=") << p->dw_src_skill_id_;
		pStream->write_string(",item_type_id=") << p->dw_item_type_id_;
		pStream->write_string(",item_serial_id=") << p->n_serial_;

		pStream->write_string(",buff_id=") << p->dw_buff_id_;
		pStream->write_string(",cur_tick=") << p->n_persist_tick_;
		pStream->write_string(",level=") << p->n_level_;
		pStream->write_string(",cur_lap_times=") << p->n_cur_lap_times_;

		if(p->n_modifier_num_ > 0)
		{
			INT n_size = p->n_modifier_num_ * sizeof(DWORD);
			BYTE* p_buff = new BYTE[n_size];
			ZeroMemory(p_buff, sizeof(*p_buff));

			BYTE* p_Temp = p_buff;

			vector<DWORD>::iterator iter = p->list_skill_id.begin();
			while(iter != p->list_skill_id.end())
			{
				memcpy(p_Temp, &(*iter), sizeof(DWORD));
				p_Temp += sizeof(DWORD);
				iter++;
			}

			pStream->write_string(",effect_skill_id='");
			pStream->write_blob(p_buff, p->n_modifier_num_ * sizeof(DWORD), p_conn);
			pStream->write_string("'");

			SAFE_DELETE_ARRAY(p_buff);
		}

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);

		iter_buffer++;
	}

	return bRet;
}

// 插入仇人数据
BOOL CombinationDB::InsertEnemyList(LIST_ENEMY& list_enemy)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ENEMY::iterator iter_enemy = list_enemy.begin();
	while(iter_enemy != list_enemy.end())
	{
		if(!VALID_POINT(*iter_enemy))
		{
			iter_enemy++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("enemy");
		pStream->write_string("role_id=") << (*iter_enemy)->dwRoleID;
		pStream->write_string(",enemy_id=") << (*iter_enemy)->dwEnemyID;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_enemy++;
	}

	return bRet;
}

// 插入好友数据
BOOL CombinationDB::InsertFriendList(LIST_FRIEND& list_friend)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_FRIEND::iterator iter_friend = list_friend.begin();
	while(iter_friend != list_friend.end())
	{
		if(!VALID_POINT(*iter_friend))
		{
			iter_friend++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("friend");
		pStream->write_string("role_id=") << (*iter_friend)->dwRoleID;
		pStream->write_string(",friend_id=") << (*iter_friend)->dw_friend_id_;
		pStream->write_string(",group_id=") << (*iter_friend)->n_group_id_;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_friend++;
	}

	return bRet;
}

// 插入好友度数据
BOOL CombinationDB::InsertFriendShipList(LIST_FRIENDSHIP& list_friend_ship)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_FRIENDSHIP::iterator iter_friend_ship = list_friend_ship.begin();
	while(iter_friend_ship != list_friend_ship.end())
	{
		if(!VALID_POINT(*iter_friend_ship))
		{
			iter_friend_ship++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("friendship");
		pStream->write_string("role_id=") << (*iter_friend_ship)->dwRoleID;
		pStream->write_string(",friend_id=") << (*iter_friend_ship)->dw_friend_id_;
		pStream->write_string(",friend_val=") << (*iter_friend_ship)->n_frival_;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_friend_ship++;
	}

	return bRet;
}

// 插入帮会数据
BOOL CombinationDB::InsertGuildList(LIST_GUILD& list_guild)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUILD::iterator iter_guild = list_guild.begin();
	while(iter_guild != list_guild.end())
	{
		if(!VALID_POINT(*iter_guild))
		{
			iter_guild++;
			continue;
		}

		s_guild_load* p = (*iter_guild);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("guild");
		pStream->write_string("id=") << p->dwID;
		pStream->write_string(",name='").write_blob(p->sz_name, (_tcsclen(p->sz_name) + 1) * sizeof(TCHAR), p_conn);
		pStream->write_string("'");
		pStream->write_string(",creater_name_id=") << p->dwFounderNameID;
		pStream->write_string(",level=") << p->byLevel;
		pStream->write_string(",fund=") << p->nFund;
		pStream->write_string(",material=") << p->nMaterial;
		pStream->write_string(",reputation=") << p->nReputation;
		pStream->write_string(",peace=") << p->n16Peace;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwCreateTime);
		
		pStream->write_string(",create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		

		pStream->write_string(",special_state=") << p->dwSpecState;

		pStream->write_string(",group_purchase=") << p->nGroupPurchase;
		pStream->write_string(",leader_id=") << p->dwLeaderRoleID;
		pStream->write_string(",remain_spread_times=") << p->byAffairRemainTimes;

		pStream->write_string(",sign_data='").write_blob(p->dwSignRoleID, sizeof(p->dwSignRoleID), p_conn);
		pStream->write_string("'");

		pStream->write_string(",enemy_data='").write_blob(p->dwEnemyID, sizeof(p->dwEnemyID), p_conn);
		pStream->write_string("'");

		pStream->write_string(",pos_name='").write_blob(p->szPosName, sizeof(p->szPosName), p_conn);
		pStream->write_string("'");
		pStream->write_string(",pos_power='").write_blob(p->dwPosPower, sizeof(p->dwPosPower), p_conn);
		pStream->write_string("'");
		pStream->write_string(",family_name='").write_blob(p->n_family_name, sizeof(p->n_family_name), p_conn);
		pStream->write_string("'");
		pStream->write_string(",npc_name='").write_blob(p->n_name, sizeof(p->n_name), p_conn);
		pStream->write_string("'");

		pStream->write_string(",hold_city0=") << p->byHoldCity[0];
		pStream->write_string(",hold_city1=") << p->byHoldCity[1];
		pStream->write_string(",hold_city2=") << p->byHoldCity[2];
		pStream->write_string(",daily_cost=") << p->nDailyCost;
		pStream->write_string(",rank=") << p->n16Rank;
		pStream->write_string(",sign_num=") << p->bySignatoryNum;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwMianzhanTime);
		pStream->write_string(",uplevel_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",league_id=") << p->dwLeagueID;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwUnLeagueBeginTime);
		pStream->write_string(",unleague_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",prosperity=") << p->nProsperity;
		pStream->write_string(",dkp='").write_blob(p->n16DKP, sizeof(p->n16DKP), p_conn);
		pStream->write_string("'");
		pStream->write_string(",change_dkp=") << p->bSignUpAttact;
		pStream->write_string(",symbol_value=") << p->dwValue;
		pStream->write_string(",script_data='").write_blob(p->n32ScriptData, sizeof(p->n32ScriptData), p_conn);
		pStream->write_string("'");
		pStream->write_string(",text='").write_blob(p->szText, sizeof(p->szText), p_conn);
		pStream->write_string("'");

		pStream->write_string(",formal=") << p->bFormal;

		// 归还数据库连接
		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guild++;
	}

	return bRet;
}

// 插入帮会跑商列表
BOOL CombinationDB::InsertGuildCommerceList(LIST_GUILD_COMMERCE& list_guild_commerce)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUILD_COMMERCE::iterator iter_guild_commerce = list_guild_commerce.begin();
	while(iter_guild_commerce != list_guild_commerce.end())
	{
		if(!VALID_POINT(*iter_guild_commerce))
		{
			iter_guild_commerce++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("guild_commodity");
		pStream->write_string("role_id=") << (*iter_guild_commerce)->dw_role_id;
		pStream->write_string(",guild_id=") << (*iter_guild_commerce)->dwGuildID;
		pStream->write_string(",role_level=") << (*iter_guild_commerce)->n_level;
		pStream->write_string(",tael=") << (*iter_guild_commerce)->n_tael;

		pStream->write_string("goods='");
		pStream->write_blob((*iter_guild_commerce)->s_good_info, sizeof(tagCommerceGoodInfo)*MAX_COMMODITY_CAPACITY, p_conn);
		pStream->write_string("'");

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guild_commerce++;
	}

	return bRet;
}

// 插入帮会成员数据
BOOL CombinationDB::InsertGuildMemberList(LIST_GUILD_MEMBER& list_guild_member)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUILD_MEMBER::iterator iter_guild_member = list_guild_member.begin();
	while(iter_guild_member != list_guild_member.end())
	{
		if(!VALID_POINT(*iter_guild_member))
		{
			iter_guild_member++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		/*pStream->select_item("guild_member", 
			"role_id,"	"guild_id,"  "guild_pos,"  "total_contribution," "cur_contribution,"
			"exploit,"	"salary,"  "can_use_guild_ware," "ballot,"	"dkp," "join_time");*/
	
		pStream->insert_item("guild_member");
		pStream->write_string("role_id=") << (*iter_guild_member)->s_guild_member_.dw_role_id;
		pStream->write_string(",guild_id=") << (*iter_guild_member)->dw_guild_id_;
		pStream->write_string(",guild_pos=") << (*iter_guild_member)->s_guild_member_.eGuildPos;
		pStream->write_string(",total_contribution=") << (*iter_guild_member)->s_guild_member_.nTotalContribution;
		pStream->write_string(",cur_contribution=") << (*iter_guild_member)->s_guild_member_.nContribution;
		pStream->write_string(",exploit=") << (*iter_guild_member)->s_guild_member_.nExploit;
		pStream->write_string(",salary=") << (*iter_guild_member)->s_guild_member_.nSalary;
		pStream->write_string(",can_use_guild_ware=") << (*iter_guild_member)->s_guild_member_.bUseGuildWare;
		pStream->write_string(",ballot=") << (*iter_guild_member)->s_guild_member_.bBallot;
		pStream->write_string(",dkp=") << (*iter_guild_member)->s_guild_member_.nDKP;
		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), (*iter_guild_member)->s_guild_member_.dwJoinTime);

		pStream->write_string(",join_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",total_fund=") << (*iter_guild_member)->s_guild_member_.nTotalFund;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guild_member++;
	}

	return bRet;
}

// 插入帮会弹劾列表
BOOL CombinationDB::InsertGuildDelateList(LIST_GUILD_DELATE& list_guild_delate)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUILD_DELATE::iterator iter_guild_delate = list_guild_delate.begin();
	while(iter_guild_delate != list_guild_delate.end())
	{
		if(!VALID_POINT(*iter_guild_delate))
		{
			iter_guild_delate++;
			continue;
		}

		s_guild_delate_load* p_info = (*iter_guild_delate);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("guild_delate");
		pStream->write_string("guild_id=") << p_info->dwGuildID;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guild_delate++;
	}

	return bRet;
}

// 插入帮会建筑列表
BOOL CombinationDB::InsertGuildUpgradeList(LIST_GUILD_UPGRADE& list_guild_upgrade)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUILD_UPGRADE::iterator iter_guild_upgrade = list_guild_upgrade.begin();
	while(iter_guild_upgrade != list_guild_upgrade.end())
	{
		if(!VALID_POINT(*iter_guild_upgrade))
		{
			iter_guild_upgrade++;
			continue;
		}

		s_facilities_load* p_info = (*iter_guild_upgrade);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("guild_upgrade");
		pStream->write_string("level=") << p_info->by_level;
		pStream->write_string(",max_level=") << p_info->by_max_level;
		pStream->write_string(",progress=") << p_info->n16_progress;
		for (int n=1; n<=MAX_UPGRADE_NEED_ITEM_TYPE; n++)
		{
			pStream->write_string(",item_type_") << n;
			pStream->write_string("=") << p_info->dw_item_type_id[n-1];
			pStream->write_string(",item_neednum_") << n;
			pStream->write_string("=") << p_info->n_item_need[n-1];
		}

		pStream->write_string(",b_up_level=") << p_info->b_up_level;
		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p_info->dw_begin_up_time);
		pStream->write_string(",up_begin_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",b_dead=") << p_info->b_dead;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p_info->dw_dead_begin_time);
		pStream->write_string(",dead_begin_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",relive_time=") << p_info->dw_relive_time_limit;
		pStream->write_string(",use_type=") << p_info->byUseType;
		pStream->write_string(",use_num=") << p_info->byUseNum;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p_info->dwUseTime);
		pStream->write_string(",use_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",holiness_step=") << p_info->byStep;
		pStream->write_string(",guild_id=") << p_info->dw_guild_id;
		pStream->write_string(",type=") << p_info->e_type;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guild_upgrade++;
	}

	return bRet;
}

// 插入物品数据
BOOL CombinationDB::InsertItem(LIST_ITEM& list_item)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ITEM::iterator iter_item = list_item.begin();
	while(iter_item != list_item.end())
	{
		if(!VALID_POINT(*iter_item))
		{
			iter_item++;
			continue;
		}

		tagItem* p = (*iter_item);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("item");

		pStream->write_string("serial=") << p->n64_serial;
		pStream->write_string(",type_id=") << p->dw_data_id;

		pStream->write_string(",num=") << p->n16Num;
		pStream->write_string(",bind=") << p->byBind;
		pStream->write_string(",lock_state=") << p->bLock;
		pStream->write_string(",create_bind=") << p->bCreateBind;
		pStream->write_string(",use_times=") << p->nUseTimes;

		pStream->write_string(",create_mode=") << p->eCreateMode;
		pStream->write_string(",create_id=") << p->dwCreateID;

		pStream->write_string(",creator_id=") << p->dwCreatorID;
		pStream->write_string(",name_id=") << p->dwNameID;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwCreateTime);
		pStream->write_string(",create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dw1stGainTime);
		pStream->write_string(",first_gain_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwBindTime);
		pStream->write_string(",bind_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		pStream->write_string(",owner_id=") << p->dwOwnerID;
		pStream->write_string(",account_id=") << p->dw_account_id;
		pStream->write_string(",container_type_id=") << p->eConType;
		pStream->write_string(",suffix=") << p->n16Index;
		pStream->write_string(",script_data1=") << p->dw_script_data[0];
		pStream->write_string(",script_data2=") << p->dw_script_data[1];


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_item++;
	}

	return bRet;
}

// 插入装备数据
BOOL CombinationDB::InsertEquip(LIST_ITEM& list_item)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ITEM::iterator iter_item = list_item.begin();
	while(iter_item != list_item.end())
	{
		if(!VALID_POINT(*iter_item))
		{
			iter_item++;
			continue;
		}

		if(!MIsEquipment((*iter_item)->dw_data_id))
		{
			iter_item++;
			continue;
		}

		tagEquip* p = (tagEquip*)(*iter_item);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("equip");

		pStream->write_string("serial=") << p->n64_serial;
		pStream->write_string(",");

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->write_string("quality=") << p->equipSpec.byQuality;
		//pStream->write_string(",min_use_level=") << p->equipSpec.byMinUseLevel;
		//pStream->write_string(",max_use_level=") << p->equipSpec.byMaxUseLevel;
		//pStream->write_string(",att_a_lim_mod=") << p->equipSpec.n16AttALimMod;
		//pStream->write_string(",att_a_lim_mod_pct=") << p->equipSpec.n16AttALimModPct;

		//pStream->write_string(",min_dmg=") << p->equipSpec.n16MinDmg;
		//pStream->write_string(",max_dmg=") << p->equipSpec.n16MaxDmg;
		//pStream->write_string(",armor=") << p->equipSpec.n16Armor;
		//pStream->write_string(",potval=") << p->equipSpec.nPotVal;
		//pStream->write_string(",potval_used=") << p->equipSpec.nPotValUsed;

		//pStream->write_string(",posy_times=") << p->equipSpec.byPosyTimes;
		//pStream->write_string(",engrave_times=") << p->equipSpec.byEngraveTimes;
		pStream->write_string(",hole_num=") << p->equipSpec.byHoleNum;
		//pStream->write_string(",brand_level=") << p->equipSpec.byTriggerCount;
		//pStream->write_string(",x_ful_level=") << p->equipSpec.byLongfuLevel;

		//pStream->write_string(",can_cut=") << p->equipSpec.bCanCut;
		pStream->write_string(",special_att=") << p->equipSpec.byLuck;
		//pStream->write_string(",flare_val=") << p->equipSpec.byFlareVal;
		//pStream->write_string(",quality_mod_pct=") << p->equipSpec.n16QltyModPct;
		//pStream->write_string(",quality_mod_pct_Ex=") << p->equipSpec.n16QltyModPctEx;
		//pStream->write_string(",pot_val_mod_pct=") <<p->equipSpec.n16PotValModPct;

		// 时装属性
		//pStream->write_string(",appearance=") << p->equipSpec.n16Appearance;
		//pStream->write_string(",rein=") << p->equipSpec.byRein;
		//pStream->write_string(",savvy=") << p->equipSpec.bySavvy;
		//pStream->write_string(",fortune=") << p->equipSpec.byFortune;
		//pStream->write_string(",color_id=") << p->equipSpec.n8ColorID;

		pStream->write_string(",consolidate_level=") << p->equipSpec.byConsolidateLevel;
		//pStream->write_string(",exp=") << p->equipSpec.nCurLevelExp;
		//pStream->write_string(",level=") << p->equipSpec.nLevel;
		//pStream->write_string(",talent_point=") << p->equipSpec.byTalentPoint;
		//pStream->write_string(",max_talent_point=") << p->equipSpec.byMaxTalentPoint;
		pStream->write_string(",rating=") << p->equipSpec.nRating;

		//pStream->write_string(",role_att_effect='").write_blob(p->equipSpec.nRoleAttEffect, sizeof(p->equipSpec.nRoleAttEffect), p_conn);
		//pStream->write_string("',posy_effect='").write_blob(p->equipSpec.PosyEffect, sizeof(p->equipSpec.PosyEffect), p_conn);
		//pStream->write_string("',engrave_att='").write_blob(p->equipSpec.nEngraveAtt, sizeof(p->equipSpec.nEngraveAtt), p_conn);
		pStream->write_string(",hole_gem_id='").write_blob(p->equipSpec.dwHoleGemID, sizeof(p->equipSpec.dwHoleGemID), p_conn);
		//pStream->write_string("',derate_val='").write_blob(p->equipSpec.nBrandAtt, sizeof(p->equipSpec.nBrandAtt), p_conn);
		//pStream->write_string("',hole_gem_ness='").write_blob(p->equipSpec.byHoleGemNess, sizeof(p->equipSpec.byHoleGemNess), p_conn);
		pStream->write_string("',equip_add_att='").write_blob(p->equipSpec.EquipAttitionalAtt, sizeof(p->equipSpec.EquipAttitionalAtt), p_conn);
		//pStream->write_string("',skill_list='").write_blob(p->equipSpec.dwSkillList, sizeof(p->equipSpec.dwSkillList), p_conn);
		pStream->write_string("',equip_rel_att='").write_blob(p->equipSpec.EquipAttitional, sizeof(p->equipSpec.EquipAttitional), p_conn);
		pStream->write_string("'");

		//pStream->write_string(",consolidate_level_star=") << p->equipSpec.byConsolidateLevelStar;
		//pStream->write_string(",add_talent_point=") << p->equipSpec.byAddTalentPoint;

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_item++;
	}

	return bRet;
}

// 插入物品cd数据
BOOL CombinationDB::InsertItemCD(LIST_ITEM_CD& list_item_cd)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ITEM_CD::iterator iter_item_cd = list_item_cd.begin();
	while(iter_item_cd != list_item_cd.end())
	{
		if(!VALID_POINT(*iter_item_cd))
		{
			iter_item_cd++;
			continue;
		}


		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("item_cd_time");
		pStream->write_string("role_id=") << (*iter_item_cd)->dw_role_id;
		if((*iter_item_cd)->n_num > 0)
		{
			tagCDTime st_CDTime[100];
			ZeroMemory(&st_CDTime, sizeof(st_CDTime));

			INT nIndex = 0;

			vector<tagCDTime>::iterator iter = (*iter_item_cd)->list_cd_time.begin();
			while(iter != (*iter_item_cd)->list_cd_time.end())
			{
				memcpy(&st_CDTime[nIndex], &(*iter), sizeof(tagCDTime));
				nIndex++;
				iter++;
			}

			pStream->write_string(",cd_time='");
			pStream->write_blob(st_CDTime, sizeof(tagCDTime) * (*iter_item_cd)->n_num, p_conn);
			pStream->write_string("'");

		}

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_item_cd++;
	}

	return bRet;
}

// 插入邮件数据
BOOL CombinationDB::InsertMail(LIST_MAIL& list_mail)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_MAIL::iterator iter_mail = list_mail.begin();
	while(iter_mail != list_mail.end())
	{
		if(!VALID_POINT(*iter_mail))
		{
			iter_mail++;
			continue;
		}

		tag_load_mail* p = (tag_load_mail*)(*iter_mail);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("mail");

		pStream->write_string("mail_id=") << p->s_mail_base_.dwID;
		pStream->write_string(",mail_name='").write_blob(p->str_name, (_tcsclen(p->str_name)+1) * sizeof(TCHAR), p_conn);
		pStream->write_string("'");
		pStream->write_string(",mail_content='").write_blob(p->sz_content_, (_tcsclen(p->sz_content_)+1) * sizeof(TCHAR), p_conn);
		pStream->write_string("'");
		pStream->write_string(",send_role_id=") << p->s_mail_base_.dwSendRoleID;
		pStream->write_string(",recv_role_id=") << p->s_mail_base_.dwRecvRoleID;
		pStream->write_string(",is_at_once=") << p->s_mail_base_.bAtOnce;
		pStream->write_string(",is_send=") << p->s_mail_base_.bSend;
		pStream->write_string(",is_read=") << p->s_mail_base_.bReed;
		pStream->write_string(",is_withdrawal=") << p->s_mail_base_.bWithdrawal;
		pStream->write_string(",solve=") << p->s_mail_base_.dwSolve;
		pStream->write_string(",give_money=") << p->s_mail_base_.dwGiveMoney;
		pStream->write_string(",moneytype=") << p->s_mail_base_.byType;
		pStream->write_string(",item_serial='").write_blob(p->s_mail_base_.n64ItemSerial, sizeof(p->s_mail_base_.n64ItemSerial), p_conn);
		pStream->write_string("'");
		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->s_mail_base_.dwSendTime);
		pStream->write_string(",send_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->s_mail_base_.dwRecvTime);
		pStream->write_string(",recv_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",yuanbao_type=") << p->s_mail_base_.n_yuanbao_type;

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_mail++;
	}

	return bRet;
}

// 插入地图限制数据
BOOL CombinationDB::InsertMapLimit(LIST_MAP_LIMIT& list_map_limit)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_MAP_LIMIT::iterator iter_map_limit = list_map_limit.begin();
	while(iter_map_limit != list_map_limit.end())
	{
		if(!VALID_POINT(*iter_map_limit))
		{
			iter_map_limit++;
			continue;
		}

		tag_map_limit* p = (tag_map_limit*)(*iter_map_limit);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("map_limit");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",map_id=") << p->dw_map_id_;
		pStream->write_string(",enter_num=") << p->dw_enter_num_;
		pStream->write_string(",type=") << p->e_enter_limit_;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_map_limit++;
	}

	return bRet;
}

// 插入地图限制数据
BOOL CombinationDB::InsertInstProcess(LIST_INTS_PROCESS& list_inst_process)
{
	BOOL bRet = TRUE;
	INT nNum = 0;


	LIST_INTS_PROCESS::iterator iter_map_limit = list_inst_process.begin();
	while(iter_map_limit != list_inst_process.end())
	{
		if(!VALID_POINT(*iter_map_limit))
		{
			iter_map_limit++;
			continue;
		}

		tag_ints_process* p = (tag_ints_process*)(*iter_map_limit);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();
		pStream->clear();

		pStream->insert_item("inst_process");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",map_id=") << p->dw_map_id;
		pStream->write_string(",mode=") << p->n_mode;
		pStream->write_string(",type=") << p->n_type;
		pStream->write_string(",door_process='").write_blob(p->st_door_state, sizeof(p->st_door_state), p_conn);
		pStream->write_string("',creature_process='").write_blob(p->dw_creature_id, sizeof(p->dw_creature_id), p_conn);
		pStream->write_string("'");

		m_pdb->return_use_connect(p_conn);

		m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);
		//m_pdb->return_use_connect(p_conn);
		iter_map_limit++;
	}

	return bRet;
}

//插入角色奖励信息
BOOL CombinationDB::InsertRoleRewardData(LIST_ROLE_REWARD_DATA& list_reward_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ROLE_REWARD_DATA::iterator iter_reward = list_reward_data.begin();
	while(iter_reward != list_reward_data.end())
	{
		if(!VALID_POINT(*iter_reward))
		{
			iter_reward++;
			continue;
		}

		tag_reward_data* p = (tag_reward_data*)(*iter_reward);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();
		pStream->clear();

		pStream->insert_item("reward");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",reward_data='").write_blob(p->st_role_reward_data, sizeof(p->st_role_reward_data), p_conn);
		pStream->write_string("'");

		m_pdb->return_use_connect(p_conn);

		m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);
		
		iter_reward++;
	}

	return bRet;
}
//插入玩家坐骑信息
BOOL CombinationDB::InsertRoleMountData(LIST_MOUNT_DATA& list_mount_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_MOUNT_DATA::iterator iter_mount = list_mount_data.begin();
	while(iter_mount != list_mount_data.end())
	{
		if(!VALID_POINT(*iter_mount))
		{
			iter_mount++;
			continue;
		}

		tag_mount_data* p = (tag_mount_data*)(*iter_mount);

		odbc::sql_language_disposal* p_stream = m_pdb->get_io();
		if(!p_stream)
		{
			return FALSE;
		}

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();
		p_stream->clear();

		p_stream->insert_item("mounts");
		p_stream->write_string("role_id=") << p->dw_role_id;
		p_stream->write_string(",step=") << (int)p->nStep;
		p_stream->write_string(",grade=") << (int)p->nGrade;
		p_stream->write_string(",exp=") << (int)p->nExp;
		
		m_pdb->return_use_connect(p_conn);

		m_pdb->sql_execute(p_stream);

		m_pdb->return_io(p_stream);

		iter_mount++;
	}

	return bRet;
}
//插入玩家名帖信息
BOOL CombinationDB::InsertRoleVCradData(LIST_ROLE_VCARD_DATA& list_role_vcrad)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ROLE_VCARD_DATA::iterator iter_vcrad = list_role_vcrad.begin();
	while(iter_vcrad != list_role_vcrad.end())
	{
		if(!VALID_POINT(*iter_vcrad))
		{
			iter_vcrad++;
			continue;
		}

		tagVCardData* p = (tagVCardData*)(*iter_vcrad);

		odbc::sql_language_disposal* p_stream = m_pdb->get_io();
		if(!p_stream)
		{
			return FALSE;
		}

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();
		p_stream->clear();

		p_stream->insert_item("visiting_card");
		p_stream->write_string("role_id=") << p->dw_role_id;
		p_stream->write_string(",level=") << (int)p->dwLevel;
		p_stream->write_string(",job=") << (int)p->dwJob;
		p_stream->write_string(",mate_role_id=") << (int)p->dwMateRoleID;
		p_stream->write_string(",guild_id=") << (int)p->dwFactionID;
		p_stream->write_string(",position=") << (int)p->dwPosition;

		//p_stream->write_string(",visibility=") << p->customVCardData.bVisibility;
		//p_stream->write_string(",sex=") << p->customVCardData.bySex;
		p_stream->write_string(",constellation=") << p->customVCardData.byConstellation;
		//p_stream->write_string(",chinesezodiac=") << p->customVCardData.byChineseZodiac;
		//p_stream->write_string(",area=") << p->customVCardData.byArea;
		//p_stream->write_string(",province=") << p->customVCardData.byProvince;
		p_stream->write_string(",city='").write_string(p->customVCardData.chCity, p_conn).write_string("'");
		//p_stream->write_string(",head_url='").write_string(reinterpret_cast<TCHAR *>(p->customVCardData.byData), p_conn).write_string("'");
		p_stream->write_string(",signature='").write_string(reinterpret_cast<TCHAR *>(&(p->customVCardData.byData)), p_conn).write_string("'");

		m_pdb->return_use_connect(p_conn);

		m_pdb->sql_execute(p_stream);

		m_pdb->return_io(p_stream);

		iter_vcrad++;
	}

	return bRet;
}
// 插入师徒数据
BOOL CombinationDB::InsertMaster(LIST_MASTER& list_master)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_MASTER::iterator iter_master = list_master.begin();
	while(iter_master != list_master.end())
	{
		if(!VALID_POINT(*iter_master))
		{
			iter_master++;
			continue;
		}

		tag_master* p = (tag_master*)(*iter_master);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		/*pStream->select_item("master_prentice",
			"master," "graduates," "master_moral," "show_in_panel," "prentices" );*/

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("master_prentice");
		pStream->write_string("master=") << p->dw_master;
		pStream->write_string(",graduates=") << p->dw_graduates;
		pStream->write_string(",master_moral=") << p->dw_master_moral;
		pStream->write_string(",show_in_panel=") << p->b_show_in_panel;
		
		if(p->by_number > 0)
		{
			INT n_size = p->by_number * sizeof(DWORD);
			BYTE* p_buff = new BYTE[n_size];
			ZeroMemory(p_buff, sizeof(*p_buff));

			BYTE* p_temp = p_buff;

			vector<DWORD>::iterator iter = p->list_role.begin();
			while(iter != p->list_role.end())
			{
				memcpy(p_temp, &(*iter), sizeof(DWORD));
				p_temp += sizeof(DWORD);
				iter++;
			}
			pStream->write_string(",prentices='");
			pStream->write_blob(p_buff, p->by_number * sizeof(DWORD), p_conn);
			pStream->write_string("'");

			SAFE_DELETE_ARRAY(p_buff);
		}

		m_pdb->return_use_connect(p_conn);
		
		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_master++;
	}

	return bRet;
}

// 插入拍卖数据
BOOL CombinationDB::InsertPaiMai(LIST_PAIMAI& list_paimai)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_PAIMAI::iterator iter_paimai = list_paimai.begin();
	while(iter_paimai != list_paimai.end())
	{
		if(!VALID_POINT(*iter_paimai))
		{
			iter_paimai++;
			continue;
		}

		tag_paimai* p = (tag_paimai*)(*iter_paimai);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("paimai");

		pStream->write_string("id=") << p->dw_paimai_id;
		pStream->write_string(",bidup=") << p->dw_bidup;
		pStream->write_string(",maxbidup=0");
		pStream->write_string(",bidup_id=") << p->dw_bidup_id;
		pStream->write_string(",chaw=") << p->dw_chaw;
		pStream->write_string(",sell_id=") << p->dw_sell_id;
		pStream->write_string(",timetype=") << p->by_time_type;
		pStream->write_string(",show_name=") << p->b_show_name;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dw_beigin_time);
		
		pStream->write_string(",begintime='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_paimai++;
	}

	return bRet;
}

// 插入宠物数据
BOOL CombinationDB::InsertPet(LIST_PET& list_pet)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_PET::iterator iter_pet = list_pet.begin();
	while(iter_pet != list_pet.end())
	{
		if(!VALID_POINT(*iter_pet))
		{
			iter_pet++;
			continue;
		}

		s_db_pet_att* p = (s_db_pet_att*)(*iter_pet);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("pet_data");
		pStream->write_string("pet_name='").write_string(p->sz_name_, p_conn).write_string("'");
		pStream->write_string(",master_id=") << p->dw_master_id_;
		pStream->write_string(",type_id=") << p->dw_proto_id_;
		pStream->write_string(",quality=") << p->n_quality_;
		pStream->write_string(",aptitude=") << p->n_aptitude_;
		pStream->write_string(",potential=") << p->n_potential_;
		pStream->write_string(",cur_spirit=") << p->n_spirit_;
		pStream->write_string(",wuxing_energy=") << p->n_wuxing_energy_;
		pStream->write_string(",talent_count=") << p->n_talent_count_;
		pStream->write_string(",pet_state=") << p->by_pet_state_;
		pStream->write_string(",cur_exp=") << p->n_exp_cur_;
		pStream->write_string(",step=") << p->n_step_;
		pStream->write_string(",grade=") << p->n_grade_;
		pStream->write_string(",pet_lock=") << p->b_locked_;
		pStream->write_string(",rename_count=") << p->n_rename_count_;
		pStream->write_string(",happy_value=") << p->n_happy_value_;

		pStream->write_string(",color=") << p->n_color;
		pStream->write_string(",strength=") << p->n_strength;
		pStream->write_string(",agility=") << p->n_agility;
		pStream->write_string(",innerforce=") << p->n_innerForce;
		pStream->write_string(",attpoint=") << p->n_att_point;
		pStream->write_string(",time_type=") << p->dw_time_type;
		pStream->write_string(",mode_type=") << p->dw_mode_type;
		pStream->write_string(",xiulian_time=") << p->dw_xiulian_time;

		pStream->write_string(",pet_id=") << p->dw_pet_id_;
		
		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_pet++;
	}

	return bRet;
}

// 插入宠物技能数据
BOOL CombinationDB::InsertPetSkill(LIST_PET_SKILL& list_pet_skill)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_PET_SKILL::iterator iter_pet_skill = list_pet_skill.begin();
	while(iter_pet_skill != list_pet_skill.end())
	{
		if(!VALID_POINT(*iter_pet_skill))
		{
			iter_pet_skill++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("pet_skill");
		pStream->write_string("pet_id=") << (*iter_pet_skill)->dw_pet_id_;
		pStream->write_string(",pet_skill_type_id=") << (*iter_pet_skill)->dw_data_id;
		pStream->write_string(",para1=") << (DWORD)(*iter_pet_skill)->n_para1_;
		pStream->write_string(",para2=") << (DWORD)(*iter_pet_skill)->n_para2_;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_pet_skill++;
	}

	return bRet;
}

// 插入宠物sns数据
BOOL CombinationDB::InsertPetSns(LIST_PET_SNS& list_pet_sns)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_PET_SNS::iterator iter_pet_sns = list_pet_sns.begin();
	while(iter_pet_sns != list_pet_sns.end())
	{
		if(!VALID_POINT(*iter_pet_sns))
		{
			iter_pet_sns++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();
		pStream->insert_item("pet_sns");
		pStream->write_string("pet_id=") << (*iter_pet_sns)->dw_pet_id;
		pStream->write_string(",master_id=") << (*iter_pet_sns)->dw_master_id;
		pStream->write_string(",friend_id=") << (*iter_pet_sns)->dw_friend_id;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), (*iter_pet_sns)->dw_begin_time);

		pStream->write_string(",begintime='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_pet_sns++;
	}

	return bRet;
}

// 插入任务数据
BOOL CombinationDB::InsertQuest(LIST_QUEST& list_quest)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_QUEST::iterator iter_quest = list_quest.begin();
	while(iter_quest != list_quest.end())
	{
		if(!VALID_POINT(*iter_quest))
		{
			iter_quest++;
			continue;
		}

		tag_quest* p = (tag_quest*)(*iter_quest);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("quest");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",quest_id=") << p->u16QuestID;
		pStream->write_string(",quest_flag=") << p->dwQuestFlag;
		pStream->write_string(",start_time=") << p->dwAcceptTime;

		for(int i=0; i<QUEST_CREATURES_COUNT; ++i)
		{
			pStream->write_string(",monster") << i;
			pStream->write_string("_num=") << (INT16)p->n16MonsterNum[i];
		}

		pStream->write_string(",script_data='");
		pStream->write_blob(p->Data.dwData, sizeof(DWORD)*ESD_Quest, p_conn);
		pStream->write_string("'");

		if(p->DynamicTarget.eTargetType != EQTT_NULL)
		{
			//任务动态目标
			pStream->write_string(",dynamic_target='");
			pStream->write_blob(&p->DynamicTarget, sizeof(tagQuestDynamicTarget), p_conn);
			pStream->write_string("'");
		}
		if( p->DynamicReward.rew_item[0] || p->DynamicReward.rew_choice_item[0] )
		{
			//任务动态奖励
			pStream->write_string(",dynamic_reward='");
			pStream->write_blob(&p->DynamicReward, sizeof(tagQuestDynamicReward), p_conn );
			pStream->write_string("'");
		}
		if( p->ScriptQuestVar.Number )
		{//脚本完成条件
			pStream->write_string(",scriptquest_var='");
			pStream->write_blob(&p->ScriptQuestVar, sizeof(tagScriptQuestVar), p_conn );
			pStream->write_string("'");
		}
		pStream->write_string(",new_flag=") << p->u16Quest_NewFlag;//add

		m_pdb->return_use_connect(p_conn);
		
		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_quest++;
	}

	return bRet;
}

// 插入任务完成数据
BOOL CombinationDB::InsertQuestDone(LIST_QUEST_DONE& list_quest_done)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_QUEST_DONE::iterator iter_quest_done = list_quest_done.begin();
	while(iter_quest_done != list_quest_done.end())
	{
		if(!VALID_POINT(*iter_quest_done))
		{
			iter_quest_done++;
			continue;
		}

		tag_quest_done* p = (tag_quest_done*)(*iter_quest_done);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("quest_done");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",quest_id=") << p->u16QuestID;
		pStream->write_string(",start_time=") << p->dwStartTime;
		pStream->write_string(",times=") << p->nTimes;
		pStream->write_string(",new_flag=") << p->u16QuestFalg;//add
		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_quest_done++;
	}

	return bRet;
}

// 插入人物数据
BOOL CombinationDB::InsertRoleData(LIST_ROLE_DATA& list_role_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ROLE_DATA::iterator iter_role_data = list_role_data.begin();
	while(iter_role_data != list_role_data.end())
	{
		if(!VALID_POINT(*iter_role_data))
		{
			iter_role_data++;
			continue;
		}
		
		tag_role_data* p = (tag_role_data*)(*iter_role_data);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("role_data");
		pStream->write_string("avatar_equip='").write_blob(&p->role_data_save_.avatar_equip_, SIZE_AVATAR_EQUIP, p_conn);
		pStream->write_string("',display_set=")<< (BYTE)p->role_data_save_.display_set_;
		pStream->write_string(",map_id=") << p->role_data_save_.dw_map_id_;
		pStream->write_string(",x=") << p->role_data_save_.f_coordinate_[0];// 坐标
		pStream->write_string(",y=") << p->role_data_save_.f_coordinate_[1];
		pStream->write_string(",z=") << p->role_data_save_.f_coordinate_[2];
		pStream->write_string(",face_x=") << p->role_data_save_.f_face_[0];// 朝向
		pStream->write_string(",face_y=") << p->role_data_save_.f_face_[1];
		pStream->write_string(",face_z=") << p->role_data_save_.f_face_[2];

		pStream->write_string(",reborn_map_id=") << p->role_data_save_.dw_reborn_map_id_;

		pStream->write_string(",class=") << (int)p->role_data_save_.e_class_;
		pStream->write_string(",classex=") << p->role_data_save_.e_class_ex_;
		pStream->write_string(",level=") << p->role_data_save_.n_level_;
		pStream->write_string(",exp_cur_level=") << p->role_data_save_.n_cur_exp_;

		pStream->write_string(",hp=") << p->role_data_save_.n_hp_;
		pStream->write_string(",mp=") << p->role_data_save_.n_mp_;
		pStream->write_string(",rage=") << p->role_data_save_.n_rage_;
		pStream->write_string(",endurance=") << p->role_data_save_.n_endurance_;
		pStream->write_string(",vitality=") << p->role_data_save_.n_brotherhood_;
		pStream->write_string(",injury=") << p->role_data_save_.n_injury_;
		pStream->write_string(",knowledge=") << p->role_data_save_.n_knowledge_;
		pStream->write_string(",morale=") <<p->role_data_save_.n_morale_;
		pStream->write_string(",morality=") << p->role_data_save_.n_morality_;
		pStream->write_string(",culture=") << p->role_data_save_.n_luck_;
		pStream->write_string(",credit=") << p->role_data_save_.n_credit_;
		pStream->write_string(",identity=") << p->role_data_save_.n_identity_;
		pStream->write_string(",vip_point=") << p->role_data_save_.n_vip_point_;

		pStream->write_string(",att_avail=") << p->role_data_save_.n_att_point_;
		pStream->write_string(",talent_avail=") << p->role_data_save_.n_talent_point_;

		pStream->write_string(",physique_added=") << p->role_data_save_.n_att_point_add_[ERA_Physique];
		pStream->write_string(",strength_added=") << p->role_data_save_.n_att_point_add_[ERA_Strength];
		pStream->write_string(",pneuma_added=") << p->role_data_save_.n_att_point_add_[ERA_Pneuma];
		pStream->write_string(",innerforce_added=") << p->role_data_save_.n_att_point_add_[ERA_InnerForce];
		pStream->write_string(",technique_added=") << p->role_data_save_.n_att_point_add_[ERA_Technique];
		pStream->write_string(",agility_added=") << p->role_data_save_.n_att_point_add_[ERA_Agility];

		pStream->write_string(",talent_type1=") << p->role_data_save_.talent_[0].eType;
		pStream->write_string(",talent_type2=") << p->role_data_save_.talent_[1].eType;
		pStream->write_string(",talent_type3=") << p->role_data_save_.talent_[2].eType;
		pStream->write_string(",talent_type4=") << p->role_data_save_.talent_[3].eType;
		pStream->write_string(",talent_val1=") << p->role_data_save_.talent_[0].nPoint;
		pStream->write_string(",talent_val2=") << p->role_data_save_.talent_[1].nPoint;
		pStream->write_string(",talent_val3=") << p->role_data_save_.talent_[2].nPoint;
		pStream->write_string(",talent_val4=") << p->role_data_save_.talent_[3].nPoint;

		pStream->write_string(",safe_guard_flag=") << p->role_data_save_.b_safe_guard_;
		pStream->write_string(",pk_value=") << p->role_data_save_.n_pk_value_;

		pStream->write_string(",bag_size=") << p->role_data_save_.n16_bag_size_;		// 背包
		pStream->write_string(",bag_gold=") << p->role_data_save_.n_bag_gold_;
		pStream->write_string(",bag_silver=") << p->role_data_save_.n_bag_silver_;
		pStream->write_string(",bag_copper=")	<< p->role_data_save_.n_bag_copper_;
		pStream->write_string(",bag_bind_gold=") << p->role_data_save_.n_bag_bind_gold_;
		pStream->write_string(",bag_bind_silver=") << p->role_data_save_.n_bag_bind_silver_;
		pStream->write_string(",bag_bind_copper=") << p->role_data_save_.n_bag_bind_copper_;
		pStream->write_string(",bag_yuanbao=") << p->role_data_save_.n_bag_tuanbao_;
		pStream->write_string(",exchange_volume=") << p->role_data_save_.n_ex_volume_;

		pStream->write_string(",pet_packet_num=") << p->role_data_save_.n16_pet_packet_size_;

		pStream->write_string(",total_tax=") << p->role_data_save_.n_total_tax_;	// 缴税总额
		pStream->write_string(",remote_open_set=") << (DWORD)p->role_data_save_.s_remote_open_set_;
		pStream->write_string(",cur_title_id=") << p->role_data_save_.u16_active_title_id[0];
		pStream->write_string(",cur_title_id2=") << p->role_data_save_.u16_active_title_id[1];
		pStream->write_string(",cur_title_id3=") << p->role_data_save_.u16_active_title_id[2];
		pStream->write_string(",guild_id=") << p->role_data_save_.dw_guild_id;
		pStream->write_string(",team_id=") << p->role_data_save_.dw_team_id_;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.login_time_);
		
		pStream->write_string(",login_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.logout_time_);
		pStream->write_string(",logout_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.close_safe_guard_time_);
		pStream->write_string(",close_safe_guard_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.dw_time_get_mall_free_);
		pStream->write_string(",get_mall_free_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
	

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.leave_guild_time_);
		
		pStream->write_string(",leave_guild_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		

		pStream->write_string(",own_instance_id=") << p->role_data_save_.dw_own_instance_id_;
		pStream->write_string(",own_instance_map_id=") << p->role_data_save_.dw_own_instance_map_id_;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.dw_instance_create_time_);
		
		pStream->write_string(",instance_create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		

		pStream->write_string(",online_time=") << p->role_data_save_.n_online_time_;
		pStream->write_string(",cur_online_time=") << p->role_data_save_.n_cur_online_time_;

		pStream->write_string(",script_data='");
		pStream->write_blob(p->role_data_save_.data_.dwData, sizeof(DWORD)*ESD_Role, p_conn);
		pStream->write_string("'");

		pStream->write_string(",stall_level=") << p->role_data_save_.by_stall_level_;
		pStream->write_string(",stall_daily_exp=") << p->role_data_save_.n_stall_daily_exp_;
		pStream->write_string(",stall_cur_exp=") << p->role_data_save_.n_stall_cur_exp_;
		pStream->write_string(",stall_last_time=") << p->role_data_save_.dw_last_stall_time_;

		pStream->write_string(",send_mail_num=") << p->role_data_save_.n_send_mail_num_;
		pStream->write_string(",master_id=") << p->role_data_save_.dw_master_id_;
		pStream->write_string(",masterprentice_forbid_time=") << p->role_data_save_.dw_master_prentice_forbid_time_;

		pStream->write_string(",map_limit_num=") << p->role_data_save_.n_map_limit_num_;

		pStream->write_string(",hang_num=") << p->role_data_save_.n16_hang_num_;
		pStream->write_string(",is_exp=") << p->role_data_save_.b_exp_;
		pStream->write_string(",is_brotherhood=") << p->role_data_save_.b_brotherhood_;
		pStream->write_string(",leave_exp=") << p->role_data_save_.n_leave_exp_;
		pStream->write_string(",leave_brotherhood=") << p->role_data_save_.n_leave_brotherhood_;
		pStream->write_string(",vigour=") << p->role_data_save_.n_vigour_;
		pStream->write_string(",role_help='");
		pStream->write_blob(p->role_data_save_.by_role_help_, sizeof(p->role_data_save_.by_role_help_), p_conn);
		pStream->write_string("'");
		pStream->write_string(",role_talk='");
		pStream->write_blob(p->role_data_save_.by_talk_data_, sizeof(p->role_data_save_.by_talk_data_), p_conn);
		pStream->write_string("'");
		pStream->write_string(",key_info='");
		pStream->write_blob(&p->role_data_save_.st_key_info_, sizeof(p->role_data_save_.st_key_info_), p_conn);
		pStream->write_string("'");
		pStream->write_string(",total_mastermoral=") << p->role_data_save_.n_total_mater_moral_;
		pStream->write_string(",kill_num=") << p->role_data_save_.n_kill_num_;
		pStream->write_string(",gift_step=") << p->role_data_save_.n_gift_step_;
		pStream->write_string(",gift_id=") << p->role_data_save_.dw_gift_id_;
		pStream->write_string(",gift_leaving_time=") << p->role_data_save_.dw_gift_leave_time_;
		pStream->write_string(",gift_get=") << p->role_data_save_.b_gift_get_;
		pStream->write_string(",gift_group_id=") << p->role_data_save_.n_gift_id_;

		pStream->write_string(",role_camp=") << p->role_data_save_.e_role_camp;
		pStream->write_string(",paimailimit=") << p->role_data_save_.n_paimai_limit;
		pStream->write_string(",banklimit=") << p->role_data_save_.n_bank_limit;

		pStream->write_string(",today_online_tick=") << p->role_data_save_.dw_today_online_tick_;
		pStream->write_string(",history_vigour_cost=") << p->role_data_save_.dw_history_vigour_cost_;

		pStream->write_string(",exbagstep=") << p->role_data_save_.n16_exbag_step;
		pStream->write_string(",exwarestep=") << p->role_data_save_.n16_exware_step;

		pStream->write_string(",signature_name='").write_string(p->role_data_save_.sz_signature_name);
		pStream->write_string("'");

		pStream->write_string(",ware_size=") << p->role_data_save_.n16WareSize;
		pStream->write_string(",ware_gold=") << p->role_data_save_.nWareGold;
		pStream->write_string(",ware_silver=") << p->role_data_save_.nWareSilver;
		pStream->write_string(",ware_copper=") << p->role_data_save_.nWareCopper;

		pStream->write_string(",circle_quest='");
		pStream->write_blob(&p->role_data_save_.circle_quest_man_, sizeof(p->role_data_save_.circle_quest_man_), p_conn);
		pStream->write_string("'");

		pStream->write_string(",yuanbao_exchange_num=") << p->role_data_save_.n_yuanbao_exchange_num;
		pStream->write_string(",achievemetn_point=") << p->role_data_save_.n_achievement_point;

		pStream->write_string(",forbid_talk_start=") << p->role_data_save_.dw_forbid_talk_start_;
		pStream->write_string(",forbid_talk_end=") << p->role_data_save_.dw_forbid_talk_end_;
		pStream->write_string(",graduate_num=") << p->role_data_save_.n_graduates_num;
		pStream->write_string(",destory_equip_count=") << p->role_data_save_.dw_destory_equip_count;
		pStream->write_string(",cur_1v1_score=") << p->role_data_save_.st_1v1_score.n_cur_score;
		pStream->write_string(",day_1v1_score=") << p->role_data_save_.st_1v1_score.n_day_max_score;
		pStream->write_string(",day_1v1_num=") << p->role_data_save_.st_1v1_score.n_day_scroe_num;
		pStream->write_string(",score_1v1_award=") << p->role_data_save_.st_1v1_score.n16_score_award;

		pStream->write_string(",role_id=") << p->dw_role_id;
		pStream->write_string(",account_id=") << p->dw_account_id;
		pStream->write_string(",remove_flag=") << p->b_remove;

		pStream->write_string(",exploits=") << p->role_data_save_.n32_exploits;
		pStream->write_string(",circle_quest_refresh=") << p->role_data_save_.n_circle_quest_fresh;
		pStream->write_string(",exploitslimit=") << p->role_data_save_.n_shop_exploits_limit;
		pStream->write_string(",active_num=") << p->role_data_save_.n32_active_num;

		pStream->write_string(",active_data='");
		pStream->write_blob(&p->role_data_save_.n32_active_data, sizeof(p->role_data_save_.n32_active_data), p_conn);
		pStream->write_string("'");

		pStream->write_string(",active_receive='");
		pStream->write_blob(&p->role_data_save_.b_active_receive, sizeof(p->role_data_save_.b_active_receive), p_conn);
		pStream->write_string("'");

		pStream->write_string(",justice=") << p->role_data_save_.n32_rating;
		pStream->write_string(",purpuredec=") <<p->role_data_save_.b_PurpureDec;

		pStream->write_string(",circle_quest_perdaynumber=") <<p->role_data_save_.n_circle_quest_perdaynum;

		pStream->write_string(",day_clear='");
		pStream->write_blob(&p->role_data_save_.by_role_day_clear, sizeof(p->role_data_save_.by_role_day_clear), p_conn);
		pStream->write_string("'");

		pStream->write_string(",cooldownrevive_cd=") << p->role_data_save_.n_CoolDownReviveCD;
		pStream->write_string(",circle_quest_refresh_daymax=") << p->role_data_save_.n_circle_quest_freshMax;

		pStream->write_string(",shihun=") << p->role_data_save_.dw_shihun;
		pStream->write_string(",perday_hang_getexp_timems=") << p->role_data_save_.n_PerDayHangGetExpTimeMS;
		pStream->write_string(",achievemetn_num=") << p->role_data_save_.n_achievement_num;

		pStream->write_string(",pet_xiulian_size=") << p->role_data_save_.n16_pet_xiulian_size;
		pStream->write_string(",perday_vigour_get_total=") << p->role_data_save_.dw_perday_get_vigour_total;

		pStream->write_string(",guild_active_num=") <<  p->role_data_save_.n32_guild_active_num;

		pStream->write_string(",guild_active_data='");
		pStream->write_blob(& p->role_data_save_.n32_guild_active_data, sizeof( p->role_data_save_.n32_guild_active_data), p_conn);
		pStream->write_string("'");

		pStream->write_string(",guild_active_receive='");
		pStream->write_blob(& p->role_data_save_.b_guild_active_receive, sizeof( p->role_data_save_.b_guild_active_receive), p_conn);
		pStream->write_string("'");


		pStream->write_string(",sex=") << p->role_data_const_.avatar.bySex;
		pStream->write_string(",hair_model_id=") << p->role_data_const_.avatar.wHairMdlID;
		pStream->write_string(",hair_color_id=") << p->role_data_const_.avatar.wHairTexID;
		pStream->write_string(",face_model_id=") << p->role_data_const_.avatar.wFaceMdlID;
		pStream->write_string(",face_detail_id=") << p->role_data_const_.avatar.wFaceDetailTexID;
		pStream->write_string(",dress_model_id=") << p->role_data_const_.avatar.wDressMdlID;
		pStream->write_string(",visualizeid=") << p->role_data_const_.avatar.byVisualize;
		pStream->write_string(",role_name='").write_string(p->role_data_const_.sz_role_name, p_conn);
		pStream->write_string("'");
		pStream->write_string(",role_name_crc=") << p->role_data_const_.dw_role_name_crc;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_const_.create_time_);
		pStream->write_string(",create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		if(p->b_change_name)
		{
			pStream->write_string(",change_name=1");
		}
		else
		{
			pStream->write_string(",change_name=0");
		}

		pStream->write_string(",last_change_name_time=") << p->dwChangeNameTime;
		pStream->write_string(",delete_role_guard_time=") << p->dwDelGuardTime;

		//gx add 2013.10.14
		pStream->write_string(",instance_pass=") << p->role_data_save_.nInstanceData;
		pStream->write_string(",shaodang_begin_time=") << p->role_data_save_.nInstanceShaodang;
		pStream->write_string(",shaodang_index=") << p->role_data_save_.nSaodangIndex;
		pStream->write_string(",spouse_id=") << p->role_data_save_.dwSpouseID;
		pStream->write_string(",vip_level=") << p->role_data_save_.dwVIPLevel;

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.dwVIP_Deadline);
		{
			pStream->write_string(",vip_deadline='").write_string(sz_time_buffer_);
			pStream->write_string("'");
		}
		//end

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_role_data++;
	}

	return bRet;
}

// 插入人物技能数据
BOOL CombinationDB::InsertRoleSkill(LIST_ROLE_SKILL& list_role_skill)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_ROLE_SKILL::iterator iter_role_skill = list_role_skill.begin();
	while(iter_role_skill != list_role_skill.end())
	{
		if(!VALID_POINT(*iter_role_skill))
		{
			iter_role_skill++;
			continue;
		}

		tag_role_skill* p = (tag_role_skill*)(*iter_role_skill);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("skill");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",id=") << p->dw_id;
		pStream->write_string(",bidden_level=") << p->n_learn_level_;
		pStream->write_string(",self_level=") << p->n_self_level_;
		pStream->write_string(",proficiency=") << p->n_proficiency_;
		pStream->write_string(",cooldown=") << p->n_cool_down_;

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_role_skill++;
	}

	return bRet;
}

// 插入称号数据
BOOL CombinationDB::InsertTitle(LIST_TITLE& list_title)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_TITLE::iterator iter_title = list_title.begin();
	while(iter_title != list_title.end())
	{
		if(!VALID_POINT(*iter_title))
		{
			iter_title++;
			continue;
		}

		tag_title* p = (tag_title*)(*iter_title);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("title");
		pStream->write_string("role_id=") << p->dw_role_id;
		pStream->write_string(",id=") << p->n_title_id_;
		pStream->write_string(",count=") << p->dw_state_mark_;
		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dw_time);
		pStream->write_string(",time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
	
		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_title++;
	}

	return bRet;
}

// 插入钱庄数据
BOOL CombinationDB::InsertBank(LIST_BANK& list_bank)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_BANK::iterator iter_bank = list_bank.begin();
	while(iter_bank != list_bank.end())
	{
		if(!VALID_POINT(*iter_bank))
		{
			iter_bank++;
			continue;
		}

		tag_bank* p = (tag_bank*)(*iter_bank);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("bank");

		pStream->write_string("id=") << p->dw_id;
		pStream->write_string(",bidup=") << p->dw_bidup;
		pStream->write_string(",bidup_id=") << p->dw_bidup_id;
		pStream->write_string(",chaw=") << p->dw_chaw;
		pStream->write_string(",sell_id=") << p->dw_sell_id;
		pStream->write_string(",timetype=") << p->by_time_type;
		pStream->write_string(",sell=") << p->dw_sell;
		pStream->write_string(",type=") << p->by_type;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dw_begin_time);
		
		pStream->write_string(",begintime='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		

		m_pdb->return_use_connect(p_conn);


		/*bRet = */m_pdb->sql_execute(pStream);

	/*	if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_bank++;
	}

	return bRet;
}

// 插入悬赏数据
BOOL CombinationDB::InsertGuerdon(LIST_GUERDON_QUEST& list_guerdon)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUERDON_QUEST::iterator iter_guerdon_quest = list_guerdon.begin();
	while(iter_guerdon_quest != list_guerdon.end())
	{
		if(!VALID_POINT(*iter_guerdon_quest))
		{
			iter_guerdon_quest++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("guerdon_quest");
		pStream->write_string("serial=") << (*iter_guerdon_quest)->n64Serial;
		pStream->write_string(",sender=") << (*iter_guerdon_quest)->dwSender;
		pStream->write_string(",reciver=") << (*iter_guerdon_quest)->dwReciver;
		pStream->write_string(",quest_id=") << (*iter_guerdon_quest)->u16QuestID;
		pStream->write_string(",guild_fix=") << (*iter_guerdon_quest)->bGuildFix;
		pStream->write_string(",state=") << (*iter_guerdon_quest)->eState;
		pStream->write_string(",yuanbao=") << (*iter_guerdon_quest)->u16YuanBao;
		pStream->write_string(",end_time=") << (*iter_guerdon_quest)->dwEndTime;


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guerdon_quest++;
	}

	return bRet;
}

// 更新称号角色ID
BOOL CombinationDB::UpadteAchievement(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("achievement");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

// 更新角色称号进度角色ID
BOOL CombinationDB::UpdateAchievementProcess(MAP_ROLE_ID &map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("achievement_progress");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}
//更新角色奖励信息
BOOL CombinationDB::UpdateRoleReward(MAP_ROLE_ID &map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	//odbc::sql_language_disposal* pStream = m_pdb->get_io();
	//if(!pStream)
	//{
	//	return FALSE;
	//}

	//pStream->clear();
	//pStream->write_string("alter table reward add index role_id(role_id)");

	//bRet = m_pdb->sql_execute(pStream);

	///*if(!bRet)
	//{
	//return bRet;
	//}*/

	//m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("reward");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}
//更新玩家坐骑信息
BOOL CombinationDB::UpdateRoleMount(MAP_ROLE_ID &map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("mounts");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}
//end
//更新玩家名帖信息
BOOL CombinationDB::UpdateRoleVCard(MAP_ROLE_ID &map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("visiting_card");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}
// 更新黑名单角色ID
BOOL CombinationDB::UpdateBlack(MAP_ROLE_ID &map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table blacklist add index black_id(black_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
		return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("blacklist");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();
		pStream->update_item("blacklist");
		pStream->write_string("black_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("black_id = ") << iter->first;

		m_pdb->return_io(pStream);

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateFriendShip(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	/*odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();*/
	//pStream->write_string("alter table friendship add index friend_id(friend_id)");

	//bRet = m_pdb->sql_execute(pStream);

	///*if(!bRet)
	//{
	//	return bRet;
	//}*/

	//m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("friendship");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();
		pStream->update_item("friendship");
		pStream->write_string("friend_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("friend_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateFriend(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table friend add index friend_id(friend_id)");

	bRet = m_pdb->sql_execute(pStream);

	//if(!bRet)
	//{
	//	return bRet;
	//}

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("friend");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();
		pStream->update_item("friend");
		pStream->write_string("friend_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("friend_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

// 更新仇人角色ID
BOOL CombinationDB::UpdateEnemy(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table enemy add index enemy_id(enemy_id)");

	bRet = m_pdb->sql_execute(pStream);

	//if(!bRet)
	//{
	//	return bRet;
	//}

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("enemy");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();
		pStream->update_item("enemy");
		pStream->write_string("enemy_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("enemy_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

// 更新buff角色ID
BOOL CombinationDB::UpdateBuff(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table buff add index src_unit_id(src_unit_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
		return bRet;
	}*/

	m_pdb->return_io(pStream);


	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("buff");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();
		pStream->update_item("buff");
		pStream->write_string("src_unit_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("src_unit_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuild(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table guild add index creater_name_id(creater_name_id)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();
	pStream->write_string("alter table guild add index leader_id(leader_id)");

	bRet = m_pdb->sql_execute(pStream);


	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);


	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("guild");
		pStream->write_string("creater_name_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("creater_name_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();
		pStream->update_item("guild");
		pStream->write_string("leader_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("leader_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuildMember(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("guild_member");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateItem(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table item add index creator_id(creator_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	INT32 nCurent = 0;
	INT32 nMaxNum = map_role_id.size();

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("item");
		pStream->write_string("owner_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("owner_id = ") << iter->first;
		pStream->write_string(" and container_type_id >= 1 and container_type_id <= 5");

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("item");
		pStream->write_string("owner_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("owner_id = ") << iter->first;
		pStream->write_string(" and container_type_id = ") << EICT_GDQuest;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		} 

		pStream->clear();

		pStream->update_item("item");
		pStream->write_string("creator_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("creator_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
		nCurent++;
		CString str;
		str.Format(_T("数量：%d/%d"), nCurent, nMaxNum);
		m_pCombin_Dlg->m_process.SetWindowText(str);
	}

	return bRet;
}

BOOL CombinationDB::UpdataItemCD(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("item_cd_time");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateMail(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table mail add index send_role_id(send_role_id)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();
	pStream->write_string("alter table mail add index recv_role_id(recv_role_id)");

	bRet = m_pdb->sql_execute(pStream);


	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("mail");
		pStream->write_string("send_role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("send_role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("mail");
		pStream->write_string("recv_role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("recv_role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateMapLimit(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table map_limit add index role_id(role_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("map_limit");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateInstanceProcess(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table inst_process add index role_id(role_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("inst_process");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);
		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateMasterPrentice(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("master_prentice");
		pStream->write_string("master = ") << iter->second;
		pStream->where_item();
		pStream->write_string("master = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdatePaimai(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table paimai add index bidup_id(bidup_id)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();
	pStream->write_string("alter table paimai add index sell_id(sell_id)");

	bRet = m_pdb->sql_execute(pStream);


	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("paimai");
		pStream->write_string("bidup_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("bidup_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("paimai");
		pStream->write_string("sell_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("sell_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateBank(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table bank add index bidup_id(bidup_id)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();
	pStream->write_string("alter table bank add index sell_id(sell_id)");

	bRet = m_pdb->sql_execute(pStream);


	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("bank");
		pStream->write_string("bidup_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("bidup_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("bank");
		pStream->write_string("sell_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("sell_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdatePet(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table pet_data add index master_id(master_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("pet_data");
		pStream->write_string("master_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("master_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		if(!bRet)
		{
			return bRet;
		}

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdatePetSNS(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table pet_sns add index master_id(master_id)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();
	pStream->write_string("alter table pet_sns add index friend_id(friend_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("pet_sns");
		pStream->write_string("master_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("master_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("pet_sns");
		pStream->write_string("friend_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("friend_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateQuest(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table quest add index role_id(role_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("quest");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateQuestDone(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table quest_done add index role_id(role_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("quest_done");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuerdonQuest(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table guerdon_quest add index sender(sender)");

	bRet = m_pdb->sql_execute(pStream);

	pStream->clear();
	pStream->write_string("alter table guerdon_quest add index reciver(reciver)");

	bRet = m_pdb->sql_execute(pStream);


	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("guerdon_quest");
		pStream->write_string("sender = ") << iter->second;
		pStream->where_item();
		pStream->write_string("sender = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("guerdon_quest");
		pStream->write_string("reciver = ") << iter->second;
		pStream->where_item();
		pStream->write_string("reciver = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateRoleSkill(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("skill");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateRoleTitle(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("title");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateRoleData(MAP_ROLE_ID& map_role_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table role_data add index master_id(master_id)");

	bRet = m_pdb->sql_execute(pStream);

	//add 2013.12.04
	pStream->clear();
	pStream->write_string("alter table role_data add index spouse_id(spouse_id)");
	bRet = m_pdb->sql_execute(pStream);
	//end
	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ROLE_ID::iterator iter = map_role_id.begin();
	while(iter != map_role_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("role_data");
		pStream->write_string("role_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("role_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("role_data");
		pStream->write_string("master_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("master_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		//更新配偶ID add 2013.12.03
		pStream->clear();
		pStream->update_item("role_data");
		pStream->write_string("spouse_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("spouse_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}
		//end
		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuildSign(LIST_GUILD& list_guild)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_GUILD::iterator iter = list_guild.begin();
	while(iter != list_guild.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->update_item("guild");
		pStream->write_string("sign_data='").write_blob((*iter)->dwSignRoleID, sizeof((*iter)->dwSignRoleID), p_conn);
		pStream->write_string("'");
		pStream->where_item();
		pStream->write_string("id = ") << (*iter)->dwID;

		m_pdb->return_use_connect(p_conn);

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateMaster(LIST_MASTER& list_master)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	LIST_MASTER::iterator iter = list_master.begin();
	while(iter != list_master.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		INT n_size = (*iter)->by_number * sizeof(DWORD);
		BYTE* p_buff = new BYTE[n_size];
		ZeroMemory(p_buff, sizeof(*p_buff));

		BYTE* p_temp = p_buff;

		vector<DWORD>::iterator iter1 = (*iter)->list_role.begin();
		while(iter1 != (*iter)->list_role.end())
		{
			memcpy(p_temp, &(*iter1), sizeof(DWORD));
			p_temp += sizeof(DWORD);
			iter1++;
		}
		pStream->update_item("master_prentice");
		pStream->write_string("prentices='");
		pStream->write_blob(p_buff, (*iter)->by_number * sizeof(DWORD), p_conn);
		pStream->write_string("'");
		pStream->where_item();
		pStream->write_string("master = ") << (*iter)->dw_master;

		SAFE_DELETE_ARRAY(p_buff);

		m_pdb->return_use_connect(p_conn);

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateRoleName(LIST_ROLE_DATA& list_role_data)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("delete from role_data");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);

	LIST_ROLE_DATA::iterator iter = list_role_data.begin();
	while(iter != list_role_data.end())
	{
		tag_role_data* p = (*iter);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("role_data");
		pStream->write_string("avatar_equip='").write_blob(&p->role_data_save_.avatar_equip_, SIZE_AVATAR_EQUIP, p_conn);
		pStream->write_string("',display_set=")<< (BYTE)p->role_data_save_.display_set_;
		pStream->write_string(",map_id=") << p->role_data_save_.dw_map_id_;
		pStream->write_string(",x=") << p->role_data_save_.f_coordinate_[0];// 坐标
		pStream->write_string(",y=") << p->role_data_save_.f_coordinate_[1];
		pStream->write_string(",z=") << p->role_data_save_.f_coordinate_[2];
		pStream->write_string(",face_x=") << p->role_data_save_.f_face_[0];// 朝向
		pStream->write_string(",face_y=") << p->role_data_save_.f_face_[1];
		pStream->write_string(",face_z=") << p->role_data_save_.f_face_[2];

		pStream->write_string(",reborn_map_id=") << p->role_data_save_.dw_reborn_map_id_;

		pStream->write_string(",class=") << (int)p->role_data_save_.e_class_;
		pStream->write_string(",classex=") << p->role_data_save_.e_class_ex_;
		pStream->write_string(",level=") << p->role_data_save_.n_level_;
		pStream->write_string(",exp_cur_level=") << p->role_data_save_.n_cur_exp_;

		pStream->write_string(",hp=") << p->role_data_save_.n_hp_;
		pStream->write_string(",mp=") << p->role_data_save_.n_mp_;
		pStream->write_string(",rage=") << p->role_data_save_.n_rage_;
		pStream->write_string(",endurance=") << p->role_data_save_.n_endurance_;
		pStream->write_string(",vitality=") << p->role_data_save_.n_brotherhood_;
		pStream->write_string(",injury=") << p->role_data_save_.n_injury_;
		pStream->write_string(",knowledge=") << p->role_data_save_.n_knowledge_;
		pStream->write_string(",morale=") <<p->role_data_save_.n_morale_;
		pStream->write_string(",morality=") << p->role_data_save_.n_morality_;
		pStream->write_string(",culture=") << p->role_data_save_.n_luck_;
		pStream->write_string(",credit=") << p->role_data_save_.n_credit_;
		pStream->write_string(",identity=") << p->role_data_save_.n_identity_;
		pStream->write_string(",vip_point=") << p->role_data_save_.n_vip_point_;

		pStream->write_string(",att_avail=") << p->role_data_save_.n_att_point_;
		pStream->write_string(",talent_avail=") << p->role_data_save_.n_talent_point_;

		pStream->write_string(",physique_added=") << p->role_data_save_.n_att_point_add_[ERA_Physique];
		pStream->write_string(",strength_added=") << p->role_data_save_.n_att_point_add_[ERA_Strength];
		pStream->write_string(",pneuma_added=") << p->role_data_save_.n_att_point_add_[ERA_Pneuma];
		pStream->write_string(",innerforce_added=") << p->role_data_save_.n_att_point_add_[ERA_InnerForce];
		pStream->write_string(",technique_added=") << p->role_data_save_.n_att_point_add_[ERA_Technique];
		pStream->write_string(",agility_added=") << p->role_data_save_.n_att_point_add_[ERA_Agility];

		pStream->write_string(",talent_type1=") << p->role_data_save_.talent_[0].eType;
		pStream->write_string(",talent_type2=") << p->role_data_save_.talent_[1].eType;
		pStream->write_string(",talent_type3=") << p->role_data_save_.talent_[2].eType;
		pStream->write_string(",talent_type4=") << p->role_data_save_.talent_[3].eType;
		pStream->write_string(",talent_val1=") << p->role_data_save_.talent_[0].nPoint;
		pStream->write_string(",talent_val2=") << p->role_data_save_.talent_[1].nPoint;
		pStream->write_string(",talent_val3=") << p->role_data_save_.talent_[2].nPoint;
		pStream->write_string(",talent_val4=") << p->role_data_save_.talent_[3].nPoint;

		pStream->write_string(",safe_guard_flag=") << p->role_data_save_.b_safe_guard_;
		pStream->write_string(",pk_value=") << p->role_data_save_.n_pk_value_;

		pStream->write_string(",bag_size=") << p->role_data_save_.n16_bag_size_;		// 背包
		pStream->write_string(",bag_gold=") << p->role_data_save_.n_bag_gold_;
		pStream->write_string(",bag_silver=") << p->role_data_save_.n_bag_silver_;
		pStream->write_string(",bag_copper=")	<< p->role_data_save_.n_bag_copper_;
		pStream->write_string(",bag_bind_gold=") << p->role_data_save_.n_bag_bind_gold_;
		pStream->write_string(",bag_bind_silver=") << p->role_data_save_.n_bag_bind_silver_;
		pStream->write_string(",bag_bind_copper=") << p->role_data_save_.n_bag_bind_copper_;
		pStream->write_string(",bag_yuanbao=") << p->role_data_save_.n_bag_tuanbao_;
		pStream->write_string(",exchange_volume=") << p->role_data_save_.n_ex_volume_;

		pStream->write_string(",pet_packet_num=") << p->role_data_save_.n16_pet_packet_size_;

		pStream->write_string(",total_tax=") << p->role_data_save_.n_total_tax_;	// 缴税总额
		pStream->write_string(",remote_open_set=") << (DWORD)p->role_data_save_.s_remote_open_set_;
		pStream->write_string(",cur_title_id=") << p->role_data_save_.u16_active_title_id[0];
		pStream->write_string(",cur_title_id2=") << p->role_data_save_.u16_active_title_id[1];
		pStream->write_string(",cur_title_id3=") << p->role_data_save_.u16_active_title_id[2];

		pStream->write_string(",guild_id=") << p->role_data_save_.dw_guild_id;
		pStream->write_string(",team_id=") << p->role_data_save_.dw_team_id_;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.login_time_);

		pStream->write_string(",login_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.logout_time_);
		pStream->write_string(",logout_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.close_safe_guard_time_);
		pStream->write_string(",close_safe_guard_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.dw_time_get_mall_free_);
		pStream->write_string(",get_mall_free_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");


		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.leave_guild_time_);

		pStream->write_string(",leave_guild_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");


		pStream->write_string(",own_instance_id=") << p->role_data_save_.dw_own_instance_id_;
		pStream->write_string(",own_instance_map_id=") << p->role_data_save_.dw_own_instance_map_id_;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.dw_instance_create_time_);

		pStream->write_string(",instance_create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");


		pStream->write_string(",online_time=") << p->role_data_save_.n_online_time_;
		pStream->write_string(",cur_online_time=") << p->role_data_save_.n_cur_online_time_;

		pStream->write_string(",script_data='");
		pStream->write_blob(p->role_data_save_.data_.dwData, sizeof(DWORD)*ESD_Role, p_conn);
		pStream->write_string("'");

		pStream->write_string(",stall_level=") << p->role_data_save_.by_stall_level_;
		pStream->write_string(",stall_daily_exp=") << p->role_data_save_.n_stall_daily_exp_;
		pStream->write_string(",stall_cur_exp=") << p->role_data_save_.n_stall_cur_exp_;
		pStream->write_string(",stall_last_time=") << p->role_data_save_.dw_last_stall_time_;

		pStream->write_string(",send_mail_num=") << p->role_data_save_.n_send_mail_num_;
		pStream->write_string(",master_id=") << p->role_data_save_.dw_master_id_;
		pStream->write_string(",masterprentice_forbid_time=") << p->role_data_save_.dw_master_prentice_forbid_time_;

		pStream->write_string(",map_limit_num=") << p->role_data_save_.n_map_limit_num_;

		pStream->write_string(",hang_num=") << p->role_data_save_.n16_hang_num_;
		pStream->write_string(",is_exp=") << p->role_data_save_.b_exp_;
		pStream->write_string(",is_brotherhood=") << p->role_data_save_.b_brotherhood_;
		pStream->write_string(",leave_exp=") << p->role_data_save_.n_leave_exp_;
		pStream->write_string(",leave_brotherhood=") << p->role_data_save_.n_leave_brotherhood_;
		pStream->write_string(",vigour=") << p->role_data_save_.n_vigour_;
		pStream->write_string(",role_help='");
		pStream->write_blob(p->role_data_save_.by_role_help_, sizeof(p->role_data_save_.by_role_help_), p_conn);
		pStream->write_string("'");
		pStream->write_string(",role_talk='");
		pStream->write_blob(p->role_data_save_.by_talk_data_, sizeof(p->role_data_save_.by_talk_data_), p_conn);
		pStream->write_string("'");
		pStream->write_string(",key_info='");
		pStream->write_blob(&p->role_data_save_.st_key_info_, sizeof(p->role_data_save_.st_key_info_), p_conn);
		pStream->write_string("'");
		pStream->write_string(",total_mastermoral=") << p->role_data_save_.n_total_mater_moral_;
		pStream->write_string(",kill_num=") << p->role_data_save_.n_kill_num_;
		pStream->write_string(",gift_step=") << p->role_data_save_.n_gift_step_;
		pStream->write_string(",gift_id=") << p->role_data_save_.dw_gift_id_;
		pStream->write_string(",gift_leaving_time=") << p->role_data_save_.dw_gift_leave_time_;
		pStream->write_string(",gift_get=") << p->role_data_save_.b_gift_get_;
		pStream->write_string(",gift_group_id=") << p->role_data_save_.n_gift_id_;

		pStream->write_string(",role_camp=") << p->role_data_save_.e_role_camp;
		pStream->write_string(",paimailimit=") << p->role_data_save_.n_paimai_limit;
		pStream->write_string(",banklimit=") << p->role_data_save_.n_bank_limit;

		pStream->write_string(",today_online_tick=") << p->role_data_save_.dw_today_online_tick_;
		pStream->write_string(",history_vigour_cost=") << p->role_data_save_.dw_history_vigour_cost_;

		pStream->write_string(",exbagstep=") << p->role_data_save_.n16_exbag_step;
		pStream->write_string(",exwarestep=") << p->role_data_save_.n16_exware_step;

		pStream->write_string(",signature_name='").write_string(p->role_data_save_.sz_signature_name);
		pStream->write_string("'");

		pStream->write_string(",ware_size=") << p->role_data_save_.n16WareSize;
		pStream->write_string(",ware_gold=") << p->role_data_save_.nWareGold;
		pStream->write_string(",ware_silver=") << p->role_data_save_.nWareSilver;
		pStream->write_string(",ware_copper=") << p->role_data_save_.nWareCopper;

		pStream->write_string(",circle_quest='");
		pStream->write_blob(&p->role_data_save_.circle_quest_man_, sizeof(p->role_data_save_.circle_quest_man_), p_conn);
		pStream->write_string("'");

		pStream->write_string(",yuanbao_exchange_num=") << p->role_data_save_.n_yuanbao_exchange_num;
		pStream->write_string(",achievemetn_point=") << p->role_data_save_.n_achievement_point;

		pStream->write_string(",forbid_talk_start=") << p->role_data_save_.dw_forbid_talk_start_;
		pStream->write_string(",forbid_talk_end=") << p->role_data_save_.dw_forbid_talk_end_;
		pStream->write_string(",graduate_num=") << p->role_data_save_.n_graduates_num;
		pStream->write_string(",destory_equip_count=") << p->role_data_save_.dw_destory_equip_count;
		pStream->write_string(",cur_1v1_score=") << p->role_data_save_.st_1v1_score.n_cur_score;
		pStream->write_string(",day_1v1_score=") << p->role_data_save_.st_1v1_score.n_day_max_score;
		pStream->write_string(",day_1v1_num=") << p->role_data_save_.st_1v1_score.n_day_scroe_num;
		pStream->write_string(",score_1v1_award=") << p->role_data_save_.st_1v1_score.n16_score_award;

		pStream->write_string(",role_id=") << p->dw_role_id;
		pStream->write_string(",account_id=") << p->dw_account_id;
		pStream->write_string(",remove_flag=") << p->b_remove;


		pStream->write_string(",exploits=") << p->role_data_save_.n32_exploits;
		pStream->write_string(",circle_quest_refresh=") << p->role_data_save_.n_circle_quest_fresh;
		pStream->write_string(",exploitslimit=") << p->role_data_save_.n_shop_exploits_limit;
		pStream->write_string(",active_num=") << p->role_data_save_.n32_active_num;

		pStream->write_string(",active_data='");
		pStream->write_blob(&p->role_data_save_.n32_active_data, sizeof(p->role_data_save_.n32_active_data), p_conn);
		pStream->write_string("'");

		pStream->write_string(",active_receive='");
		pStream->write_blob(&p->role_data_save_.b_active_receive, sizeof(p->role_data_save_.b_active_receive), p_conn);
		pStream->write_string("'");

		pStream->write_string(",justice=") << p->role_data_save_.n32_rating;
		pStream->write_string(",purpuredec=") <<p->role_data_save_.b_PurpureDec;

		pStream->write_string(",circle_quest_perdaynumber=") <<p->role_data_save_.n_circle_quest_perdaynum;

		pStream->write_string(",day_clear='");
		pStream->write_blob(&p->role_data_save_.by_role_day_clear, sizeof(p->role_data_save_.by_role_day_clear), p_conn);
		pStream->write_string("'");

		pStream->write_string(",cooldownrevive_cd=") << p->role_data_save_.n_CoolDownReviveCD;
		pStream->write_string(",circle_quest_refresh_daymax=") << p->role_data_save_.n_circle_quest_freshMax;

		pStream->write_string(",shihun=") << p->role_data_save_.dw_shihun;
		pStream->write_string(",perday_hang_getexp_timems=") << p->role_data_save_.n_PerDayHangGetExpTimeMS;
		pStream->write_string(",achievemetn_num=") << p->role_data_save_.n_achievement_num;
		pStream->write_string(",pet_xiulian_size=") << p->role_data_save_.n16_pet_xiulian_size;
		pStream->write_string(",perday_vigour_get_total=") << p->role_data_save_.dw_perday_get_vigour_total;

		pStream->write_string(",guild_active_num=") <<  p->role_data_save_.n32_guild_active_num;

		pStream->write_string(",guild_active_data='");
		pStream->write_blob(& p->role_data_save_.n32_guild_active_data, sizeof( p->role_data_save_.n32_guild_active_data), p_conn);
		pStream->write_string("'");

		pStream->write_string(",guild_active_receive='");
		pStream->write_blob(& p->role_data_save_.b_guild_active_receive, sizeof( p->role_data_save_.b_guild_active_receive), p_conn);
		pStream->write_string("'");

		pStream->write_string(",sex=") << p->role_data_const_.avatar.bySex;
		pStream->write_string(",hair_model_id=") << p->role_data_const_.avatar.wHairMdlID;
		pStream->write_string(",hair_color_id=") << p->role_data_const_.avatar.wHairTexID;
		pStream->write_string(",face_model_id=") << p->role_data_const_.avatar.wFaceMdlID;
		pStream->write_string(",face_detail_id=") << p->role_data_const_.avatar.wFaceDetailTexID;
		pStream->write_string(",dress_model_id=") << p->role_data_const_.avatar.wDressMdlID;
		pStream->write_string(",visualizeid=") << p->role_data_const_.avatar.byVisualize;
		pStream->write_string(",role_name='").write_string(p->role_data_const_.sz_role_name, p_conn);
		pStream->write_string("'");
		pStream->write_string(",role_name_crc=") << p->role_data_const_.dw_role_name_crc;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_const_.create_time_);
		pStream->write_string(",create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");

		if(p->b_change_name)
		{
			pStream->write_string(",change_name=1");
		}
		else
		{
			pStream->write_string(",change_name=0");
		}

		pStream->write_string(",last_change_name_time=") << p->dwChangeNameTime;
		pStream->write_string(",delete_role_guard_time=") << p->dwDelGuardTime;
		//gx add 2013.10.14
		pStream->write_string(",instance_pass=") << p->role_data_save_.nInstanceData;
		pStream->write_string(",shaodang_begin_time=") << p->role_data_save_.nInstanceShaodang;
		pStream->write_string(",shaodang_index=") << p->role_data_save_.nSaodangIndex;
		pStream->write_string(",spouse_id=") << p->role_data_save_.dwSpouseID;
		pStream->write_string(",vip_level=") << p->role_data_save_.dwVIPLevel;

		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->role_data_save_.dwVIP_Deadline);
		{
			pStream->write_string(",vip_deadline='").write_string(sz_time_buffer_);
			pStream->write_string("'");
		}
		//end

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
			return bRet;
		}*/

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuerdonQuest(LIST_GUERDON_QUEST& list_guerdon_quest)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("delete from guerdon_quest");

	/*bRet = */m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	LIST_GUERDON_QUEST::iterator iter_guerdon_quest = list_guerdon_quest.begin();
	while(iter_guerdon_quest != list_guerdon_quest.end())
	{
		if(!VALID_POINT(*iter_guerdon_quest))
		{
			iter_guerdon_quest++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("guerdon_quest");
		pStream->write_string("serial=") << (*iter_guerdon_quest)->n64Serial;
		pStream->write_string(",sender=") << (*iter_guerdon_quest)->dwSender;
		pStream->write_string(",reciver=") << (*iter_guerdon_quest)->dwReciver;
		pStream->write_string(",quest_id=") << (*iter_guerdon_quest)->u16QuestID;
		pStream->write_string(",guild_fix=") << (*iter_guerdon_quest)->bGuildFix;
		pStream->write_string(",state=") << (*iter_guerdon_quest)->eState;
		pStream->write_string(",yuanbao=") << (*iter_guerdon_quest)->u16YuanBao;
		pStream->write_string(",end_time=") << (*iter_guerdon_quest)->dwEndTime;


		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
		return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guerdon_quest++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateMail(LIST_MAIL& list_mail)
{
	BOOL bRet = TRUE;
	INT nNum = 0;


	LIST_MAIL::iterator iter_mail = list_mail.begin();
	while(iter_mail != list_mail.end())
	{
		if(!VALID_POINT(*iter_mail))
		{
			iter_mail++;
			continue;
		}

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->update_item("mail");
		pStream->write_string("item_serial='").write_blob((*iter_mail)->s_mail_base_.n64ItemSerial, sizeof((*iter_mail)->s_mail_base_.n64ItemSerial), p_conn);
		pStream->write_string("'");
		pStream->where_item();
		pStream->write_string("mail_id = ") << (*iter_mail)->s_mail_base_.dwID;

		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
		return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_mail++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateBuff(MAP_ITEM_ID& map_item_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table buff add index item_serial_id(item_serial_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_ITEM_ID::iterator iter = map_item_id.begin();
	while(iter != map_item_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("buff");
		pStream->write_string("item_serial_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("item_serial_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateBankID(MAP_BANK_ID& map_bank_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_BANK_ID::iterator iter = map_bank_id.begin();
	while(iter != map_bank_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("bank");
		pStream->write_string("id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateMailID(MAP_MAIL_ID& map_mail_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_MAIL_ID::iterator iter = map_mail_id.begin();
	while(iter != map_mail_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("mail");
		pStream->write_string("mail_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("mail_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->update_item("item");
		pStream->write_string("owner_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("owner_id = ") << iter->first;
		pStream->write_string(" and container_type_id = ") << EICT_MailItem;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}


		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdatePaimaiID(MAP_PAIMAI_ID& map_paimai_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_PAIMAI_ID::iterator iter = map_paimai_id.begin();
	while(iter != map_paimai_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("paimai");
		pStream->write_string("id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("item");
		pStream->write_string("owner_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("owner_id = ") << iter->first;
		pStream->write_string(" and container_type_id = ") << EICT_PaiMai;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdatePetID(MAP_PET_ID& map_pet_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();
	pStream->write_string("alter table pet_skill add index pet_id(pet_id)");

	bRet = m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	MAP_PET_ID::iterator iter = map_pet_id.begin();
	while(iter != map_pet_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("pet_data");
		pStream->write_string("pet_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("pet_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("pet_skill");
		pStream->write_string("pet_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("pet_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("pet_sns");
		pStream->write_string("pet_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("pet_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateItemID(MAP_ITEM_ID& map_item_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	INT32 nCurent = 0;
	INT32 nMaxNum = map_item_id.size();

	MAP_ITEM_ID::iterator iter = map_item_id.begin();
	while(iter != map_item_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("item");
		pStream->write_string("serial = ") << iter->second;
		pStream->where_item();
		pStream->write_string("serial = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		pStream->clear();

		pStream->update_item("equip");
		pStream->write_string("serial = ") << iter->second;
		pStream->where_item();
		pStream->write_string("serial = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}


		m_pdb->return_io(pStream);

		iter++;
		nCurent++;

		CString str;
		str.Format(_T("数量：%d/%d"), nCurent, nMaxNum);
		m_pCombin_Dlg->m_process.SetWindowText(str);
	}

	return bRet;
}

BOOL CombinationDB::UpdateRoleGuildID(MAP_GUILD_ID& map_guild_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_GUILD_ID::iterator iter = map_guild_id.begin();
	while(iter != map_guild_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("role_data");
		pStream->write_string("guild_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("guild_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuildMemberID(MAP_GUILD_ID& map_guild_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_GUILD_ID::iterator iter = map_guild_id.begin();
	while(iter != map_guild_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("guild_member");
		pStream->write_string("guild_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("guild_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuildGradeID(MAP_GUILD_ID& map_guild_id)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	MAP_GUILD_ID::iterator iter = map_guild_id.begin();
	while(iter != map_guild_id.end())
	{
		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->update_item("guild_upgrade");
		pStream->write_string("guild_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("guild_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);

		if(!bRet)
		{
			return bRet;
		}

		m_pdb->return_io(pStream);

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::UpdateGuildID(LIST_GUILD& list_guild)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("delete from guild");

	/*bRet = */m_pdb->sql_execute(pStream);

	/*if(!bRet)
	{
	return bRet;
	}*/

	m_pdb->return_io(pStream);

	LIST_GUILD::iterator iter_guild = list_guild.begin();
	while(iter_guild != list_guild.end())
	{
		if(!VALID_POINT(*iter_guild))
		{
			iter_guild++;
			continue;
		}

		s_guild_load* p = (*iter_guild);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->insert_item("guild");
		pStream->write_string("id=") << p->dwID;
		pStream->write_string(",name='").write_blob(p->sz_name, (_tcsclen(p->sz_name) + 1) * sizeof(TCHAR), p_conn);
		pStream->write_string("'");
		pStream->write_string(",creater_name_id=") << p->dwFounderNameID;
		pStream->write_string(",level=") << p->byLevel;
		pStream->write_string(",fund=") << p->nFund;
		pStream->write_string(",material=") << p->nMaterial;
		pStream->write_string(",reputation=") << p->nReputation;
		pStream->write_string(",peace=") << p->n16Peace;

		char sz_time_buffer_[X_DATATIME_LEN + 1];
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwCreateTime);

		pStream->write_string(",create_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");


		pStream->write_string(",special_state=") << p->dwSpecState;

		pStream->write_string(",group_purchase=") << p->nGroupPurchase;
		pStream->write_string(",leader_id=") << p->dwLeaderRoleID;
		pStream->write_string(",remain_spread_times=") << p->byAffairRemainTimes;

		pStream->write_string(",sign_data='").write_blob(p->dwSignRoleID, sizeof(p->dwSignRoleID), p_conn);
		pStream->write_string("'");

		pStream->write_string(",enemy_data='").write_blob(p->dwEnemyID, sizeof(p->dwEnemyID), p_conn);
		pStream->write_string("'");

		pStream->write_string(",pos_name='").write_blob(p->szPosName, sizeof(p->szPosName), p_conn);
		pStream->write_string("'");
		pStream->write_string(",pos_power='").write_blob(p->dwPosPower, sizeof(p->dwPosPower), p_conn);
		pStream->write_string("'");
		pStream->write_string(",family_name='").write_blob(p->n_family_name, sizeof(p->n_family_name), p_conn);
		pStream->write_string("'");
		pStream->write_string(",npc_name='").write_blob(p->n_name, sizeof(p->n_name), p_conn);
		pStream->write_string("'");

		pStream->write_string(",hold_city0=") << p->byHoldCity[0];
		pStream->write_string(",hold_city1=") << p->byHoldCity[1];
		pStream->write_string(",hold_city2=") << p->byHoldCity[2];
		pStream->write_string(",daily_cost=") << p->nDailyCost;
		pStream->write_string(",rank=") << p->n16Rank;
		pStream->write_string(",sign_num=") << p->bySignatoryNum;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwMianzhanTime);
		pStream->write_string(",uplevel_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",league_id=") << p->dwLeagueID;
		DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_), p->dwUnLeagueBeginTime);
		pStream->write_string(",unleague_time='").write_string(sz_time_buffer_);
		pStream->write_string("'");
		pStream->write_string(",prosperity=") << p->nProsperity;
		pStream->write_string(",dkp='").write_blob(p->n16DKP, sizeof(p->n16DKP), p_conn);
		pStream->write_string("'");
		pStream->write_string(",change_dkp=") << p->bSignUpAttact;
		pStream->write_string(",symbol_value=") << p->dwValue;
		pStream->write_string(",script_data='").write_blob(p->n32ScriptData, sizeof(p->n32ScriptData), p_conn);
		pStream->write_string("'");
		pStream->write_string(",text='").write_blob(p->szText, sizeof(p->szText), p_conn);
		pStream->write_string("'");

		pStream->write_string(",formal=") << p->bFormal;

		// 归还数据库连接
		m_pdb->return_use_connect(p_conn);

		/*bRet = */m_pdb->sql_execute(pStream);

		/*if(!bRet)
		{
		return bRet;
		}*/

		m_pdb->return_io(pStream);
		iter_guild++;
	}

	return bRet;
}


/**/
BOOL CombinationDB::UpdateGuildKillBoss(MAP_GUILD_ID& map_guild_id)
{
	BOOL bRet;


	MAP_GUILD_ID::iterator iter = map_guild_id.begin();
	while(iter != map_guild_id.end())
	{

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream) return FALSE;

		pStream->clear();

		pStream->update_item("guild_kill_boss");
		pStream->write_string("guild_id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("guild_id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);
		m_pdb->return_io(pStream);

		if(!bRet) return bRet;

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::InitGuildKillBoss(LIST_GUILD_KILL_BOSS& list_guild_kill)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild_kill_boss", "monster_id,"	"guild_id");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_guild_kill_boss* p = new s_guild_kill_boss;
		ZeroMemory(p, sizeof(*p));

		p->dw_monster_id = (*pResult)[0].get_dword();
		p->dw_guild_id = (*pResult)[1].get_dword();

		list_guild_kill.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InsertGuildKillBoss(LIST_GUILD_KILL_BOSS& list_guild_kill)
{
	BOOL bRet = TRUE;
	INT nNum = 0;


	LIST_GUILD_KILL_BOSS::iterator iter_kill_boss = list_guild_kill.begin();
	while(iter_kill_boss != list_guild_kill.end())
	{
		if(!VALID_POINT(*iter_kill_boss))
		{
			iter_kill_boss++;
			continue;
		}

		s_guild_kill_boss* p = (s_guild_kill_boss*)(*iter_kill_boss);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		pStream->insert_item("guild_kill_boss");
		pStream->write_string("guild_kill_boss=") << p->dw_monster_id;
		pStream->write_string(",guild_id=") << p->dw_guild_id;
		m_pdb->sql_execute(pStream);

		m_pdb->return_io(pStream);
		iter_kill_boss++;
	}

	return bRet;
}

/**/
// BOOL CombinationDB::UpdateGuildWarHistory(MAP_ROLE_ID& map_role_id, MAP_GUILD_ID& map_guild_id)
// {
// 	BOOL bRet;
// 
// 	MAP_ROLE_ID::iterator iter = map_role_id.begin( );
// 	while( iter != map_role_id.end( ) )
// 	{
// 		odbc::sql_language_disposal* pStream = m_pdb->get_io();
// 		if(!pStream) return FALSE;
// 
// 		pStream->clear( ); 
// 		pStream->update_item("guild_war_history");
// 		pStream->write_string("enemy_leader_id = ") << iter->second;
// 		pStream->where_item();
// 		pStream->write_string("enemy_leader_id= ") << iter->first;
// 
// 		bRet = m_pdb->sql_execute(pStream);
// 		m_pdb->return_io(pStream);
// 
// 		if(!bRet) return bRet;
// 
// 		iter++;
// 	}
// 
// 
// 	MAP_GUILD_ID::iterator iter2 = map_guild_id.begin( );
// 	while( iter2 != map_guild_id.end( ) )
// 	{
// 		odbc::sql_language_disposal* pStream = m_pdb->get_io();
// 		if(!pStream) return FALSE;
// 
// 		pStream->clear( ); 
// 		pStream->update_item("guild_war_history");
// 		pStream->write_string("guild_id = ") << iter2->second;
// 		pStream->where_item();
// 		pStream->write_string("guild_id= ") << iter2->first;
// 		bRet = m_pdb->sql_execute(pStream);
// 		m_pdb->return_io(pStream);
// 		if(!bRet) return bRet;
// 
// 
// 		pStream->clear( ); 
// 		pStream->update_item("guild_war_history");
// 		pStream->write_string("enemy_id = ") << iter2->second;
// 		pStream->where_item();
// 		pStream->write_string("enemy_id= ") << iter2->first;
// 		bRet = m_pdb->sql_execute(pStream);
// 		m_pdb->return_io(pStream);
// 		if(!bRet) return bRet;
// 
// 		iter2++;
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CombinationDB::InitGuildWarHistory(LIST_GUILD_WAR_HISTORY& list_guild_war_histroy)
// {
// 	BOOL bRet = TRUE;
// 	INT nNum = 0;
// 
// 	odbc::sql_language_disposal* pStream = m_pdb->get_io();
// 	if(!pStream)
// 	{
// 		return FALSE;
// 	}
// 
// 	pStream->clear();
// 
// 	pStream->select_item("guild_war_history", "guild_id,"	"enemy_id," "time," "type," "enemy_leader_id");
// 
// 	odbc::execute_result* pResult = m_pdb->sql_query(pStream);
// 
// 	if(!pResult)
// 	{
// 		bRet = FALSE;
// 		goto exit;
// 	}
// 
// 	nNum = pResult->get_row_count() ;
// 
// 	while(nNum)
// 	{
// 		tagGuildWarHistory* p = new tagGuildWarHistory;
// 		ZeroMemory(p, sizeof(*p));
// 
// 		p->dw_guild_id = (*pResult)[0].get_dword();
// 		p->dw_enemy_id = (*pResult)[1].get_dword();
// 		DataTime2DwordTime(p->dw_time, (*pResult)[2].get_string(), (*pResult)[2].get_length());
// 		p->e_war_history_type = (EWarHistoryTyep)(*pResult)[3].get_byte();
// 		p->dw_enemy_leader_id = (*pResult)[4].get_dword();
// 		list_guild_war_histroy.push_back(p);
// 
// 		nNum--;
// 		pResult->next_row();
// 	}
// 
// exit:
// 	m_pdb->return_io(pStream);
// 	m_pdb->free_result_query(pResult);
// 
// 	return bRet;
// }
// 
// BOOL CombinationDB::InsertGuildWarHistory(LIST_GUILD_WAR_HISTORY& list_guild_war_histroy)
// {
// 	INT nNum = 0;
// 
// 	char sz_time_buffer_[X_DATATIME_LEN + 1];
// 
// 	LIST_GUILD_WAR_HISTORY::iterator iter = list_guild_war_histroy.begin();
// 	while(iter != list_guild_war_histroy.end())
// 	{
// 		if(!VALID_POINT(*iter))
// 		{
// 			iter++;
// 			continue;
// 		}
// 
// 		tagGuildWarHistory* p = (tagGuildWarHistory*)(*iter);
// 
// 		odbc::sql_language_disposal* pStream = m_pdb->get_io();
// 		if(!pStream)
// 		{
// 			return FALSE;
// 		}
// 
// 		pStream->clear();
// 
// 		pStream->insert_item("guild_war_history");
// 		pStream->write_string("guild_id=") << p->dw_guild_id;
// 		pStream->write_string(",enemy_id=") << p->dw_enemy_id;
// 		if(DwordTime2DataTime(sz_time_buffer_, sizeof(sz_time_buffer_),p->dw_time))
// 		{
// 			pStream->write_string(",time='").write_string(sz_time_buffer_);
// 			pStream->write_string("'");
// 		}
// 		pStream->write_string(",type=") << p->e_war_history_type;
// 		pStream->write_string(",enemy_leader_id=") << p->dw_enemy_leader_id;
// 	
// 		m_pdb->sql_execute(pStream);
// 		m_pdb->return_io(pStream);
// 
// 		iter++;
// 	}
// 
// 	return TRUE;
// }
/**/
BOOL CombinationDB::UpdateGuildPlant(MAP_GUILD_ID& map_guild_id)
{
	BOOL bRet;


	MAP_GUILD_ID::iterator iter = map_guild_id.begin();
	while(iter != map_guild_id.end())
	{

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream) return FALSE;

		pStream->clear();

		pStream->update_item("guild_plant");
		pStream->write_string("id = ") << iter->second;
		pStream->where_item();
		pStream->write_string("id = ") << iter->first;

		bRet = m_pdb->sql_execute(pStream);
		m_pdb->return_io(pStream);

		if(!bRet) return bRet;

		iter++;
	}

	return bRet;
}

BOOL CombinationDB::InitGuildPlant(LIST_GUILD_PLANT& list_guild_plant)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->select_item("guild_plant", "id,"	"data");

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		s_guild_plant* p = new s_guild_plant;
		ZeroMemory(p, sizeof(*p));

		p->dw_guild_id = (*pResult)[0].get_dword();
		(*pResult)[1].get_blob(p->s_data, (*pResult)[1].get_length());

		list_guild_plant.push_back(p);

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::InsertGuildPlant(LIST_GUILD_PLANT& list_guild_plant)
{
	BOOL bRet = TRUE;

	LIST_GUILD_PLANT::iterator iter = list_guild_plant.begin();
	while(iter != list_guild_plant.end())
	{
		if(!VALID_POINT(*iter))
		{
			iter++;
			continue;
		}

		s_guild_plant* p = (s_guild_plant*)(*iter);

		odbc::sql_language_disposal* pStream = m_pdb->get_io();
		if(!pStream)
		{
			return FALSE;
		}

		pStream->clear();

		odbc::tag_mysql_connect* p_conn = m_pdb->get_idlesse_connect();

		pStream->replace_item("guild_plant");

		pStream->write_string("id=") << p->dw_guild_id;
		pStream->write_string(",data='").write_blob(p->s_data, sizeof(p->s_data), p_conn);
		pStream->write_string("'");


		// 归还数据库连接
		m_pdb->return_use_connect(p_conn);

		m_pdb->return_io(pStream);
		iter++;
	}

	return bRet;
}

BOOL CombinationDB::AddItemRead()
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("alter table item add column bRead tinyint unsigned not null default '0'");

	bRet = m_pdb->sql_execute(pStream);


	m_pdb->return_io(pStream);
}
BOOL CombinationDB::ChangeItemRead(INT64 n64Serial)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->update_item("item");
	pStream->write_string("bRead = 1");
	pStream->where_item();
	pStream->write_string("serial = ") << n64Serial;
	pStream->write_string(" and ");
	pStream->write_string("bRead = 0");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}


BOOL CombinationDB::AddQuestDoneRead()
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string("alter table quest_done add column bRead tinyint unsigned not null default '0'");

	bRet = m_pdb->sql_execute(pStream);


	m_pdb->return_io(pStream);
}

BOOL CombinationDB::ChangeQuestDoneRead(DWORD dw_role_id, DWORD dw_quest_id)
{
	BOOL bRet = TRUE;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->update_item("quest_done");
	pStream->write_string("bRead = 1");
	pStream->where_item();
	pStream->write_string("role_id = ") << dw_role_id;
	pStream->write_string(" and ");
	pStream->write_string("quest_id = ") << dw_quest_id;
	pStream->write_string(" and ");
	pStream->write_string("bRead = 0");

	bRet = m_pdb->sql_execute(pStream);

	m_pdb->return_io(pStream);
}

BOOL CombinationDB::GetItemNotReadNum(DWORD& dw_num)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string(_T("select count(*) from item where bRead = 0"));

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_num = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}

BOOL CombinationDB::GetQuestNotReadNum(DWORD& dw_num)
{
	BOOL bRet = TRUE;
	INT nNum = 0;

	odbc::sql_language_disposal* pStream = m_pdb->get_io();
	if(!pStream)
	{
		return FALSE;
	}

	pStream->clear();

	pStream->write_string(_T("select count(*) from quest_done where bRead = 0"));

	odbc::execute_result* pResult = m_pdb->sql_query(pStream);

	if(!pResult)
	{
		bRet = FALSE;
		goto exit;
	}

	nNum = pResult->get_row_count() ;

	while(nNum)
	{
		dw_num = (DWORD)(*pResult)[0].get_long();

		nNum--;
		pResult->next_row();
	}

exit:
	m_pdb->return_io(pStream);
	m_pdb->free_result_query(pResult);

	return bRet;
}
