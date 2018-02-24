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

// CombinationDlg �Ի���

class CombinationDlg : public CDialog
{
	DECLARE_DYNAMIC(CombinationDlg)

public:
	CombinationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CombinationDlg();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton3();

	MAP_ROLE_NAME& get_map_role_name() { return m_map_role_name; }

	VOID InitCombinData();			// ��ʼ���ϲ����ݿ�����

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_main_db_ip;				// �����ݿ�ip
	CEdit m_main_db_port;			// �����ݿ�port
	CEdit m_main_db_user;			// �����ݿ��û���
	CEdit m_main_db_psd;			// �����ݿ�����
	CEdit m_main_db_name;			// �����ݿ�����

	CEdit m_combin_db_ip;			// ���ϲ����ݿ�ip
	CEdit m_combin_db_port;			// ���ϲ����ݿ�port
	CEdit m_combin_db_user;			// ���ϲ����ݿ��û���
	CEdit m_combin_db_psd;			// ���ϲ����ݿ�����
	CEdit m_combin_db_name;			// ���ϲ����ݿ�����
	CString changename;
	CListBox m_message_lb;			// ��Ϣ���

	CButton m_combin_bt;			// �ϲ���ť


private:
	VOID InitControl();

	VOID ClearCombinData();			// ����ϲ����ݿ�����
		
	BOOL GetMaxRoleID();			// ��ȡ�������ݿ�����ɫid

	BOOL GetMaxBankID();			// ��ȡǮׯ���ID

	BOOL GetMaxPaimaiID();			// ��ȡ�������ID

	BOOL GetMaxItemID();			// ��ȡ��Ʒ���ID

	BOOL GetMaxMailID();			// ��ȡ�ʼ����ID

	BOOL GetMaxPetID();				// ��ȡ�������ID

	BOOL GetMaxGuerdonID();			// ��ȡ�������ID

	BOOL GetMaxAccountID();			// ��ȡaccount���ID

	VOID ChangeAccountCommon();		// �޸Ľ�ɫ��������

	VOID ChangeRoleID(DWORD dw_role_max_id);		// �ı��ɫid

	VOID ChangeRoleName();							// �޸Ľ�ɫ����

	VOID ChangeBankID(DWORD dw_bank_max_id);		// �޸�Ǯׯid

	VOID ChangeItemID(INT64 n64_item_max_id);		// �޸���Ʒid

	VOID ChangeGuildID();							// �޸İ��id

	VOID ChangeGuildIDNew();						

	VOID ChangeMailID();							// �޸��ʼ�id

	VOID ChangePaiMaiID();							// �޸�����id

	VOID ChangePetID();								// �޸ĳ���id

	VOID ChangeGuerdonID();							// �޸�����id

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
	CombinationDB* m_pMain_db;		// �����ݿ�db����

	CombinationDB* m_pCombin_db;	// �ϲ����ݿ�db����

	CombinationDB* m_pMainAccount_db; //��accountdb

	CombinationDB* m_pCombinAccount_db;	// �ϲ�accountdb

	MAP_ROLE_NAME	m_map_role_name;	// ��������б�

	MAP_ACCOUNT_COMMON m_map_main_account_common;

	MAP_ACCOUNT_COMMON m_map_com_account_common;

	LIST_ACHIEVEMENT m_list_achievement;	// �ϲ����ݿ�ƺ��б�

	LIST_ACHIEVEMENT_PROCESS m_list_achievement_process;	// �ϲ����ݿ�ƺŽ����б�

	LIST_BLACK		m_list_combin_black;	// �ϲ����ݿ����б�

	LIST_BUFFER		m_list_buffer;			// �ϲ����ݿ�buffer�б�

	LIST_ENEMY		m_list_enemy;			// �ϲ����ݿ�����б�

	LIST_FRIEND		m_list_friend;			// �ϲ����ݿ�����б�

	LIST_FRIENDSHIP m_list_friendship;		// �ϲ����ݿ���ѿ��б�

	LIST_GUILD		m_list_guild;			// �ϲ����ݿ����б�

	LIST_GUILD_COMMERCE m_list_guild_commerce;	// �ϲ����ݿ�������

	LIST_GUILD_DELATE	m_list_guild_delate;	// �ϲ����ݿ��ᵯ��

	LIST_GUILD_MEMBER	m_list_guild_member;	// �ϲ����ݿ����Ա

	LIST_GUILD_UPGRADE	m_list_guild_upgrade;	// �ϲ����ݿ��Ὠ��

	LIST_ITEM			m_list_item;			// �ϲ����ݿ���Ʒ

	LIST_ITEM_CD		m_list_item_cd;			// �ϲ����ݿ���ƷCD

	LIST_MAIL			m_list_mail;			// �ϲ����ݿ��ʼ�

	LIST_MAP_LIMIT		m_list_map_limit;		// �ϲ����ݿ��ͼ����
	LIST_INTS_PROCESS		m_list_inst_process;		// ��������

	LIST_ROLE_REWARD_DATA m_list_role_reward;	//��ɫ������Ϣ gx add

	LIST_ROLE_VCARD_DATA m_list_role_vcard;		//��ɫ������Ϣ

	LIST_MOUNT_DATA	m_list_role_mount_data;		//���������Ϣ

	LIST_MASTER			m_list_master;			// �ϲ����ݿ�ʦͽ��ϵ

	LIST_PAIMAI			m_list_paimai;			// �ϲ����ݿ�������

	LIST_PET			m_list_pet;				// �ϲ����ݿ����

	LIST_PET_SKILL		m_list_pet_skill;		// �ϲ����ݿ���＼��

	LIST_PET_SNS		m_list_pet_sns;			// �ϲ����ݿ����sns

	LIST_QUEST			m_list_quest;			// �ϲ����ݿ�����

	LIST_QUEST_DONE		m_list_quest_done;		// �ϲ����ݿ��������

	LIST_ROLE_DATA		m_list_role_data;		// �ϲ����ݿ���������

	LIST_ROLE_SKILL		m_list_role_skill;		// �ϲ����ݿ����＼��

	LIST_TITLE			m_list_title;			// �ϲ����ݿ�ƺ�

	LIST_BANK			m_list_bank;			// �ϲ����ݿ�Ǯׯ

	LIST_GUERDON_QUEST	m_list_guerdon_quest;	// �ϲ����ݿ�����

	MAP_ROLE_NAME_CRC	m_map_role_name_crc;	// �����ݿ��ɫ����crc

	MAP_GUILD_ID		m_map_guild_id;		// �����ݿ���

	MAP_ROLE_ID			m_map_role_id;		// ��ɫID���ձ�

	MAP_ITEM_ID			m_map_item_id;		// ��ƷID���ձ�

	MAP_BANK_ID			m_map_bank_id;		// ǮׯID���ձ�

	MAP_GUILD_ID		m_map_guild_id_pair;	// ���ID���ձ�

	MAP_MAIL_ID			m_map_mail_id;			// �ʼ�ID���ձ�

	MAP_PAIMAI_ID		m_map_paimai_id;		// ����ID���ձ�

	MAP_PET_ID			m_map_pet_id;			// ����ID���ձ�
/**/
	LIST_GUILD_KILL_BOSS m_list_guild_kill;
	LIST_GUILD_WAR_HISTORY m_list_guild_war_history;
	LIST_GUILD_PLANT		m_list_guild_plant;

	//LIST_XUANSHANG		m_list_xuanshang;		// �ϲ����ݿ�����

	LIST_ACCOUNT_DATA	m_list_combin_account;		// �ϲ����ݿ�account����
	LIST_ACCOUNT_DATA   m_list_no_exist_account;	// �����в����ڵ�account����
	LIST_ACCOUNT_DATA   m_list_change_account;		// ��Ҫת����account����

	/*gx add third_account �ϲ���*/
	MAP_THIRD_ACCOUNT_DATA m_map_combin_third_account;//�ϲ����ݿ��third����
	MAP_THIRD_ACCOUNT_DATA m_map_no_exist_third_account;//�����в����ڵ�third����
	MAP_THIRD_ACCOUNT_DATA m_map_change_third_account;//��Ҫת����third����
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
	BOOL m_bThirdAccount;//�Ƿ����ݵ�����ƽ̨�˺źϲ�
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
