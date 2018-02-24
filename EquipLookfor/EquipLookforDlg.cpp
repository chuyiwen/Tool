// EquipLookforDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EquipLookfor.h"
#include "EquipLookforDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEquipLookforDlg 对话框




CEquipLookforDlg::CEquipLookforDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEquipLookforDlg::IDD, pParent),mDBSession(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEquipLookforDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mDatabaseIP);
	DDX_Control(pDX, IDC_EDIT2, mDatabasePort);
	DDX_Control(pDX, IDC_EDIT3, mDatabaseUser);
	DDX_Control(pDX, IDC_EDIT4, mDatabasePassword);
	DDX_Control(pDX, IDC_EDIT6, mItemSerial);
	DDX_Control(pDX, IDC_LIST1, mListProperty);
	DDX_Control(pDX, ID_BUTTION_CONNECT, mConnectDB);
	DDX_Control(pDX, ID_BUTTION_GET, mQuery);
	DDX_Control(pDX, IDC_EDIT5, mDatabaseName);
	DDX_Control(pDX, IDC_CHECK1, mQueryFromDel);
}

BEGIN_MESSAGE_MAP(CEquipLookforDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BUTTION_GET, &CEquipLookforDlg::OnBnClickedButtionGet)
	ON_BN_CLICKED(ID_BUTTION_CONNECT, &CEquipLookforDlg::OnBnClickedButtionConnect)
END_MESSAGE_MAP()


// CEquipLookforDlg 消息处理程序

BOOL CEquipLookforDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	serverbase::init_network();
	serverbase::init_serverbase();
	mDatabaseIP.SetWindowText(_T("127.0.0.1"));
	mDatabasePort.SetWindowText(_T("3306"));
	mDatabaseUser.SetWindowText(_T("root"));
	mDatabaseName.SetWindowText(_T("gamedb"));
	mDatabasePassword.SetWindowText(_T("123456"));
	mQueryFromDel.SetCheck(TRUE);

	INT idx = 0;
	mListProperty.InsertColumn(idx++, _T("ServerID"));
	mListProperty.InsertColumn(idx++, _T("TypeID"));
	mListProperty.InsertColumn(idx++, _T("Number"));
	mListProperty.InsertColumn(idx++, _T("Bind"));
	mListProperty.InsertColumn(idx++, _T("OwnerID"));
	mListProperty.InsertColumn(idx++, _T("Quality"));
	mListProperty.InsertColumn(idx++, _T("Train Level"));
	mListProperty.InsertColumn(idx++, _T("Talent Point"));
	mListProperty.InsertColumn(idx++, _T("Star Level"));
	mListProperty.InsertColumn(idx++, _T("Ablity Level"));
	mListProperty.InsertColumn(idx++, _T("YiQi"));
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr1"));
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr2"));
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr3"));
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr4"));
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr5"));	
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr6"));	
	mListProperty.InsertColumn(idx++, _T("AdditionalAttr7"));	
	mListProperty.InsertColumn(idx++, _T("HoleNumber"));
	mListProperty.InsertColumn(idx++, _T("Hole1"));
	mListProperty.InsertColumn(idx++, _T("Hole2"));
	mListProperty.InsertColumn(idx++, _T("Hole3"));
	mListProperty.InsertColumn(idx++, _T("Hole4"));
	mListProperty.InsertColumn(idx++, _T("Hole5"));
	mListProperty.InsertColumn(idx++, _T("Hole6"));

	idx = 0;
	mListProperty.SetColumnWidth(idx++, 100);
	mListProperty.SetColumnWidth(idx++, 60);
	mListProperty.SetColumnWidth(idx++, 60); // number
	mListProperty.SetColumnWidth(idx++, 100); // bind
	mListProperty.SetColumnWidth(idx++, 75); //owner
	mListProperty.SetColumnWidth(idx++, 75);	// Quality
	mListProperty.SetColumnWidth(idx++, 100); // Train Level
	mListProperty.SetColumnWidth(idx++, 100); // Talent Point
	mListProperty.SetColumnWidth(idx++, 75); // Star Level
	mListProperty.SetColumnWidth(idx++, 100); // Ablity Level
	mListProperty.SetColumnWidth(idx++, 75); //YiQi
	mListProperty.SetColumnWidth(idx++, 200); //add1
	mListProperty.SetColumnWidth(idx++, 200);
	mListProperty.SetColumnWidth(idx++, 200);
	mListProperty.SetColumnWidth(idx++, 200);
	mListProperty.SetColumnWidth(idx++, 200);
	mListProperty.SetColumnWidth(idx++, 200);
	mListProperty.SetColumnWidth(idx++, 200);//add7
	mListProperty.SetColumnWidth(idx++, 80);//HoleNumber
	mListProperty.SetColumnWidth(idx++, 60);//hole1
	mListProperty.SetColumnWidth(idx++, 60);
	mListProperty.SetColumnWidth(idx++, 60);
	mListProperty.SetColumnWidth(idx++, 60);
	mListProperty.SetColumnWidth(idx++, 60);
	mListProperty.SetColumnWidth(idx++, 60);//hole6

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEquipLookforDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEquipLookforDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEquipLookforDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEquipLookforDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(mDBSession)
	{
		mDBSession->shut_down();
		delete mDBSession;
		mDBSession = NULL;
	}
	serverbase::destroy_network();
	serverbase::destroy_serverbase();
	CDialog::OnCancel();
}

const TCHAR* BA2(int t)
{
#define  CATTSTR(N)  case N: return _T(#N);

	switch(t)
	{
		CATTSTR(ERA_Physique)
		CATTSTR(ERA_Strength)
		CATTSTR(ERA_InnerForce)
		CATTSTR(ERA_Agility)
		CATTSTR(ERA_MaxHP)
		CATTSTR(ERA_MaxMP)
		CATTSTR(ERA_ExAttack)
		CATTSTR(ERA_ExDefense)
		CATTSTR(ERA_HitRate)
		CATTSTR(ERA_Dodge)
		CATTSTR(ERA_Block_Rate)
		CATTSTR(ERA_Crit_Rate)
		CATTSTR(ERA_Crit_Amount)
		CATTSTR(ERA_UnCrit_Rate)
		CATTSTR(ERA_UnCrit_Amount)
		CATTSTR(ERA_HPRegainRate)
		CATTSTR(ERA_MPRegainRate)
		CATTSTR(ERA_ExAttackMin)
		CATTSTR(ERA_ExAttackMax)
		CATTSTR(ERA_Derate_Ordinary)
		CATTSTR(ERA_Derate_Soil)
		CATTSTR(ERA_Derate_Gold)
		CATTSTR(ERA_Derate_Wood)
		CATTSTR(ERA_Derate_Fire)
		CATTSTR(ERA_Derate_Water)
	}
	return _T("");
}

const TCHAR* Q2S(int quality)
{
	switch(quality)
	{
	case EIQ_Quality0:		return _T("White");
	case EIQ_Quality1:		return _T("Blue");
	case EIQ_Quality2:		return _T("Blue");
	case EIQ_Quality3:		return _T("Purple");
	case EIQ_Quality4:		return _T("Orange");
	}
	return _T("UnKnown");
}

void CEquipLookforDlg::OnBnClickedButtionGet()
{
#pragma warning(push)
#pragma warning(disable:4800)
	mListProperty.DeleteAllItems( );
	if(!mDBSession || mDBSession->is_disconnect( )) 
	{
		DisableButton(FALSE);
		return;
	}

	CString tSerial; mItemSerial.GetWindowText(tSerial);
	INT64 n64Serial = _ttoi64(tSerial.GetBuffer( ));

	sql_language_disposal* in = mDBSession->get_io( );

	in->clear();
	in->write_string("select ");
	in->write_string(
		"serial,"	"num,"				"type_id,"		"bind,"				"lock_state,"
		"use_times,"		"first_gain_time,"	"creator_id,"	"create_time,"		"owner_id,"
		"account_id,"	"container_type_id,"	"suffix,"		"quality,"			"potval_used,"
		"min_use_level,"	"max_use_level,"		"min_dmg_in,"		"min_dmg,"			"max_dmg,"		
		"armor,"		"potval,"			"role_att_effect," "posy_times," "posy_effect,"
		"engrave_times,"	"engrave_att,"		"hole_num,"		"hole_gem_id,"		"brand_level,"
		"derate_val,"	"x_ful_level,"		"wuxing,"		"can_cut,"			"xer_in_id,"
		"xer_out_id,"	"0,"				"0,"			"special_att,"			"appearance,"
		"rein,"			"savvy,"			"fortune,"		"color_id,"			"quality_mod_pct,"
		"quality_mod_pct_ex,"	"create_mode,"		"create_id,"		"att_a_lim_mod," "att_a_lim_mod_pct,"
		"flare_val,"		"name_id,"			"pot_val_mod_pct,"	"consolidate_level," "exp," "level," 
		"max_dmg_in,"		"armor_in,"			"equip_add_att,"	"talent_point,"		"max_talent_point,"
		"skill_list,"	"bind_time,"			"rating,"			"script_data1,"		"script_data2, " 
		"create_bind,"	"consolidate_level_star");
	if(mQueryFromDel.GetCheck( ))
		in->write_string(" from item_del left join equip_del using(serial)");
	else in->write_string(" from item left join equip using(serial)");

	in->where_item();
	in->write_string("serial=") << n64Serial;

	execute_result*  p_result = mDBSession->sql_query(in);mDBSession->return_io(in);
	if(!p_result || p_result->get_row_count( ) <= 0)
	{
		if(p_result)mDBSession->free_result_query(p_result);
		AfxMessageBox(_T("Equip is not exist!"), MB_ICONINFORMATION | MB_OK);
		return;
	}

	void* mem = malloc(sizeof(tagEquip));
	for(int n = 0; n < p_result->get_row_count( ); ++n, p_result->next_row( ))
	{
		memset(mem, 0, sizeof(tagEquip));

		tagItem* pItem = static_cast<tagItem*>(mem);
		pItem->n64_serial 					= (*p_result)[0].get_long();
		pItem->n16Num 						= (*p_result)[1].get_short();
		pItem->dw_data_id 					= (*p_result)[2].get_dword();
		pItem->byBind 						= (*p_result)[3].get_int();
		pItem->bCreateBind					= (*p_result)[66].get_bool();
		pItem->bLock 						= (*p_result)[4].get_bool();
		pItem->nUseTimes 					= (*p_result)[5].get_int();
		pItem->dwCreatorID 					= (*p_result)[7].get_dword();
		pItem->dwOwnerID 					= (*p_result)[9].get_dword();
		pItem->dw_account_id 					= (*p_result)[10].get_dword();
		pItem->eConType 					= (EItemConType)(*p_result)[11].get_int();
		pItem->n16Index 					= (*p_result)[12].get_short();
		pItem->eCreateMode					= (EItemCreateMode)(*p_result)[46].get_int();
		pItem->dwCreateID					= (*p_result)[47].get_dword();
		pItem->dwNameID						=(*p_result)[51].get_dword();
		DataTime2DwordTime(pItem->dw1stGainTime, (*p_result)[6].get_string(), (*p_result)[6].get_length());
		DataTime2DwordTime(pItem->dwCreateTime, (*p_result)[8].get_string(), (*p_result)[8].get_length());
		DataTime2DwordTime(pItem->dwBindTime, (*p_result)[62].get_string(), (*p_result)[62].get_length());

		pItem->dw_script_data[0] = (*p_result)[64].get_dword();
		pItem->dw_script_data[1] = (*p_result)[65].get_dword();

		if(MIsEquipment(pItem->dw_data_id))
		{
			tagEquip * p_equip = ( tagEquip *) mem ;  

			// 装备附加属性
			p_equip->equipSpec.byQuality 		= (*p_result)[13].get_byte();
			p_equip->equipSpec.nPotValUsed 		= (*p_result)[14].get_int();
			p_equip->equipSpec.byMinUseLevel 	= (*p_result)[15].get_byte();
			p_equip->equipSpec.byMaxUseLevel 	= (*p_result)[16].get_byte();
			p_equip->equipSpec.n16MinDmg 		= (*p_result)[18].get_short();
			p_equip->equipSpec.n16MaxDmg 		= (*p_result)[19].get_short();
			p_equip->equipSpec.n16Armor 		= (*p_result)[20].get_short();
			p_equip->equipSpec.nPotVal 			= (*p_result)[21].get_int();
			p_equip->equipSpec.byPosyTimes 		= (*p_result)[23].get_byte();
			p_equip->equipSpec.byEngraveTimes 	= (*p_result)[25].get_byte();
			p_equip->equipSpec.byHoleNum 		= (*p_result)[27].get_byte();
			p_equip->equipSpec.byBrandLevel 	= (*p_result)[29].get_byte();
			p_equip->equipSpec.byLongfuLevel	= (*p_result)[31].get_byte();
			p_equip->equipSpec.bCanCut 			= (*p_result)[33].get_bool();
			p_equip->equipSpec.bySpecAtt		= (*p_result)[38].get_int();

			// 时装附加属性
			p_equip->equipSpec.n16Appearance				= (*p_result)[39].get_int();
			p_equip->equipSpec.byRein					= (*p_result)[40].get_byte();
			p_equip->equipSpec.bySavvy					= (*p_result)[41].get_byte();
			p_equip->equipSpec.byFortune					= (*p_result)[42].get_byte();
			p_equip->equipSpec.n8ColorID					= (INT8)(*p_result)[43].get_int();

			p_equip->equipSpec.n16QltyModPct				= (*p_result)[44].get_short();
			p_equip->equipSpec.n16QltyModPctEx			= (*p_result)[45].get_short();
			p_equip->equipSpec.n16PotValModPct			= (*p_result)[52].get_short();
			p_equip->equipSpec.n16AttALimMod				= (*p_result)[48].get_int();
			p_equip->equipSpec.n16AttALimModPct			= (*p_result)[49].get_int();
			p_equip->equipSpec.byFlareVal				= (*p_result)[50].get_byte();
			p_equip->equipSpec.byConsolidateLevel		= (*p_result)[53].get_byte();
			p_equip->equipSpec.nCurLevelExp				= (*p_result)[54].get_int();
			p_equip->equipSpec.nLevel					= (*p_result)[55].get_int();
			p_equip->equipSpec.byTalentPoint				= (*p_result)[59].get_int();
			p_equip->equipSpec.byMaxTalentPoint			= (*p_result)[60].get_int();
			p_equip->equipSpec.nRating					= (*p_result)[63].get_int();

			(*p_result)[22].get_blob(p_equip->equipSpec.nRoleAttEffect, min((*p_result)[22].get_length(), sizeof(p_equip->equipSpec.nRoleAttEffect)));
			(*p_result)[24].get_blob(p_equip->equipSpec.PosyEffect, min((*p_result)[24].get_length(), sizeof(p_equip->equipSpec.PosyEffect)));
			(*p_result)[26].get_blob(p_equip->equipSpec.nEngraveAtt, min((*p_result)[26].get_length(), sizeof(p_equip->equipSpec.nEngraveAtt)));
			(*p_result)[28].get_blob(p_equip->equipSpec.dwHoleGemID, min((*p_result)[28].get_length(), sizeof(p_equip->equipSpec.dwHoleGemID)));
			(*p_result)[30].get_blob(p_equip->equipSpec.nBrandAtt, min((*p_result)[30].get_length(), sizeof(p_equip->equipSpec.nBrandAtt)));
			(*p_result)[32].get_blob(p_equip->equipSpec.byLongfuAtt, min((*p_result)[32].get_length(), sizeof(p_equip->equipSpec.byLongfuAtt)));
			(*p_result)[58].get_blob(p_equip->equipSpec.EquipAttitionalAtt, min((*p_result)[58].get_length(), sizeof(p_equip->equipSpec.EquipAttitionalAtt)));
			(*p_result)[61].get_blob(p_equip->equipSpec.dwSkillList, min((*p_result)[61].get_length(), sizeof(p_equip->equipSpec.dwSkillList)));
			p_equip->equipSpec.byConsolidateLevelStar		= (*p_result)[67].get_byte();
		}

		ShowEquip(pItem);
	}

	free(mem);
	mDBSession->free_result_query(p_result);
#pragma warning(pop)
}
void CEquipLookforDlg::ShowEquip(VOID* p, INT i)
{
#define INSERT_ONE_ROW_HAED(VALUE)\
	nRows = mListProperty.InsertItem(i, VALUE);

#define INSERT_ONE_ROW_ITEM(VALUE)\
	mListProperty.SetItemText(nRows, ++nIndex, VALUE);

	INT nIndex = 0, nRows = 0;
	TCHAR tBuffer[256] = {0}, tCommonBuffer[128] = {0};

	tagItem* pItem = static_cast<tagItem*>(p);
	_i64tot(pItem->n64_serial, tBuffer, 10);
	INSERT_ONE_ROW_HAED(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot( pItem->dw_data_id, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pItem->n16Num, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	switch(pItem->byBind)
	{
	case 0:
		_tcscpy(tBuffer, _T("Unknow"));
		break;
	case 1:
		_tcscpy(tBuffer, _T("UnBind"));
		break;
	case 2:
		_tcscpy(tBuffer, _T("StoneBind"));
		break;
	case 3:
		_tcscpy(tBuffer, _T("NPCBind"));
		break;
	case 4:
		_tcscpy(tBuffer, _T("SystemBind"));
		break;
	case 5:
		_tcscpy(tBuffer, _T("EquipmentBind"));
		break;
	}
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pItem->dwOwnerID, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	if(!MIsEquipment(pItem->dw_data_id))
	{
		return;
	}
	
	tagEquip* pEquip = static_cast<tagEquip*>(p);

	INSERT_ONE_ROW_ITEM(Q2S(pEquip->equipSpec.byQuality));

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pEquip->equipSpec.nLevel, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pEquip->equipSpec.byTalentPoint, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pEquip->equipSpec.byConsolidateLevelStar, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pEquip->equipSpec.byConsolidateLevel, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pEquip->equipSpec.nCurLevelExp, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	for(int k = 0 ; k < MAX_ADDITIONAL_EFFECT ; ++k)
	{
		memset(tBuffer, 0, sizeof(tBuffer));
		memset(tCommonBuffer, 0, sizeof(tCommonBuffer));
		if(pEquip->equipSpec.EquipAttitionalAtt[k].nValue)
		{
			if(pEquip->equipSpec.EquipAttitionalAtt[k].eRoleAtt == ERA_ExAttack)
				_itot(pEquip->equipSpec.EquipAttitionalAtt[k].nValue / 10, tBuffer, 10);
			else _itot(pEquip->equipSpec.EquipAttitionalAtt[k].nValue, tBuffer, 10);
			_stprintf(tCommonBuffer, _T("%s:%d"), BA2(pEquip->equipSpec.EquipAttitionalAtt[k].eRoleAtt), pEquip->equipSpec.EquipAttitionalAtt[k].nValue);
		}
	
		INSERT_ONE_ROW_ITEM(tCommonBuffer);
	}

	memset(tBuffer, 0, sizeof(tBuffer));
	_itot(pEquip->equipSpec.byHoleNum, tBuffer, 10);
	INSERT_ONE_ROW_ITEM(tBuffer);

	for(int n = 0; n < MAX_EQUIPHOLE_NUM; ++n)
	{
		memset(tBuffer, 0, sizeof(tBuffer));
		_itot(pEquip->equipSpec.dwHoleGemID[n], tBuffer, 10);
		INSERT_ONE_ROW_ITEM(tBuffer);
	}
}
void CEquipLookforDlg::OnBnClickedButtionConnect()
{
	// TODO: 在此添加控件通知处理程序代码
#define MAX_CHAR 128
	INT nPort = 3306;
	CString tDBIP, tDBPort, tDBUser, tDBName, tDBPassword, tMSG;

	mDatabaseIP.GetWindowText(tDBIP);
	mDatabasePort.GetWindowText(tDBPort);
	mDatabaseUser.GetWindowText(tDBUser);
	mDatabaseName.GetWindowText(tDBName);
	mDatabasePassword.GetWindowText(tDBPassword);
	nPort = _ttoi(tDBPort.GetBuffer( ));

	if(mDBSession) delete mDBSession;

	mDBSession = new odbc::db_interface;
	BOOL bResult = mDBSession->init_db( tDBIP.GetBuffer( ), tDBUser.GetBuffer( ), 
		tDBPassword.GetBuffer( ), tDBName.GetBuffer( ), nPort);

	DisableButton(bResult);

	tMSG.LoadString(bResult ? IDS_CONNECTDBOK : IDS_CONNECTDBFAIL);
	if(!bResult)AfxMessageBox(tMSG.GetBuffer( ), MB_ICONERROR | MB_OK);
}

void CEquipLookforDlg::DisableButton(BOOL Success)
{
	mDatabaseIP.EnableWindow(!Success);
	mDatabasePort.EnableWindow(!Success);
	mDatabaseUser.EnableWindow(!Success);
	mDatabaseName.EnableWindow(!Success);
	mDatabasePassword.EnableWindow(!Success);
	mConnectDB.EnableWindow(!Success);
	mItemSerial.EnableWindow(Success);
	mQuery.EnableWindow(Success);
	mQueryFromDel.EnableWindow(Success);
}
