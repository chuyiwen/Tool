#ifndef COMBINATIONDB
#define COMBINATIONDB

#include "Combination_Define.h"
class CombinationDlg;

class CombinationDB
{
public:
	CombinationDB(void);
	~CombinationDB(void);

	BOOL InitDB(LPCTSTR ip, LPCTSTR port, LPCTSTR user, LPCTSTR psd, LPCTSTR name, CombinationDlg* pCombin_Dlg);

	VOID ShutDown();

	BOOL InitRoleID(MAP_ROLE_ID& map_role_id, DWORD& dw_role_max_id);
	BOOL InitItemID(MAP_ITEM_ID& map_item_id, INT64& dw_item_max_id);
	BOOL InitBankID(MAP_BANK_ID& map_bank_id, DWORD& dw_bank_max_id);
	BOOL InitMailID(MAP_MAIL_ID& map_mail_id, DWORD& dw_mail_max_id);
	BOOL InitPetID(MAP_PET_ID& map_pet_id,	DWORD& dw_pet_max_id);
	BOOL InitPaimaiID(MAP_PAIMAI_ID& map_paimai_id, DWORD& dw_paimai_max_id);
	BOOL InitRoleName(MAP_ROLE_NAME& map_role_name);
	BOOL InitRoleNameCrc(MAP_ROLE_NAME_CRC& list_role_name_crc);
	BOOL InitGuildID(MAP_GUILD_ID& list_guild_id);
	BOOL InitAccountCommon(MAP_ACCOUNT_COMMON& map_account_common);
	BOOL InitAchievement(LIST_ACHIEVEMENT& list_achievement);
	BOOL InitAchievementProcess(LIST_ACHIEVEMENT_PROCESS& list_achievement_process);
	BOOL InitBlackList(LIST_BLACK& list_black);
	BOOL InitBufferList(LIST_BUFFER& list_buffer);
	BOOL InitEnemyList(LIST_ENEMY& list_enemy);
	BOOL InitFriendList(LIST_FRIEND& list_friend);
	BOOL InitFriendShipList(LIST_FRIENDSHIP& list_friendship);
	BOOL InitGuildList(LIST_GUILD& list_guild);
	BOOL InitGuildCommerceList(LIST_GUILD_COMMERCE& list_guild_commerce);
	BOOL InitGuildDelateList(LIST_GUILD_DELATE& list_guild_delate);
	BOOL InitGuildMemberList(LIST_GUILD_MEMBER& list_guild_member);
	BOOL InitGuildUpgradeList(LIST_GUILD_UPGRADE& list_guild_upgrade);
	BOOL InitItem(LIST_ITEM& list_item, DWORD dw_read = 0);
	BOOL InitItemCD(LIST_ITEM_CD& list_item_cd);
	BOOL InitMail(LIST_MAIL& list_mail);
	BOOL InitMapLimit(LIST_MAP_LIMIT& list_map_limit);
	BOOL InitMaster(LIST_MASTER& list_master);
	BOOL InitPaiMai(LIST_PAIMAI& list_paimai);
	BOOL InitPet(LIST_PET& list_pet);
	BOOL InitPetSkill(LIST_PET_SKILL& list_pet_skill);
	BOOL InitPetSns(LIST_PET_SNS& list_pet_sns);
	BOOL InitQuest(LIST_QUEST& list_quest);
	BOOL InitQuestDone(LIST_QUEST_DONE& list_quest_done, DWORD dw_read_num = 0);
	BOOL InitRoleData(LIST_ROLE_DATA& list_role_data);
	BOOL InitRoleSkill(LIST_ROLE_SKILL& list_role_skill);
	BOOL InitTitle(LIST_TITLE& list_title);
	BOOL InitBank(LIST_BANK& list_bank);
	BOOL InitGuerdonQuest(LIST_GUERDON_QUEST& list_guerdon_quest);
	BOOL InitRoleRewardData(LIST_ROLE_REWARD_DATA& list_reward_data);
	BOOL InitRoleVCardData(LIST_ROLE_VCARD_DATA& list_vcard_data);
	BOOL InitRoleMountData(LIST_MOUNT_DATA& list_mount_data);
	//BOOL InitXuanShang(LIST_XUANSHANG& list_xuanshang);

	BOOL InitAccount(LIST_ACCOUNT_DATA&	list_main_account);
	BOOL InitThirdAccount(MAP_THIRD_ACCOUNT_DATA& map_main_account);
	BOOL GetThirdAccount_Name(tag_third_account_data* pThirdAccountData);
	VOID CheckAccount(tag_account_data* pAccountData, DWORD& dw_account_max_id);
	VOID CheckThirdAccount(tag_third_account_data* pThirdAccountData,DWORD& dw_account_max_id);//
	BOOL ChangeAccountCommonIndex();
	BOOL ChangeAccountCommonID(tag_account_data* pAccountData);
	BOOL ChangeAccountCommonID(tag_third_account_data* pThirdAccountData);
	BOOL AddRoleDataChange();
	BOOL ChangeRoleDataAccountID(tag_account_data* pAccountData);
	BOOL ChangeRoleDataAccountID(tag_third_account_data* pThirdAccountData);
	BOOL InsertAccount(tag_account_data* pAccountData);
	BOOL InsertAccount(tag_third_account_data* pAccountThird);
	BOOL InsertThirdAccount(tag_third_account_data* pAccountThird);
	BOOL UpadteAchievement(MAP_ROLE_ID& map_role_id);
	BOOL UpdateAchievementProcess(MAP_ROLE_ID &map_role_id);
	BOOL UpdateRoleReward(MAP_ROLE_ID &map_role_id);//
	BOOL UpdateRoleVCard(MAP_ROLE_ID &map_role_id);//更新玩家名帖表
	BOOL UpdateRoleMount(MAP_ROLE_ID &map_role_id);//更新玩家坐骑表
	BOOL UpdateBlack(MAP_ROLE_ID &map_role_id);
	BOOL UpdateBuff(MAP_ROLE_ID& map_role_id);
	BOOL UpdateEnemy(MAP_ROLE_ID& map_role_id);
	BOOL UpdateFriend(MAP_ROLE_ID& map_role_id);
	BOOL UpdateFriendShip(MAP_ROLE_ID& map_role_id);
	BOOL UpdateGuild(MAP_ROLE_ID& map_role_id);
	BOOL UpdateGuildMember(MAP_ROLE_ID& map_role_id);
	BOOL UpdateItem(MAP_ROLE_ID& map_role_id);
	BOOL UpdataItemCD(MAP_ROLE_ID& map_role_id);
	BOOL UpdateMail(MAP_ROLE_ID& map_role_id);
	BOOL UpdateMapLimit(MAP_ROLE_ID& map_role_id);
	BOOL UpdateMasterPrentice(MAP_ROLE_ID& map_role_id);
	BOOL UpdatePaimai(MAP_ROLE_ID& map_role_id);
	BOOL UpdateBank(MAP_ROLE_ID& map_role_id);
	BOOL UpdatePet(MAP_ROLE_ID& map_role_id);
	BOOL UpdatePetSNS(MAP_ROLE_ID& map_role_id);
	BOOL UpdateQuest(MAP_ROLE_ID& map_role_id);
	BOOL UpdateQuestDone(MAP_ROLE_ID& map_role_id);
	BOOL UpdateGuerdonQuest(MAP_ROLE_ID& map_role_id);
	BOOL UpdateRoleSkill(MAP_ROLE_ID& map_role_id);
	BOOL UpdateRoleTitle(MAP_ROLE_ID& map_role_id);
	BOOL UpdateRoleData(MAP_ROLE_ID& map_role_id);
	BOOL UpdateGuildSign(LIST_GUILD& list_guild);
	BOOL UpdateMaster(LIST_MASTER& list_master);
	BOOL UpdateGuerdonQuest(LIST_GUERDON_QUEST& list_guerdon_quest);
	BOOL UpdateRoleName(LIST_ROLE_DATA& list_role_data);
	BOOL UpdateBuff(MAP_ITEM_ID& map_item_id);
	BOOL UpdateMail(LIST_MAIL& list_mail);
	BOOL UpdateBankID(MAP_BANK_ID& map_bank_id);
	BOOL UpdateMailID(MAP_MAIL_ID& map_mail_id);
	BOOL UpdateGuildID(LIST_GUILD& list_guild);
	BOOL UpdateRoleGuildID(MAP_GUILD_ID& map_guild_id);
	BOOL UpdateGuildMemberID(MAP_GUILD_ID& map_guild_id);
	BOOL UpdateGuildGradeID(MAP_GUILD_ID& map_guild_id);
	BOOL UpdatePaimaiID(MAP_PAIMAI_ID& map_paimai_id);
	BOOL UpdatePetID(MAP_PET_ID& map_pet_id);
	BOOL UpdateItemID(MAP_ITEM_ID& map_item_id);

	BOOL GetMaxRoleID(DWORD&	dw_role_max_id);
	BOOL GetMaxBankID(DWORD&	dw_bank_max_id);
	BOOL GetMaxPaimaiID(DWORD&	dw_paimai_max_id);
	BOOL GetMaxItemID(INT64&	n64_item_max_id, LPCSTR sz_table_name);
	BOOL GetMaxMailID(DWORD&	dw_mail_max_id);
	BOOL GetMaxPetID(DWORD&		dw_pet_max_id);
	BOOL GetMaxGuerdonID(DWORD& dw_guerdon_max_id);
	BOOL GetMaxAccountID(DWORD& dw_account_max_id);

	BOOL InsertAccountCommon(MAP_ACCOUNT_COMMON& map_main_account_common, BOOL bDel = FALSE);
	BOOL InsertAchievement(LIST_ACHIEVEMENT& list_achievement);
	BOOL InsertAchievement(LIST_ACHIEVEMENT_PROCESS& list_achievement_process);
	BOOL InsertBlackList(LIST_BLACK& list_black);
	BOOL InsertBufferList(LIST_BUFFER& list_buffer);
	BOOL InsertEnemyList(LIST_ENEMY& list_enemy);
	BOOL InsertFriendList(LIST_FRIEND& list_friend);
	BOOL InsertFriendShipList(LIST_FRIENDSHIP& list_friend_ship);
	BOOL InsertGuildList(LIST_GUILD& list_guild);
	BOOL InsertGuildCommerceList(LIST_GUILD_COMMERCE& list_guild_commerce);
	BOOL InsertGuildMemberList(LIST_GUILD_MEMBER& list_guild_member);
	BOOL InsertGuildUpgradeList(LIST_GUILD_UPGRADE& list_guild_upgrade);
	BOOL InsertGuildDelateList(LIST_GUILD_DELATE& list_guild_delate);
	BOOL InsertItem(LIST_ITEM& list_item);
	BOOL InsertEquip(LIST_ITEM& list_item);
	BOOL InsertItemCD(LIST_ITEM_CD& list_item_cd);
	BOOL InsertMail(LIST_MAIL& list_mail);
	BOOL InsertMapLimit(LIST_MAP_LIMIT& list_map_limit);
	BOOL InsertMaster(LIST_MASTER& list_master);
	BOOL InsertPaiMai(LIST_PAIMAI& list_paimai);
	BOOL InsertPet(LIST_PET& list_pet);
	BOOL InsertPetSkill(LIST_PET_SKILL& list_pet_skill);
	BOOL InsertPetSns(LIST_PET_SNS& list_pet_sns);
	BOOL InsertQuest(LIST_QUEST& list_quest);
	BOOL InsertQuestDone(LIST_QUEST_DONE& list_quest_done);
	BOOL InsertRoleData(LIST_ROLE_DATA& list_role_data);
	BOOL InsertRoleSkill(LIST_ROLE_SKILL& list_role_skill);
	BOOL InsertTitle(LIST_TITLE& list_title);
	BOOL InsertBank(LIST_BANK& list_bank);
	BOOL InsertGuerdon(LIST_GUERDON_QUEST& list_guerdon);
	//BOOL InsertXuanShang(LIST_XUANSHANG& list_xuanshang);
public:
	BOOL UpdateInstanceProcess(MAP_ROLE_ID& map_role_id);
	BOOL InitInstanceProcess(LIST_INTS_PROCESS& list_inst_process);
	BOOL InsertInstProcess(LIST_INTS_PROCESS& list_inst_process);

	BOOL InsertRoleRewardData(LIST_ROLE_REWARD_DATA& list_reward_data);//gx add
	BOOL InsertRoleVCradData(LIST_ROLE_VCARD_DATA& list_role_vcrad);//add
	BOOL InsertRoleMountData(LIST_MOUNT_DATA& list_mount_data);//gx add

	BOOL UpdateGuildKillBoss(MAP_GUILD_ID& map_guild_id);
	BOOL InitGuildKillBoss(LIST_GUILD_KILL_BOSS& list_guild_kill);
	BOOL InsertGuildKillBoss(LIST_GUILD_KILL_BOSS& list_guild_kill);

//	BOOL UpdateGuildWarHistory(MAP_ROLE_ID& map_role_id, MAP_GUILD_ID& map_guild_id);
// 	BOOL InitGuildWarHistory(LIST_GUILD_WAR_HISTORY& list_guild_war_histroy);
// 	BOOL InsertGuildWarHistory(LIST_GUILD_WAR_HISTORY& list_guild_war_histroy);

	BOOL UpdateGuildPlant(MAP_GUILD_ID& map_guild_id);
	BOOL InitGuildPlant(LIST_GUILD_PLANT& list_guild_plant);
	BOOL InsertGuildPlant(LIST_GUILD_PLANT& list_guild_plant);
	/* TODO: auto_paimai && serial_reward 未操作*/
public:
	BOOL AddItemRead();
	BOOL ChangeItemRead(INT64 n64Serial);
	BOOL AddQuestDoneRead();
	BOOL ChangeQuestDoneRead(DWORD dw_role_id, DWORD dw_quest_id);
	BOOL GetItemNotReadNum(DWORD& dw_num);
	BOOL GetQuestNotReadNum(DWORD& dw_num);
private:
	odbc::db_interface* m_pdb;

	CombinationDlg*		m_pCombin_Dlg;
};
#endif
