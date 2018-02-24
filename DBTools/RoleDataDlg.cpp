// RoleDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBTools.h"
#include "RoleDataDlg.h"
#include "DB.h"
#include "DBToolsDlg.h"


// CRoleDataDlg dialog

IMPLEMENT_DYNAMIC(CRoleDataDlg, CDialog)

CRoleDataDlg::CRoleDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoleDataDlg::IDD, pParent)
{

}

CRoleDataDlg::~CRoleDataDlg()
{
}

void CRoleDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_EDIT1, m_RoleNameEdit);
	DDX_Control(pDX, IDC_LIST1, m_RoleDataList);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_EDIT2, m_szRoleNameEdit);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_EDIT3, m_bySexEdit);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_EDIT4, m_wHairMdlIDEdit);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_EDIT5, m_wHairTexIDEdit);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);
	DDX_Control(pDX, IDC_EDIT6, m_wFaceMdlIDEdit);
	DDX_Control(pDX, IDC_STATIC7, m_Static7);
	DDX_Control(pDX, IDC_EDIT7, m_wFaceDetailTexIDEdit);
	DDX_Control(pDX, IDC_STATIC8, m_Static8);
	DDX_Control(pDX, IDC_EDIT8, m_wDressMdlIDEdit);
	DDX_Control(pDX, IDC_STATIC9, m_Static9);
	DDX_Control(pDX, IDC_EDIT9, m_bFashionDisplayEdit);
	DDX_Control(pDX, IDC_STATIC10, m_Static10);
	DDX_Control(pDX, IDC_EDIT10, m_dwMapIDEdit);
	DDX_Control(pDX, IDC_EDIT11, m_fCoordinateX);
	DDX_Control(pDX, IDC_EDIT12, m_fCoordinateY);
	DDX_Control(pDX, IDC_EDIT13, m_fCoordinateZ);
	DDX_Control(pDX, IDC_EDIT14, m_fFaceX);
	DDX_Control(pDX, IDC_EDIT15, m_fFaceY);
	DDX_Control(pDX, IDC_EDIT16, m_fFaceZ);
	DDX_Control(pDX, IDC_COMBO2, m_eClassCB);
	DDX_Control(pDX, IDC_STATIC17, m_Static17);
	DDX_Control(pDX, IDC_STATIC18, m_Static18);
	DDX_Control(pDX, IDC_COMBO3, m_eClassExCB);
	DDX_Control(pDX, IDC_STATIC19, m_Static19);
	DDX_Control(pDX, IDC_EDIT17, m_nLevelEdit);
	DDX_Control(pDX, IDC_STATIC20, m_Static20);
	DDX_Control(pDX, IDC_EDIT18, m_nCurExpEdit);
	DDX_Control(pDX, IDC_STATIC21, m_Static21);
	DDX_Control(pDX, IDC_EDIT19, m_nHPEdit);
	DDX_Control(pDX, IDC_STATIC22, m_Static22);
	DDX_Control(pDX, IDC_EDIT20, m_nMPEdit);
	DDX_Control(pDX, IDC_STATIC23, m_Static23);
	DDX_Control(pDX, IDC_EDIT21, m_nAttPointEdit);
	DDX_Control(pDX, IDC_STATIC24, m_Static24);
	DDX_Control(pDX, IDC_EDIT22, m_nTalentPointEdit);
	DDX_Control(pDX, IDC_STATIC25, m_Static25);
	DDX_Control(pDX, IDC_EDIT23, m_ERA_PhysiqueEdit);
	DDX_Control(pDX, IDC_STATIC26, m_Static26);
	DDX_Control(pDX, IDC_EDIT24, m_ERA_StrengthEdit);
	DDX_Control(pDX, IDC_STATIC27, m_Static27);
	DDX_Control(pDX, IDC_EDIT25, m_ERA_PneumaEdit);
	DDX_Control(pDX, IDC_STATIC28, m_Static28);
	DDX_Control(pDX, IDC_EDIT26, m_ERA_InnerForceEdit);
	DDX_Control(pDX, IDC_STATIC29, m_Static29);
	DDX_Control(pDX, IDC_EDIT27, m_ERA_TechniqueEdit);
	DDX_Control(pDX, IDC_STATIC30, m_Static30);
	DDX_Control(pDX, IDC_EDIT28, m_ERA_AgilityEdit);
	DDX_Control(pDX, IDC_STATIC31, m_Static31);
	DDX_Control(pDX, IDC_EDIT29, m_nInjuryEdit);
	DDX_Control(pDX, IDC_STATIC32, m_Static32);
	DDX_Control(pDX, IDC_EDIT30, m_nVitalityEdit);
	DDX_Control(pDX, IDC_STATIC33, m_Static33);
	DDX_Control(pDX, IDC_EDIT31, m_nKnowledgeEdit);
	DDX_Control(pDX, IDC_STATIC34, m_Static34);
	DDX_Control(pDX, IDC_EDIT32, m_nMoralityEdit);
	DDX_Control(pDX, IDC_STATIC35, m_Static35);
	DDX_Control(pDX, IDC_EDIT33, m_nCultureEdit);
	DDX_Control(pDX, IDC_STATIC36, m_Static36);
	DDX_Control(pDX, IDC_EDIT34, m_nCreditEdit);
	DDX_Control(pDX, IDC_STATIC37, m_Static37);
	DDX_Control(pDX, IDC_EDIT35, m_nIdentityEdit);
	DDX_Control(pDX, IDC_STATIC38, m_Static38);
	DDX_Control(pDX, IDC_EDIT36, m_nVIPPointEdit);
	DDX_Control(pDX, IDC_STATIC39, m_Static39);
	DDX_Control(pDX, IDC_EDIT37, m_n16BagSizeEdit);
	DDX_Control(pDX, IDC_STATIC40, m_Static40);
	DDX_Control(pDX, IDC_EDIT38, m_nBagGoldEdit);
	DDX_Control(pDX, IDC_STATIC41, m_Static41);
	DDX_Control(pDX, IDC_EDIT39, m_nBagSilverEdit);
	DDX_Control(pDX, IDC_STATIC42, m_Static42);
	DDX_Control(pDX, IDC_EDIT40, m_nBagYuanBaoEdit);
	DDX_Control(pDX, IDC_STATIC43, m_Static43);
	DDX_Control(pDX, IDC_EDIT41, m_dwGuildIDEdit);
	DDX_Control(pDX, IDC_STATIC44, m_Static44);
	DDX_Control(pDX, IDC_EDIT42, m_CreateTimeEdit);
	DDX_Control(pDX, IDC_STATIC45, m_Static45);
	DDX_Control(pDX, IDC_EDIT43, m_LoginTimeEdit);
	DDX_Control(pDX, IDC_STATIC46, m_Static46);
	DDX_Control(pDX, IDC_EDIT44, m_LogoutTimeEdit);
	DDX_Control(pDX, IDC_STATIC47, m_Static47);
	DDX_Control(pDX, IDC_EDIT45, m_nOnlineTimeEdit);
	DDX_Control(pDX, IDC_STATIC48, m_Static48);
	DDX_Control(pDX, IDC_EDIT46, m_nCurOnlineTimeEdit);
	DDX_Control(pDX, IDC_STATIC49, m_Static49);
	DDX_Control(pDX, IDC_EDIT47, m_nRageEdit);
	DDX_Control(pDX, IDC_STATIC50, m_Static50);
	DDX_Control(pDX, IDC_EDIT48, m_nEnduranceEdit);
	DDX_Control(pDX, IDC_STATIC51, m_Static51);
	DDX_Control(pDX, IDC_EDIT49, m_bSafeGuardEdit);
	DDX_Control(pDX, IDC_STATIC52, m_Static52);
	DDX_Control(pDX, IDC_EDIT50, m_CloseSafeGuardTimeEdit);
	DDX_Control(pDX, IDC_COMBO4, m_eTypeCB0);
	DDX_Control(pDX, IDC_EDIT51, m_nPointEdit0);
	DDX_Control(pDX, IDC_COMBO5, m_eTypeEdit1);
	DDX_Control(pDX, IDC_EDIT52, m_nPointEdit1);
	DDX_Control(pDX, IDC_COMBO6, m_eTypeEdit2);
	DDX_Control(pDX, IDC_EDIT53, m_nPointEdit2);
	DDX_Control(pDX, IDC_COMBO7, m_eTypeEdit3);
	DDX_Control(pDX, IDC_EDIT54, m_nPointEdit3);
	DDX_Control(pDX, IDC_STATIC53, m_Static53);
	DDX_Control(pDX, IDC_EDIT55, m_dwRebornMapIDEdit);
	DDX_Control(pDX, IDC_STATIC54, m_Static54);
	DDX_Control(pDX, IDC_EDIT56, m_nTotalTaxEdit);
	DDX_Control(pDX, IDC_STATIC55, m_Static55);
	DDX_Control(pDX, IDC_EDIT57, m_nMoraleEdit);
	DDX_Control(pDX, IDC_STATIC56, m_Static56);
	DDX_Control(pDX, IDC_EDIT58, m_dwTimeGetMallFreeEdit);
	DDX_Control(pDX, IDC_STATIC57, m_Static57);
	DDX_Control(pDX, IDC_EDIT59, m_u16ActiveTitleIDEdit);
	DDX_Control(pDX, IDC_STATIC58, m_Static58);
	DDX_Control(pDX, IDC_EDIT60, m_nExVolumeEdit);
	DDX_Control(pDX, IDC_STATIC59, m_Static59);
	DDX_Control(pDX, IDC_EDIT61, m_nTreasureSumEdit);
	DDX_Control(pDX, IDC_STATIC60, m_Static60);
	DDX_Control(pDX, IDC_EDIT62, m_byStallLevelEdit);
	DDX_Control(pDX, IDC_STATIC61, m_Static61);
	DDX_Control(pDX, IDC_EDIT63, m_nStallDailyExpEdit);
	DDX_Control(pDX, IDC_STATIC62, m_Static62);
	DDX_Control(pDX, IDC_EDIT64, m_nStallCurExpEdit);
	DDX_Control(pDX, IDC_STATIC63, m_Static63);
	DDX_Control(pDX, IDC_EDIT65, m_dwLastStallTimeEdit);
}


BEGIN_MESSAGE_MAP(CRoleDataDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CRoleDataDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CRoleDataDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CRoleDataDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CRoleDataDlg message handlers

BOOL CRoleDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	InitStatic();
	InitRoleData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

VOID CRoleDataDlg::InitStatic()
{
	m_Static1.SetWindowText(_T("账号查询"));
	m_RoleNameEdit.SetWindowText(_T(""));
	m_Static3.SetWindowText(_T("性别"));
	m_Static4.SetWindowText(_T("发型"));
	m_Static5.SetWindowText(_T("发色"));
	m_Static6.SetWindowText(_T("面部五官"));
	m_Static7.SetWindowText(_T("面部细节"));
	m_Static8.SetWindowText(_T("服装样式"));
	m_Static9.SetWindowText(_T("是否显示时装"));
	m_Static10.SetWindowText(_T("所在地图ID"));
	m_Static17.SetWindowText(_T("职业"));
	m_Static18.SetWindowText(_T("扩展职业"));
	m_Static19.SetWindowText(_T("玩家等级"));
	m_Static20.SetWindowText(_T("玩家当前级别的升级经验"));
	m_Static21.SetWindowText(_T("体力"));
	m_Static22.SetWindowText(_T("真气"));
	m_Static23.SetWindowText(_T("玩家可用的属性点"));
	m_Static24.SetWindowText(_T("玩家可用的天资点"));
	m_Static25.SetWindowText(_T("当前筋骨"));
	m_Static26.SetWindowText(_T("当前劲力"));
	m_Static27.SetWindowText(_T("当前元气"));
	m_Static28.SetWindowText(_T("当前内力"));
	m_Static29.SetWindowText(_T("当前技力"));
	m_Static30.SetWindowText(_T("当前身法"));
	m_Static31.SetWindowText(_T("内伤"));
	m_Static32.SetWindowText(_T("活力"));
	m_Static33.SetWindowText(_T("阅历"));
	m_Static34.SetWindowText(_T("道德"));
	m_Static35.SetWindowText(_T("武学修为"));
	m_Static36.SetWindowText(_T("信用度"));
	m_Static37.SetWindowText(_T("身份"));
	m_Static38.SetWindowText(_T("会员积分"));
	m_Static39.SetWindowText(_T("背包大小"));
	m_Static40.SetWindowText(_T("背包中金子数"));
	m_Static41.SetWindowText(_T("背包中银子数"));
	m_Static42.SetWindowText(_T("背包中元宝数"));
	m_Static43.SetWindowText(_T("帮派id"));
	m_Static44.SetWindowText(_T("创建时间"));
	m_Static45.SetWindowText(_T("登入时间"));
	m_Static46.SetWindowText(_T("登出时间"));
	m_Static47.SetWindowText(_T("总在线时常"));
	m_Static48.SetWindowText(_T("当次在线时常"));
	m_Static49.SetWindowText(_T("怒气"));
	m_Static50.SetWindowText(_T("持久力"));
	m_Static51.SetWindowText(_T("是否被PK保护"));
	m_Static52.SetWindowText(_T("上次关闭PK保护的时间"));
	m_Static53.SetWindowText(_T("复活地图ID"));
	m_Static54.SetWindowText(_T("缴税总额"));
	m_Static55.SetWindowText(_T("士气"));
	m_Static56.SetWindowText(_T("上次从商城领取免费物品时间"));
	m_Static57.SetWindowText(_T("当前称号"));
	m_Static58.SetWindowText(_T("角色赠点数"));
	m_Static59.SetWindowText(_T("玩家开启宝箱数"));
	m_Static60.SetWindowText(_T("摊位等级"));
	m_Static61.SetWindowText(_T("摊位当日经验"));
	m_Static62.SetWindowText(_T("摊位当前等级经验"));
	m_Static63.SetWindowText(_T("摊位最近更新时间"));
}

VOID CRoleDataDlg::InitRoleData()
{
	m_szRoleNameEdit.SetWindowText(_T(""));
	m_bySexEdit.SetWindowText(_T(""));
	m_wHairMdlIDEdit.SetWindowText(_T(""));
	m_wHairTexIDEdit.SetWindowText(_T(""));
	m_wFaceMdlIDEdit.SetWindowText(_T(""));
	m_wFaceDetailTexIDEdit.SetWindowText(_T(""));
	m_wDressMdlIDEdit.SetWindowText(_T(""));
	m_bFashionDisplayEdit.SetWindowText(_T(""));
	m_dwMapIDEdit.SetWindowText(_T(""));
	m_fCoordinateX.SetWindowText(_T(""));
	m_fCoordinateY.SetWindowText(_T(""));
	m_fCoordinateZ.SetWindowText(_T(""));
	m_fFaceX.SetWindowText(_T(""));
	m_fFaceY.SetWindowText(_T(""));
	m_fFaceZ.SetWindowText(_T(""));
	m_eClassCB.SetCurSel(0);
	m_eClassExCB.SetCurSel(0);
	m_nLevelEdit.SetWindowText(_T(""));
	m_nCurExpEdit.SetWindowText(_T(""));
	m_nHPEdit.SetWindowText(_T(""));
	m_nMPEdit.SetWindowText(_T(""));
	m_nAttPointEdit.SetWindowText(_T(""));
	m_nTalentPointEdit.SetWindowText(_T(""));
	m_ERA_PhysiqueEdit.SetWindowText(_T(""));
	m_ERA_StrengthEdit.SetWindowText(_T(""));
	m_ERA_PneumaEdit.SetWindowText(_T(""));
	m_ERA_InnerForceEdit.SetWindowText(_T(""));
	m_ERA_TechniqueEdit.SetWindowText(_T(""));
	m_ERA_AgilityEdit.SetWindowText(_T(""));
	m_nInjuryEdit.SetWindowText(_T(""));
	m_nVitalityEdit.SetWindowText(_T(""));
	m_nKnowledgeEdit.SetWindowText(_T(""));
	m_nMoralityEdit.SetWindowText(_T(""));
	m_nCultureEdit.SetWindowText(_T(""));
	m_nCreditEdit.SetWindowText(_T(""));
	m_nIdentityEdit.SetWindowText(_T(""));
	m_nVIPPointEdit.SetWindowText(_T(""));
	m_n16BagSizeEdit.SetWindowText(_T(""));
	m_nBagGoldEdit.SetWindowText(_T(""));
	m_nBagSilverEdit.SetWindowText(_T(""));
	m_nBagYuanBaoEdit.SetWindowText(_T(""));
	m_dwGuildIDEdit.SetWindowText(_T(""));
	m_CreateTimeEdit.SetWindowText(_T(""));
	m_LoginTimeEdit.SetWindowText(_T(""));
	m_LogoutTimeEdit.SetWindowText(_T(""));
	m_nOnlineTimeEdit.SetWindowText(_T(""));
	m_nCurOnlineTimeEdit.SetWindowText(_T(""));
	m_nRageEdit.SetWindowText(_T(""));
	m_nEnduranceEdit.SetWindowText(_T(""));
	m_bSafeGuardEdit.SetWindowText(_T(""));
	m_CloseSafeGuardTimeEdit.SetWindowText(_T(""));
	m_eTypeCB0.SetCurSel(0);
	m_nPointEdit0.SetWindowText(_T(""));
	m_eTypeEdit1.SetCurSel(0);
	m_nPointEdit1.SetWindowText(_T(""));
	m_eTypeEdit2.SetCurSel(0);
	m_nPointEdit2.SetWindowText(_T(""));
	m_eTypeEdit3.SetCurSel(0);
	m_nPointEdit3.SetWindowText(_T(""));
	m_dwRebornMapIDEdit.SetWindowText(_T(""));
	m_nTotalTaxEdit.SetWindowText(_T(""));
	m_nMoraleEdit.SetWindowText(_T(""));
	m_dwTimeGetMallFreeEdit.SetWindowText(_T(""));
	m_u16ActiveTitleIDEdit.SetWindowText(_T(""));
	m_nExVolumeEdit.SetWindowText(_T(""));
	m_nTreasureSumEdit.SetWindowText(_T(""));
	m_byStallLevelEdit.SetWindowText(_T(""));
	m_nStallDailyExpEdit.SetWindowText(_T(""));
	m_nStallCurExpEdit.SetWindowText(_T(""));
	m_dwLastStallTimeEdit.SetWindowText(_T(""));
}

void CRoleDataDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pDB)
	{
		m_pDB->GetDataBase()->shut_down();
		m_pDB->GetDBToolsDlg()->ShowWindow(TRUE);
		m_pDB = NULL;
	}
	CDialog::OnCancel();
}

void CRoleDataDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_RoleNameEdit.GetWindowText(str);
	if(m_pDB)
	{
		m_pDB->CleanRoleData();
		m_RoleDataList.ResetContent();
		CHAR RoleName[X_SHORT_NAME];
		WideCharToMultiByte(CP_ACP, 0, str, -1, RoleName, sizeof(CHAR)*X_SHORT_NAME, NULL, NULL);
		m_pDB->LoadRoleData(RoleName);
	}
}

VOID CRoleDataDlg::AddRoleData(CString &str)
{
	m_RoleDataList.AddString(str);
}

VOID CRoleDataDlg::SetRoleData(s_role_data_load* pRoleData)
{
	s_role_data_const	*pRoleDataConst = &pRoleData->role_data_const_;
	s_role_data_save		*pRoleDataSave	= &pRoleData->role_data_save_;
	CString str;
	str.Format(_T("%s"), pRoleDataConst->sz_role_name);
	m_szRoleNameEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataConst->avatar.bySex);
	m_bySexEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataConst->avatar.wHairMdlID);
	m_wHairMdlIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataConst->avatar.wHairTexID);
	m_wHairTexIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataConst->avatar.wFaceMdlID);
	m_wFaceMdlIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataConst->avatar.wFaceDetailTexID);
	m_wFaceDetailTexIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataConst->avatar.wDressMdlID);
	m_wDressMdlIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->display_set_.bFashionDisplay);
	m_bFashionDisplayEdit.SetWindowText(str);

	str.Format(_T("%u"), pRoleDataSave->dw_map_id_);
	m_dwMapIDEdit.SetWindowText(str);

	str.Format(_T("%f"), pRoleDataSave->f_coordinate_[0]);
	m_fCoordinateX.SetWindowText(str);

	str.Format(_T("%f"), pRoleDataSave->f_coordinate_[1]);
	m_fCoordinateY.SetWindowText(str);

	str.Format(_T("%f"), pRoleDataSave->f_coordinate_[2]);
	m_fCoordinateZ.SetWindowText(str);

	str.Format(_T("%f"), pRoleDataSave->f_face_[0]);
	m_fFaceX.SetWindowText(str);

	str.Format(_T("%f"), pRoleDataSave->f_face_[1]);
	m_fFaceY.SetWindowText(str);

	str.Format(_T("%f"), pRoleDataSave->f_face_[2]);
	m_fFaceZ.SetWindowText(str);

	m_eClassCB.SetCurSel(pRoleDataSave->e_class_);

	m_eClassExCB.SetCurSel(pRoleDataSave->e_class_ex_);

	str.Format(_T("%d"), pRoleDataSave->n_level_);
	m_nLevelEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_cur_exp_);
	m_nCurExpEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_hp_);
	m_nHPEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_mp_);
	m_nMPEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_);
	m_nAttPointEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_talent_point_);
	m_nTalentPointEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_add_[ERA_Physique]);
	m_ERA_PhysiqueEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_add_[ERA_Strength]);
	m_ERA_StrengthEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_add_[ERA_Pneuma]);
	m_ERA_PneumaEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_add_[ERA_InnerForce]);
	m_ERA_InnerForceEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_add_[ERA_Technique]);
	m_ERA_TechniqueEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_att_point_add_[ERA_Agility]);
	m_ERA_AgilityEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_injury_);
	m_nInjuryEdit.SetWindowText(str);

	/*str.Format(_T("%d"), pRoleDataSave->nVitality);
	m_nVitalityEdit.SetWindowText(str);*/

	str.Format(_T("%d"), pRoleDataSave->n_knowledge_);
	m_nKnowledgeEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_morality_);
	m_nMoralityEdit.SetWindowText(str);

	//str.Format(_T("%d"), pRoleDataSave->n_culture_);
	//m_nCultureEdit.SetWindowText(str);

	//str.Format(_T("%d"), pRoleDataSave->n_culture_);
	//m_nCreditEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_identity_);
	m_nIdentityEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_vip_point_);
	m_nVIPPointEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n16_bag_size_);
	m_n16BagSizeEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_bag_bind_gold_);
	m_nBagGoldEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_bag_silver_);
	m_nBagSilverEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_bag_tuanbao_);
	m_nBagYuanBaoEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->dw_guild_id);
	m_dwGuildIDEdit.SetWindowText(str);

	CHAR time[X_DATATIME_LEN+1] = "";
	TCHAR wTime[X_DATATIME_LEN+1] = _T("");
	DwordTime2DataTime(time, sizeof(time), pRoleDataConst->create_time_);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wTime, sizeof(wTime));
	m_CreateTimeEdit.SetWindowText(wTime);

	::ZeroMemory(time, sizeof(time));
	::ZeroMemory(wTime, sizeof(wTime));
	DwordTime2DataTime(time, sizeof(time), pRoleDataSave->login_time_);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wTime, sizeof(wTime));
	m_LoginTimeEdit.SetWindowText(wTime);

	::ZeroMemory(time, sizeof(time));
	::ZeroMemory(wTime, sizeof(wTime));
	DwordTime2DataTime(time, sizeof(time), pRoleDataSave->logout_time_);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wTime, sizeof(wTime));
	m_LogoutTimeEdit.SetWindowText(wTime);

	str.Format(_T("%d"), pRoleDataSave->n_online_time_);
	m_nOnlineTimeEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_cur_online_time_);
	m_nCurOnlineTimeEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_rage_);
	m_nRageEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_endurance_);
	m_nEnduranceEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->b_safe_guard_);
	m_bSafeGuardEdit.SetWindowText(str);

	::ZeroMemory(time, sizeof(time));
	::ZeroMemory(wTime, sizeof(wTime));
	DwordTime2DataTime(time, sizeof(time), pRoleDataSave->close_safe_guard_time_);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wTime, sizeof(wTime));
	m_CloseSafeGuardTimeEdit.SetWindowText(wTime);

	m_eTypeCB0.SetCurSel(pRoleDataSave->talent_[0].eType+1);

	str.Format(_T("%d"), pRoleDataSave->talent_[0].nPoint);
	m_nPointEdit0.SetWindowText(str);

	m_eTypeEdit1.SetCurSel(pRoleDataSave->talent_[1].eType+1);

	str.Format(_T("%d"), pRoleDataSave->talent_[1].nPoint);
	m_nPointEdit1.SetWindowText(str);

	m_eTypeEdit2.SetCurSel(pRoleDataSave->talent_[2].eType+1);

	str.Format(_T("%d"), pRoleDataSave->talent_[2].nPoint);
	m_nPointEdit2.SetWindowText(str);

	m_eTypeEdit3.SetCurSel(pRoleDataSave->talent_[3].eType+1);

	str.Format(_T("%d"), pRoleDataSave->talent_[3].nPoint);
	m_nPointEdit3.SetWindowText(str);

	str.Format(_T("%u"), pRoleDataSave->dw_reborn_map_id_);
	m_dwRebornMapIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_total_tax_);
	m_nTotalTaxEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_morale_);
	m_nMoraleEdit.SetWindowText(str);

	::ZeroMemory(time, sizeof(time));
	::ZeroMemory(wTime, sizeof(wTime));
	DwordTime2DataTime(time, sizeof(time), pRoleDataSave->dw_time_get_mall_free_);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wTime, sizeof(wTime));
	m_dwTimeGetMallFreeEdit.SetWindowText(str);

	str.Format(_T("%u"), pRoleDataSave->u16_active_title_id);
	m_u16ActiveTitleIDEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_ex_volume_);
	m_nExVolumeEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_treasure_sum_);
	m_nTreasureSumEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->by_stall_level_);
	m_byStallLevelEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_stall_daily_exp_);
	m_nStallDailyExpEdit.SetWindowText(str);

	str.Format(_T("%d"), pRoleDataSave->n_stall_cur_exp_);
	m_nStallCurExpEdit.SetWindowText(str);

	::ZeroMemory(time, sizeof(time));
	::ZeroMemory(wTime, sizeof(wTime));
	DwordTime2DataTime(time, sizeof(time), pRoleDataSave->dw_last_stall_time_);
	MultiByteToWideChar(CP_UTF8, 0, time, -1, wTime, sizeof(wTime));
	m_dwLastStallTimeEdit.SetWindowText(wTime);

	UpdateData();
}

void CRoleDataDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	if(m_pDB)
	{
		/*InitRoleData();
		CString str;
		INT32 index = m_RoleDataList.GetCurSel();
		if(index != -1)
		{
			m_RoleDataList.GetText(index, str);
			tagRoleDataLoad* pData = m_pDB->GetRoleData(str);
			if(pData)
			{
				SetRoleData(pData);
			}
		}*/
	}
}

void CRoleDataDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pDB)
	{
		m_pDB->export_indagate();
		MessageBox(_T("调查问卷导出完成"));
	}
}
