#ifndef COMBINATIONDLG
#define COMBINATIONDLG
#include "afxwin.h"
#include "resource.h"
#include "CombinationDB.h"
#include "list"
#include "Combination_Define.h"

using namespace std;

struct tag_Param
{
	CombinationDlg* pDlg;
	DWORD		dw_old_role_id;
	DWORD		dw_role_max_id;
}; 

class Event
{
public:
	Event() { m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); ASSERT(m_hEvent != NULL); }
	Event(BOOL bManual, BOOL bInitState) { m_hEvent = CreateEvent(NULL, bManual, bInitState, NULL); ASSERT(m_hEvent != NULL); }
	~Event() { CloseHandle(m_hEvent); }

	VOID Set() { SetEvent(m_hEvent); }
	VOID ReSet() { ResetEvent(m_hEvent); }
	VOID Pulse() { PulseEvent(m_hEvent); }
	VOID Wait()	{ WaitForSingleObject(m_hEvent, INFINITE); }

private:
	HANDLE	m_hEvent;
};

// CombinationDlg 对话框

class CombinationDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinationDlg)

public:
	CombinationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CombinationDlg();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton3();

	MAP_ROLE_NAME& get_map_role_name() { return m_map_role_name; }

	VOID InitCombinData();			// 初始化合并数据库数据

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_main_db_ip;				// 主数据库ip
	CEdit m_main_db_port;			// 主数据库port
	CEdit m_main_db_user;			// 主数据库用户名
	CEdit m_main_db_psd;			// 主数据库密码
	CEdit m_main_db_name;			// 主数据库名称

	CEdit m_combin_db_ip;			// 被合并数据库ip
	CEdit m_combin_db_port;			// 被合并数据库port
	CEdit m_combin_db_user;			// 被合并数据库用户名
	CEdit m_combin_db_psd;			// 被合并数据库密码
	CEdit m_combin_db_name;			// 被合并数据库名称
	CString changename;
	CListBox m_message_lb;			// 消息输出

	CButton m_combin_bt;			// 合并按钮


private:
	VOID InitControl();

	VOID ClearCombinData();			// 清理合并数据库数据
		
	BOOL GetMaxRoleID();			// 获取两边数据库最大角色id

	BOOL GetMaxBankID();			// 获取钱庄最大ID

	BOOL GetMaxPaimaiID();			// 获取拍卖最大ID

	BOOL GetMaxItemID();			// 获取物品最大ID

	BOOL GetMaxMailID();			// 获取邮件最大ID

	BOOL GetMaxPetID();				// 获取宠物最大ID

	BOOL GetMaxGuerdonID();			// 获取悬赏最大ID

	BOOL GetMaxAccountID();			// 获取account最大ID

	VOID ChangeAccountCommon();		// 修改角色共用数据

	VOID ChangeRoleID(DWORD dw_role_max_id);		// 改变角色id

	VOID ChangeRoleName();							// 修改角色名称

	VOID ChangeBankID(DWORD dw_bank_max_id);		// 修改钱庄id

	VOID ChangeItemID(INT64 n64_item_max_id);		// 修改物品id

	VOID ChangeGuildID();							// 修改帮会id

	VOID ChangeGuildIDNew();						

	VOID ChangeMailID();							// 修改邮件id

	VOID ChangePaiMaiID();							// 修改拍卖id

	VOID ChangePetID();								// 修改宠物id

	VOID ChangeGuerdonID();							// 修改悬赏id

	VOID InitThread();

	VOID CleanAccountCommon();

	VOID CleanRoleData();

	VOID ChangeGuildSignID();

	VOID ChangeMasterID();

	VOID ChangeGuerdonQuestID();

	VOID ChangeMailItemID();

	VOID CheckAccountData();

	VOID ChangeAccountCommonID();

	VOID ChangeRoleDataAccountID();

	VOID InsertAccount();

	VOID InsertThirdAccount();

	VOID CleanAccountData();

public:
	INT		n_event_num;

	Event	h_event;
	static HANDLE	h_thread[19];
	static tag_Param* pParam;
	LIST_ACHIEVEMENT& get_list_achievement() { return m_list_achievement; }
	LIST_ACHIEVEMENT_PROCESS& get_list_achievement_process() { return m_list_achievement_process; }
	LIST_BLACK&	get_list_black() { return m_list_combin_black; }
	LIST_BUFFER& get_list_buffer() { return m_list_buffer; }
	LIST_ENEMY& get_list_enemy() { return m_list_enemy; }
	LIST_FRIEND& get_list_friend() { return m_list_friend; }
	LIST_FRIENDSHIP& get_list_friend_ship() { return m_list_friendship; }
	LIST_GUILD& get_list_guild() { return m_list_guild; }
	LIST_GUILD_COMMERCE& get_list_commerce() { return m_list_guild_commerce; }
	LIST_GUILD_DELATE& get_list_delate() { return m_list_guild_delate; }
	LIST_GUILD_MEMBER& get_list_member() { return m_list_guild_member; }
	LIST_ITEM& get_list_item() { return m_list_item; }
	LIST_ITEM_CD& get_list_item_cd() { return m_list_item_cd; }
	LIST_MAIL& get_list_mail() { return m_list_mail; }
	LIST_MAP_LIMIT& get_list_map_limit() { return m_list_map_limit; }
	LIST_MASTER& get_list_master() { return m_list_master; }
	LIST_PAIMAI& get_list_paimai() { return m_list_paimai; }
	LIST_PET& get_list_pet() { return m_list_pet; }
	LIST_PET_SNS& get_list_pet_sns() { return m_list_pet_sns; }
	LIST_QUEST& get_list_quest() { return m_list_quest; }
	LIST_QUEST_DONE& get_list_quest_done() { return m_list_quest_done; }
	LIST_GUERDON_QUEST& get_list_guerdon_quest() { return m_list_guerdon_quest; }
	LIST_BANK& get_list_bank() { return m_list_bank; }
	LIST_ROLE_SKILL& get_list_role_skill() { return m_list_role_skill; }
	LIST_TITLE& get_list_title() { return m_list_title; }
	LIST_ACCOUNT_DATA& get_list_no_exist_account() { return m_list_no_exist_account; }
	LIST_ACCOUNT_DATA& get_list_change_account() { return m_list_change_account; }
	
	MAP_THIRD_ACCOUNT_DATA& get_map_no_exist_third_account() {return m_map_no_exist_third_account;}
	MAP_THIRD_ACCOUNT_DATA& get_map_change_third_account() {return m_map_change_third_account;}
private:
	CombinationDB* m_pMain_db;		// 主数据库db连接

	CombinationDB* m_pCombin_db;	// 合并数据库db连接

	CombinationDB* m_pMainAccount_db; //主accountdb

	CombinationDB* m_pCombinAccount_db;	// 合并accountdb

	MAP_ROLE_NAME	m_map_role_name;	// 玩家名称列表

	MAP_ACCOUNT_COMMON m_map_main_account_common;

	MAP_ACCOUNT_COMMON m_map_com_account_common;

	LIST_ACHIEVEMENT m_list_achievement;	// 合并数据库称号列表

	LIST_ACHIEVEMENT_PROCESS m_list_achievement_process;	// 合并数据库称号进度列表

	LIST_BLACK		m_list_combin_black;	// 合并数据库仇恨列表

	LIST_BUFFER		m_list_buffer;			// 合并数据库buffer列表

	LIST_ENEMY		m_list_enemy;			// 合并数据库仇人列表

	LIST_FRIEND		m_list_friend;			// 合并数据库好友列表

	LIST_FRIENDSHIP m_list_friendship;		// 合并数据库好友库列表

	LIST_GUILD		m_list_guild;			// 合并数据库帮会列表

	LIST_GUILD_COMMERCE m_list_guild_commerce;	// 合并数据库帮会跑商

	LIST_GUILD_DELATE	m_list_guild_delate;	// 合并数据库帮会弹劾

	LIST_GUILD_MEMBER	m_list_guild_member;	// 合并数据库帮会成员

	LIST_GUILD_UPGRADE	m_list_guild_upgrade;	// 合并数据库帮会建筑

	LIST_ITEM			m_list_item;			// 合并数据库物品

	LIST_ITEM_CD		m_list_item_cd;			// 合并数据库物品CD

	LIST_MAIL			m_list_mail;			// 合并数据库邮件

	LIST_MAP_LIMIT		m_list_map_limit;		// 合并数据库地图限制
	LIST_INTS_PROCESS		m_list_inst_process;		// 副本进度

	LIST_ROLE_REWARD_DATA m_list_role_reward;	//角色奖励信息 gx add

	LIST_ROLE_VCARD_DATA m_list_role_vcard;		//角色名帖信息

	LIST_MOUNT_DATA	m_list_role_mount_data;		//玩家坐骑信息

	LIST_MASTER			m_list_master;			// 合并数据库师徒关系

	LIST_PAIMAI			m_list_paimai;			// 合并数据库拍卖行

	LIST_PET			m_list_pet;				// 合并数据库宠物

	LIST_PET_SKILL		m_list_pet_skill;		// 合并数据库宠物技能

	LIST_PET_SNS		m_list_pet_sns;			// 合并数据库宠物sns

	LIST_QUEST			m_list_quest;			// 合并数据库任务

	LIST_QUEST_DONE		m_list_quest_done;		// 合并数据库任务完成

	LIST_ROLE_DATA		m_list_role_data;		// 合并数据库人物数据

	LIST_ROLE_SKILL		m_list_role_skill;		// 合并数据库人物技能

	LIST_TITLE			m_list_title;			// 合并数据库称号

	LIST_BANK			m_list_bank;			// 合并数据库钱庄

	LIST_GUERDON_QUEST	m_list_guerdon_quest;	// 合并数据库悬赏

	MAP_ROLE_NAME_CRC	m_map_role_name_crc;	// 主数据库角色名称crc

	MAP_GUILD_ID		m_map_guild_id;		// 主数据库帮会

	MAP_ROLE_ID			m_map_role_id;		// 角色ID对照表

	MAP_ITEM_ID			m_map_item_id;		// 物品ID对照表

	MAP_BANK_ID			m_map_bank_id;		// 钱庄ID对照表

	MAP_GUILD_ID		m_map_guild_id_pair;	// 帮会ID对照表

	MAP_MAIL_ID			m_map_mail_id;			// 邮件ID对照表

	MAP_PAIMAI_ID		m_map_paimai_id;		// 拍卖ID对照表

	MAP_PET_ID			m_map_pet_id;			// 宠物ID对照表
/**/
	LIST_GUILD_KILL_BOSS m_list_guild_kill;
	LIST_GUILD_WAR_HISTORY m_list_guild_war_history;
	LIST_GUILD_PLANT		m_list_guild_plant;

	//LIST_XUANSHANG		m_list_xuanshang;		// 合并数据库悬赏

	LIST_ACCOUNT_DATA	m_list_combin_account;		// 合并数据库account数据
	LIST_ACCOUNT_DATA   m_list_no_exist_account;	// 主库中不存在的account数据
	LIST_ACCOUNT_DATA   m_list_change_account;		// 需要转换的account数据

	/*gx add third_account 合并用*/
	MAP_THIRD_ACCOUNT_DATA m_map_combin_third_account;//合并数据库的third数据
	MAP_THIRD_ACCOUNT_DATA m_map_no_exist_third_account;//主库中不存在的third数据
	MAP_THIRD_ACCOUNT_DATA m_map_change_third_account;//需要转换的third数据
	/*end*/

	DWORD				dw_role_max_id;
	DWORD				dw_bank_max_id;
	DWORD				dw_paimai_max_id;
	INT64				n64_item_max_id;
	DWORD				dw_mail_max_id;
	DWORD				dw_pet_max_id;
	DWORD				dw_guerdon_max_id;
	DWORD				dw_account_max_id;
protected:
	virtual void OnCancel();
public:
	BOOL m_bArea;
	BOOL m_bThirdAccount;//是否依据第三方平台账号合并
	CStatic m_process;
	CEdit m_main_account_ip;
	CEdit m_main_account_port;
	CEdit m_main_account_user;
	CEdit m_main_account_psd;
	CEdit m_main_account_dbname;
	CEdit m_combin_account_ip;
	CEdit m_combin_account_port;
	CEdit m_combin_account_user;
	CEdit m_combin_account_psd;
	CEdit m_combin_account_dbname;
	CEdit m_ChangeNameEd;
};

UINT WINAPI thread_com(LPVOID p);
UINT WINAPI	thread_achievement(LPVOID p);
UINT WINAPI thread_achievement_process(LPVOID p);
UINT WINAPI thread_black(LPVOID p);
UINT WINAPI thread_buffer(LPVOID p);
UINT WINAPI thread_enemy(LPVOID p);
UINT WINAPI thread_friend(LPVOID p);
UINT WINAPI thread_friend_ship(LPVOID p);
UINT WINAPI thread_guild(LPVOID p);
UINT WINAPI thread_guild_commerce(LPVOID p);
UINT WINAPI thread_guild_delate(LPVOID p);
UINT WINAPI thread_guild_member(LPVOID p);
UINT WINAPI thread_item(LPVOID p);
UINT WINAPI thread_mail(LPVOID p);
UINT WINAPI thread_map_limit(LPVOID p);
UINT WINAPI thread_master(LPVOID p);
UINT WINAPI thread_paimai(LPVOID p);
UINT WINAPI thread_pet(LPVOID p);
UINT WINAPI thread_quest(LPVOID p);
UINT WINAPI thread_role_skill(LPVOID p);

#endif
