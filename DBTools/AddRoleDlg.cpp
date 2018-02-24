// AddRoleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DBTools.h"
#include "AddRoleDlg.h"
#include "DB.h"
#include "DBToolsDlg.h"

// AddRoleDlg 对话框

IMPLEMENT_DYNAMIC(AddRoleDlg, CDialog)

AddRoleDlg::AddRoleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddRoleDlg::IDD, pParent),m_pDB(NULL)
	, m_min_account_id(0)
	, m_max_account_id(0)
	, m_role_name(_T(""))
	, m_class(0)
	, m_sex(0)
	,m_dw_max_role_id(0)
{

}

AddRoleDlg::~AddRoleDlg()
{
}

void AddRoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_min_account_id);
	DDX_Text(pDX, IDC_EDIT2, m_max_account_id);
	DDX_Text(pDX, IDC_EDIT3, m_role_name);
	DDX_CBIndex(pDX, IDC_COMBO1, m_class);
	DDX_CBIndex(pDX, IDC_COMBO8, m_sex);
}


BEGIN_MESSAGE_MAP(AddRoleDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &AddRoleDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// AddRoleDlg 消息处理程序

VOID AddRoleDlg::SetDB(CDB* pDB)
{
	m_pDB = pDB;
}

VOID AddRoleDlg::Get_Role_Max_id()
{
	m_pDB->Get_Role_Max_ID(m_dw_max_role_id);
}

static DWORD n_rand_seed = 0;
void AddRoleDlg::OnBnClickedButton1()
{
	UpdateData();
	Get_Role_Max_id();
	s_create_role_info st_create;
	// TODO: 在此添加控件通知处理程序代码
	for(DWORD i = m_min_account_id; i < m_max_account_id; i++)
	{
		ZeroMemory(&st_create, sizeof(s_create_role_info));
		DWORD n_result = ((n_rand_seed = n_rand_seed * 1103515245 + 12345) >> 1 ) & LONG_MAX;
		
		INT n_class = (n_result%5)+1;
		st_create.e_class_type_ = (EClassType)n_class;
		st_create.avatar.byClass = (EClassType)n_class;
		st_create.by_level_ = 1;
		st_create.create_time_ = GetCurrentDWORDTime();
		st_create.dw_map_id_ = get_tool()->crc32("s01");

	/*	switch(st_create.e_class_type_)
		{
		case EV_Assassin:
		case EV_Apothecary:
			{
				st_create.avatar.bySex = 0;
				break;
			}
		case EV_Warrior:
			{
				st_create.avatar.bySex = 1;
				break;
			}
		default:
			{
				INT n_sex = n_result%2;
				st_create.avatar.bySex = n_sex;
				break;
			}
		}*/
		
		CString str;
		str.Format(_T("%s%d"), m_role_name, ++m_dw_max_role_id);
		wcsncpy(st_create.sz_role_name, str, X_SHORT_NAME);

		m_pDB->create_role(i, m_dw_max_role_id, st_create);
	}

	if(MessageBox(_T("角色添加完成"), _T("提示"), MB_OK) == IDOK)
	{
		OnCancel();
	}
}

void AddRoleDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDB->GetDBToolsDlg()->ShowWindow(TRUE);
	CDialog::OnCancel();
}
