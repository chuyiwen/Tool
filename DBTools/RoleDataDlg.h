#ifndef ROLEDATA
#define ROLEDATA
#include "resource.h"
#include "afxwin.h"

class CDB;

// CRoleDataDlg dialog

class CRoleDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoleDataDlg)

public:
	CRoleDataDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRoleDataDlg();

// Dialog Data
	enum { IDD = IDD_ROLEDATADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	VOID SetDB(CDB *pDB)
	{
		m_pDB = pDB;
	}

	VOID InitRoleData();

	VOID AddRoleData(CString &str);

	VOID SetRoleData(s_role_data_load* pRoleData);

private:
	VOID InitStatic();

private:
	CDB *m_pDB;
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnCancel();
public:
	CStatic m_Static1;
	CEdit m_RoleNameEdit;
	afx_msg void OnBnClickedButton1();
	CListBox m_RoleDataList;
	CStatic m_Static2;
	CEdit m_szRoleNameEdit;
	afx_msg void OnLbnSelchangeList1();
	CStatic m_Static3;
	CEdit m_bySexEdit;
	CStatic m_Static4;
	CEdit m_wHairMdlIDEdit;
	CStatic m_Static5;
	CEdit m_wHairTexIDEdit;
	CStatic m_Static6;
	CEdit m_wFaceMdlIDEdit;
	CStatic m_Static7;
	CEdit m_wFaceDetailTexIDEdit;
	CStatic m_Static8;
	CEdit m_wDressMdlIDEdit;
	CStatic m_Static9;
	CEdit m_bFashionDisplayEdit;
	CStatic m_Static10;
	CEdit m_dwMapIDEdit;
	CEdit m_fCoordinateX;
	CEdit m_fCoordinateY;
	CEdit m_fCoordinateZ;
	CEdit m_fFaceX;
	CEdit m_fFaceY;
	CEdit m_fFaceZ;
	CComboBox m_eClassCB;
	CStatic m_Static17;
	CStatic m_Static18;
	CComboBox m_eClassExCB;
	CStatic m_Static19;
	CEdit m_nLevelEdit;
	CStatic m_Static20;
	CEdit m_nCurExpEdit;
	CStatic m_Static21;
	CEdit m_nHPEdit;
	CStatic m_Static22;
	CEdit m_nMPEdit;
	CStatic m_Static23;
	CEdit m_nAttPointEdit;
	CStatic m_Static24;
	CEdit m_nTalentPointEdit;
	CStatic m_Static25;
	CEdit m_ERA_PhysiqueEdit;
	CStatic m_Static26;
	CEdit m_ERA_StrengthEdit;
	CStatic m_Static27;
	CEdit m_ERA_PneumaEdit;
	CStatic m_Static28;
	CEdit m_ERA_InnerForceEdit;
	CStatic m_Static29;
	CEdit m_ERA_TechniqueEdit;
	CStatic m_Static30;
	CEdit m_ERA_AgilityEdit;
	CStatic m_Static31;
	CEdit m_nInjuryEdit;
	CStatic m_Static32;
	CEdit m_nVitalityEdit;
	CStatic m_Static33;
	CEdit m_nKnowledgeEdit;
	CStatic m_Static34;
	CEdit m_nMoralityEdit;
	CStatic m_Static35;
	CEdit m_nCultureEdit;
	CStatic m_Static36;
	CEdit m_nCreditEdit;
	CStatic m_Static37;
	CEdit m_nIdentityEdit;
	CStatic m_Static38;
	CEdit m_nVIPPointEdit;
	CStatic m_Static39;
	CEdit m_n16BagSizeEdit;
	CStatic m_Static40;
	CEdit m_nBagGoldEdit;
	CStatic m_Static41;
	CEdit m_nBagSilverEdit;
	CStatic m_Static42;
	CEdit m_nBagYuanBaoEdit;
	CStatic m_Static43;
	CEdit m_dwGuildIDEdit;
	CStatic m_Static44;
	CEdit m_CreateTimeEdit;
	CStatic m_Static45;
	CEdit m_LoginTimeEdit;
	CStatic m_Static46;
	CEdit m_LogoutTimeEdit;
	CStatic m_Static47;
	CEdit m_nOnlineTimeEdit;
	CStatic m_Static48;
	CEdit m_nCurOnlineTimeEdit;
	CStatic m_Static49;
	CEdit m_nRageEdit;
	CStatic m_Static50;
	CEdit m_nEnduranceEdit;
	CStatic m_Static51;
	CEdit m_bSafeGuardEdit;
	CStatic m_Static52;
	CEdit m_CloseSafeGuardTimeEdit;
	CComboBox m_eTypeCB0;
	CEdit m_nPointEdit0;
	CComboBox m_eTypeEdit1;
	CEdit m_nPointEdit1;
	CComboBox m_eTypeEdit2;
	CEdit m_nPointEdit2;
	CComboBox m_eTypeEdit3;
	CEdit m_nPointEdit3;
	CStatic m_Static53;
	CEdit m_dwRebornMapIDEdit;
	CStatic m_Static54;
	CEdit m_nTotalTaxEdit;
	CStatic m_Static55;
	CEdit m_nMoraleEdit;
	CStatic m_Static56;
	CEdit m_dwTimeGetMallFreeEdit;
	CStatic m_Static57;
	CEdit m_u16ActiveTitleIDEdit;
	CStatic m_Static58;
	CEdit m_nExVolumeEdit;
	CStatic m_Static59;
	CEdit m_nTreasureSumEdit;
	CStatic m_Static60;
	CEdit m_byStallLevelEdit;
	CStatic m_Static61;
	CEdit m_nStallDailyExpEdit;
	CStatic m_Static62;
	CEdit m_nStallCurExpEdit;
	CStatic m_Static63;
	CEdit m_dwLastStallTimeEdit;
	afx_msg void OnBnClickedButton5();
};
#endif
