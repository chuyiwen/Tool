#pragma once

#include "base_define.h"
#include "AvatarAtt.h"

#pragma pack(push, 1)

const INT	MAX_ROLENUM_ONEACCOUNT		= 5;				// 帐号的最大角色数量
const INT	MAX_ROLE_LEVEL				= 150;				// 玩家可升到的最高级别
const DWORD MAX_SAFECODE_RESET_TIME		= (72 * 60 * 60);	// 安全码最大重置时间(72小时)

const INT	ROLE_LEVEL_LIMIT			= 100;				// 等级上限

const INT	ROLE_HELP_NUM				= 255;				// 人物帮助数量
const INT	TALK_DATA_NUM				= 255;				// 对话数据数量
const INT	MAX_KEY_NUM					= 70;				// 快捷键

//---------------------------------------------------------------------------
// 数据变化状态,数据库保存相关
//---------------------------------------------------------------------------
enum EUpdateDBStatus
{
	EUDBS_Null			= 0, // 不保存(默认状态)
	EUDBS_Insert		= 1, // 需插入记录
	EUDBS_Remove		= 2, // 删除
	EUDBS_Update		= 3, // 数据更新
};

//---------------------------------------------------------------------------
// 性别
//---------------------------------------------------------------------------
enum ESex
{
	ES_Null			= -1,
	ES_Woman		= 0,	// 女限制，即女可用
	ES_Man			= 1,	// 男限制，即男可用
};

//----------------------------------------------------------------------------
// 职业类型
//----------------------------------------------------------------------------
//enum EClassType
//{
//	ECT_Start		= -1,
//
//	ECT_Null		= -1,
//	ECT_Hobo		= 0,	// 浪人
//	ECT_Sword		= 1,	// 剑客
//	ECT_Blade		= 2,	// 刀客
//	ECT_Wand		= 3,	// 杖客
//	ECT_Bow			= 4,	// 灵羽
//	ECT_Valor		= 5,	// 气师
//	ECT_Supple		= 6,	// 玄师
//	ECT_Apothecary	= 7,	// 药师
//	ECT_Musician	= 8,	// 乐师
//	ECT_Stabber		= 9,	// 刺客
//
//	ECT_End			= 10,
//};
//
//const INT32 X_ClASS_TYPE_NUM = ECT_End - ECT_Start - 1;

//---------------------------------------------------------------------------
// 职业类型扩展
//---------------------------------------------------------------------------
//enum EClassTypeEx
//{
//	ECTE_Base		= 0x1,	// 基础职业
//
//	ECTE_JianXian	= 0x2,	// 剑仙
//	ECTE_XieWu		= 0x4,	// 邪舞
//
//	ECTE_BaDao		= 0x2,	// 霸刀
//	ECTE_GangRen	= 0x4,	// 罡刃
//
//	ECTE_ZongZhang	= 0x2,	// 宗杖
//	ECTE_DiMo		= 0x4,	// 地墨
//
//	ECTE_TianJian	= 0x2,	// 天箭
//	ECTE_MoLing		= 0x4,	// 魔翎
//
//	ECTE_XuXing		= 0x2,	// 虚行
//	ECTE_GuiQi		= 0x4,	// 鬼气
//
//	ECTE_XuangWang	= 0x2,	// 玄王
//	ECTE_MiZong		= 0x4,	// 密宗
//
//	ECTE_XianYi		= 0x2,	// 仙医
//	ECTE_DuYin		= 0x4,	// 毒隐
//n 
//	ECTE_YuSheng	= 0x2,	// 乐圣
//	ECTE_HuanYin	= 0x4,	// 幻音
//
//	ECTE_YingWu		= 0x2,	// 影武
//	ECTE_GuiWu		= 0x4,	// 鬼武
//};

//---------------------------------------------------------------
// 专精职业
//---------------------------------------------------------------
enum EClassType				 
{
	EV_Begin = -1,
    EV_Null  = 0,
	
	EV_Warrior,			// 猛将
	EV_defend,			// 少保
	EV_knight,			// 侠客
	EV_Assassin,		// 刺客
	EV_Apothecary,		// 药师 


	EV_End,
};

const INT32 X_ClASS_TYPE_NUM = EV_End - EV_Begin - 2;
//--------------------------------------------------------------
// 英雄职业
//--------------------------------------------------------------
enum EClassTypeEx
{
	EHV_Begin = -1,

	EHV_Base = 0,		// 基础职业，未选择英雄职业

	EHV_JianXian,		// 仙剑
	EHV_XieWu,			// 邪舞

	EHV_BaDao,			// 霸刀
	EHV_YingWu,			// 影舞
	
	EHV_JinGang,		// 金刚
	EHV_KuangZhan,		// 狂战
	
	EHV_TianJian,		// 天箭
	EHV_MoLing,			// 魔翎
	
	EHV_XuanHuang,		// 玄皇
	EHV_MiaoFa,			// 妙法
	
	EHV_MingWang,		// 冥王
	EHV_XuKong,			// 虚空
	
	EHV_XianYi,			// 仙医
	EHV_DuYin,			// 毒隐
	
	EHV_YueSheng,		// 乐圣
	EHV_HuanYin,		// 幻音

	EHV_End,
};

//--------------------------------------------------------------------------
// 天资类型
//--------------------------------------------------------------------------
enum ETalentType
{
	ETT_Start		= -1,
	ETT_Null		= -1,

	ETT_Hammer		= 0, // 猛将武器1 锤
	ETT_Ax			= 1, // 猛将武器2 斧
	ETT_Stick		= 2, // 少保武器1 枪
	ETT_Halberd		= 3, // 少保武器2 戟
	ETT_HornBow		= 4, // 游侠武器1 牛角弓
	ETT_IronBow		= 5, // 游侠武器2 铁弓
	ETT_Thorn		= 6, // 刺客武器1 拳刺
	ETT_Round		= 7, // 刺客武器2 月轮
	ETT_Wood		= 8, // 药师武器1 木杖
	ETT_Glass		= 9, // 药师武器2 琉璃杖

	ETT_End			= 10,
};

const INT32 X_TALENT_TYPE_NUM = ETT_End - ETT_Start - 1;

//--------------------------------------------------------------------------
// 能量类型
//--------------------------------------------------------------------------
enum EPowers
{
	EPower_Mana		= 0, //魔法
	EPower_Rage		= 1, //怒气
	EPower_Point	= 2, //点数
	EPower_Energy	= 3, //能量
	Epower_Focus	= 4	 //集中点数
};

const INT32 X_MAX_POWERS = 5;


//--------------------------------------------------------------------------
// 声望类型（可能会有两种类型的声望）
//--------------------------------------------------------------------------
// enum EReputationType
// {
// 	ERT_Start		= -1,
// 	ERT_Null		= -1,
// 
// 	ERT_End			= 0,
// };

//--------------------------------------------------------------------------
// 角色与生物公有状态标示
//--------------------------------------------------------------------------
enum EState
{
	ES_Dead			=	0,	// 死亡
	ES_Dizzy		=	1,	// 眩晕
	ES_Tie			=	2,	// 定身
	ES_Spor			=	3,	// 昏睡
	ES_Invincible	=	4,	// 无敌
	ES_Lurk			=	5,	// 隐身
	ES_DisArm		=	6,	// 缴械
	ES_NoSkill		=	7,	// 封技
	ES_Special		=	8,  // 特殊状态，这样叫为了是能通用一些[但不知道是否能通用]
	ES_Feat			=	9,	// 恐惧

	ES_End			=	10,
};

//------------------------------------------------------------------
// 角色与怪物共有阵营
//------------------------------------------------------------------
enum ECamp
{
	ECA_Null				= -1,				// 无

	ECA_WaGang			= 0,				// 瓦岗
	ECA_Tang			= 1,				// 唐朝
	ECA_Sui				= 2,				// 隋朝
	ECA_Normal			= 3,				// 野外生物
	ECA_Common			= 4,				// 角色公共势力
	ECA_Battle_a		= 5,				// 战场势力a
	ECA_Battle_b		= 6,				// 战场势力b

	ECA_End				= 7,				
};

//--------------------------------------------------------------------------
// 角色状态标识 -- 该状态改变，需要向周围玩家广播
//--------------------------------------------------------------------------
enum ERoleState
{
	ERS_Safeguard	= 0x0001,	// 被保护
	ERS_Combat		= 0x0002,	// 战斗姿态
	ERS_PK			= 0x0004,	// 行凶状态
	ERS_Arena		= 0x0008,	// 擂台(用于PVP活动或战场，该状态由脚本设置）

	ERS_SafeArea	= 0x0010,	// 安全区
	ERS_PVPArea		= 0x0020,	// PVP区
	ERS_StallArea	= 0x0040,	// 摆摊区
	ERS_PVP			= 0x0080,	// PVP状态

	ERS_Shop		= 0x0100,	// 商店交易
	ERS_Exchange	= 0x0200,	// 玩家间直接交易
	ERS_Stall		= 0x0400,	// 摆摊交易
	ERS_StallSet	= 0x0800,	// 设置摆摊物品

	ERS_PrisonArea	= 0x1000,	// 牢狱状态

	ERS_Mount		= 0x2000,	// 骑乘
	ERS_WaterWalk   = 0x4000,   // 水上行走
	ERS_Mount2		= 0x8000,	// 骑乘2

	ERS_Commerce	= 0x10000,	// 跑商中	
	ERS_PetExchange	= 0x20000,	// 宠物交易
	ERS_Prictice	= 0x40000,	// 修炼武器	

	ERS_CommonArea	= 0x100000,	// 普通区域
	ERS_RealSafeArea= 0x200000,	// 绝对安全区
	ERS_GuildBattle = 0x400000,	// 帮会战区
	ERS_NoPunishArea= 0x800000, // 无惩罚区

	ERS_EquipTrans = 0x1000000,	// 装备变形
	ERS_HangArea   = 0x2000000,	// 挂机区
	ERS_Hang	   = 0x4000000, // 挂机状态

	ERS_End			= 0x40000000,
};

//--------------------------------------------------------------------------
// 角色状态标识 -- 该状态改变，只需要通知玩家本人
//--------------------------------------------------------------------------
enum ERoleStateEx
{
	ERSE_BagPsdPass		= 0x1,	// 行囊密码验证已通过
	ERSE_BagPsdExist	= 0x2,	// 行囊密码存在
};

//--------------------------------------------------------------------------
// 角色PK模式
//--------------------------------------------------------------------------
enum ERolePKState
{
	ERolePK_Peace	= 0,		// 和平模式
	ERolePK_Guild,				// 帮会模式
	ERolePK_All,				// 全体模式

	ERPKS_End,
};

//-------------------------------------------------------------------------------
// PK模式
//-------------------------------------------------------------------------------
enum EBattleMode
{
	EBM_Peace		= 0,		// 和平模式
	EBM_Guild		= 1,		// 帮会模式
	EBM_Group		= 2,		// 组队模式
	EBM_Whole		= 3,		// 全体模式
};

//-------------------------------------------------------------------------------
// 人物基本属性枚举(该处枚举顺序、个数调整,可能会影响到数据库装备表)
//-------------------------------------------------------------------------------
enum ERoleAttribute
{
	ERA_Null					=	-1,		//
	
	// 一级属性
	ERA_AttA_Start				=	0,
	ERA_Physique				=	0,		// 	体质
	ERA_Strength				=	1,		// 	力量
	ERA_InnerForce				=	2,		//  智慧	
	ERA_Agility					=	3,		// 	敏捷
	ERA_Pneuma					=	4,		// 	--废弃
	ERA_Technique				=	5,		// 	--废弃
	ERA_AttA_End				=	5,

	// 玩家的点数
	ERA_AttPoint				=	6,		// 当前属性点数
	ERA_TalentPoint				=	7,		// 当前天资点数

	// 二级属性
	ERA_AttB_Start				=	8,
	ERA_MaxHP					=	8,		// 最大体力
	ERA_HP						=	9,		// 当前体力
	ERA_MaxMP					=	10,		// 最大真气
	ERA_MP						=	11,		// 当前真气
	ERA_ExAttack				=	12,		// 攻击
	ERA_ExDefense				=	13,		// 防御
	ERA_InAttack				=	14,		// 远程攻击
	ERA_InDefense				=	15,		// 远程防御
	ERA_HitRate					=	16,		// 命中率
	ERA_Dodge					=	17,		// 闪避率
	ERA_Block_Rate				=	18,		// 招架
	ERA_Crit_Rate				=	19,		// 暴击率
	ERA_Crit_Amount				=	20,		// 暴击量
	ERA_UnCrit_Rate				=	21,		// 反暴击
	ERA_UnCrit_Amount			=	22,		// 反暴伤
	ERA_HPRegainRate			=	23,		// 体力恢复速度
	ERA_MPRegainRate			=	24,		// 真气恢复速度
	ERA_AttB_End				=	24,

	// 固有属性
	ERA_Rage					=	25,		// 怒气
	ERA_Brotherhood				=	26,		// 义气值
	ERA_MaxBrotherhood			=	27,		// 最大义气
	ERA_VitalityRegainRate		=	28,		// 活力恢复速度
	ERA_Speed_XZ				=	29,		// XZ平面速度速度
	ERA_Speed_Y					=	30,		// Y方向速度
	ERA_Speed_Swim				=	31,		// 游泳的XZ速度
	ERA_Speed_Mount				=	32,		// 骑乘的XZ速度

	// 镌刻影响属性
	ERA_EngraveAtt_Start		=	33,		
	ERA_ExAttackMin				=	33,		// 最小攻击
	ERA_ExAttackMax				=	34,		// 最大攻击
	ERA_InAttackMin				=	35,		// 最小远程攻击(废弃)
	ERA_InAttackMax				=	36,		// 最大远程攻击(废弃)
	ERA_ArmorEx					=	37,		// 护甲
	ERA_ArmorIn					=	38,		// 远程护甲(废弃)
	ERA_EngraveAtt_End			=	38,		


	ERA_Derate_Ordinary			=	39,		// 普通伤害减免	

	ERA_Derate_Start			=	40,
	ERA_Derate_Soil				=	40,		// 土伤害减免
	ERA_Derate_Gold				=	41,		// 金伤害减免
	ERA_Derate_Wood				=	42,		// 木伤害减免
	ERA_Derate_Fire				=	43,		// 火伤害减免
	ERA_Derate_Water			=	44,		// 水伤害减免
	ERA_Derate_End				=	44,

	ERA_Derate_Injury			=	45,		// 内损伤害减免
	ERA_Derate_Stunt			=	46,		// 绝技伤害减免
	ERA_Derate_ExAttack			=	47,		// 近战伤害减免
	ERA_Derate_InAttack			=	48,		// 远程伤害减免
	ERA_Derate_ALL				=	49,		// 所有伤害减免
	

	ERA_ExDamage				=	50,		// 额外伤害
	ERA_ExDamage_Absorb			=	51,		// 额外伤害吸收

	ERA_Resist_Bleeding			=	52,		// 出血抗性——命中几率
	ERA_Resist_Weak				=	53,		// 虚弱抗性——命中几率
	ERA_Resist_Choas			=	54,		// 混乱抗性——命中几率
	ERA_Resist_Special			=	55,		// 特殊抗性——命中几率
	ERA_Regain_Addtion			=	56,		// 恢复量加成

	ERA_Attack_MissRate			=	57,		// 攻击失误率
	ERA_CloseAttack_DodgeRate	=	58,		// 近战躲避率加成
	ERA_RemoteAttack_DodgeRate	=	59,		// 远程躲避率加成

	ERA_Inspiration				=	60,		// 灵感
	ERA_Lurk					=	61,		// 隐匿
	ERA_Savvy					=	62,		// 悟性
	ERA_Morale					=	63,		// 士气
	ERA_Injury					=	64,		// 内伤
	ERA_Enmity_Degree			=	65,		// 仇恨度
	ERA_Shape					=	66,		// 体型
	ERA_Exp_Add_Rate			=	67,		// 经验获得加成		原经验/金钱/掉率 * (1+加成/10000)
	ERA_Money_Add_Rate			=	68,		// 金钱获得加成
	ERA_Loot_Add_Rate			=	69,		// 物品掉落几率加成

	// 社会属性
	ERA_Fortune					=	70,		// 元气
	ERA_Appearance				=	71,		// 仪容
	ERA_Rein					=	72,		// 统御
	ERA_Knowledge				=	73,		// 阅历
	ERA_Morality				=	74,		// 道德
	ERA_Culture					=	75,		// 修为

	ERA_End						=	76,
	// 玩家的姓名，声望，投放属性点，已经投放的天资点没有放到基本属性中
};

const INT32	X_ERA_ATTA_NUM		= ERA_AttA_End - ERA_AttA_Start + 1;
#define MTransERAAttA2Index(ERAAttA)		((ERAAttA) - ERA_AttA_Start)
#define MTransIndex2ERAATTA(Index)			((Index) + ERA_AttA_Start)

const INT32 X_ERA_AttB_NUM		= ERA_AttB_End - ERA_AttB_Start;
#define MTransERAAttB2Index(ERAAttB)		((ERAAttB) - ERA_AttB_Start)
#define MTransIndex2ERAATTB(Index)			((Index) + ERA_AttB_Start)

const INT32	X_ERA_DERATE_NUM	= ERA_Derate_End - ERA_Derate_Start + 1;
#define MTransERADerate2Index(ERADerate)	((ERADerate) - ERA_Derate_Start)
#define MTransIndex2ERADerate(Index)		((Index) + ERA_Derate_Start)

//--------------------------------------------------------------------------------------
// 远程玩家的属性枚举
//--------------------------------------------------------------------------------------
enum ERemoteRoleAtt
{
	ERRA_Null		=	-1,		//

	ERRA_MaxHP		=	0,		// 最大体力
	ERRA_HP			=	1,		// 当前体力
	ERRA_MaxMP		=	2,		// 最大真气
	ERRA_MP			=	3,		// 当前真气
	ERRA_Rage		=	4,		// 怒气
	ERRA_Speed_XZ	=	5,		// XZ平面速度
	ERRA_Speed_Y	=	6,		// Y平面速度
	ERRA_Speed_Swim	=	7,		// 游泳速度
	ERRA_Speed_Mount=	8,		// 骑乘速度
	ERRA_Shape		=	9,		// 体型

	ERRA_End		=	10,
};

//-----------------------------------------------------------------------------------------
// 目标类型标示位
//-----------------------------------------------------------------------------------------
enum ETargetFlag
{
	ETF_Self				=	0x00000001,	// 自身
	ETF_Teammate			=	0x00000002,	// 队友
	ETF_Guildmate			=	0x00000004,	// 同门
	ETF_Lover				=	0x00000008,	// 情侣
	ETF_Couple				=	0x00000010,	// 配偶
	ETF_Brother				=	0x00000020,	// 结拜
	ETF_Teacher				=	0x00000040,	// 师徒
	ETF_Player				=	0x00000080,	// 玩家

	ETF_Pet					=	0x00000100,	// 宠物
	ETF_NPC					=	0x00000200,	// NPC
	ETF_NormalMonster		=	0x00000400,	// 普通怪物
	ETF_Boss				=	0x00000800,	// Boss
	ETF_Nest				=	0x00001000,	// 巢穴
	ETF_NatuRes				=	0x00002000,	// 自然资源
	ETF_ManRes				=	0x00004000,	// 人造资源
	ETF_Door				=	0x00008000,	// 城门
	ETF_Building			=	0x00010000,	// 建筑
	ETF_NormalGameObject	=	0x00020000,	// 普通可交互地物
	ETF_InvesGameObject		=	0x00040000,	// 可调查地物
	ETF_QuestTalkGameObject	=	0x00080000,	// 任务对话地物
    ETF_GuildGameObject     =   0x00100000, // 帮派相关地物 (比如帮派复活点?)
};

//-----------------------------------------------------------------------------------------
// 状态标示位
//-----------------------------------------------------------------------------------------
enum EStateFlag
{
	ESF_Dead			=	0x00000001,	// 死亡
	ESF_NoDead			=	0x00000002,	// 非死亡
	ESF_Dizzy			=	0x00000004,	// 眩晕
	ESF_NoDizzy			=	0x00000008,	// 非眩晕
	ESF_Spor			=	0x00000010,	// 昏睡
	ESF_NoSpor			=	0x00000020,	// 非昏睡
	ESF_Tie				=	0x00000040,	// 定身
	ESF_NoTie			=	0x00000080,	// 非定身
	ESF_Invincible		=	0x00000100,	// 无敌
	ESF_NoInvincible	=	0x00000200,	// 非无敌
	ESF_NoSkill			=	0x00000400,	// 封技
	ESF_NoNoSkill		=	0x00000800, // 非封技
	ESF_DisArm			=	0x00001000,	// 缴械
	ESF_NoDisArm		=	0x00002000,	// 非缴械
	ESF_Lurk			=	0x00004000,	// 隐身
	ESF_NoLurk			=	0x00008000,	// 非隐身
	ESF_Mount			=	0x00010000,	// 骑乘
	ESF_NoMount			=	0x00020000, // 非骑乘
	ESF_Prison			=	0x00040000,	// 牢狱
	ESF_NoPrison		=	0x00080000,	// 非牢狱
	ESF_Mount2			=	0x00100000,	// 骑乘2
	ESF_NoMount2		=	0x00200000, // 非骑乘2
	ESF_Commerce		=	0x00400000,	// 跑商中
	ESF_NoCommerce		=	0x00800000,	// 非跑商中
	ESF_Prictice		=	0x01000000,	// 修炼武器
	ESF_NoPrictice		=	0x02000000,	// 非修炼武器
	ESF_Hang			=   0x04000000, // 挂机
	ESF_NoHang			=   0x08000000,	// 非挂机

};
//Ares 请不要修改此行，RoleDefine.h 和 QuestDef.h相互包含
//#include "QuestDef.h" 
//-----------------------------------------------------------------------------------------
// 人物生物基本属性的默认值及最大最小值
//-----------------------------------------------------------------------------------------
struct tagAttDefMinMax
{
	INT		nDefRole;			// 人物初始化默认值
	INT		nDefCreature;		// 生物初始化默认值
	INT		nMin;				// 属性最小值
	INT		nMax;				// 属性最大值
};

////---------------------------------------------------------------------------------------
//// 客户端本地玩家同步数据消息结构（未完成）
////---------------------------------------------------------------------------------------
//struct tagRoleData
//{
//	DWORD			dwID;						// 玩家ID
//	DWORD			dwRoleNameCrc;				// 名称CRC
//	TCHAR			sz_role_name[X_SHORT_NAME];	// 名称
//
//	DWORD			dwMapID;					// 所在的地图的ID
//	FLOAT			fPos[3];					// 位置
//	FLOAT			fFaceTo[3];					// 朝向
//
//	tagAvatarAtt	Avatar;						// 外观
//	tagAvatarEquip	AvatarEquip;				// 装备外观
//	tagDisplaySet	DisplaySet;					// 外观显示设置
//	INT				nAtt[ERA_End];				// 当前人物属性
//
//	INT				nAttPointAdd[X_ERA_ATTA_NUM];// 玩家投放到各个一级属性中的值
//
//	EClassType		eClass;						// 职业
//	EClassTypeEx	eClassEx;					// 扩展职业
//
//	INT16			n16MaxBagSize;				// 背包大小
//	INT16			n16MaxWareSize;				// 账号仓库大小
//
//	INT				nSkillNum;					// 技能个数
//	INT				nBuffNum;					// 状态个数
//	INT				nTitleNum;					// 称号个数
//	INT				nItemNum;					// 物品个数
//	INT				nEquipNum;					// 装备个数
//	INT				nFriendNum;					// 好友个数
//	INT				nEnemyNum;					// 仇敌个数
//	INT				nQuestNum;					// 任务列表个数
//	INT				nQuestDoneNum;				// 已完成的任务个数
//
//	/*********************************************************************************************************
//	 *技能列表，状态列表，称号列表，物品列表，装备列表，好友列表，仇敌列表，任务列表，已完成任务列表
//	 *必须按顺序拷贝
//	 *********************************************************************************************************/
//	//任务列表
//	DWORD			dwIncompleteQuestID[QUEST_MAX_COUNT];			// 在当前玩家身上未完成的任务 30上限
//	DWORD			dwIncompleteQuestTakeTime[QUEST_MAX_COUNT];		// 在当前玩家身上当前任务的接取时间 30上限
//	//任务列表
//	
//
//	BYTE			byData[1];
//};

//------------------------------------------------------------------------------------------
// 在选人界面要看到的人物信息
//------------------------------------------------------------------------------------------
struct tagSimRole								// size = 64
{
	tagAvatarAtt	Avatar;						// size = 16
	tagAvatarEquip	AvatarEquip;				// size = (2 * 9 + 1) * 4
	TCHAR			szRoleName[X_SHORT_NAME];

	DWORD			dw_role_id;
	DWORD			dwMapID;
	BYTE			byLevel;
	EClassType		eClassType;
	tagDisplaySet	sDisplaySet;
	tagDWORDTime	dwLoginTime;
	BYTE			byReserved[2];
};

//------------------------------------------------------------------------------------------
// 是否对远端玩家公开相关信息 -- 注：数据库表记录用32位
//------------------------------------------------------------------------------------------
struct tagRemoteOpenSet
{
	DWORD	bTitle		: 1,	// 称号
			bVCard		: 1,	// 名帖
			bRoleAtt	: 1,	// 角色属性
			bDummy		: 29;	// 占位用

	tagRemoteOpenSet() { ZeroMemory(this, sizeof(*this)); }
	
	tagRemoteOpenSet& operator = (DWORD dw)
	{
		return *this = *(tagRemoteOpenSet*)&dw;
	}

	operator DWORD()
	{
		return *(DWORD*)this;
	}
};


//------------------------------------------------------------------------------------------
// 玩家信息的公开类型
//------------------------------------------------------------------------------------------
enum EPlayerPersonlInfoOpenType
{
	EPIS_Private,  // 完全保密
	EPIS_Friend,   // 仅对互为好友的玩家公开
	EPIS_Public,   // 完全公开
	EPIS_End,
};

//------------------------------------------------------------------------------------------
// 玩家的个人设置
//------------------------------------------------------------------------------------------
struct tagDWPlayerPersonalSet
{
	DWORD	bAcceptTeamInvite		: 1,	// 是否接受组队邀请
			bAcceptFactionInvite	: 1,	// 是否接受帮派邀请
			bAllowFriendAdd			: 1,	// 是否允许其他人添加自己为好友
			bAcceptTradeRequest		: 1,	// 是否接受交易请求
			eInfoOpenType           : 4,    // 信息的公开类型
			bDummy					: 24;	// 占位用

	tagDWPlayerPersonalSet() { ZeroMemory(this, sizeof(*this)); }

	tagDWPlayerPersonalSet& operator = (DWORD dw)
	{
		return *this = *(tagDWPlayerPersonalSet*)&dw;
	}

	operator DWORD()
	{
		return *(DWORD*)this;
	}
};
//-------------------------------------------------------------------------------------------
// 快捷键信息
//-------------------------------------------------------------------------------------------
struct tagKeyInfo
{
    DWORD		dwID;
    DWORD		dwKey;			// 快捷键1
	DWORD		dwKeyTwo;		// 快捷键2
};


#pragma pack(pop)
