#ifndef COMBINATIONDEFINE
#define COMBINATIONDEFINE

#include <list>
#include <map>
#include <vector>

using namespace std;

struct tag_black_list
{
	DWORD			dwRoleID;
	DWORD			dwBlackID;
};

struct tag_buffer_list : public s_buff_save
{
	DWORD		dwRoleID;
	vector<DWORD> list_skill_id;
};

struct tag_enemy_list
{
	DWORD			dwRoleID;
	DWORD			dwEnemyID;
};


struct tag_friend_list : public s_friend_save
{
	DWORD			dwRoleID;
};

struct tag_friendship_list : public s_friendship_save
{
	DWORD			dwRoleID;
};

struct tag_guild_commerce : public s_guild_commerce_info
{
	DWORD			dwGuildID;
};

struct tag_item_cd
{
	DWORD					dw_role_id;
	INT						n_num;
	vector<tagCDTime>		list_cd_time;
};

struct tag_load_mail : public s_load_mail
{
	TCHAR sz_content_[Max_Mail_Content+1]; 
};

struct tag_map_limit : public s_enter_map_limit
{
	DWORD		dw_role_id;
};

struct tag_ints_process : public s_inst_process
{
	DWORD		dw_role_id;
};



struct tag_master
{
	DWORD	dw_master;					// 师傅id
	DWORD	dw_graduates;				// 出师人数
	DWORD	dw_master_moral;			// 师德值
	BYTE	b_show_in_panel;			// 是否在师徒榜中显示
	BYTE	by_number;					// 徒弟个数
	vector<DWORD>	list_role;				// 徒弟id
};

struct tag_pet_skill : public s_db_pet_skill
{
	DWORD	dw_pet_id_;
};

struct tag_quest : public tagQuestSave
{
	DWORD	dw_role_id;
};

struct tag_quest_done : public tagQuestDoneSave
{
	DWORD	dw_role_id;
};

struct tag_role_data : public s_role_data_load
{
	DWORD	dw_role_id;
	DWORD	dw_account_id;
	BOOL	b_remove;
	BOOL	b_change_name;
	tagDWORDTime	dwDelGuardTime;
	tagDWORDTime	dwChangeNameTime;
};

struct tag_role_skill : public s_skill_save
{
	DWORD	dw_role_id;
};

struct tag_title : public s_title_save
{
	DWORD	dw_role_id;
};

struct tag_achievement : public s_achievement_complate_save
{
	DWORD	dw_role_id;
};

struct tag_achievement_process : public s_achievement_process_save
{
	DWORD	dw_role_id;
};
//gx add
struct tag_reward_data
{
	DWORD dw_role_id;
	tagRewardData	st_role_reward_data[RF_NUM][MAX_REWARD_NUMBER];
};

struct tag_account_common : public s_account_common
{
	DWORD dw_account_id;
	CHAR  sz_account_name[X_SHORT_NAME];
};

struct tag_account_data
{
	DWORD	dw_account_id;
	CHAR	sz_account_name[X_SHORT_NAME];
	CHAR	sz_password[50];
	DWORD	dw_change_account_id;
};
struct tag_third_key//第三方平台Map键值
{
	INT   n_thirdtype;//第三方类型
	DWORD dw_thirdid;//平台Id
	bool operator <(const tag_third_key& other)const
	{
		if (n_thirdtype < other.n_thirdtype)
		{
			return true;
		}
		else if (n_thirdtype == other.n_thirdtype)
		{
			return dw_thirdid < other.dw_thirdid;
		}
		return false;
	}
};
//第三方平台账号 gx add
struct tag_third_account_data
{
	DWORD dw_account_id;
	CHAR  sz_password[50];
	INT   n_thirdtype;//第三方类型
	DWORD dw_thirdid;//平台Id
	DWORD	dw_change_account_id;
	CHAR	sz_account_name[X_SHORT_NAME];
	CHAR	sz_account_password[50];
	DWORD   dw_forbid_mask;
	CHAR	sz_account_ip[X_IP_LEN];
};
//增加坐骑表合并 gx add 2013.11.11
struct tag_mount_data: public s_mounts_save
{
	DWORD	dw_role_id;
};
typedef std::list<tag_achievement*> LIST_ACHIEVEMENT;

typedef std::list<tag_achievement_process*> LIST_ACHIEVEMENT_PROCESS;

typedef std::list<tag_black_list*> LIST_BLACK;

typedef std::map<DWORD, tstring> MAP_ROLE_NAME;

typedef std::map<DWORD, DWORD> MAP_ROLE_ID;

typedef std::map<INT64, INT64> MAP_ITEM_ID;

typedef std::map<DWORD, DWORD> MAP_BANK_ID;

typedef std::map<DWORD, DWORD> MAP_MAIL_ID;

typedef std::map<DWORD, DWORD> MAP_PAIMAI_ID;

typedef std::map<DWORD, DWORD> MAP_PET_ID;

typedef std::map<DWORD, DWORD>	MAP_ROLE_NAME_CRC;

typedef std::map<DWORD, DWORD>	MAP_GUILD_ID;

typedef std::list<tag_buffer_list*> LIST_BUFFER;

typedef std::list<tag_enemy_list*>	LIST_ENEMY;

typedef std::list<tag_friend_list*>	LIST_FRIEND;

typedef std::list<tag_friendship_list*> LIST_FRIENDSHIP;

typedef std::list<s_guild_load*>	LIST_GUILD;

typedef std::list<s_guild_kill_boss*> LIST_GUILD_KILL_BOSS;

typedef std::list<tagGuildWarHistory*> LIST_GUILD_WAR_HISTORY;

typedef std::list<s_guild_plant*> LIST_GUILD_PLANT;

typedef std::list<tag_guild_commerce*> LIST_GUILD_COMMERCE;

typedef std::list<s_guild_delate_load*> LIST_GUILD_DELATE;

typedef std::list<s_guild_member_load*> LIST_GUILD_MEMBER;

typedef std::list<s_facilities_load*> LIST_GUILD_UPGRADE;

typedef std::list<tagItem*> LIST_ITEM;

typedef std::list<tag_item_cd*> LIST_ITEM_CD;

typedef std::list<tag_load_mail*> LIST_MAIL;

typedef std::list<tag_map_limit*> LIST_MAP_LIMIT;

typedef std::list<tag_ints_process*> LIST_INTS_PROCESS;

typedef std::list<tag_master*> LIST_MASTER;

typedef std::list<tag_paimai*> LIST_PAIMAI;

typedef std::list<s_db_pet_att*> LIST_PET;

typedef std::list<tag_pet_skill*> LIST_PET_SKILL;

typedef std::list<tagPetSNSInfo*> LIST_PET_SNS;

typedef std::list<tag_quest*> LIST_QUEST;

typedef std::list<tag_quest_done*> LIST_QUEST_DONE;

typedef std::list<tag_role_data*> LIST_ROLE_DATA;

typedef std::list<tag_role_skill*> LIST_ROLE_SKILL;

typedef std::list<tag_title*> LIST_TITLE;

typedef std::list<tag_bank*> LIST_BANK;

typedef std::list<guerdon_quest*> LIST_GUERDON_QUEST;

typedef std::map<DWORD, tag_account_common*> MAP_ACCOUNT_COMMON;

//typedef std::list<tagXuanShangQuestLoad*> LIST_XUANSHANG;

typedef std::list<tag_account_data*> LIST_ACCOUNT_DATA;

typedef std::map<tag_third_key,tag_third_account_data*> MAP_THIRD_ACCOUNT_DATA;//gx add 第三方平台链表

typedef std::list<DWORD>	LIST_ACCOUNT_ID;

typedef std::list<tag_reward_data*> LIST_ROLE_REWARD_DATA;//gx add 玩家奖励数据信息

typedef std::list<tagVCardData*> LIST_ROLE_VCARD_DATA;//add 玩家名帖信息

typedef std::list<tag_mount_data*> LIST_MOUNT_DATA;//gx add 坐骑数据

#endif