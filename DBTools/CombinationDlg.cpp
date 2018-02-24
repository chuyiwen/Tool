// CombinationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBTools.h"
#include "CombinationDlg.h"


// CombinationDlg �Ի���

IMPLEMENT_DYNAMIC(CombinationDlg, CDialog)

HANDLE	CombinationDlg::h_thread[19];
tag_Param* CombinationDlg::pParam = NULL;

CombinationDlg::CombinationDlg(CWnd* pParent /*=NULL*/)
: CDialog(CombinationDlg::IDD, pParent)
{
	m_pMain_db = new CombinationDB;

	m_pCombin_db = new CombinationDB;

	m_pMainAccount_db = new CombinationDB;

	m_pCombinAccount_db = new CombinationDB;

	m_bArea = FALSE;
	m_bThirdAccount = TRUE;

	dw_role_max_id = 0;
	dw_bank_max_id = 0;
	n64_item_max_id = MIN_ITEM_SERIAL_INTERNAL;
	dw_mail_max_id = 0;
	dw_pet_max_id = MIN_PET_ID;
	dw_guerdon_max_id = 0;
	dw_account_max_id = 0;
	CombinationDlg::pParam = new tag_Param;
}

CombinationDlg::~CombinationDlg()
{
	SAFE_DELETE(m_pMain_db);
	SAFE_DELETE(m_pCombin_db);
	SAFE_DELETE(m_pMainAccount_db);
	SAFE_DELETE(m_pCombinAccount_db);
}

void CombinationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_main_db_ip);
	DDX_Control(pDX, IDC_EDIT2, m_main_db_port);
	DDX_Control(pDX, IDC_EDIT3, m_main_db_user);
	DDX_Control(pDX, IDC_EDIT4, m_main_db_psd);
	DDX_Control(pDX, IDC_EDIT66, m_main_db_name);
	DDX_Control(pDX, IDC_EDIT5, m_combin_db_ip);
	DDX_Control(pDX, IDC_EDIT6, m_combin_db_port);
	DDX_Control(pDX, IDC_EDIT67, m_combin_db_user);
	DDX_Control(pDX, IDC_EDIT68, m_combin_db_psd);
	DDX_Control(pDX, IDC_EDIT69, m_combin_db_name);
	DDX_Control(pDX, IDC_LIST2, m_message_lb);
	DDX_Control(pDX, IDC_BUTTON3, m_combin_bt);
	DDX_Control(pDX, IDC_PROCESS, m_process);
	DDX_Control(pDX, IDC_EDIT70, m_main_account_ip);
	DDX_Control(pDX, IDC_EDIT71, m_main_account_port);
	DDX_Control(pDX, IDC_EDIT72, m_main_account_user);
	DDX_Control(pDX, IDC_EDIT73, m_main_account_psd);
	DDX_Control(pDX, IDC_EDIT74, m_main_account_dbname);
	DDX_Control(pDX, IDC_EDIT7, m_combin_account_ip);
	DDX_Control(pDX, IDC_EDIT75, m_combin_account_port);
	DDX_Control(pDX, IDC_EDIT76, m_combin_account_user);
	DDX_Control(pDX, IDC_EDIT77, m_combin_account_psd);
	DDX_Control(pDX, IDC_EDIT78, m_combin_account_dbname);
	DDX_Control(pDX, IDC_EDIT10, m_ChangeNameEd);
}


BEGIN_MESSAGE_MAP(CombinationDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CombinationDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CombinationDlg ��Ϣ�������

BOOL CombinationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

VOID CombinationDlg::InitControl()
{
	m_main_db_ip.SetWindowText(_T(""));
	m_main_db_port.SetWindowText(_T(""));
	m_main_db_user.SetWindowText(_T(""));
	m_main_db_psd.SetWindowText(_T(""));
	m_main_db_name.SetWindowText(_T(""));

	m_combin_db_ip.SetWindowText(_T(""));
	m_combin_db_port.SetWindowText(_T(""));
	m_combin_db_user.SetWindowText(_T(""));
	m_combin_db_psd.SetWindowText(_T(""));
	m_combin_db_name.SetWindowText(_T(""));

	m_combin_bt.SetWindowText(_T("�ϲ�"));

	m_message_lb.ResetContent();

	CButton* checkBtn1 = (CButton*)GetDlgItem(IDC_CHECK3);
	if (!checkBtn1)
		return;
	checkBtn1->SetCheck(1);
}

void CombinationDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString ip;
	CString port;
	CString user;
	CString psd;
	CString name;

	CButton* checkBtn1 = (CButton*)GetDlgItem(IDC_CHECK2);
	if (!checkBtn1)
		return;
	m_bArea = checkBtn1->GetCheck();

	CButton* checkBtn2 = (CButton*)GetDlgItem(IDC_CHECK3);
	if (!checkBtn2)
		return;
	m_bThirdAccount = checkBtn2->GetCheck();


	m_ChangeNameEd.GetWindowText(changename);
	if(changename.Compare(_T("")) == 0)
	{
		m_message_lb.AddString(_T("�������Բ���Ϊ��"));
		return;
	}

	if(m_bArea)
	{
		m_main_account_ip.GetWindowText(ip);
		m_main_account_port.GetWindowText(port);
		m_main_account_user.GetWindowText(user);
		m_main_account_psd.GetWindowText(psd);
		m_main_account_dbname.GetWindowText(name);

		if(!m_pMainAccount_db->InitDB(ip, port, user, psd, name, this))
		{
			m_message_lb.AddString(_T("��accountdb����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��accountdb���ӳɹ�"));

		m_combin_account_ip.GetWindowText(ip);
		m_combin_account_port.GetWindowText(port);
		m_combin_account_user.GetWindowText(user);
		m_combin_account_psd.GetWindowText(psd);
		m_combin_account_dbname.GetWindowText(name);

		if(!m_pCombinAccount_db->InitDB(ip, port, user, psd, name, this))
		{
			m_message_lb.AddString(_T("�ϲ�accountdb����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ϲ�accountdb���ӳɹ�"));
	}

	m_main_db_ip.GetWindowText(ip);
	m_main_db_port.GetWindowText(port);
	m_main_db_user.GetWindowText(user);
	m_main_db_psd.GetWindowText(psd);
	m_main_db_name.GetWindowText(name);

	if(!m_pMain_db->InitDB(ip, port, user, psd, name, this))
	{
		m_message_lb.AddString(_T("�����ݿ�����ʧ��"));
		return ;
	}

	m_message_lb.AddString(_T("�����ݿ����ӳɹ�"));

	m_combin_db_ip.GetWindowText(ip);
	m_combin_db_port.GetWindowText(port);
	m_combin_db_user.GetWindowText(user);
	m_combin_db_psd.GetWindowText(psd);
	m_combin_db_name.GetWindowText(name);

	if(!m_pCombin_db->InitDB(ip, port, user, psd, name, this))
	{
		m_message_lb.AddString(_T("���ϲ����ݿ�����ʧ��"));
		return;
	}
	m_message_lb.AddString(_T("���ϲ����ݿ����ӳɹ�"));

	m_combin_bt.ShowWindow(FALSE);

	INT n_return = _beginthreadex(NULL, 0, thread_com, (LPVOID)this, 0, NULL);

	//InitCombinData();
}

UINT WINAPI thread_com(LPVOID p)
{
	CombinationDlg* pDlg = (CombinationDlg*)p;

	if(VALID_POINT(pDlg))
	{
		pDlg->InitCombinData();
	}

	_endthreadex(0);
	return 0;
}

void CombinationDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pMain_db->ShutDown();
	m_pCombin_db->ShutDown();
	ClearCombinData();
	CDialog::OnCancel();
}

VOID CombinationDlg::InitCombinData()
{
	_set_se_translator(serverdump::si_translation); 

	try
	{
#ifdef	NEW

		if(m_bArea)
		{
			if(!GetMaxAccountID())
			{
				m_message_lb.AddString(_T("��ȡ���accountIDʧ��"));
				return;
			}
			//m_bThirdAccountΪTRUE:���ݵ�����ƽ̨����account�ϲ�
			//m_bThirdAccountΪFALSE:�����Լ�ƽ̨�˺Ž���account�ϲ�
			//add
			if (m_bThirdAccount)
			{
				m_message_lb.AddString(_T("��ȡ�ϲ�������������ƽ̨�˺�����"));
				if (!m_pCombinAccount_db->InitThirdAccount(m_map_combin_third_account))
				{
					m_message_lb.AddString(_T("��ȡ�ϲ�������������ƽ̨�˺���������"));
					return;
				}
			}
			else
			{
				m_message_lb.AddString(_T("��ȡ�ϲ��������˺�����"));
				if(!m_pCombinAccount_db->InitAccount(m_list_combin_account))
				{
					m_message_lb.AddString(_T("��ȡ�ϲ��������˺���������"));
					return;
				}
			}
			

			CheckAccountData();
			m_message_lb.AddString(_T("�˺�����ɸѡ���"));

			ChangeAccountCommonID();

			m_message_lb.AddString(_T("��ҹ��ñ��˺�IDת�����"));

			ChangeRoleDataAccountID();

			m_message_lb.AddString(_T("������ݱ��˺�IDת�����"));

			if (m_bThirdAccount)
			{
				InsertThirdAccount();//����ƽ̨�˺ű�
			}

			InsertAccount();

			CleanAccountData();
			m_message_lb.AddString(_T("������ݱ��˺���Ϣ�������"));
		}
		m_message_lb.AddString(_T("��ʼ��ȡ��ɫ������ر�����id��Ϣ"));

		if(!m_pMain_db->InitRoleNameCrc(m_map_role_name_crc))
		{
			m_message_lb.AddString(_T("�����ݿ�--��ɫ����crc��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InitGuildID(m_map_guild_id))
		{
			m_message_lb.AddString(_T("�����ݿ�--���id��ʼ��ʧ��"));
			return;
		}

		if(!GetMaxRoleID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�����ɫ���ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ����ɫ���"));

		if(!GetMaxPaimaiID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�����������ʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("��ȡ����������"));

		if(!GetMaxBankID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ����Ǯׯ���ʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("��ȡ���Ǯׯ���"));

		if(!GetMaxItemID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ������Ʒ���ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ�����Ʒ���"));

		/*if(!GetMaxMailID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�����ʼ����ʧ��"));
			return;
		}*/

		//m_message_lb.AddString(_T("��ȡ����ʼ����"));

		if(!GetMaxPetID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ���������ʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("��ȡ��������"));

		if(!GetMaxGuerdonID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�������ͱ��ʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("��ȡ������ͱ��"));

		if(!m_pCombin_db->InitRoleID(m_map_role_id, dw_role_max_id))
		{
			m_message_lb.AddString(_T("��ȡ��ɫID����ʧ��"));
			return;
		}

		if(!m_pCombin_db->InitItemID(m_map_item_id, n64_item_max_id))
		{
			m_message_lb.AddString(_T("��ȡ��ƷID����ʧ��"));
			return;
		}

		if(!m_pCombin_db->InitBankID(m_map_bank_id, dw_bank_max_id))
		{
			m_message_lb.AddString(_T("��ȡǮׯID����ʧ��"));
			return;
		}

		/*if(!m_pCombin_db->InitMailID(m_map_mail_id, dw_mail_max_id))
		{
			m_message_lb.AddString(_T("��ȡ�ʼ�ID����ʧ��"));
			return;
		}*/

		if(!m_pCombin_db->InitPaimaiID(m_map_paimai_id, dw_paimai_max_id))
		{
			m_message_lb.AddString(_T("��ȡ����ID����ʧ��"));
			return;
		}

		if(!m_pCombin_db->InitPetID(m_map_pet_id, dw_pet_max_id))
		{
			m_message_lb.AddString(_T("��ȡ����ID����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������Map��ʼ�����"));

		m_message_lb.AddString(_T("��ʼ���½�ɫ������ر��role_id��Ϣ"));

		if (!m_pCombin_db->UpdateRoleReward(m_map_role_id))//add
		{
			m_message_lb.AddString(_T("���½�����ɫIDʧ��"));
			return;
		}
		if (!m_pCombin_db->UpdateRoleMount(m_map_role_id))
		{
			m_message_lb.AddString(_T("���½�ɫ����IDʧ��"));
			return;
		}
		if (!m_pCombin_db->UpdateRoleVCard(m_map_role_id))//add
		{
			m_message_lb.AddString(_T("���½�ɫ����IDʧ��"));
			return;
		}
		if(!m_pCombin_db->UpadteAchievement(m_map_role_id))
		{
			m_message_lb.AddString(_T("���³ƺŽ�ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���³ɾͽ�ɫID���"));

		if(!m_pCombin_db->UpdateAchievementProcess(m_map_role_id))
		{
			m_message_lb.AddString(_T("���³ƺŽ��Ƚ�ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���³ɾͽ��Ƚ�ɫID���"));

		if(!m_pCombin_db->UpdateBlack(m_map_role_id))
		{
			m_message_lb.AddString(_T("���º�������ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���º�������ɫID���"));

		if(!m_pCombin_db->UpdateBuff(m_map_role_id))
		{
			m_message_lb.AddString(_T("����buff��ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����buff��ɫID���"));

		if(!m_pCombin_db->UpdateEnemy(m_map_role_id))
		{
			m_message_lb.AddString(_T("���³��˽�ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���³��˽�ɫID���"));

		if(!m_pCombin_db->UpdateFriend(m_map_role_id))
		{
			m_message_lb.AddString(_T("���º��ѽ�ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���º��ѽ�ɫID���"));

		if(!m_pCombin_db->UpdateFriendShip(m_map_role_id))
		{
			m_message_lb.AddString(_T("���º��ѶȽ�ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���º��ѶȽ�ɫID���"));

		if(!m_pCombin_db->UpdateGuild(m_map_role_id))
		{
			m_message_lb.AddString(_T("���°���ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���°���ɫID���"));

		if(!m_pCombin_db->UpdateGuildMember(m_map_role_id))
		{
			m_message_lb.AddString(_T("���°���Ա��ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���°���Ա��ɫID���"));

		if(!m_pCombin_db->UpdateItem(m_map_role_id))
		{
			m_message_lb.AddString(_T("������Ʒ��ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������Ʒ��ɫID���"));

		if(!m_pCombin_db->UpdataItemCD(m_map_role_id))
		{
			m_message_lb.AddString(_T("������ƷCD��ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������ƷCD��ɫID���"));

		/*if(!m_pCombin_db->UpdateMail(m_map_role_id))
		{
			m_message_lb.AddString(_T("�����ʼ���ɫIDʧ��"));
			return;
		}*/

		//m_message_lb.AddString(_T("�����ʼ���ɫID���"));

		if(!m_pCombin_db->UpdateMapLimit(m_map_role_id))
		{
			m_message_lb.AddString(_T("���µ�ͼ���ƽ�ɫIDʧ��"));
			return;
		}

		if(!m_pCombin_db->UpdateInstanceProcess(m_map_role_id))
		{
			m_message_lb.AddString(_T("���¸������Ƚ�ɫIDʧ��"));
			return;
		}


		if(!m_pCombin_db->UpdateGuildKillBoss(m_map_guild_id))
		{
			m_message_lb.AddString(_T("����ɱBOSS IDʧ��"));
			return;
		}

		// 		if(!m_pCombin_db->UpdateGuildWarHistory(m_map_role_id, m_map_guild_id))
		// 		{
		// 			m_message_lb.AddString(_T("���ս��ʷ��¼ IDʧ��"));
		// 			return;
		// 		}

		if(!m_pCombin_db->UpdateGuildPlant(m_map_guild_id))
		{
			m_message_lb.AddString(_T("�����ֲʧ��"));
			return;
		}


		m_message_lb.AddString(_T("���µ�ͼ���ƽ�ɫID���"));

		if(!m_pCombin_db->UpdateMasterPrentice(m_map_role_id))
		{
			m_message_lb.AddString(_T("����ʦͽ��ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("����ʦͽ��ɫID���"));

		if(!m_pCombin_db->UpdatePaimai(m_map_role_id))
		{
			m_message_lb.AddString(_T("����������ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("����������ɫID���"));

		if(!m_pCombin_db->UpdateBank(m_map_role_id))
		{
			m_message_lb.AddString(_T("����Ǯׯ��ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("����Ǯׯ��ɫID���"));

		if(!m_pCombin_db->UpdatePet(m_map_role_id))
		{
			m_message_lb.AddString(_T("���³����ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���³����ɫID���"));

		if(!m_pCombin_db->UpdatePetSNS(m_map_role_id))
		{
			m_message_lb.AddString(_T("���³���SNS��ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���³���SNS��ɫID���"));

		if(!m_pCombin_db->UpdateQuest(m_map_role_id))
		{
			m_message_lb.AddString(_T("���������ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�����ѽ������ɫID���"));

		if(!m_pCombin_db->UpdateQuestDone(m_map_role_id))
		{
			m_message_lb.AddString(_T("����������ɽ�ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��������������ɫID���"));

		if(!m_pCombin_db->UpdateGuerdonQuest(m_map_role_id))
		{
			m_message_lb.AddString(_T("�������������ɫIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("�������������ɫID���"));

		if(!m_pCombin_db->UpdateRoleSkill(m_map_role_id))
		{
			m_message_lb.AddString(_T("���¼��ܽ�ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���¼��ܽ�ɫID���"));

		if(!m_pCombin_db->UpdateRoleTitle(m_map_role_id))
		{
			m_message_lb.AddString(_T("���³ƺŽ�ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���³ƺŽ�ɫID���"));

		if(!m_pCombin_db->UpdateRoleData(m_map_role_id))
		{
			m_message_lb.AddString(_T("���½�ɫIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���½�ɫID���"));

/**********************************************

*****************************************************/

		if(!m_pCombin_db->InitGuildList(m_list_guild))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���������ݳ�ʼ��ʧ��"));
			return;
		}

		ChangeGuildSignID();

		m_message_lb.AddString(_T("���°��ǩ����ɫID���"));

		if(!m_pCombin_db->InitMaster(m_list_master))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--ʦͽ��ʼ��ʧ��"));
			return;
		}

		ChangeMasterID();

		//m_message_lb.AddString(_T("����ʦͽ��ɫID���"));

		if(!m_pCombin_db->InitGuerdonQuest(m_list_guerdon_quest))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���ͳ�ʼ��ʧ��"));
			return;
		}

		ChangeGuerdonQuestID();

		//m_message_lb.AddString(_T("�������������ɫID���"));

		if(!m_pCombin_db->InitRoleData(m_list_role_data))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�������ݳ�ʼ��ʧ��"));
			return;
		}

		ChangeRoleName();

		m_message_lb.AddString(_T("ת����ɫ�������"));

		if(!m_pCombin_db->UpdateRoleName(m_list_role_data))
		{
			m_message_lb.AddString(_T("���½�ɫ����ʧ��"));
			return ;
		}

		CleanRoleData();

		m_message_lb.AddString(_T("���½�ɫ�������"));

		//------------------------------------------------------------------------

		if(!m_pCombin_db->UpdateBuff(m_map_item_id))
		{
			m_message_lb.AddString(_T("����buff��ƷIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����buff��ƷID���"));

		/*if(!m_pCombin_db->InitMail(m_list_mail))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ʼ���ʼ��ʧ��"));
			return;
		}

		ChangeMailItemID();*/

		//m_message_lb.AddString(_T("�����ʼ���ƷID���"));

		if(!m_pCombin_db->UpdateBankID(m_map_bank_id))
		{
			m_message_lb.AddString(_T("����ǮׯIDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("����ǮׯID���"));

		if(!m_pCombin_db->InitGuildList(m_list_guild))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���������ݳ�ʼ��ʧ��"));
			return;
		}

		ChangeGuildIDNew();

		m_message_lb.AddString(_T("���°��ID���"));

		if(!m_pCombin_db->UpdateRoleGuildID(m_map_guild_id_pair))
		{
			m_message_lb.AddString(_T("���½�ɫ���IDʧ��"));
			return ;
		}

		m_message_lb.AddString(_T("���½�ɫ���ID���"));

		if(!m_pCombin_db->UpdateGuildMemberID(m_map_guild_id_pair))
		{
			m_message_lb.AddString(_T("���°���Ա���IDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���°���Ա���ID���"));

		if(!m_pCombin_db->UpdateGuildGradeID(m_map_guild_id_pair))
		{
			m_message_lb.AddString(_T("���°�Ὠ�����IDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���°�Ὠ�����ID���"));

		/*if(!m_pCombin_db->UpdateMailID(m_map_mail_id))
		{
			m_message_lb.AddString(_T("�����ʼ�IDʧ��"));
			return;
		}*/

		//m_message_lb.AddString(_T("�����ʼ�ID���"));

		if(!m_pCombin_db->UpdatePaimaiID(m_map_paimai_id))
		{
			m_message_lb.AddString(_T("��������IDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("��������ID���"));

		if(!m_pCombin_db->UpdatePetID(m_map_pet_id))
		{
			m_message_lb.AddString(_T("���³���IDʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("���³���ID���"));

		if(!m_pCombin_db->UpdateItemID(m_map_item_id))
		{
			m_message_lb.AddString(_T("������ƷIDʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������ƷID���"));

		//--------------------------------------------------------------------------------

		if(!m_pMain_db->InitAccountCommon(m_map_main_account_common))
		{
			m_message_lb.AddString(_T("�����ݿ�--��ɫ�������ݳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�����ݿ��ɫ�������ݳ�ʼ�����"));

		if(!m_pCombin_db->InitAccountCommon(m_map_com_account_common))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ɫ�������ݳ�ʼ��ʧ��"));
			return;
		}

		ChangeAccountCommon();

		m_message_lb.AddString(_T("��ɫ��������ת�����"));

		if(!m_pMain_db->InsertAccountCommon(m_map_main_account_common))
		{
			m_message_lb.AddString(_T("��ɫ�����б����ʧ��"));
			return;
		}

		CleanAccountCommon();


		m_pCombin_db->AddItemRead();

		DWORD dw_not_read = 0;
		m_pCombin_db->GetItemNotReadNum(dw_not_read);

		while(dw_not_read > 0)
		{
			if(dw_not_read > 50000)
			{
				dw_not_read = 50000;
			}
			if(!m_pCombin_db->InitItem(m_list_item, dw_not_read))
			{
				m_message_lb.AddString(_T("�ϲ����ݿ�--��Ʒ��ʼ��ʧ��"));
				return;
			}

			if(!m_pMain_db->InsertItem(m_list_item))
			{
				m_message_lb.AddString(_T("��Ʒ�б����ʧ��"));
				return;
			}

			if(!m_pMain_db->InsertEquip(m_list_item))
			{
				m_message_lb.AddString(_T("װ���б����ʧ��"));
				return;
			}

			LIST_ITEM::iterator iter_item = m_list_item.begin();
			while(iter_item != m_list_item.end())
			{
				if(VALID_POINT(*iter_item))
				{
					m_pCombin_db->ChangeItemRead((*iter_item)->n64_serial);
					SAFE_DELETE(*iter_item);
				}
				iter_item++;
			}
			m_list_item.clear();

			dw_not_read = 0;
			m_pCombin_db->GetItemNotReadNum(dw_not_read);

		}

		m_message_lb.AddString(_T("��Ʒ�������"));

		if(!m_pCombin_db->InitItemCD(m_list_item_cd))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ƷCD��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertItemCD(m_list_item_cd))
		{
			m_message_lb.AddString(_T("��Ʒcd�б����ʧ��"));
			return;
		}
		else
		{
			LIST_ITEM_CD::iterator iter_item_cd = m_list_item_cd.begin();
			while(iter_item_cd != m_list_item_cd.end())
			{
				if(VALID_POINT(*iter_item_cd))
				{
					SAFE_DELETE(*iter_item_cd);
				}
				iter_item_cd++;
			}
			m_list_item_cd.clear();
		}

		m_message_lb.AddString(_T("��Ʒcd�������"));

		if(!m_pCombin_db->InitRoleData(m_list_role_data))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�������ݳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertRoleData(m_list_role_data))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_ROLE_DATA::iterator iter_role_data = m_list_role_data.begin();
			while(iter_role_data != m_list_role_data.end())
			{
				if(VALID_POINT(*iter_role_data))
				{
					SAFE_DELETE(*iter_role_data);
				}
				iter_role_data++;
			}
			m_list_role_data.clear();
		}

		m_message_lb.AddString(_T("�������ݲ������"));

		if(!m_pCombin_db->InitRoleSkill(m_list_role_skill))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���＼�ܳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertRoleSkill(m_list_role_skill))
		{
			m_message_lb.AddString(_T("���＼���б����ʧ��"));
			return;
		}
		else
		{
			LIST_ROLE_SKILL::iterator iter_role_skill = m_list_role_skill.begin();
			while(iter_role_skill != m_list_role_skill.end())
			{
				if(VALID_POINT(*iter_role_skill))
				{
					SAFE_DELETE(*iter_role_skill);
				}
				iter_role_skill++;
			}
			m_list_role_skill.clear();
		}

		m_message_lb.AddString(_T("���＼�ܲ������"));

		if(!m_pCombin_db->InitAchievement(m_list_achievement))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ƺų�ʼ��ʧ��"));
			return;
		}


		if(!m_pMain_db->InsertAchievement(m_list_achievement))
		{
			m_message_lb.AddString(_T("�ɾͳƺ��б����ʧ��"));
			return;
		}
		else
		{
			LIST_ACHIEVEMENT::iterator iter_achievement = m_list_achievement.begin();
			while(iter_achievement != m_list_achievement.end())
			{
				if(VALID_POINT(*iter_achievement))
				{
					SAFE_DELETE(*iter_achievement);
				}
				iter_achievement++;
			}
			m_list_achievement.clear();
		}

		//m_message_lb.AddString(_T("�ƺ����ݲ������"));

		if(!m_pCombin_db->InitAchievementProcess(m_list_achievement_process))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ƺŽ��ȳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertAchievement(m_list_achievement_process))
		{
			m_message_lb.AddString(_T("�ɾͳƺŽ����б����ʧ��"));
			return;
		}
		else
		{
			LIST_ACHIEVEMENT_PROCESS::iterator iter_achievement_process = m_list_achievement_process.begin();
			while(iter_achievement_process != m_list_achievement_process.end())
			{
				if(!VALID_POINT(*iter_achievement_process))
				{
					SAFE_DELETE(*iter_achievement_process);
				}
				iter_achievement_process++;
			}
			m_list_achievement_process.clear();
		}

		//m_message_lb.AddString(_T("�ƺŽ��Ȳ������"));

		if(!m_pCombin_db->InitBlackList(m_list_combin_black))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��������ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertBlackList(m_list_combin_black))
		{
			m_message_lb.AddString(_T("�������б����ʧ��"));
			return;
		}
		else
		{
			LIST_BLACK::iterator iter_black = m_list_combin_black.begin();
			while(iter_black != m_list_combin_black.end())
			{
				if(VALID_POINT(*iter_black))
				{
					SAFE_DELETE(*iter_black);
				}
				iter_black++;
			}
			m_list_combin_black.clear();
		}

		m_message_lb.AddString(_T("�������������"));

		if(!m_pCombin_db->InitBufferList(m_list_buffer))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--buffer��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertBufferList(m_list_buffer))
		{
			m_message_lb.AddString(_T("buffer�б����ʧ��"));
			return;
		}
		else
		{
			LIST_BUFFER::iterator iter_buffer = m_list_buffer.begin();
			while(iter_buffer != m_list_buffer.end())
			{
				if(VALID_POINT(*iter_buffer))
				{
					SAFE_DELETE(*iter_buffer);
				}
				iter_buffer++;
			}
			m_list_buffer.clear();
		}

		m_message_lb.AddString(_T("buffer�������"));

		if(!m_pCombin_db->InitEnemyList(m_list_enemy))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���˳�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertEnemyList(m_list_enemy))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_ENEMY::iterator iter_enemy = m_list_enemy.begin();
			while(iter_enemy != m_list_enemy.end())
			{
				if(VALID_POINT(*iter_enemy))
				{
					SAFE_DELETE(*iter_enemy);
				}
				iter_enemy++;
			}
			m_list_enemy.clear();
		}

		//m_message_lb.AddString(_T("���˲������"));

		if(!m_pCombin_db->InitFriendList(m_list_friend))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���ѳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertFriendList(m_list_friend))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_FRIEND::iterator iter_friend = m_list_friend.begin();
			while(iter_friend != m_list_friend.end())
			{
				if(VALID_POINT(*iter_friend))
				{
					SAFE_DELETE(*iter_friend);
				}
				iter_friend++;
			}
			m_list_friend.clear();
		}

		m_message_lb.AddString(_T("���Ѳ������"));

		if(!m_pCombin_db->InitFriendShipList(m_list_friendship))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���Ѷȳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertFriendShipList(m_list_friendship))
		{
			m_message_lb.AddString(_T("���Ѷ��б����ʧ��"));
			return;
		}
		else
		{
			LIST_FRIENDSHIP::iterator iter_friendship = m_list_friendship.begin();
			while(iter_friendship != m_list_friendship.end())
			{
				if(VALID_POINT(*iter_friendship))
				{
					SAFE_DELETE(*iter_friendship);
				}
				iter_friendship++;
			}
			m_list_friendship.clear();
		}

		//m_message_lb.AddString(_T("���ѶȲ������"));

		if(!m_pCombin_db->InitGuildList(m_list_guild))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���������ݳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertGuildList(m_list_guild))
		{
			m_message_lb.AddString(_T("����б����ʧ��"));
			return;
		}
		else
		{
			LIST_GUILD::iterator iter_guild = m_list_guild.begin();
			while(iter_guild != m_list_guild.end())
			{
				if(VALID_POINT(*iter_guild))
				{
					SAFE_DELETE(*iter_guild);
				}
				iter_guild++;
			}
			m_list_guild.clear();
		}

		m_message_lb.AddString(_T("���������"));

		if(!m_pCombin_db->InitGuildMemberList(m_list_guild_member))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--����Ա��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertGuildMemberList(m_list_guild_member))
		{
			m_message_lb.AddString(_T("����Ա�б����ʧ��"));
			return;
		}
		else
		{
			LIST_GUILD_MEMBER::iterator iter_guild_member = m_list_guild_member.begin();
			while(iter_guild_member != m_list_guild_member.end())
			{
				if(VALID_POINT(*iter_guild_member))
				{
					SAFE_DELETE(*iter_guild_member);
				}
				iter_guild_member++;
			}
			m_list_guild_member.clear();
		}

		m_message_lb.AddString(_T("����Ա�������"));

		if(!m_pCombin_db->InitGuildUpgradeList(m_list_guild_upgrade))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��Ὠ����ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertGuildUpgradeList(m_list_guild_upgrade))
		{
			m_message_lb.AddString(_T("��Ὠ���б����ʧ��"));
			return;
		}
		else
		{
			LIST_GUILD_UPGRADE::iterator iter_guild_upgrade = m_list_guild_upgrade.begin();
			while(iter_guild_upgrade != m_list_guild_upgrade.end())
			{
				if(VALID_POINT(*iter_guild_upgrade))
				{
					SAFE_DELETE(*iter_guild_upgrade);
				}
				iter_guild_upgrade++;
			}
			m_list_guild_upgrade.clear();
		}

		//m_message_lb.AddString(_T("��Ὠ���������"));

		/*if(!m_pCombin_db->InitMail(m_list_mail))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ʼ���ʼ��ʧ��"));
			return;
		}*/

		if(!m_pCombin_db->InitGuildKillBoss(m_list_guild_kill))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--����ɱBOSS��ʼ��ʧ��"));
			return;
		} 
		if(!m_pMain_db->InsertGuildKillBoss(m_list_guild_kill))
		{
			m_message_lb.AddString(_T("����ɱBOSS����ʧ��"));
			return;
		}
		else
		{
			LIST_GUILD_KILL_BOSS::iterator iter = m_list_guild_kill.begin();
			for(; iter != m_list_guild_kill.end();iter++)
			{
				SAFE_DELETE((*iter));
			}
		}
		//m_message_lb.AddString(_T("����ɱBOSS�������"));

		// 
		// 		if(!m_pCombin_db->InitGuildWarHistory(m_list_guild_war_history))
		// 		{
		// 			m_message_lb.AddString(_T("�ϲ����ݿ�--���ս��ʷ��¼��ʼ��ʧ��"));
		// 			return;
		// 		} 
		// 		if(!m_pMain_db->InsertGuildWarHistory(m_list_guild_war_history))
		// 		{
		// 			m_message_lb.AddString(_T("���ս��ʷ��¼����ʧ��"));
		// 			return;
		// 		}
		// 		else
		// 		{
		// 			LIST_GUILD_WAR_HISTORY::iterator iter = m_list_guild_war_history.begin();
		// 			for(; iter != m_list_guild_war_history.end();iter++)
		// 			{
		// 				SAFE_DELETE((*iter));
		// 			}
		// 		}
		// 		m_message_lb.AddString(_T("���ս��ʷ��¼�������"));


		if(!m_pCombin_db->InitGuildPlant(m_list_guild_plant))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����ֲ��ʼ��ʧ��"));
			return;
		} 
		if(!m_pMain_db->InsertGuildPlant(m_list_guild_plant))
		{
			m_message_lb.AddString(_T("�����ֲ����ʧ��"));
			return;
		}
		else
		{
			LIST_GUILD_WAR_HISTORY::iterator iter = m_list_guild_war_history.begin();
			for(; iter != m_list_guild_war_history.end();iter++)
			{
				SAFE_DELETE((*iter));
			}
		}
		//m_message_lb.AddString(_T("�����ֲ�������"));




		/*if(!m_pMain_db->InsertMail(m_list_mail))
		{
			m_message_lb.AddString(_T("�ʼ��б����ʧ��"));
			return;
		}
		else
		{
			LIST_MAIL::iterator iter_mail = m_list_mail.begin();
			while(iter_mail != m_list_mail.end())
			{
				if(VALID_POINT(*iter_mail))
				{
					SAFE_DELETE(*iter_mail);
				}
				iter_mail++;
			}
			m_list_mail.clear();
		}*/

		//m_message_lb.AddString(_T("�ʼ��������"));

		if(!m_pCombin_db->InitMapLimit(m_list_map_limit))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ͼ���Ƴ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertMapLimit(m_list_map_limit))
		{
			m_message_lb.AddString(_T("��ͼ�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_MAP_LIMIT::iterator iter_map_limit = m_list_map_limit.begin();
			while(iter_map_limit != m_list_map_limit.end())
			{
				if(VALID_POINT(*iter_map_limit))
				{
					SAFE_DELETE(*iter_map_limit);
				}
				iter_map_limit++;
			}
			m_list_map_limit.clear();
		}

		m_message_lb.AddString(_T("��ͼ���Ʋ������"));

		if(!m_pCombin_db->InitInstanceProcess(m_list_inst_process))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�������ȳ�ʼ��ʧ��"));
			return;
		}
		if(!m_pMain_db->InsertInstProcess(m_list_inst_process))
		{
			m_message_lb.AddString(_T("���������б����ʧ��"));
			return;
		}
		else
		{
			LIST_INTS_PROCESS::iterator inter_ints = m_list_inst_process.begin();
			while(inter_ints != m_list_inst_process.end())
			{
				if(VALID_POINT(*inter_ints))
				{
					SAFE_DELETE(*inter_ints);
				}
				inter_ints++;
			}
			m_list_inst_process.clear();
		}
		m_message_lb.AddString(_T("�������Ȳ������"));

		//�����ɫ������Ϣ
		if(!m_pCombin_db->InitRoleRewardData(m_list_role_reward))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ɫ������Ϣ��ʼ��ʧ��"));
			return;
		}
		if(!m_pMain_db->InsertRoleRewardData(m_list_role_reward))
		{
			m_message_lb.AddString(_T("��ɫ������Ϣ�б����ʧ��"));
			return;
		}
		else
		{
			LIST_ROLE_REWARD_DATA::iterator inter_ints = m_list_role_reward.begin();
			while(inter_ints != m_list_role_reward.end())
			{
				if(VALID_POINT(*inter_ints))
				{
					SAFE_DELETE(*inter_ints);
				}
				inter_ints++;
			}
			m_list_role_reward.clear();
		}
		m_message_lb.AddString(_T("��ɫ������Ϣ�������"));
		//end

		//�������������Ϣ gx add 2013.11.11
		if(!m_pCombin_db->InitRoleMountData(m_list_role_mount_data))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ɫ������Ϣ��ʼ��ʧ��"));
			return;
		}
		if(!m_pMain_db->InsertRoleMountData(m_list_role_mount_data))
		{
			m_message_lb.AddString(_T("��ɫ������Ϣ�б����ʧ��"));
			return;
		}
		else
		{
			LIST_MOUNT_DATA::iterator iter_mount = m_list_role_mount_data.begin();
			while(iter_mount != m_list_role_mount_data.end())
			{
				byte* pData = (byte*)(*iter_mount);
				if(VALID_POINT(pData))
				{
					SAFE_DELETE_ARRAY(pData);
				}
				iter_mount++;
			}
			m_list_role_mount_data.clear();
		}
		m_message_lb.AddString(_T("��ɫ������Ϣ�������"));
		//end

		//�������������Ϣ
		if(!m_pCombin_db->InitRoleVCardData(m_list_role_vcard))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ɫ������Ϣ��ʼ��ʧ��"));
			return;
		}
		if(!m_pMain_db->InsertRoleVCradData(m_list_role_vcard))
		{
			m_message_lb.AddString(_T("��ɫ������Ϣ�б����ʧ��"));
			return;
		}
		else
		{
			LIST_ROLE_VCARD_DATA::iterator iter_vcard = m_list_role_vcard.begin();
			while(iter_vcard != m_list_role_vcard.end())
			{
				byte* pData = (byte*)(*iter_vcard);
				if(VALID_POINT(pData))
				{
					SAFE_DELETE_ARRAY(pData);
				}
				iter_vcard++;
			}
			m_list_role_vcard.clear();
		}
		m_message_lb.AddString(_T("��ɫ������Ϣ�������"));
		//end

		if(!m_pCombin_db->InitMaster(m_list_master))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--ʦͽ��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertMaster(m_list_master))
		{
			m_message_lb.AddString(_T("ʦͽ�б����ʧ��"));
			return;
		}
		else
		{
			LIST_MASTER::iterator iter_master = m_list_master.begin();
			while(iter_master != m_list_master.end())
			{
				if(VALID_POINT(*iter_master))
				{
					SAFE_DELETE(*iter_master);
				}
				iter_master++;
			}
			m_list_master.clear();

		}

		//m_message_lb.AddString(_T("ʦͽ�������"));

		if(!m_pCombin_db->InitPaiMai(m_list_paimai))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����г�ʼ��ʧ��"));
			return;
		}

		//m_message_lb.AddString(_T("������ʼ�����"));

		if(!m_pMain_db->InsertPaiMai(m_list_paimai))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_PAIMAI::iterator iter_paimai = m_list_paimai.begin();
			while(iter_paimai != m_list_paimai.end())
			{
				if(VALID_POINT(*iter_paimai))
				{
					SAFE_DELETE(*iter_paimai);
				}
				iter_paimai++;
			}
			m_list_paimai.clear();
		}

		//m_message_lb.AddString(_T("�����������"));

		if(!m_pCombin_db->InitPet(m_list_pet))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertPet(m_list_pet))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_PET::iterator iter_pet = m_list_pet.begin();
			while(iter_pet != m_list_pet.end())
			{
				if(VALID_POINT(*iter_pet))
				{
					SAFE_DELETE(*iter_pet)
				}
				iter_pet++;
			}
			m_list_pet.clear();
		}

		//m_message_lb.AddString(_T("����������"));

		if(!m_pCombin_db->InitPetSkill(m_list_pet_skill))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���＼�ܳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertPetSkill(m_list_pet_skill))
		{
			m_message_lb.AddString(_T("���＼���б����ʧ��"));
			return;
		}
		else
		{
			LIST_PET_SKILL::iterator iter_pet_skill = m_list_pet_skill.begin();
			while(iter_pet_skill != m_list_pet_skill.end())
			{
				if(VALID_POINT(*iter_pet_skill))
				{
					SAFE_DELETE(*iter_pet_skill);
				}
				iter_pet_skill++;
			}
			m_list_pet_skill.clear();

		}

		//m_message_lb.AddString(_T("���＼�ܲ������"));

		if(!m_pCombin_db->InitPetSns(m_list_pet_sns))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--����sns��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertPetSns(m_list_pet_sns))
		{
			m_message_lb.AddString(_T("����sns�б����ʧ��"));
			return;
		}
		else
		{
			LIST_PET_SNS::iterator iter_pet_sns = m_list_pet_sns.begin();
			while(iter_pet_sns != m_list_pet_sns.end())
			{
				if(VALID_POINT(*iter_pet_sns))
				{
					SAFE_DELETE(*iter_pet_sns);
				}
				iter_pet_sns++;
			}
			m_list_pet_sns.clear();
		}

		//m_message_lb.AddString(_T("����sns�������"));

		if(!m_pCombin_db->InitQuest(m_list_quest))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertQuest(m_list_quest))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_QUEST::iterator iter_quest = m_list_quest.begin();
			while(iter_quest != m_list_quest.end())
			{
				if(VALID_POINT(*iter_quest))
				{
					SAFE_DELETE(*iter_quest);
				}
				iter_quest++;
			}
			m_list_quest.clear();
		}

		m_message_lb.AddString(_T("����������"));

		m_pCombin_db->AddQuestDoneRead();
		dw_not_read = 0;
		m_pCombin_db->GetQuestNotReadNum(dw_not_read);
		while(dw_not_read > 0)
		{
			if(dw_not_read > 50000)
			{
				dw_not_read = 50000;
			}

			if(!m_pCombin_db->InitQuestDone(m_list_quest_done, dw_not_read))
			{
				m_message_lb.AddString(_T("�ϲ����ݿ�--������ɳ�ʼ��ʧ��"));
				return;
			}

			if(!m_pMain_db->InsertQuestDone(m_list_quest_done))
			{
				m_message_lb.AddString(_T("��������б����ʧ��"));
				return;
			}
			else
			{
				LIST_QUEST_DONE::iterator iter_quest_done = m_list_quest_done.begin();
				while(iter_quest_done != m_list_quest_done.end())
				{
					if(VALID_POINT(*iter_quest_done))
					{
						m_pCombin_db->ChangeQuestDoneRead((*iter_quest_done)->dw_role_id, (*iter_quest_done)->u16QuestID);
						SAFE_DELETE(*iter_quest_done)
					}
					iter_quest_done++;
				}
				m_list_quest_done.clear();
			}

			dw_not_read = 0;
			m_pCombin_db->GetQuestNotReadNum(dw_not_read);
		}


		if(!m_pCombin_db->InitBank(m_list_bank))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--Ǯׯ��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertBank(m_list_bank))
		{
			m_message_lb.AddString(_T("Ǯׯ�б����ʧ��"));
			return;
		}
		else
		{
			LIST_BANK::iterator iter_bank = m_list_bank.begin();
			while(iter_bank != m_list_bank.end())
			{
				if(VALID_POINT(*iter_bank))
				{
					SAFE_DELETE(*iter_bank)
				}
				iter_bank++;
			}
			m_list_bank.clear();
		}

		//m_message_lb.AddString(_T("Ǯׯ�������"));

		if(!m_pCombin_db->InitTitle(m_list_title))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ƺų�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertTitle(m_list_title))
		{
			m_message_lb.AddString(_T("�ƺ��б����ʧ��"));
			return;
		}
		else
		{
			LIST_TITLE::iterator iter_title = m_list_title.begin();
			while(iter_title != m_list_title.end())
			{
				if(VALID_POINT(*iter_title))
				{
					SAFE_DELETE(*iter_title);
				}
				iter_title++;
			}
			m_list_title.clear();
		}

		m_message_lb.AddString(_T("�ƺŲ������"));

		if(!m_pCombin_db->InitGuerdonQuest(m_list_guerdon_quest))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���ͳ�ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InsertGuerdon(m_list_guerdon_quest))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}
		else
		{
			LIST_GUERDON_QUEST::iterator iter_guerdon_quest = m_list_guerdon_quest.begin();
			while(iter_guerdon_quest != m_list_guerdon_quest.end())
			{
				if(VALID_POINT(*iter_guerdon_quest))
				{
					SAFE_DELETE(*iter_guerdon_quest);
				}
				iter_guerdon_quest++;
			}
			m_list_guerdon_quest.clear();
		}

		//m_message_lb.AddString(_T("���Ͳ������"));


#else
		InitThread();

		if(!m_pMain_db->InitRoleNameCrc(m_map_role_name_crc))
		{
			m_message_lb.AddString(_T("�����ݿ�--��ɫ����crc��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InitGuildID(m_map_guild_id))
		{
			m_message_lb.AddString(_T("�����ݿ�--���id��ʼ��ʧ��"));
			return;
		}

		if(!m_pMain_db->InitAccountCommon(m_map_main_account_common))
		{
			m_message_lb.AddString(_T("�����ݿ�--��ɫ�������ݳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�����ݿ��ɫ�������ݳ�ʼ�����"));

		if(!m_pCombin_db->InitAccountCommon(m_map_com_account_common))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ɫ�������ݳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ϲ����ݿ��ɫ�������ݳ�ʼ�����"));

		if(!m_pCombin_db->InitItem(m_list_item))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��Ʒ��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��Ʒ��ʼ�����"));

		if(!m_pCombin_db->InitItemCD(m_list_item_cd))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ƷCD��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ƷCD��ʼ�����"));

		if(!m_pCombin_db->InitRoleData(m_list_role_data))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�������ݳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�������ݳ�ʼ�����"));

		if(!m_pCombin_db->InitRoleSkill(m_list_role_skill))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���＼�ܳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���＼�ܳ�ʼ�����"));

		if(!m_pCombin_db->InitAchievement(m_list_achievement))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ƺų�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ƺų�ʼ�����"));

		if(!m_pCombin_db->InitAchievementProcess(m_list_achievement_process))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ƺŽ��ȳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ƺŽ��ȳ�ʼ�����"));

		if(!m_pCombin_db->InitBlackList(m_list_combin_black))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��������ʼ��ʧ��"));
			return;
		}

		if(!m_pCombin_db->InitBufferList(m_list_buffer))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--buffer��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("buffer��ʼ�����"));

		if(!m_pCombin_db->InitEnemyList(m_list_enemy))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���˳�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���˳�ʼ�����"));

		if(!m_pCombin_db->InitFriendList(m_list_friend))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���ѳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���ѳ�ʼ�����"));

		if(!m_pCombin_db->InitFriendShipList(m_list_friendship))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���Ѷȳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���Ѷȳ�ʼ�����"));

		if(!m_pCombin_db->InitGuildList(m_list_guild))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���������ݳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���������ݳ�ʼ�����"));

		/*if(!m_pCombin_db->InitGuildCommerceList(m_list_guild_commerce))
		{
		m_message_lb.AddString(_T("�ϲ����ݿ�--������̳�ʼ��ʧ��"));
		return;
		}*/

		if(!m_pCombin_db->InitGuildDelateList(m_list_guild_delate))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ᵯ����ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ᵯ�����ݳ�ʼ�����"));

		if(!m_pCombin_db->InitGuildMemberList(m_list_guild_member))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--����Ա��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����Ա���ݳ�ʼ�����"));

		if(!m_pCombin_db->InitGuildUpgradeList(m_list_guild_upgrade))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��Ὠ����ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��Ὠ����ʼ�����"));

		if(!m_pCombin_db->InitMail(m_list_mail))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ʼ���ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ʼ���ʼ�����"));

		if(!m_pCombin_db->InitMapLimit(m_list_map_limit))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--��ͼ���Ƴ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ͼ���Ƴ�ʼ�����"));

		if(!m_pCombin_db->InitMaster(m_list_master))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--ʦͽ��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("ʦͽ��ʼ�����"));

		if(!m_pCombin_db->InitPaiMai(m_list_paimai))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����г�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������ʼ�����"));

		if(!m_pCombin_db->InitPet(m_list_pet))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�����ʼ�����"));

		if(!m_pCombin_db->InitPetSkill(m_list_pet_skill))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���＼�ܳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���＼�ܳ�ʼ�����"));

		if(!m_pCombin_db->InitPetSns(m_list_pet_sns))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--����sns��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����sns��ʼ�����"));

		if(!m_pCombin_db->InitQuest(m_list_quest))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�����ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�����ʼ�����"));

		if(!m_pCombin_db->InitQuestDone(m_list_quest_done))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--������ɳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������ɶȳ�ʼ�����"));

		if(!m_pCombin_db->InitBank(m_list_bank))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--Ǯׯ��ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("Ǯׯ��ʼ�����"));

		if(!m_pCombin_db->InitTitle(m_list_title))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--�ƺų�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ƺų�ʼ�����"));

		if(!m_pCombin_db->InitGuerdonQuest(m_list_guerdon_quest))
		{
			m_message_lb.AddString(_T("�ϲ����ݿ�--���ͳ�ʼ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���ͳ�ʼ�����"));

		/*if(!m_pCombin_db->InitXuanShang(m_list_xuanshang))
		{
		m_message_lb.AddString(_T("�ϲ����ݿ�--���ͳ�ʼ��ʧ��"));
		return;
		}*/

		if(!GetMaxRoleID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�����ɫ���ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ����ɫ���"));

		if(!GetMaxPaimaiID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�����������ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ����������"));

		if(!GetMaxBankID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ����Ǯׯ���ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ���Ǯׯ���"));

		if(!GetMaxItemID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ������Ʒ���ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ�����Ʒ���"));

		if(!GetMaxMailID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�����ʼ����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ����ʼ����"));

		if(!GetMaxPetID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ���������ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ��������"));

		if(!GetMaxGuerdonID())
		{
			m_message_lb.AddString(_T("��ȡ���ݿ�������ͱ��ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ȡ������ͱ��"));

		ChangeAccountCommon();

		m_message_lb.AddString(_T("��ɫ��������ת�����"));

		ChangeRoleID(dw_role_max_id);

		m_message_lb.AddString(_T("��ɫIDת�����"));

		ChangeRoleName();

		m_message_lb.AddString(_T("ת����ɫ�������"));

		ChangeBankID(dw_bank_max_id);

		m_message_lb.AddString(_T("ת��ǮׯID���"));

		ChangeItemID(n64_item_max_id);

		m_message_lb.AddString(_T("ת����ƷID���"));

		ChangeGuildID();

		m_message_lb.AddString(_T("ת�����ID���"));

		ChangeMailID();

		m_message_lb.AddString(_T("ת���ʼ�ID���"));

		ChangePaiMaiID();

		m_message_lb.AddString(_T("ת������ID���"));

		ChangePetID();

		m_message_lb.AddString(_T("ת������ID���"));

		//ChangeGuerdonID();		//�������ã����Ͳ���������

		m_message_lb.AddString(_T("ת������ID���"));

		if(!m_pMain_db->InsertAccountCommon(m_map_main_account_common))
		{
			m_message_lb.AddString(_T("��ɫ�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ɫ�������ݲ������"));

		if(!m_pMain_db->InsertAchievement(m_list_achievement))
		{
			m_message_lb.AddString(_T("�ɾͳƺ��б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ƺ����ݲ������"));

		if(!m_pMain_db->InsertAchievement(m_list_achievement_process))
		{
			m_message_lb.AddString(_T("�ɾͳƺŽ����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ƺŽ��Ȳ������"));

		if(!m_pMain_db->InsertBlackList(m_list_combin_black))
		{
			m_message_lb.AddString(_T("����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�������������"));

		if(!m_pMain_db->InsertBufferList(m_list_buffer))
		{
			m_message_lb.AddString(_T("buffer�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("buffer�������"));

		if(!m_pMain_db->InsertEnemyList(m_list_enemy))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���˲������"));

		if(!m_pMain_db->InsertFriendList(m_list_friend))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���Ѳ������"));

		if(!m_pMain_db->InsertFriendShipList(m_list_friendship))
		{
			m_message_lb.AddString(_T("���Ѷ��б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���ѶȲ������"));

		if(!m_pMain_db->InsertGuildList(m_list_guild))
		{
			m_message_lb.AddString(_T("����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���������"));

		/*if(!m_pMain_db->InsertGuildCommerceList(m_list_guild_commerce))
		{
		m_message_lb.AddString(_T("��������б����ʧ��"));
		return;
		}*/

		if(!m_pMain_db->InsertGuildMemberList(m_list_guild_member))
		{
			m_message_lb.AddString(_T("����Ա�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����Ա�������"));

		if(!m_pMain_db->InsertGuildUpgradeList(m_list_guild_upgrade))
		{
			m_message_lb.AddString(_T("��Ὠ���б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��Ὠ���������"));

		if(!m_pMain_db->InsertGuildDelateList(m_list_guild_delate))
		{
			m_message_lb.AddString(_T("��ᵯ���б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ᵯ���������"));

		if(!m_pMain_db->InsertItem(m_list_item))
		{
			m_message_lb.AddString(_T("��Ʒ�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��Ʒ�������"));

		if(!m_pMain_db->InsertEquip(m_list_item))
		{
			m_message_lb.AddString(_T("װ���б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("װ���������"));

		if(!m_pMain_db->InsertItemCD(m_list_item_cd))
		{
			m_message_lb.AddString(_T("��Ʒcd�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��Ʒcd�������"));

		if(!m_pMain_db->InsertMail(m_list_mail))
		{
			m_message_lb.AddString(_T("�ʼ��б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ʼ��������"));

		if(!m_pMain_db->InsertMapLimit(m_list_map_limit))
		{
			m_message_lb.AddString(_T("��ͼ�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("��ͼ���Ʋ������"));

		if(!m_pMain_db->InsertMaster(m_list_master))
		{
			m_message_lb.AddString(_T("ʦͽ�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("ʦͽ�������"));

		if(!m_pMain_db->InsertPaiMai(m_list_paimai))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�����������"));

		if(!m_pMain_db->InsertPet(m_list_pet))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����������"));

		if(!m_pMain_db->InsertPetSkill(m_list_pet_skill))
		{
			m_message_lb.AddString(_T("���＼���б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���＼�ܲ������"));

		if(!m_pMain_db->InsertPetSns(m_list_pet_sns))
		{
			m_message_lb.AddString(_T("����sns�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����sns�������"));

		if(!m_pMain_db->InsertQuest(m_list_quest))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("����������"));

		if(!m_pMain_db->InsertQuestDone(m_list_quest_done))
		{
			m_message_lb.AddString(_T("��������б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("������ɶȲ������"));


		if(!m_pMain_db->InsertRoleData(m_list_role_data))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�������ݲ������"));


		if(!m_pMain_db->InsertRoleSkill(m_list_role_skill))
		{
			m_message_lb.AddString(_T("���＼���б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���＼�ܲ������"));

		if(!m_pMain_db->InsertTitle(m_list_title))
		{
			m_message_lb.AddString(_T("�ƺ��б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("�ƺŲ������"));

		if(!m_pMain_db->InsertBank(m_list_bank))
		{
			m_message_lb.AddString(_T("Ǯׯ�б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("Ǯׯ�������"));

		if(!m_pMain_db->InsertGuerdon(m_list_guerdon_quest))
		{
			m_message_lb.AddString(_T("�����б����ʧ��"));
			return;
		}

		m_message_lb.AddString(_T("���Ͳ������"));

		/*	if(!m_pMain_db->InsertXuanShang(m_list_xuanshang))
		{
		m_message_lb.AddString(_T("�����б����ʧ��"));
		return;
		}*/
#endif

	}
	catch (serverdump::throw_exception)
	{
		m_message_lb.AddString(_T("�Ϸ������쳣��"));
		if( get_tool()->is_debug_present() )
		{
			throw;
		}
		else
		{
			exit(1);
		}
	}

	m_message_lb.AddString(_T("�Ϸ����"));

}

VOID CombinationDlg::ClearCombinData()
{

	MAP_ACCOUNT_COMMON::iterator iter_main_account_common = m_map_main_account_common.begin();
	while(iter_main_account_common != m_map_main_account_common.end())
	{
		s_account_common* pAccount_Common = iter_main_account_common->second;
		if(VALID_POINT(pAccount_Common))
		{
			SAFE_DELETE(pAccount_Common);
		}
		iter_main_account_common++;
	}
	m_map_main_account_common.clear();

	MAP_ACCOUNT_COMMON::iterator iter_com_account_common = m_map_com_account_common.begin();
	while(iter_com_account_common != m_map_com_account_common.end())
	{
		s_account_common* pAccount_Common = iter_com_account_common->second;
		if(VALID_POINT(pAccount_Common))
		{
			SAFE_DELETE(pAccount_Common);
		}
		iter_com_account_common++;
	}
	m_map_com_account_common.clear();

	LIST_ACHIEVEMENT::iterator iter_achievement = m_list_achievement.begin();
	while(iter_achievement != m_list_achievement.end())
	{
		if(VALID_POINT(*iter_achievement))
		{
			SAFE_DELETE(*iter_achievement);
		}
		iter_achievement++;
	}
	m_list_achievement.clear();

	LIST_ACHIEVEMENT_PROCESS::iterator iter_achievement_process = m_list_achievement_process.begin();
	while(iter_achievement_process != m_list_achievement_process.end())
	{
		if(!VALID_POINT(*iter_achievement_process))
		{
			SAFE_DELETE(*iter_achievement_process);
		}
		iter_achievement_process++;
	}
	m_list_achievement_process.clear();

	LIST_BLACK::iterator iter_black = m_list_combin_black.begin();
	while(iter_black != m_list_combin_black.end())
	{
		if(VALID_POINT(*iter_black))
		{
			SAFE_DELETE(*iter_black);
		}
		iter_black++;
	}
	m_list_combin_black.clear();

	LIST_BUFFER::iterator iter_buffer = m_list_buffer.begin();
	while(iter_buffer != m_list_buffer.end())
	{
		if(VALID_POINT(*iter_buffer))
		{
			SAFE_DELETE(*iter_buffer);
		}
		iter_buffer++;
	}
	m_list_buffer.clear();

	LIST_ENEMY::iterator iter_enemy = m_list_enemy.begin();
	while(iter_enemy != m_list_enemy.end())
	{
		if(VALID_POINT(*iter_enemy))
		{
			SAFE_DELETE(*iter_enemy);
		}
		iter_enemy++;
	}
	m_list_enemy.clear();

	LIST_FRIEND::iterator iter_friend = m_list_friend.begin();
	while(iter_friend != m_list_friend.end())
	{
		if(VALID_POINT(*iter_friend))
		{
			SAFE_DELETE(*iter_friend);
		}
		iter_friend++;
	}
	m_list_friend.clear();

	LIST_FRIENDSHIP::iterator iter_friendship = m_list_friendship.begin();
	while(iter_friendship != m_list_friendship.end())
	{
		if(VALID_POINT(*iter_friendship))
		{
			SAFE_DELETE(*iter_friendship);
		}
		iter_friendship++;
	}
	m_list_friendship.clear();

	LIST_GUILD::iterator iter_guild = m_list_guild.begin();
	while(iter_guild != m_list_guild.end())
	{
		if(VALID_POINT(*iter_guild))
		{
			SAFE_DELETE(*iter_guild);
		}
		iter_guild++;
	}
	m_list_guild.clear();

	LIST_GUILD_COMMERCE::iterator iter_guild_commerce = m_list_guild_commerce.begin();
	while(iter_guild_commerce != m_list_guild_commerce.end())
	{
		if(VALID_POINT(*iter_guild_commerce))
		{
			SAFE_DELETE(*iter_guild_commerce);
		}
		iter_guild_commerce++;
	}
	m_list_guild_commerce.clear();

	LIST_GUILD_DELATE::iterator iter_guild_delate = m_list_guild_delate.begin();
	while(iter_guild_delate != m_list_guild_delate.end())
	{
		if(VALID_POINT(*iter_guild_delate))
		{
			SAFE_DELETE(*iter_guild_delate);
		}
		iter_guild_delate++;
	}
	m_list_guild_delate.clear();

	LIST_GUILD_MEMBER::iterator iter_guild_member = m_list_guild_member.begin();
	while(iter_guild_member != m_list_guild_member.end())
	{
		if(VALID_POINT(*iter_guild_member))
		{
			SAFE_DELETE(*iter_guild_member);
		}
		iter_guild_member++;
	}
	m_list_guild_member.clear();

	LIST_GUILD_UPGRADE::iterator iter_guild_upgrade = m_list_guild_upgrade.begin();
	while(iter_guild_upgrade != m_list_guild_upgrade.end())
	{
		if(VALID_POINT(*iter_guild_upgrade))
		{
			SAFE_DELETE(*iter_guild_upgrade);
		}
		iter_guild_upgrade++;
	}
	m_list_guild_upgrade.clear();

	LIST_ITEM::iterator iter_item = m_list_item.begin();
	while(iter_item != m_list_item.end())
	{
		if(VALID_POINT(*iter_item))
		{
			SAFE_DELETE(*iter_item);
		}
		iter_item++;
	}
	m_list_item.clear();

	LIST_ITEM_CD::iterator iter_item_cd = m_list_item_cd.begin();
	while(iter_item_cd != m_list_item_cd.end())
	{
		if(VALID_POINT(*iter_item_cd))
		{
			SAFE_DELETE(*iter_item_cd);
		}
		iter_item_cd++;
	}
	m_list_item_cd.clear();

	LIST_MAIL::iterator iter_mail = m_list_mail.begin();
	while(iter_mail != m_list_mail.end())
	{
		if(VALID_POINT(*iter_mail))
		{
			SAFE_DELETE(*iter_mail);
		}
		iter_mail++;
	}
	m_list_mail.clear();

	LIST_MAP_LIMIT::iterator iter_map_limit = m_list_map_limit.begin();
	while(iter_map_limit != m_list_map_limit.end())
	{
		if(VALID_POINT(*iter_map_limit))
		{
			SAFE_DELETE(*iter_map_limit);
		}
		iter_map_limit++;
	}
	m_list_map_limit.clear();

	LIST_MASTER::iterator iter_master = m_list_master.begin();
	while(iter_master != m_list_master.end())
	{
		if(VALID_POINT(*iter_master))
		{
			SAFE_DELETE(*iter_master);
		}
		iter_master++;
	}
	m_list_master.clear();

	LIST_PAIMAI::iterator iter_paimai = m_list_paimai.begin();
	while(iter_paimai != m_list_paimai.end())
	{
		if(VALID_POINT(*iter_paimai))
		{
			SAFE_DELETE(*iter_paimai);
		}
		iter_paimai++;
	}
	m_list_paimai.clear();

	LIST_PET::iterator iter_pet = m_list_pet.begin();
	while(iter_pet != m_list_pet.end())
	{
		if(VALID_POINT(*iter_pet))
		{
			SAFE_DELETE(*iter_pet)
		}
		iter_pet++;
	}
	m_list_pet.clear();

	LIST_PET_SKILL::iterator iter_pet_skill = m_list_pet_skill.begin();
	while(iter_pet_skill != m_list_pet_skill.end())
	{
		if(VALID_POINT(*iter_pet_skill))
		{
			SAFE_DELETE(*iter_pet_skill);
		}
		iter_pet_skill++;
	}
	m_list_pet_skill.clear();

	LIST_PET_SNS::iterator iter_pet_sns = m_list_pet_sns.begin();
	while(iter_pet_sns != m_list_pet_sns.end())
	{
		if(VALID_POINT(*iter_pet_sns))
		{
			SAFE_DELETE(*iter_pet_sns);
		}
		iter_pet_sns++;
	}
	m_list_pet_sns.clear();

	LIST_QUEST::iterator iter_quest = m_list_quest.begin();
	while(iter_quest != m_list_quest.end())
	{
		if(VALID_POINT(*iter_quest))
		{
			SAFE_DELETE(*iter_quest);
		}
		iter_quest++;
	}
	m_list_quest.clear();

	LIST_QUEST_DONE::iterator iter_quest_done = m_list_quest_done.begin();
	while(iter_quest_done != m_list_quest_done.end())
	{
		if(VALID_POINT(*iter_quest_done))
		{
			SAFE_DELETE(*iter_quest_done)
		}
		iter_quest_done++;
	}
	m_list_quest_done.clear();

	LIST_ROLE_DATA::iterator iter_role_data = m_list_role_data.begin();
	while(iter_role_data != m_list_role_data.end())
	{
		if(VALID_POINT(*iter_role_data))
		{
			SAFE_DELETE(*iter_role_data);
		}
		iter_role_data++;
	}
	m_list_role_data.clear();

	LIST_ROLE_SKILL::iterator iter_role_skill = m_list_role_skill.begin();
	while(iter_role_skill != m_list_role_skill.end())
	{
		if(VALID_POINT(*iter_role_skill))
		{
			SAFE_DELETE(*iter_role_skill);
		}
		iter_role_skill++;
	}
	m_list_role_skill.clear();

	LIST_TITLE::iterator iter_title = m_list_title.begin();
	while(iter_title != m_list_title.end())
	{
		if(VALID_POINT(*iter_title))
		{
			SAFE_DELETE(*iter_title);
		}
		iter_title++;
	}
	m_list_title.clear();

	LIST_BANK::iterator iter_bank = m_list_bank.begin();
	while(iter_bank != m_list_bank.end())
	{
		if(VALID_POINT(*iter_bank))
		{
			SAFE_DELETE(*iter_bank)
		}
		iter_bank++;
	}
	m_list_bank.clear();

	LIST_GUERDON_QUEST::iterator iter_guerdon_quest = m_list_guerdon_quest.begin();
	while(iter_guerdon_quest != m_list_guerdon_quest.end())
	{
		if(VALID_POINT(*iter_guerdon_quest))
		{
			SAFE_DELETE(*iter_guerdon_quest);
		}
		iter_guerdon_quest++;
	}
	m_list_guerdon_quest.clear();

	/*LIST_XUANSHANG::iterator iter_xuanshang = m_list_xuanshang.begin();
	while(iter_xuanshang != m_list_xuanshang.end())
	{
	if(VALID_POINT(*iter_xuanshang))
	{
	SAFE_DELETE(*iter_xuanshang);
	}
	iter_xuanshang++;
	}
	m_list_xuanshang.clear();*/
}

BOOL CombinationDlg::GetMaxRoleID()
{
	DWORD dw_main_role_max_id = 0;
	DWORD dw_com_role_max_id = 0;
	if(!m_pMain_db->GetMaxRoleID(dw_main_role_max_id))
	{
		return FALSE;
	}
	if(!m_pCombin_db->GetMaxRoleID(dw_com_role_max_id))
	{
		return FALSE;
	}

	dw_role_max_id = max(dw_main_role_max_id, dw_com_role_max_id);
	return TRUE;
}

BOOL CombinationDlg::GetMaxBankID()
{
	DWORD dw_main_bank_max_id = 0;
	DWORD dw_com_bank_max_id = 0;
	if(!m_pMain_db->GetMaxBankID(dw_main_bank_max_id))
	{
		return FALSE;
	}
	if(!m_pCombin_db->GetMaxBankID(dw_com_bank_max_id))
	{
		return FALSE;
	}

	dw_bank_max_id = max(dw_main_bank_max_id, dw_com_bank_max_id);
	return TRUE;
}

BOOL CombinationDlg::GetMaxPaimaiID()
{
	DWORD dw_main_paimai_max_id = 0;
	DWORD dw_com_paimai_id = 0;

	if(!m_pMain_db->GetMaxPaimaiID(dw_main_paimai_max_id))
	{
		return FALSE;
	}

	if(!m_pCombin_db->GetMaxPaimaiID(dw_com_paimai_id))
	{
		return FALSE;
	}

	dw_paimai_max_id = max(dw_main_paimai_max_id, dw_com_paimai_id);
	return TRUE;

}

BOOL CombinationDlg::GetMaxItemID()
{
	INT64 n64_main_item_max_id = MIN_ITEM_SERIAL_INTERNAL;
	INT64 n64_main_item_del_max_id = MIN_ITEM_SERIAL_INTERNAL;

	INT64 n64_com_item_max_id = MIN_ITEM_SERIAL_INTERNAL;
	INT64 n64_com_item_del_max_id = MIN_ITEM_SERIAL_INTERNAL;

	if(!m_pMain_db->GetMaxItemID(n64_main_item_max_id, "item"))
	{
		return FALSE;
	}
	if(!m_pMain_db->GetMaxItemID(n64_main_item_del_max_id, "item_del"))
	{
		return FALSE;
	}

	n64_main_item_max_id = max(n64_main_item_max_id, n64_main_item_del_max_id);

	if(!m_pCombin_db->GetMaxItemID(n64_com_item_max_id, "item"))
	{
		return FALSE;
	}
	if(!m_pCombin_db->GetMaxItemID(n64_com_item_del_max_id, "item_del"))
	{
		return FALSE;
	}

	n64_com_item_max_id = max(n64_com_item_max_id, n64_com_item_del_max_id);

	n64_item_max_id = max(n64_main_item_max_id, n64_com_item_max_id);

	return TRUE;
}

BOOL CombinationDlg::GetMaxMailID()
{
	DWORD dw_main_mail_max_id = 0;
	DWORD dw_com_mail_max_id = 0;

	if(!m_pMain_db->GetMaxMailID(dw_main_mail_max_id))
	{
		return FALSE;
	}

	if(!m_pCombin_db->GetMaxMailID(dw_com_mail_max_id))
	{
		return FALSE;
	}

	dw_mail_max_id = max(dw_main_mail_max_id, dw_com_mail_max_id);
	return TRUE;
}

BOOL CombinationDlg::GetMaxPetID()
{
	DWORD	dw_main_pet_max_id = MIN_PET_ID;
	DWORD	dw_com_pet_max_id = MIN_PET_ID;

	if(!m_pMain_db->GetMaxPetID(dw_main_pet_max_id))
	{
		return FALSE;
	}

	if(!m_pCombin_db->GetMaxPetID(dw_com_pet_max_id))
	{
		return FALSE;
	}

	dw_pet_max_id = max(dw_main_pet_max_id, dw_com_pet_max_id);
	return TRUE;
}

BOOL CombinationDlg::GetMaxGuerdonID()
{
	DWORD dw_main_guerdon_max_id = 0;
	DWORD dw_com_guerdon_max_id = 0;

	if(!m_pMain_db->GetMaxGuerdonID(dw_main_guerdon_max_id))
	{
		return FALSE;
	}

	if(!m_pCombin_db->GetMaxGuerdonID(dw_com_guerdon_max_id))
	{
		return FALSE;
	}

	dw_guerdon_max_id = max(dw_main_guerdon_max_id, dw_com_guerdon_max_id);

	return TRUE;
}

BOOL CombinationDlg::GetMaxAccountID()
{
	DWORD dw_main_account_max_id = 0;
	DWORD dw_combin_account_max_id = 0;

	if(!m_pMainAccount_db->GetMaxAccountID(dw_main_account_max_id))
	{
		return FALSE;
	}

	if(!m_pCombinAccount_db->GetMaxAccountID(dw_combin_account_max_id))
	{
		return FALSE;
	}

	dw_account_max_id = max(dw_main_account_max_id, dw_combin_account_max_id);

	return TRUE;
}

VOID CombinationDlg::ChangeAccountCommon()
{
	MAP_ACCOUNT_COMMON::iterator iter_com_account_common = m_map_com_account_common.begin();
	while(iter_com_account_common != m_map_com_account_common.end())
	{
		MAP_ACCOUNT_COMMON::iterator iter_main_account_common = m_map_main_account_common.find(iter_com_account_common->first);
		if(iter_main_account_common != m_map_main_account_common.end())
		{
			iter_main_account_common->second->n_baibao_yuanbao_ += iter_com_account_common->second->n_baibao_yuanbao_;
			iter_main_account_common->second->n_yuanbao_recharge += iter_com_account_common->second->n_yuanbao_recharge;
			iter_main_account_common->second->dw_total_recharge += iter_com_account_common->second->dw_total_recharge;
			iter_main_account_common->second->n32_score = max(iter_main_account_common->second->n32_score,iter_com_account_common->second->n32_score);//�콱���Ҫȡ���ֵ
			iter_main_account_common->second->b_receive |= iter_com_account_common->second->b_receive;
			iter_main_account_common->second->dw_receive_type |= iter_com_account_common->second->dw_receive_type;
			if(!iter_main_account_common->second->b_receive) 
				iter_main_account_common->second->n16_receive_type = iter_com_account_common->second->n16_receive_type;
		}
		else
		{
			tag_account_common* pAccount_Common = new tag_account_common;
			ZeroMemory(pAccount_Common, sizeof(tag_account_common));

			memcpy(pAccount_Common, iter_com_account_common->second, sizeof(tag_account_common));

			m_map_main_account_common.insert(std::make_pair(pAccount_Common->dw_account_id, pAccount_Common));
		}
		iter_com_account_common++;
	}
}

UINT WINAPI	thread_achievement(LPVOID p)
{
	while(TRUE)
	{
		LIST_ACHIEVEMENT::iterator iter_achievement = CombinationDlg::pParam->pDlg->get_list_achievement().begin();
		while(iter_achievement != CombinationDlg::pParam->pDlg->get_list_achievement().end())
		{
			if((*iter_achievement)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_achievement)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_achievement++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[0]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_achievement_process(LPVOID p)
{

	while(TRUE)
	{
		LIST_ACHIEVEMENT_PROCESS::iterator iter_achievement_process = CombinationDlg::pParam->pDlg->get_list_achievement_process().begin();
		while(iter_achievement_process != CombinationDlg::pParam->pDlg->get_list_achievement_process().end())
		{
			if((*iter_achievement_process)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_achievement_process)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_achievement_process++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[1]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_black(LPVOID p)
{

	while(TRUE)
	{
		LIST_BLACK::iterator iter_black = CombinationDlg::pParam->pDlg->get_list_black().begin();
		while(iter_black != CombinationDlg::pParam->pDlg->get_list_black().end())
		{
			if((*iter_black)->dwRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_black)->dwRoleID = CombinationDlg::pParam->dw_role_max_id;
			}

			if((*iter_black)->dwBlackID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_black)->dwBlackID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_black++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[2]);
	}

	_endthread();

	return 0;
}

UINT WINAPI thread_buffer(LPVOID p)
{

	while(TRUE)
	{
		LIST_BUFFER::iterator iter_buffer = CombinationDlg::pParam->pDlg->get_list_buffer().begin();
		while(iter_buffer != CombinationDlg::pParam->pDlg->get_list_buffer().end())
		{
			if((*iter_buffer)->dw_src_unit_id_ == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_buffer)->dw_src_unit_id_ = CombinationDlg::pParam->dw_role_max_id;
			}

			if((*iter_buffer)->dwRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_buffer)->dwRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_buffer++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[3]);
	}

	_endthread();

	return 0;
}

UINT WINAPI thread_enemy(LPVOID p)
{

	while(TRUE)
	{
		LIST_ENEMY::iterator iter_enemy = CombinationDlg::pParam->pDlg->get_list_enemy().begin();
		while(iter_enemy != CombinationDlg::pParam->pDlg->get_list_enemy().end())
		{
			if((*iter_enemy)->dwEnemyID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_enemy)->dwEnemyID = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_enemy)->dwRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_enemy)->dwRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_enemy++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[4]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_friend(LPVOID p)
{

	while(TRUE)
	{
		LIST_FRIEND::iterator iter_friend = CombinationDlg::pParam->pDlg->get_list_friend().begin();
		while(iter_friend != CombinationDlg::pParam->pDlg->get_list_friend().end())
		{
			if((*iter_friend)->dwRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_friend)->dwRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_friend)->dw_friend_id_ == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_friend)->dw_friend_id_ = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_friend++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[5]);
	}


	_endthread();
	return 0;
}

UINT WINAPI thread_friend_ship(LPVOID p)
{

	while(TRUE)
	{
		LIST_FRIENDSHIP::iterator iter_friendship = CombinationDlg::pParam->pDlg->get_list_friend_ship().begin();
		while(iter_friendship != CombinationDlg::pParam->pDlg->get_list_friend_ship().end())
		{
			if((*iter_friendship)->dwRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_friendship)->dwRoleID = CombinationDlg::pParam->dw_role_max_id;
			}

			if((*iter_friendship)->dw_friend_id_ == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_friendship)->dw_friend_id_ = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_friendship++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[6]);
	}


	_endthread();
	return 0;
}

UINT WINAPI thread_guild(LPVOID p)
{
	while(TRUE)
	{
		LIST_GUILD::iterator iter_guild = CombinationDlg::pParam->pDlg->get_list_guild().begin();
		while(iter_guild != CombinationDlg::pParam->pDlg->get_list_guild().end())
		{
			if((*iter_guild)->dwFounderNameID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guild)->dwFounderNameID = CombinationDlg::pParam->dw_role_max_id;
			}

			for(INT i = 0; i < MAX_GUILD_SIGN_NUM; i++)
			{
				if((*iter_guild)->dwSignRoleID[i] == CombinationDlg::pParam->dw_old_role_id)
				{
					(*iter_guild)->dwSignRoleID[i] = CombinationDlg::pParam->dw_role_max_id;
				}
			}

			if((*iter_guild)->dwLeaderRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guild)->dwLeaderRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_guild++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[7]);
	}



	_endthread();

	return 0;
}

UINT WINAPI thread_guild_commerce(LPVOID p)
{
	while(TRUE)
	{
		LIST_GUILD_COMMERCE::iterator iter_commerce = CombinationDlg::pParam->pDlg->get_list_commerce().begin();
		while(iter_commerce != CombinationDlg::pParam->pDlg->get_list_commerce().end())
		{
			if((*iter_commerce)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_commerce)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_commerce++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[8]);
	}



	_endthread();

	return 0;
}

UINT WINAPI thread_guild_delate(LPVOID p)
{
	while(TRUE)
	{
		LIST_GUILD_DELATE::iterator iter_guild_delate = CombinationDlg::pParam->pDlg->get_list_delate().begin();
		while(iter_guild_delate != CombinationDlg::pParam->pDlg->get_list_delate().end())
		{
			if((*iter_guild_delate)->dwBeDelateRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guild_delate)->dwBeDelateRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_guild_delate)->dwInitiateRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guild_delate)->dwInitiateRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_guild_delate++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[9]);
	}



	_endthread();
	return 0;
}

UINT WINAPI thread_guild_member(LPVOID p)
{

	while(TRUE)
	{
		LIST_GUILD_MEMBER::iterator iter_guild_member = CombinationDlg::pParam->pDlg->get_list_member().begin();
		while(iter_guild_member != CombinationDlg::pParam->pDlg->get_list_member().end())
		{
			if((*iter_guild_member)->s_guild_member_.dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guild_member)->s_guild_member_.dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_guild_member++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[10]);
	}



	_endthread();

	return 0;
}

UINT WINAPI thread_item(LPVOID p)
{

	while(TRUE)
	{
		LIST_ITEM::iterator iter_item = CombinationDlg::pParam->pDlg->get_list_item().begin();
		while(iter_item != CombinationDlg::pParam->pDlg->get_list_item().end())
		{
			if((*iter_item)->eConType >= EICT_Bag && (*iter_item)->eConType <= EICT_Equip && (*iter_item)->dwOwnerID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_item)->dwOwnerID = CombinationDlg::pParam->dw_role_max_id;
			}

			if((*iter_item)->dwCreatorID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_item)->dwCreatorID = CombinationDlg::pParam->dw_role_max_id;
			}

			if((*iter_item)->eConType == EICT_GDQuest && (*iter_item)->dwOwnerID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_item)->dwOwnerID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_item++;
		}

		LIST_ITEM_CD::iterator iter_item_cd = CombinationDlg::pParam->pDlg->get_list_item_cd().begin();
		while(iter_item_cd != CombinationDlg::pParam->pDlg->get_list_item_cd().end())
		{
			if((*iter_item_cd)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_item_cd)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_item_cd++;
		}


		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[11]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_mail(LPVOID p)
{

	while(TRUE)
	{
		LIST_MAIL::iterator iter_mail = CombinationDlg::pParam->pDlg->get_list_mail().begin();
		while(iter_mail != CombinationDlg::pParam->pDlg->get_list_mail().end())
		{
			if((*iter_mail)->s_mail_base_.dwRecvRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_mail)->s_mail_base_.dwRecvRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_mail)->s_mail_base_.dwSendRoleID == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_mail)->s_mail_base_.dwSendRoleID = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_mail++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[12]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_map_limit(LPVOID p)
{
	while(TRUE)
	{
		LIST_MAP_LIMIT::iterator iter_map_limit = CombinationDlg::pParam->pDlg->get_list_map_limit().begin();
		while(iter_map_limit != CombinationDlg::pParam->pDlg->get_list_map_limit().end())
		{
			if((*iter_map_limit)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_map_limit)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_map_limit++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[13]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_master(LPVOID p)
{
	while(TRUE)
	{
		LIST_MASTER::iterator iter_master = CombinationDlg::pParam->pDlg->get_list_master().begin();
		while(iter_master != CombinationDlg::pParam->pDlg->get_list_master().end())
		{
			if((*iter_master)->dw_master == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_master)->dw_master = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_master++;		
		}

		LIST_MASTER::iterator  iter_master2= CombinationDlg::pParam->pDlg->get_list_master().begin();
		while(iter_master2 != CombinationDlg::pParam->pDlg->get_list_master().end())
		{
			vector<DWORD>::iterator iter = (*iter_master2)->list_role.begin();
			while(iter != (*iter_master2)->list_role.end())
			{
				if(*iter == CombinationDlg::pParam->dw_old_role_id)
				{
					*iter = CombinationDlg::pParam->dw_role_max_id;
				}
				iter++;
			}
			iter_master2++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[14]);
	}

	_endthread();

	return 0;
}

UINT WINAPI thread_paimai(LPVOID p)
{
	while(TRUE)
	{
		LIST_PAIMAI::iterator iter_paimai = CombinationDlg::pParam->pDlg->get_list_paimai().begin();
		while(iter_paimai != CombinationDlg::pParam->pDlg->get_list_paimai().end())
		{
			if((*iter_paimai)->dw_bidup_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_paimai)->dw_bidup_id = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_paimai)->dw_sell_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_paimai)->dw_sell_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_paimai++;
		}

		LIST_BANK::iterator iter_bank = CombinationDlg::pParam->pDlg->get_list_bank().begin();
		while(iter_bank != CombinationDlg::pParam->pDlg->get_list_bank().end())
		{
			if((*iter_bank)->dw_bidup_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_bank)->dw_bidup_id = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_bank)->dw_sell_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_bank)->dw_sell_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_bank++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[15]);

	}

	_endthread();

	return 0;
}

UINT WINAPI thread_pet(LPVOID p)
{
	while(TRUE)
	{
		LIST_PET::iterator iter_pet = CombinationDlg::pParam->pDlg->get_list_pet().begin();
		while(iter_pet != CombinationDlg::pParam->pDlg->get_list_pet().end())
		{
			if((*iter_pet)->dw_master_id_ == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_pet)->dw_master_id_ = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_pet++;
		}

		LIST_PET_SNS::iterator iter_pet_sns = CombinationDlg::pParam->pDlg->get_list_pet_sns().begin();
		while(iter_pet_sns != CombinationDlg::pParam->pDlg->get_list_pet_sns().end())
		{
			if((*iter_pet_sns)->dw_master_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_pet_sns)->dw_master_id = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_pet_sns)->dw_friend_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_pet_sns)->dw_friend_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_pet_sns++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[16]);
	}

	_endthread();

	return 0;
}

UINT WINAPI thread_quest(LPVOID p)
{

	while(TRUE)
	{
		LIST_QUEST::iterator iter_quest = CombinationDlg::pParam->pDlg->get_list_quest().begin();
		while(iter_quest != CombinationDlg::pParam->pDlg->get_list_quest().end())
		{
			if((*iter_quest)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_quest)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_quest++;
		}

		LIST_QUEST_DONE::iterator iter_quest_done = CombinationDlg::pParam->pDlg->get_list_quest_done().begin();
		while(iter_quest_done != CombinationDlg::pParam->pDlg->get_list_quest_done().end())
		{
			if((*iter_quest_done)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_quest_done)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_quest_done++;
		}

		LIST_GUERDON_QUEST::iterator iter_guerdon_quest = CombinationDlg::pParam->pDlg->get_list_guerdon_quest().begin();
		while(iter_guerdon_quest != CombinationDlg::pParam->pDlg->get_list_guerdon_quest().end())
		{
			if((*iter_guerdon_quest)->dwReciver == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guerdon_quest)->dwReciver = CombinationDlg::pParam->dw_role_max_id;
			}
			if((*iter_guerdon_quest)->dwSender == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_guerdon_quest)->dwSender = CombinationDlg::pParam->dw_role_max_id;

				INT16 quest_id = (INT16)(*iter_guerdon_quest)->n64Serial;
				(*iter_guerdon_quest)->n64Serial = (INT64)((INT64)(*iter_guerdon_quest)->dwSender << 32 | quest_id);

			}

			iter_guerdon_quest++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[17]);
	}


	_endthread();

	return 0;
}

UINT WINAPI thread_role_skill(LPVOID p)
{
	while(TRUE)
	{
		LIST_ROLE_SKILL::iterator iter_role_skill = CombinationDlg::pParam->pDlg->get_list_role_skill().begin();
		while(iter_role_skill != CombinationDlg::pParam->pDlg->get_list_role_skill().end())
		{
			if((*iter_role_skill)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_role_skill)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_role_skill++;
		}

		LIST_TITLE::iterator iter_title = CombinationDlg::pParam->pDlg->get_list_title().begin();
		while(iter_title != CombinationDlg::pParam->pDlg->get_list_title().end())
		{
			if((*iter_title)->dw_role_id == CombinationDlg::pParam->dw_old_role_id)
			{
				(*iter_title)->dw_role_id = CombinationDlg::pParam->dw_role_max_id;
			}
			iter_title++;
		}

		if( 0 == Interlocked_Decrement((LPLONG)&CombinationDlg::pParam->pDlg->n_event_num ) ) 
		{
			CombinationDlg::pParam->pDlg->h_event.Set();
		}
		SuspendThread(CombinationDlg::h_thread[18]);
	}

	_endthread();

	return 0;
}

VOID CombinationDlg::InitThread()
{
	CombinationDlg::h_thread[0] = (HANDLE)_beginthreadex(NULL, 0, thread_achievement, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[1] = (HANDLE)_beginthreadex(NULL, 0, thread_achievement_process, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[2] = (HANDLE)_beginthreadex(NULL, 0, thread_black, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[3] = (HANDLE)_beginthreadex(NULL, 0, thread_buffer, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[4] = (HANDLE)_beginthreadex(NULL, 0, thread_enemy, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[5] = (HANDLE)_beginthreadex(NULL, 0, thread_friend, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[6] = (HANDLE)_beginthreadex(NULL, 0, thread_friend_ship, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[7] = (HANDLE)_beginthreadex(NULL, 0, thread_guild, NULL, CREATE_SUSPENDED, NULL);
	CombinationDlg::h_thread[8] = (HANDLE)_beginthreadex(NULL, 0, thread_guild_commerce, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[9] = (HANDLE)_beginthreadex(NULL, 0, thread_guild_delate, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[10] = (HANDLE)_beginthreadex(NULL, 0, thread_guild_member, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[11] = (HANDLE)_beginthreadex(NULL, 0, thread_item, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[12] = (HANDLE)_beginthreadex(NULL, 0, thread_mail, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[13] = (HANDLE)_beginthreadex(NULL, 0, thread_map_limit, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[14] = (HANDLE)_beginthreadex(NULL, 0, thread_master, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[15] = (HANDLE)_beginthreadex(NULL, 0, thread_paimai, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[16] = (HANDLE)_beginthreadex(NULL, 0, thread_pet, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[17] = (HANDLE)_beginthreadex(NULL, 0, thread_quest, NULL, CREATE_SUSPENDED , NULL);
	CombinationDlg::h_thread[18] = (HANDLE)_beginthreadex(NULL, 0, thread_role_skill, NULL, CREATE_SUSPENDED , NULL);
}

VOID CombinationDlg::ChangeRoleID(DWORD dw_role_max_id)
{
	dw_role_max_id++;

	INT32 nNum = m_list_role_data.size();
	INT32 nCurent = 0;
	n_event_num = 0;

	map<DWORD, DWORD> map_role_id;

	LIST_ROLE_DATA::iterator iter_role_data = m_list_role_data.begin();
	while(iter_role_data != m_list_role_data.end())
	{
		//���ﲻ��ָ���ж��ˣ����������Ͳ��ܺϲ�
		tag_role_data* p_role_data = *iter_role_data;
		DWORD	dw_old_role_id = p_role_data->dw_role_id;
		p_role_data->dw_role_id = dw_role_max_id;
		map_role_id.insert(std::make_pair(dw_old_role_id, dw_role_max_id));

		ZeroMemory(CombinationDlg::pParam, sizeof(tag_Param));
		CombinationDlg::pParam->pDlg = this;
		CombinationDlg::pParam->dw_old_role_id = dw_old_role_id;
		CombinationDlg::pParam->dw_role_max_id = dw_role_max_id;


		Interlocked_Exchange((LPLONG)&n_event_num, 19);
		for(INT i = 0; i < 19; i++)
		{
			ResumeThread(h_thread[i]);
		}

		/*LIST_ACHIEVEMENT::iterator iter_achievement = m_list_achievement.begin();
		while(iter_achievement != m_list_achievement.end())
		{
		if((*iter_achievement)->dw_role_id == dw_old_role_id)
		{
		(*iter_achievement)->dw_role_id = dw_role_max_id;
		}
		iter_achievement++;
		}

		LIST_ACHIEVEMENT_PROCESS::iterator iter_achievement_process = m_list_achievement_process.begin();
		while(iter_achievement_process != m_list_achievement_process.end())
		{
		if((*iter_achievement_process)->dw_role_id == dw_old_role_id)
		{
		(*iter_achievement_process)->dw_role_id = dw_role_max_id;
		}
		iter_achievement_process++;
		}

		LIST_BLACK::iterator iter_black = m_list_combin_black.begin();
		while(iter_black != m_list_combin_black.end())
		{
		if((*iter_black)->dwRoleID == dw_old_role_id)
		{
		(*iter_black)->dwRoleID = dw_role_max_id;
		}

		if((*iter_black)->dwBlackID == dw_old_role_id)
		{
		(*iter_black)->dwBlackID = dw_role_max_id;
		}
		iter_black++;
		}

		LIST_BUFFER::iterator iter_buffer = m_list_buffer.begin();
		while(iter_buffer != m_list_buffer.end())
		{
		if((*iter_buffer)->dw_src_unit_id_ == dw_old_role_id)
		{
		(*iter_buffer)->dw_src_unit_id_ = dw_role_max_id;
		}

		if((*iter_buffer)->dwRoleID == dw_old_role_id)
		{
		(*iter_buffer)->dwRoleID = dw_role_max_id;
		}
		iter_buffer++;
		}

		LIST_ENEMY::iterator iter_enemy = m_list_enemy.begin();
		while(iter_enemy != m_list_enemy.end())
		{
		if((*iter_enemy)->dwEnemyID == dw_old_role_id)
		{
		(*iter_enemy)->dwEnemyID = dw_role_max_id;
		}
		if((*iter_enemy)->dwRoleID == dw_old_role_id)
		{
		(*iter_enemy)->dwRoleID = dw_role_max_id;
		}
		iter_enemy++;
		}

		LIST_FRIEND::iterator iter_friend = m_list_friend.begin();
		while(iter_friend != m_list_friend.end())
		{
		if((*iter_friend)->dwRoleID == dw_old_role_id)
		{
		(*iter_friend)->dwRoleID = dw_role_max_id;
		}
		if((*iter_friend)->dw_friend_id_ == dw_old_role_id)
		{
		(*iter_friend)->dw_friend_id_ = dw_role_max_id;
		}
		iter_friend++;
		}

		LIST_FRIENDSHIP::iterator iter_friendship = m_list_friendship.begin();
		while(iter_friendship != m_list_friendship.end())
		{
		if((*iter_friendship)->dwRoleID == dw_old_role_id)
		{
		(*iter_friendship)->dwRoleID = dw_role_max_id;
		}

		if((*iter_friendship)->dw_friend_id_ == dw_old_role_id)
		{
		(*iter_friendship)->dw_friend_id_ = dw_role_max_id;
		}
		iter_friendship++;
		}

		LIST_GUILD::iterator iter_guild = m_list_guild.begin();
		while(iter_guild != m_list_guild.end())
		{
		if((*iter_guild)->dwFounderNameID == dw_old_role_id)
		{
		(*iter_guild)->dwFounderNameID = dw_role_max_id;
		}

		for(INT i = 0; i < MAX_GUILD_SIGN_NUM; i++)
		{
		if((*iter_guild)->dwSignRoleID[i] == dw_old_role_id)
		{
		(*iter_guild)->dwSignRoleID[i] = dw_role_max_id;
		}
		}

		if((*iter_guild)->dwLeaderRoleID == dw_old_role_id)
		{
		(*iter_guild)->dwLeaderRoleID = dw_role_max_id;
		}
		iter_guild++;
		}

		LIST_GUILD_COMMERCE::iterator iter_commerce = m_list_guild_commerce.begin();
		while(iter_commerce != m_list_guild_commerce.end())
		{
		if((*iter_commerce)->dw_role_id == dw_old_role_id)
		{
		(*iter_commerce)->dw_role_id = dw_role_max_id;
		}
		iter_commerce++;
		}

		LIST_GUILD_DELATE::iterator iter_guild_delate = m_list_guild_delate.begin();
		while(iter_guild_delate != m_list_guild_delate.end())
		{
		if((*iter_guild_delate)->dwBeDelateRoleID == dw_old_role_id)
		{
		(*iter_guild_delate)->dwBeDelateRoleID = dw_role_max_id;
		}
		if((*iter_guild_delate)->dwInitiateRoleID == dw_old_role_id)
		{
		(*iter_guild_delate)->dwInitiateRoleID = dw_role_max_id;
		}
		iter_guild_delate++;
		}

		LIST_GUILD_MEMBER::iterator iter_guild_member = m_list_guild_member.begin();
		while(iter_guild_member != m_list_guild_member.end())
		{
		if((*iter_guild_member)->s_guild_member_.dw_role_id == dw_old_role_id)
		{
		(*iter_guild_member)->s_guild_member_.dw_role_id = dw_role_max_id;
		}
		iter_guild_member++;
		}

		LIST_ITEM::iterator iter_item = m_list_item.begin();
		while(iter_item != m_list_item.end())
		{
		if((*iter_item)->eConType >= EICT_Bag && (*iter_item)->eConType <= EICT_Equip && (*iter_item)->dwOwnerID == dw_old_role_id)
		{
		(*iter_item)->dwOwnerID = dw_role_max_id;
		}
		iter_item++;
		}

		LIST_ITEM_CD::iterator iter_item_cd = m_list_item_cd.begin();
		while(iter_item_cd != m_list_item_cd.end())
		{
		if((*iter_item_cd)->dw_role_id == dw_old_role_id)
		{
		(*iter_item_cd)->dw_role_id = dw_role_max_id;
		}
		iter_item_cd++;
		}

		LIST_MAIL::iterator iter_mail = m_list_mail.begin();
		while(iter_mail != m_list_mail.end())
		{
		if((*iter_mail)->s_mail_base_.dwRecvRoleID == dw_old_role_id)
		{
		(*iter_mail)->s_mail_base_.dwRecvRoleID = dw_role_max_id;
		}
		if((*iter_mail)->s_mail_base_.dwSendRoleID == dw_old_role_id)
		{
		(*iter_mail)->s_mail_base_.dwSendRoleID = dw_role_max_id;
		}
		iter_mail++;
		}

		LIST_MAP_LIMIT::iterator iter_map_limit = m_list_map_limit.begin();
		while(iter_map_limit != m_list_map_limit.end())
		{
		if((*iter_map_limit)->dw_role_id == dw_old_role_id)
		{
		(*iter_map_limit)->dw_role_id = dw_role_max_id;
		}
		iter_map_limit++;
		}

		LIST_MASTER::iterator iter_master = m_list_master.begin();
		while(iter_master != m_list_master.end())
		{
		if((*iter_master)->dw_master == dw_old_role_id)
		{
		(*iter_master)->dw_master = dw_role_max_id;
		}
		vector<DWORD>::iterator iter = (*iter_master)->list_role.begin();
		while(iter != (*iter_master)->list_role.end())
		{
		if(*iter == dw_old_role_id)
		{
		*iter = dw_role_max_id;
		}
		iter++;
		}
		iter_master++;
		}

		LIST_PAIMAI::iterator iter_paimai = m_list_paimai.begin();
		while(iter_paimai != m_list_paimai.end())
		{
		if((*iter_paimai)->dw_bidup_id == dw_old_role_id)
		{
		(*iter_paimai)->dw_bidup_id = dw_role_max_id;
		}
		if((*iter_paimai)->dw_sell_id == dw_old_role_id)
		{
		(*iter_paimai)->dw_sell_id = dw_role_max_id;
		}
		iter_paimai++;
		}

		LIST_PET::iterator iter_pet = m_list_pet.begin();
		while(iter_pet != m_list_pet.end())
		{
		if((*iter_pet)->dw_master_id_ == dw_old_role_id)
		{
		(*iter_pet)->dw_master_id_ = dw_role_max_id;
		}
		iter_pet++;
		}

		LIST_PET_SNS::iterator iter_pet_sns = m_list_pet_sns.begin();
		while(iter_pet_sns != m_list_pet_sns.end())
		{
		if((*iter_pet_sns)->dw_master_id == dw_old_role_id)
		{
		(*iter_pet_sns)->dw_master_id = dw_role_max_id;
		}
		if((*iter_pet_sns)->dw_friend_id == dw_old_role_id)
		{
		(*iter_pet_sns)->dw_friend_id = dw_role_max_id;
		}
		iter_pet_sns++;
		}

		LIST_QUEST::iterator iter_quest = m_list_quest.begin();
		while(iter_quest != m_list_quest.end())
		{
		if((*iter_quest)->dw_role_id == dw_old_role_id)
		{
		(*iter_quest)->dw_role_id = dw_role_max_id;
		}
		iter_quest++;
		}

		LIST_QUEST_DONE::iterator iter_quest_done = m_list_quest_done.begin();
		while(iter_quest_done != m_list_quest_done.end())
		{
		if((*iter_quest_done)->dw_role_id == dw_old_role_id)
		{
		(*iter_quest_done)->dw_role_id = dw_role_max_id;
		}
		iter_quest_done++;
		}

		LIST_ROLE_SKILL::iterator iter_role_skill = m_list_role_skill.begin();
		while(iter_role_skill != m_list_role_skill.end())
		{
		if((*iter_role_skill)->dw_role_id == dw_old_role_id)
		{
		(*iter_role_skill)->dw_role_id = dw_role_max_id;
		}
		iter_role_skill++;
		}

		LIST_TITLE::iterator iter_title = m_list_title.begin();
		while(iter_title != m_list_title.end())
		{
		if((*iter_title)->dw_role_id == dw_old_role_id)
		{
		(*iter_title)->dw_role_id = dw_role_max_id;
		}
		iter_title++;
		}

		LIST_BANK::iterator iter_bank = m_list_bank.begin();
		while(iter_bank != m_list_bank.end())
		{
		if((*iter_bank)->dw_bidup_id == dw_old_role_id)
		{
		(*iter_bank)->dw_bidup_id = dw_role_max_id;
		}
		if((*iter_bank)->dw_sell_id == dw_old_role_id)
		{
		(*iter_bank)->dw_sell_id = dw_role_max_id;
		}
		iter_bank++;
		}

		LIST_GUERDON_QUEST::iterator iter_guerdon_quest = m_list_guerdon_quest.begin();
		while(iter_guerdon_quest != m_list_guerdon_quest.end())
		{
		if((*iter_guerdon_quest)->dwReciver == dw_old_role_id)
		{
		(*iter_guerdon_quest)->dwReciver = dw_role_max_id;
		}
		if((*iter_guerdon_quest)->dwSender == dw_old_role_id)
		{
		(*iter_guerdon_quest)->dwSender = dw_role_max_id;
		}
		iter_guerdon_quest++;
		}*/

		h_event.Wait();
		h_event.ReSet();

		iter_role_data++;
		dw_role_max_id++;

		nCurent++;

		CString str;
		str.Format(_T("������%d/%d"), nCurent, nNum);
		m_process.SetWindowText(str);
	}

	iter_role_data = m_list_role_data.begin();
	while(iter_role_data != m_list_role_data.end())
	{
		if((*iter_role_data)->role_data_save_.dw_master_id_ != 0)
		{
			map<DWORD, DWORD>::iterator iter = map_role_id.find((*iter_role_data)->role_data_save_.dw_master_id_);
			if(iter != map_role_id.end())
			{
				(*iter_role_data)->role_data_save_.dw_master_id_ = iter->second;
			}
		}

		iter_role_data++;
	}
}

VOID CombinationDlg::ChangeBankID(DWORD dw_bank_max_id)
{
	dw_bank_max_id++;

	LIST_BANK::iterator iter_bank = m_list_bank.begin();
	while(iter_bank != m_list_bank.end())
	{
		DWORD dw_old_bank_id = (*iter_bank)->dw_id;
		(*iter_bank)->dw_id = dw_bank_max_id;

		dw_bank_max_id++;
		iter_bank++;
	}
}

VOID CombinationDlg::ChangeItemID(INT64 n64_item_max_id)
{
	n64_item_max_id++;

	INT32 nNum = m_list_item.size();
	INT32 nCurent = 0;

	LIST_ITEM::iterator iter_item = m_list_item.begin();
	while(iter_item != m_list_item.end())
	{
		INT64 n64_old_item_id = (*iter_item)->n64_serial;
		(*iter_item)->n64_serial = n64_item_max_id;

		LIST_MAIL::iterator iter_mail = m_list_mail.begin();
		while(iter_mail != m_list_mail.end())
		{
			for(INT i = 0; i < Max_Item_Num; i++)
			{
				if((*iter_mail)->s_mail_base_.n64ItemSerial[i] == n64_old_item_id)
				{
					(*iter_mail)->s_mail_base_.n64ItemSerial[i] = n64_item_max_id;
				}
			}
			iter_mail++;
		}

		LIST_BUFFER::iterator iter_buffer = m_list_buffer.begin();
		while(iter_buffer != m_list_buffer.end())
		{
			if((*iter_buffer)->n_serial_ == n64_old_item_id)
			{
				(*iter_buffer)->n_serial_ = n64_item_max_id;
			}
			iter_buffer++;
		}

		iter_item++;
		n64_item_max_id++;

		nCurent++;

		CString str;
		str.Format(_T("������%d/%d"), nCurent, nNum);
		m_process.SetWindowText(str);
	}
}

VOID CombinationDlg::ChangeGuildIDNew()
{
	LIST_GUILD::iterator iter_guild = m_list_guild.begin();
	while(iter_guild != m_list_guild.end())
	{
		MAP_GUILD_ID::iterator iter_id = m_map_guild_id.find((*iter_guild)->dwID);
		if(iter_id != m_map_guild_id.end())
		{
			wcsncat((*iter_guild)->sz_name, changename, changename.GetLength());
			TCHAR	buf[X_SHORT_NAME] = {0};
			_tcsncpy(buf, (*iter_guild)->sz_name, X_SHORT_NAME);
			buf[X_SHORT_NAME-1] = _T('\0');
			_tcslwr(buf);
			DWORD dwNameCrc = get_tool()->crc32(buf);
			DWORD dw_ole_id = (*iter_guild)->dwID;
			(*iter_guild)->dwID = dwNameCrc;
			m_map_guild_id_pair.insert(make_pair(dw_ole_id, dwNameCrc));
		}

		iter_guild++;
	}

	map<DWORD, DWORD>::iterator iter_map = m_map_guild_id_pair.begin();
	while(iter_map != m_map_guild_id_pair.end())
	{
		iter_guild = m_list_guild.begin();
		while(iter_guild != m_list_guild.end())
		{
			for(INT i = 0; i < MAX_ENEMY_NUM; i++)
			{
				if((*iter_guild)->dwEnemyID[i] == iter_map->first)
				{
					(*iter_guild)->dwEnemyID[i] = iter_map->second;
				}
			}
			if((*iter_guild)->dwLeagueID == iter_map->first)
			{
				(*iter_guild)->dwLeagueID = iter_map->second;
			}

			iter_guild++;
		}
		iter_map++;
	}

	m_pCombin_db->UpdateGuildID(m_list_guild);

	iter_guild = m_list_guild.begin();
	while(iter_guild != m_list_guild.end())
	{
		s_guild_load* p = (*iter_guild);
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_guild++;
	}
	m_list_guild.clear();
}

VOID CombinationDlg::ChangeGuildID()
{
	map<DWORD, DWORD> map_;
	LIST_GUILD::iterator iter_guild = m_list_guild.begin();
	while(iter_guild != m_list_guild.end())
	{
		MAP_GUILD_ID::iterator iter_id = m_map_guild_id.find((*iter_guild)->dwID);
		if(iter_id != m_map_guild_id.end())
		{
			wcsncat((*iter_guild)->sz_name, changename, changename.GetLength());
			TCHAR	buf[X_SHORT_NAME] = {0};
			_tcsncpy(buf, (*iter_guild)->sz_name, X_SHORT_NAME);
			buf[X_SHORT_NAME-1] = _T('\0');
			_tcslwr(buf);
			DWORD dwNameCrc = get_tool()->crc32(buf);
			DWORD dw_ole_id = (*iter_guild)->dwID;
			(*iter_guild)->dwID = dwNameCrc;
			map_.insert(make_pair(dw_ole_id, dwNameCrc));
		}

		iter_guild++;
	}

	map<DWORD, DWORD>::iterator iter_map = map_.begin();
	while(iter_map != map_.end())
	{
		iter_guild = m_list_guild.begin();
		while(iter_guild != m_list_guild.end())
		{
			for(INT i = 0; i < MAX_ENEMY_NUM; i++)
			{
				if((*iter_guild)->dwEnemyID[i] == iter_map->first)
				{
					(*iter_guild)->dwEnemyID[i] = iter_map->second;
				}
			}
			if((*iter_guild)->dwLeagueID == iter_map->first)
			{
				(*iter_guild)->dwLeagueID = iter_map->second;
			}

			iter_guild++;
		}

		LIST_ROLE_DATA::iterator iter_role_data = m_list_role_data.begin();
		while(iter_role_data != m_list_role_data.end())
		{
			if((*iter_role_data)->role_data_save_.dw_guild_id == iter_map->first)
			{
				(*iter_role_data)->role_data_save_.dw_guild_id = iter_map->second;
			}
			iter_role_data++;
		}

		LIST_GUILD_COMMERCE::iterator iter_guild_commerce = m_list_guild_commerce.begin();
		while(iter_guild_commerce != m_list_guild_commerce.end())
		{
			if((*iter_guild_commerce)->dwGuildID == iter_map->first)
			{
				(*iter_guild_commerce)->dwGuildID = iter_map->second;
			}
			iter_guild_commerce++;
		}

		LIST_GUILD_DELATE::iterator iter_guild_delate = m_list_guild_delate.begin();
		while(iter_guild_delate != m_list_guild_delate.end())
		{
			if((*iter_guild_delate)->dwGuildID == iter_map->first)
			{
				(*iter_guild_delate)->dwGuildID = iter_map->second;
			}
			iter_guild_delate++;
		}

		LIST_GUILD_MEMBER::iterator iter_guild_member = m_list_guild_member.begin();
		while(iter_guild_member != m_list_guild_member.end())
		{
			if((*iter_guild_member)->dw_guild_id_ == iter_map->first)
			{
				(*iter_guild_member)->dw_guild_id_ = iter_map->second;
			}
			iter_guild_member++;
		}

		LIST_GUILD_UPGRADE::iterator iter_guild_upgrade = m_list_guild_upgrade.begin();
		while(iter_guild_upgrade != m_list_guild_upgrade.end())
		{
			if((*iter_guild_upgrade)->dw_guild_id == iter_map->first)
			{
				(*iter_guild_upgrade)->dw_guild_id = iter_map->second;
			}
			iter_guild_upgrade++;
		}

		iter_map++;
	}
}

VOID CombinationDlg::ChangeMailID()
{
	dw_mail_max_id++;

	INT32 nNum = m_list_mail.size();
	INT32 nCurent = 0;

	LIST_MAIL::iterator iter_mail = m_list_mail.begin();
	while(iter_mail != m_list_mail.end())
	{
		DWORD dw_old_mail_id = (*iter_mail)->s_mail_base_.dwID;
		(*iter_mail)->s_mail_base_.dwID = dw_mail_max_id;

		LIST_ITEM::iterator iter_item = m_list_item.begin();
		while(iter_item != m_list_item.end())
		{
			if((*iter_item)->eConType == EICT_MailItem && (*iter_item)->dwOwnerID == dw_old_mail_id)
			{
				(*iter_item)->dwOwnerID = dw_mail_max_id;
			}
			iter_item++;
		}
		dw_mail_max_id++;
		iter_mail++;

		nCurent++;

		CString str;
		str.Format(_T("������%d/%d"), nCurent, nNum);
		m_process.SetWindowText(str);
	}
}

VOID CombinationDlg::ChangePaiMaiID()
{
	dw_paimai_max_id++;

	INT32 nNum = m_list_paimai.size();
	INT32 nCurent = 0;

	LIST_PAIMAI::iterator iter_paimai = m_list_paimai.begin();
	while(iter_paimai != m_list_paimai.end())
	{
		DWORD dw_old_paimai_id = (*iter_paimai)->dw_paimai_id;
		(*iter_paimai)->dw_paimai_id = dw_paimai_max_id;

		LIST_ITEM::iterator iter_item = m_list_item.begin();
		while(iter_item != m_list_item.end())
		{
			if((*iter_item)->eConType == EICT_PaiMai && (*iter_item)->dwOwnerID == dw_old_paimai_id)
			{
				(*iter_item)->dwOwnerID = dw_paimai_max_id;
			}
			iter_item++;
		}
		dw_paimai_max_id++;
		iter_paimai++;

		nCurent++;

		CString str;
		str.Format(_T("������%d/%d"), nCurent, nNum);
		m_process.SetWindowText(str);
	}
}

VOID CombinationDlg::ChangePetID()
{
	dw_pet_max_id++;

	LIST_PET::iterator iter_pet = m_list_pet.begin();
	while(iter_pet != m_list_pet.end())
	{
		DWORD dw_old_pet_id = (*iter_pet)->dw_pet_id_;
		(*iter_pet)->dw_pet_id_ = dw_pet_max_id;

		LIST_PET_SKILL::iterator iter_pet_skill = m_list_pet_skill.begin();
		while(iter_pet_skill != m_list_pet_skill.end())
		{
			if((*iter_pet_skill)->dw_pet_id_ == dw_old_pet_id)
			{
				(*iter_pet_skill)->dw_pet_id_ = dw_pet_max_id;
			}
			iter_pet_skill++;
		}

		LIST_PET_SNS::iterator iter_pet_sns = m_list_pet_sns.begin();
		while(iter_pet_sns != m_list_pet_sns.end())
		{
			if((*iter_pet_sns)->dw_pet_id == dw_old_pet_id)
			{
				(*iter_pet_sns)->dw_pet_id = dw_pet_max_id;
			}
			iter_pet_sns++;
		}

		dw_pet_max_id++;
		iter_pet++;
	}
}

VOID CombinationDlg::ChangeGuerdonID()
{
	dw_guerdon_max_id++;

	LIST_GUERDON_QUEST::iterator iter_querdon_quest = m_list_guerdon_quest.begin();
	while(iter_querdon_quest != m_list_guerdon_quest.end())
	{
		DWORD dw_old_guerdon_id = (*iter_querdon_quest)->n64Serial;
		(*iter_querdon_quest)->n64Serial = dw_guerdon_max_id;

		LIST_ITEM::iterator iter_item = m_list_item.begin();
		while(iter_item != m_list_item.end())
		{
			if((*iter_item)->eConType == EICT_GDQuest && (*iter_item)->dwOwnerID == dw_old_guerdon_id)
			{
				(*iter_item)->dwOwnerID = dw_guerdon_max_id;
			}
			iter_item++;
		}

		dw_guerdon_max_id++;
		iter_querdon_quest++;
	}

}

VOID CombinationDlg::ChangeRoleName()
{
	LIST_ROLE_DATA::iterator iter_role_data = m_list_role_data.begin();
	while(iter_role_data != m_list_role_data.end())
	{
		MAP_ROLE_NAME_CRC::iterator iter_crc = m_map_role_name_crc.find((*iter_role_data)->role_data_const_.dw_role_name_crc);
		if(iter_crc != m_map_role_name_crc.end())
		{
			wcsncat((*iter_role_data)->role_data_const_.sz_role_name, changename, changename.GetLength());

			TCHAR	buf[X_SHORT_NAME] = {0};
			_tcsncpy(buf, (*iter_role_data)->role_data_const_.sz_role_name, X_SHORT_NAME);
			buf[X_SHORT_NAME-1] = _T('\0');
			_tcslwr(buf);
			DWORD dwNameCrc = get_tool()->crc32(buf);
			(*iter_role_data)->role_data_const_.dw_role_name_crc = dwNameCrc;
			(*iter_role_data)->b_change_name = TRUE;
		}

		iter_role_data++;
	}
}

VOID CombinationDlg::CleanAccountCommon()
{
	MAP_ACCOUNT_COMMON::iterator iter_main_account_common = m_map_main_account_common.begin();
	while(iter_main_account_common != m_map_main_account_common.end())
	{
		s_account_common* pAccount_Common = iter_main_account_common->second;
		if(VALID_POINT(pAccount_Common))
		{
			SAFE_DELETE(pAccount_Common);
		}
		iter_main_account_common++;
	}
	m_map_main_account_common.clear();

	MAP_ACCOUNT_COMMON::iterator iter_com_account_common = m_map_com_account_common.begin();
	while(iter_com_account_common != m_map_com_account_common.end())
	{
		s_account_common* pAccount_Common = iter_com_account_common->second;
		if(VALID_POINT(pAccount_Common))
		{
			SAFE_DELETE(pAccount_Common);
		}
		iter_com_account_common++;
	}
	m_map_com_account_common.clear();
}

VOID CombinationDlg::CleanRoleData()
{
	LIST_ROLE_DATA::iterator iter = m_list_role_data.begin();
	while(iter != m_list_role_data.end())
	{
		tag_role_data* p = (*iter);

		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}

		iter++;
	}

	m_list_role_data.clear();
}

VOID CombinationDlg::ChangeGuildSignID()
{
	MAP_ROLE_ID::iterator iter = m_map_role_id.begin();
	while(iter != m_map_role_id.end())
	{
		LIST_GUILD::iterator iter_guild = m_list_guild.begin();
		while(iter_guild != m_list_guild.end())
		{
			for(INT i = 0; i < MAX_GUILD_SIGN_NUM; i++)
			{
				if((*iter_guild)->dwSignRoleID[i] == iter->first)
				{
					(*iter_guild)->dwSignRoleID[i] = iter->second;
				}
			}
			iter_guild++;
		}
		iter++;
	}

	m_pCombin_db->UpdateGuildSign(m_list_guild);

	LIST_GUILD::iterator iter_guild = m_list_guild.begin();
	while(iter_guild != m_list_guild.end())
	{
		s_guild_load* p = (*iter_guild);

		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}

		iter_guild++;
	}
	m_list_guild.clear();
}

VOID CombinationDlg::ChangeMasterID()
{
	MAP_ROLE_ID::iterator iter_role = m_map_role_id.begin();
	while(iter_role != m_map_role_id.end())
	{
		LIST_MASTER::iterator  iter_master2= get_list_master().begin();
		while(iter_master2 != get_list_master().end())
		{
			vector<DWORD>::iterator iter = (*iter_master2)->list_role.begin();
			while(iter != (*iter_master2)->list_role.end())
			{
				if(*iter == iter_role->first)
				{
					*iter = iter_role->second;
				}
				iter++;
			}
			iter_master2++;
		}

		iter_role++;
	}

	m_pCombin_db->UpdateMaster(m_list_master);

	LIST_MASTER::iterator iter_master = m_list_master.begin();
	while(iter_master != m_list_master.end())
	{
		tag_master* p = (*iter_master);
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_master++;
	}
	m_list_master.clear();
}

VOID CombinationDlg::ChangeGuerdonQuestID()
{
	LIST_GUERDON_QUEST::iterator iter_guerdon_quest = get_list_guerdon_quest().begin();
	while(iter_guerdon_quest != get_list_guerdon_quest().end())
	{
		INT16 quest_id = (INT16)(*iter_guerdon_quest)->n64Serial;
		(*iter_guerdon_quest)->n64Serial = (INT64)((INT64)(*iter_guerdon_quest)->dwSender << 32 | quest_id);
		iter_guerdon_quest++;
	}

	m_pCombin_db->UpdateGuerdonQuest(m_list_guerdon_quest);

	iter_guerdon_quest = get_list_guerdon_quest().begin();
	while(iter_guerdon_quest != get_list_guerdon_quest().end())
	{
		guerdon_quest* p = (*iter_guerdon_quest);
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_guerdon_quest++;
	}
	get_list_guerdon_quest().clear();
}

VOID CombinationDlg::ChangeMailItemID()
{

	INT32 nCurent = 0;
	INT32 nNum = m_map_item_id.size();

	MAP_ITEM_ID::iterator iter_item = m_map_item_id.begin();
	while(iter_item != m_map_item_id.end())
	{
		LIST_MAIL::iterator iter_mail = m_list_mail.begin();
		while(iter_mail != m_list_mail.end())
		{
			for(INT i = 0; i < 3; i++)
			{
				if((*iter_mail)->s_mail_base_.n64ItemSerial[i] == iter_item->first)
				{
					(*iter_mail)->s_mail_base_.n64ItemSerial[i] = iter_item->second;
				}
			}
			iter_mail++;
		}
		iter_item++;
		nCurent++;
		CString str;
		str.Format(_T("������%d/%d"), nCurent, nNum);
		m_process.SetWindowText(str);
	}

	m_pCombin_db->UpdateMail(m_list_mail);

	LIST_MAIL::iterator iter_mail = m_list_mail.begin();
	while(iter_mail != m_list_mail.end())
	{
		tag_load_mail* p = (*iter_mail);
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_mail++;
	}
	m_list_mail.clear();
}




VOID CombinationDlg::CheckAccountData()
{
	if (m_bThirdAccount)
	{
		MAP_THIRD_ACCOUNT_DATA::iterator iter = m_map_combin_third_account.begin();
		while(iter != m_map_combin_third_account.end())
		{
			m_pMainAccount_db->CheckThirdAccount(iter->second,dw_account_max_id);
			iter++;
		}
	}
	else
	{
		LIST_ACCOUNT_DATA::iterator iter = m_list_combin_account.begin();
		while(iter != m_list_combin_account.end())
		{
			m_pMainAccount_db->CheckAccount(*iter, dw_account_max_id);
			iter++;
		}
	}
}

VOID CombinationDlg::ChangeAccountCommonID()
{
	m_pCombin_db->ChangeAccountCommonIndex();

	if (m_bThirdAccount)
	{
		MAP_THIRD_ACCOUNT_DATA::iterator iter = m_map_no_exist_third_account.begin();
		while (iter != m_map_no_exist_third_account.end())
		{
			m_pCombin_db->ChangeAccountCommonID(iter->second);
			iter++;
		}
		MAP_THIRD_ACCOUNT_DATA::iterator iter1 = m_map_change_third_account.begin();
		while (iter1 != m_map_change_third_account.end())
		{
			m_pCombin_db->ChangeAccountCommonID(iter1->second);
			iter1++;
		}
	}
	else
	{
		LIST_ACCOUNT_DATA::iterator iter =  m_list_no_exist_account.begin();
		while(iter != m_list_no_exist_account.end())
		{
			m_pCombin_db->ChangeAccountCommonID(*iter);
			iter++;
		}

		LIST_ACCOUNT_DATA::iterator iter1 = m_list_change_account.begin();
		while(iter1 != m_list_change_account.end())
		{
			m_pCombin_db->ChangeAccountCommonID(*iter1);
			iter1++;
		}
	}
}

VOID CombinationDlg::ChangeRoleDataAccountID()
{
	m_pCombin_db->AddRoleDataChange();

	if (m_bThirdAccount)
	{
		MAP_THIRD_ACCOUNT_DATA::iterator iter = m_map_no_exist_third_account.begin();
		while(iter != m_map_no_exist_third_account.end())
		{
			m_pCombin_db->ChangeRoleDataAccountID(iter->second);
			iter++;
		}
		MAP_THIRD_ACCOUNT_DATA::iterator iter1 = m_map_change_third_account.begin();
		while (iter1 != m_map_change_third_account.end())
		{
			m_pCombin_db->ChangeRoleDataAccountID(iter1->second);
			iter1++;
		}
	}
	else
	{
		LIST_ACCOUNT_DATA::iterator iter =  m_list_no_exist_account.begin();
		while(iter != m_list_no_exist_account.end())
		{
			m_pCombin_db->ChangeRoleDataAccountID(*iter);
			iter++;
		}

		LIST_ACCOUNT_DATA::iterator iter1 = m_list_change_account.begin();
		while(iter1 != m_list_change_account.end())
		{
			m_pCombin_db->ChangeRoleDataAccountID(*iter1);
			iter1++;
		}
	}
}

VOID CombinationDlg::InsertAccount()
{
	if (m_bThirdAccount)
	{
		MAP_THIRD_ACCOUNT_DATA::iterator iter = m_map_no_exist_third_account.begin();
		while(iter != m_map_no_exist_third_account.end())
		{
			m_pMainAccount_db->InsertAccount(iter->second);
			iter++;
		}
	}
	else
	{
		LIST_ACCOUNT_DATA::iterator iter =  m_list_no_exist_account.begin();
		while(iter != m_list_no_exist_account.end())
		{
			m_pMainAccount_db->InsertAccount(*iter);
			iter++;
		}
	}
}
VOID CombinationDlg::InsertThirdAccount()
{
	MAP_THIRD_ACCOUNT_DATA::iterator iter = m_map_no_exist_third_account.begin();
	while(iter != m_map_no_exist_third_account.end())
	{
		m_pMainAccount_db->InsertThirdAccount(iter->second);
		iter++;
	}
}

VOID CombinationDlg::CleanAccountData()
{
	LIST_ACCOUNT_DATA::iterator iter = m_list_combin_account.begin();
	while(iter != m_list_combin_account.end())
	{
		tag_account_data* p = *iter;
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter++;
	}
	m_list_combin_account.clear();

	iter = m_list_no_exist_account.begin();
	while(iter != m_list_no_exist_account.end())
	{
		tag_account_data* p = *iter;
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter++;
	}
	m_list_no_exist_account.clear();

	iter = m_list_change_account.begin();
	while(iter != m_list_change_account.end())
	{
		tag_account_data* p = *iter;
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter++;
	}
	m_list_change_account.clear();
	//
	MAP_THIRD_ACCOUNT_DATA::iterator iter_third = m_map_change_third_account.begin();
	while(iter_third != m_map_change_third_account.end())
	{
		tag_third_account_data* p = iter_third->second;
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_third++;
	}
	m_map_change_third_account.clear();

	iter_third = m_map_no_exist_third_account.begin();
	while(iter_third != m_map_no_exist_third_account.end())
	{
		tag_third_account_data* p = iter_third->second;
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_third++;
	}
	m_map_no_exist_third_account.clear();

	iter_third = m_map_change_third_account.begin();
	while(iter_third != m_map_change_third_account.end())
	{
		tag_third_account_data* p = iter_third->second;
		if(VALID_POINT(p))
		{
			SAFE_DELETE(p);
		}
		iter_third++;
	}
	m_map_change_third_account.clear();
}

