// ServerToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerTool.h"
#include "ServerToolDlg.h"
#include "DumbDlg.h"
#include "NetSession.h"
#include "../LogSystem/protocal.h"
#include "ontinueTime.h"
#include "tinyxml.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
wchar_t  m_pTCharPool[512];
#define MASKBITS 0x3F
#define MASKBYTE 0x80
#define MASK2BYTES 0xC0
#define MASK3BYTES 0xE0

using namespace CEGUITinyXML;


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


// CServerToolDlg 对话框




CServerToolDlg::CServerToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerToolDlg::IDD, pParent)
{
	p_char_buffer = new CHAR[1024*64];
	p_tchar_buffer = new TCHAR[1024*64];
	mTotal = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	net_session::instance2()->register_cmd("NET_GMS2C_QueryLoginStatus" , this , &CServerToolDlg::onLoginStatus);
	net_session::instance2()->register_cmd("NET_GMS2C_GMLogin" , this , &CServerToolDlg::onLoginOK);
	net_session::instance2()->register_cmd("NET_GMS2C_QueryGameServerList" , this , &CServerToolDlg::onUpdateServerList);
}
CServerToolDlg::~CServerToolDlg()
{
	net_session::instance2()->unregister_cmd("NET_GMS2C_QueryLoginStatus" , this , &CServerToolDlg::onLoginStatus);
	net_session::instance2()->unregister_cmd("NET_GMS2C_GMLogin" , this , &CServerToolDlg::onLoginOK);
	net_session::instance2()->unregister_cmd("NET_GMS2C_QueryGameServerList" , this , &CServerToolDlg::onUpdateServerList);
}

void CServerToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mAreaList);
	DDX_Control(pDX, IDC_LIST3, mServerList);
	DDX_Control(pDX, IDC_EDIT1, mNumber);
	DDX_Control(pDX, IDC_EDIT3, mEXP);
	DDX_Control(pDX, IDC_EDIT4, mITEM);
	DDX_Control(pDX, IDC_TOTAL, mOnline);
	DDX_Control(pDX, IDC_ServerList, mServerTip);
	DDX_Control(pDX, IDC_EDIT2, mTrain);
}

BEGIN_MESSAGE_MAP(CServerToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CServerToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CServerToolDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CServerToolDlg::OnNMDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON10, &CServerToolDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON7, &CServerToolDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CServerToolDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CServerToolDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON3, &CServerToolDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CServerToolDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON11, &CServerToolDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON5, &CServerToolDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON12, &CServerToolDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CServerToolDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CServerToolDlg::OnBnClickedButton14)
END_MESSAGE_MAP()


// CServerToolDlg 消息处理程序

LPCSTR CServerToolDlg::unicode_to_ansi(LPCTSTR sz_src_)
{
	p_char_buffer[0] = 0;
	WideCharToMultiByte(CP_ACP, 0, sz_src_, -1, p_char_buffer, CHAR_BUFFER_SIZE, NULL, NULL);
	return p_char_buffer;
}

LPCTSTR CServerToolDlg::ansi_to_unicode(LPCSTR sz_src_)
{
	p_char_buffer[0] = 0;
	MultiByteToWideChar(CP_ACP, 0, sz_src_, -1, p_tchar_buffer, CHAR_BUFFER_SIZE);
	return p_tchar_buffer;
}
static BYTE by_num[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void CServerToolDlg::md5_init()
{
	st_context._count[0] = st_context._count[1] = 0;

	st_context._state[0] = 0x67452301;
	st_context._state[1] = 0xefcdab89;
	st_context._state[2] = 0x98badcfe;
	st_context._state[3] = 0x10325476;
}

void CServerToolDlg::md5_update(BYTE *p_in_, UINT n_in_length_)
{
	UINT i=0;
	UINT n_index = 0;
	UINT n_length = 0;

	n_index = (UINT)( (st_context._count[0] >> 3) & 0x3F );
	if( (st_context._count[0] += ((DWORD)n_in_length_ << 3)) < ((DWORD)n_in_length_ << 3) )
		st_context._count[1]++;
	st_context._count[1] += ((DWORD)n_in_length_ >> 29);
	n_length = 64 - n_index;

	if( n_in_length_ >= n_length )
	{
		memcpy(st_context._buffer+n_index, p_in_, n_length);
		md5_transform(st_context._state, st_context._buffer);

		for(i=n_length; i+63 < n_in_length_; i+=64)
			md5_transform(st_context._state, p_in_+i);

		n_index = 0;
	}
	else 
		i = 0;
	memcpy(st_context._buffer+n_index, p_in_+i, n_in_length_-i);
}

void CServerToolDlg::encode(BYTE* p_out_, DWORD* p_in_, unsigned int n_length_)
{
	UINT i, j;

	for (i=0, j=0; j<n_length_; i++, j+=4)
	{
		p_out_[j] = (unsigned char)(p_in_[i] & 0xff);
		p_out_[j+1] = (unsigned char)((p_in_[i] >> 8) & 0xff);
		p_out_[j+2] = (unsigned char)((p_in_[i] >> 16) & 0xff);
		p_out_[j+3] = (unsigned char)((p_in_[i] >> 24) & 0xff);
	}
}


void CServerToolDlg::md5_final(BYTE by_digest_[16])
{
	BYTE by_bits[8];
	UINT n_index = 0;
	UINT n_length;

	encode(by_bits, st_context._count, 8);

	n_index = (UINT)((st_context._count[0] >> 3) & 0x3f);
	n_length = (n_index < 56) ? (56-n_index) : (120-n_index);

	md5_update(by_num, n_length);
	md5_update(by_bits, 8);
	encode(by_digest_, st_context._state, 16);

	memset(&st_context, 0, sizeof(MD5_CONTEXT));
}


VOID CServerToolDlg::md5_for_buffer(BYTE* p_buffer_, UINT n_buffer_length_, BYTE by_digest_[16])
{
	md5_init();
	md5_update(p_buffer_, n_buffer_length_);
	md5_final(by_digest_);
}
VOID CServerToolDlg::md5_for_string(CHAR* sz_string_, BYTE by_digest_[16])
{
	UINT n_length = (UINT)strlen(sz_string_);
	md5_for_buffer((BYTE*)sz_string_, n_length, by_digest_);
}
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))


#define RIGHT_ROTATE_MOVE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))


#define FF(a, b, c, d, x, s, ac) \
{ \
	(a) += F ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = RIGHT_ROTATE_MOVE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac)\
{ \
	(a) += G ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = RIGHT_ROTATE_MOVE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) \
{ \
	(a) += H ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = RIGHT_ROTATE_MOVE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) \
{ \
	(a) += I ((b), (c), (d)) + (x) + (DWORD)(ac); \
	(a) = RIGHT_ROTATE_MOVE_LEFT ((a), (s)); \
	(a) += (b); \
}


void CServerToolDlg::md5_transform(DWORD state_[4], unsigned char block_[64])
{
	DWORD a = state_[0], b = state_[1], c = state_[2], d = state_[3];
	DWORD x[16];

	decode (x, block_, 64);

	/* Round 1 */
	FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

	/* Round 2 */
	GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

	/* Round 3 */
	HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

	/* Round 4 */
	II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

	state_[0] += a;
	state_[1] += b;
	state_[2] += c;
	state_[3] += d;

	memset(x, 0, sizeof(x));
}

void CServerToolDlg::decode( DWORD* p_out_, BYTE* p_in_, unsigned int n_length_)
{
	UINT i, j;

	for (i=0, j=0; j<n_length_; i++, j+=4)
		p_out_[i] = ((DWORD)p_in_[j]) | (((DWORD)p_in_[j+1]) << 8) |
		(((DWORD)p_in_[j+2]) << 16) | (((DWORD)p_in_[j+3]) << 24);

}

VOID CServerToolDlg::md5_to_string( std::string& string_, BYTE by_digest_[16] )
{ 
	char sz_buffer[256];
	ZeroMemory(sz_buffer, sizeof(sz_buffer));
	for(int i=0; i<16; i++)
		sprintf(sz_buffer, "%s%02x", sz_buffer, by_digest_[i]);

	string_ = sz_buffer;
}
LPCTSTR	Unicode8ToUnicode(LPCSTR szSrc, LPTSTR szOut)
{
	if( !szOut )
		szOut = m_pTCharPool;

	LPTSTR szDest = szOut;

	while( *szSrc )
	{
		if( !(*szSrc & MASKBYTE) )	// 0xxxxxxx
		{
			*szDest++ = *szSrc++;
		}
		else if( (*szSrc & MASK3BYTES) == MASK3BYTES )	// 1110xxxx 10xxxxxx 10xxxxxx
		{
			*szDest++ = ((*szSrc & 0x0F) << 12) | ((*(szSrc+1) & MASKBITS) << 6) | (*(szSrc+2) & MASKBITS);
			++szSrc;
			++szSrc;
			++szSrc;
		}
		else if( (*szSrc & MASK2BYTES) == MASK2BYTES )	// 110xxxxx 10xxxxxx
		{
			*szDest++ = ((*szSrc & 0x1F) << 6) | (*(szSrc+1) & MASKBITS);
			++szSrc;
			++szSrc;
		}
	}

	*szDest = 0; // 加上0结束符
	return szOut;
}


TiXmlNode* travel(TiXmlNode* ele)
{
	TiXmlNode* tmp = 0;
	if(ele->FirstChild())
	{
		return  ele->FirstChild();
	}
	else if(ele->NextSibling())
	{
		return  ele->NextSibling();
	}
	else
	{
		while(1)
		{
			ele = ele->Parent();
			if(!ele)
			{
				return 0;
			}
			if(ele->NextSibling())
			{
				return ele->NextSibling();
			}
		}
	}
}

BOOL CServerToolDlg::OnInitDialog()
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

	mAreaList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	mServerList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// TODO: 在此添加额外的初始化代码
	while(mAreaList.DeleteColumn(0));
	mAreaList.InsertColumn(0 , L"IP");
	mAreaList.InsertColumn(1 , L"Name");
	mAreaList.InsertColumn(2 , L"Login");
	mAreaList.InsertColumn(3 , L"Total");
	mAreaList.SetColumnWidth(0 , 120);
	mAreaList.SetColumnWidth(1 , 100);
	mAreaList.SetColumnWidth(2 , 60);
	mAreaList.SetColumnWidth(3 , 100);

	while(mServerList.DeleteColumn(0));
	mServerList.InsertColumn(0 , L"IP");
	mServerList.InsertColumn(1 , L"Name");
	mServerList.InsertColumn(2 , L"Server");
	mServerList.InsertColumn(3 , L"DB");
	mServerList.InsertColumn(4 , L"Total");
	mServerList.InsertColumn(5 , L"Limit");
	mServerList.InsertColumn(6 , L"Ping");
	mServerList.SetColumnWidth(0 , 120);
	mServerList.SetColumnWidth(1 , 100);
	mServerList.SetColumnWidth(2 , 60);
	mServerList.SetColumnWidth(3 , 60);
	mServerList.SetColumnWidth(4 , 80);
	mServerList.SetColumnWidth(5 , 80);
	mServerList.SetColumnWidth(6 , 80);


	TiXmlDocument xml;
	FILE* fp = fopen("area.cfg" , "rb");
	fseek(fp , 0 , SEEK_END);
	size_t sz = ftell(fp);
	fseek(fp , 0 , SEEK_SET);
	char* buf = (char*)malloc(sz*sizeof(char));
	fread(buf , 1 , sz , fp);
	xml.Parse(buf);
	TiXmlNode* root = xml.RootElement();
	TiXmlNode* ele = root->FirstChild();
	std::wstring name;
	std::string ip;
	std::wstring wip;
	short port;	
	do
	{
		if(!strcmp(ele->Value() , "area"))
		{
			wchar_t fg[512];
			Unicode8ToUnicode(ele->ToElement()->Attribute("name") , fg);
			name = fg;
			ip = ele->ToElement()->Attribute("gmserver");
			wchar_t ipip[128];
			Unicode8ToUnicode(ip.c_str() , ipip);
			std::string tmp = ele->ToElement()->Attribute("port");
			wip = ipip;
			port = atoi(tmp.c_str());
			m_ipport[name].port = port;
			m_ipport[name].ip= ip;
		}
		else
			;
		int nrow = mAreaList.InsertItem(0  , wip.c_str());	
		mAreaList.SetItemText(nrow ,1  , name.c_str());
		mAreaList.SetItemText(nrow ,2  , L"block");
		mAreaList.SetItemText(nrow ,3  , L"0");
		m_ipport[name].line = nrow;
		ele = travel(ele);
	}while(ele);
	fclose(fp);
	free(buf);
	connect_all();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerToolDlg::OnPaint()
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
HCURSOR CServerToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerToolDlg::connect_all()
{
	int col = -1;
	std::map<std::wstring , com>::iterator p = m_ipport.begin();
	for(;p!=m_ipport.end();++p)
	{
		net_session::instance()->try_create_connect(p->second.ip.c_str() , p->second.port);
		for(int i = 0 ; i < 3 ; ++i)
		{
			if(net_session::instance()->is_connect())
				break;
			else
				Sleep(1000);
		}
		if(net_session::instance()->is_connect())
		{
// 			NP_LOGIN send;
// 			send.eToolType = ETTYPE_SERVERTOOL;
// 			_tcscpy(send.szAccount, _T("gm1"));
// 
// 			std::string pass = unicode_to_ansi(_T("111111"));
// 			pass += "xvDvgqZq";
// 			unsigned char digest[16];
// 			md5_for_string( (char*)pass.c_str(), digest );
// 			std::string strPswMD5;
// 			md5_to_string( strPswMD5, digest );
// 			char szBuff[X_LONG_NAME] = {0};
// 			strncpy( szBuff, strPswMD5.c_str(), MAX_MD5_ARRAY );
// 			strupr( szBuff );
// 			_tcscpy(send.szPsd, ansi_to_unicode(szBuff));
// 			net_session::instance()->send_msg(&send, send.dw_size);			
// 			m_event.timed_wait(2000);
	
		}
		col++;
	}
	mAreaList.SetItemState(col,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}

void CServerToolDlg::onLoginStatus( NP_NET_CMD* mdg )
{
	NET_GMS2C_QueryLoginStatus* cmd = (NET_GMS2C_QueryLoginStatus*)mdg;
	char szIP[128] = {0};
	strncpy(szIP, inet_ntoa((*(in_addr*)&cmd->dwIP)), 128);
	com cc;
	std::map<std::wstring , com>::iterator p = m_ipport.find(cmd->szServerName);
	if(p!=m_ipport.end())
		cc = p->second;
	wchar_t buf[128];
	Unicode8ToUnicode(szIP , buf);
	net_session::instance2()->gmip = buf;
	mAreaList.SetItemText(cc.line ,0  , buf);
	mAreaList.SetItemText(cc.line ,2  , cmd->bOK ? L"connected":L"block");
	wchar_t num[64] = {0};
	_itow(cmd->nOnlinNumber , num , 10);
	mAreaList.SetItemText(cc.line ,3  , num);
	m_event.signal();
	mTotal+=cmd->nOnlinNumber;
	wchar_t onl[128];
	wsprintf(onl , L"total: %d" , mTotal);
	mOnline.SetWindowText(onl);
}

void CServerToolDlg::onLoginOK( NP_NET_CMD* msg )
{
	NET_C2GMS_QueryLoginStatus cmd;
	net_session::instance()->send_msg(&cmd , cmd.dw_size);
	NET_C2GMS_QueryGameServerList cmd1;
	net_session::instance()->send_msg(&cmd1 , cmd1.dw_size);
}
void CServerToolDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CServerToolDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CServerToolDlg::onUpdateServerList( NP_NET_CMD* msg )
{
	mServerList.DeleteAllItems();
	while(mServerList.DeleteColumn(0));
	mServerList.InsertColumn(0 , L"IP");
	mServerList.InsertColumn(1 , L"Name");
	mServerList.InsertColumn(2 , L"Server");
	mServerList.InsertColumn(3 , L"DBServer");
	mServerList.InsertColumn(4 , L"DB");
	mServerList.InsertColumn(5 , L"Total");
	mServerList.InsertColumn(6 , L"Limit");
	mServerList.InsertColumn(7 , L"Ping");
	mServerList.SetColumnWidth(0 , 120);
	mServerList.SetColumnWidth(1 , 100);
	mServerList.SetColumnWidth(2 , 60);
	mServerList.SetColumnWidth(3 , 60);
	mServerList.SetColumnWidth(4 , 60);
	mServerList.SetColumnWidth(5 , 80);
	mServerList.SetColumnWidth(6 , 80);
	
	NET_GMS2C_QueryGameServerList* cmd = (NET_GMS2C_QueryGameServerList*)msg;
	{
		int num = mAreaList.GetItemCount();
		for(int i = 0 ; i < num ; ++i)
		{			
			CString str = mAreaList.GetItemText(i , 0);
			mServerTip.SetWindowText(mAreaList.GetItemText(i , 1));
		}
	}
	for(int i = 0 ; i < cmd->nNumber ; ++i)
	{
		tag_gamaserver_info info = cmd->info[i];
		char szIP[128] = {0};
		strncpy(szIP, inet_ntoa((*(in_addr*)&info.dwIP)), 128);
		wchar_t fg[512];
		Unicode8ToUnicode(szIP , fg);
		int nrow = mServerList.InsertItem(0  , fg);
		mServerList.SetItemText(nrow , 1 , info.szServerName);
		mServerList.SetItemText(nrow , 2 , info.mStatus?L"connected":L"blocked");
		mServerList.SetItemText(nrow , 3 , info.mDBStatus?L"connected":L"blocked");
		mServerList.SetItemText(nrow , 4 , info.mDatebase?L"connected":L"blocked");
		wchar_t buf[32];
		_itow(info.mOnlineNumber , buf , 10);
		mServerList.SetItemText(nrow , 5 , buf);
		memset(buf , 0 , 32*sizeof(wchar_t));
		_itow(info.mMaxNumber , buf , 10);
		mServerList.SetItemText(nrow , 6 , buf);
		sDoubleInfo xxx;
		net_session::instance2()->mDoublePolicy[info.szServerName] = xxx;
	}
}
void CServerToolDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int index = mAreaList.GetSelectionMark();
	CString name = mAreaList.GetItemText(index , 1);
	std::map<std::wstring , com>::iterator p = m_ipport.find(name.GetBuffer());
	if(p!=m_ipport.end())
	{
		net_session::instance()->try_create_connect(p->second.ip.c_str() , p->second.port);
		for(int i = 0 ; i < 3 ; ++i)
		{
			if(net_session::instance()->is_connect())
				break;
			else
				Sleep(2000);
		}
		if(net_session::instance()->is_connect())
		{
			mLogin.DoModal();
			NP_LOGIN send;
			send.eToolType = ETTYPE_SERVERTOOL;	
			_tcscpy(send.szAccount, mLogin.user.GetBuffer());
			std::string pass = unicode_to_ansi(mLogin.pwd.GetBuffer());
			pass += "ssplay.log";
			unsigned char digest[16];
			md5_for_string( (char*)pass.c_str(), digest );
			std::string strPswMD5;
			md5_to_string( strPswMD5, digest );
			char szBuff[X_LONG_NAME] = {0};
			strncpy( szBuff, strPswMD5.c_str(), MAX_MD5_ARRAY );
			strupr( szBuff );
			_tcscpy(send.szPsd, ansi_to_unicode(szBuff));
			net_session::instance()->send_msg(&send, send.dw_size);			
			m_event.timed_wait(2000);
		}
		else
			::MessageBox(0 , _T("can not connect the gm server") , _T("error") , 0);
	}
}

//!全选
void CServerToolDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	int num = mServerList.GetItemCount();
	for(int i = 0 ; i < num ; ++i)
	{
		mServerList.SetFocus();
		mServerList.SetItemState(i , LVIS_SELECTED , LVIS_SELECTED);
		mServerList.EnsureVisible(i, TRUE);
	}	
}
//!公共发言
void CServerToolDlg::OnBnClickedButton7()
{
	mBoardcast.servernamelist.clear();
	// TODO: 在此添加控件通知处理程序代码
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mBoardcast.servernamelist.push_back(name.GetBuffer());
		}
	}
	mBoardcast.DoModal();
}

void CServerToolDlg::OnBnClickedButton8()
{
	mKick.servernamelist.clear();
	// TODO: 在此添加控件通知处理程序代码
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mKick.servernamelist.push_back(name.GetBuffer());
		}
	}
	mKick.DoModal();
}

void CServerToolDlg::OnBnClickedButton9()
{
	mfor.servernamelist.clear();
	// TODO: 在此添加控件通知处理程序代码
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mfor.servernamelist.push_back(name.GetBuffer());
		}
	}
	mfor.DoModal();
}
//!刷新
void CServerToolDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	mTotal = 0;
	NET_C2GMS_QueryLoginStatus cmd;
	net_session::instance()->send_msg(&cmd , cmd.dw_size);
	NET_C2GMS_QueryGameServerList cmd1;
	net_session::instance()->send_msg(&cmd1 , cmd1.dw_size);
}

void CServerToolDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	mNumber.GetWindowText(str);
	int num = _wtoi(str.GetBuffer());
	if(num<=0||num>=3000)
	{
		::MessageBox(0 , _T("please set the limit number between 0 - 3000") , _T("error") , 0);
		return;
	}
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select server") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			NET_C2GMS_SetServerMaxPlayerNumber cmd;
			cmd.nMaxPlayerNumber = num;
			_tcscpy(cmd.szServerName, name.GetBuffer());
			net_session::instance()->send_msg(&cmd , cmd.dw_size);
		}
	}
}


//!禁言
void CServerToolDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			dlg.servernamelist = name.GetBuffer();
		}
	}
	dlg.DoModal();
}
//!关闭服务器
void CServerToolDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	mShutdown.servernamelist.clear();
	// TODO: 在此添加控件通知处理程序代码
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mShutdown.servernamelist.push_back(name.GetBuffer());
		}
	}
	mShutdown.DoModal();
}



void CServerToolDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	mTrain.GetWindowText(str);
	int exp = _wtoi(str.GetBuffer());
	if(!exp||exp<0)
	{
		mTrainCheck = false;
		::MessageBox(0 , _T("input number is invalid") , _T("error") , 0);
		return;
	}
	POSITION i7 = mServerList.GetFirstSelectedItemPosition();
	if(i7 == NULL)
	{
		::MessageBox(0 , _T("please select the server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i7)
		{
			int item = mServerList.GetNextSelectedItem(i7);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mCTime.servernamelist.push_back(name.GetBuffer());
			sDoubleInfo& xxx = net_session::instance2()->mDoublePolicy[name.GetBuffer()];
			xxx.bei[2] = exp;
		}
	}
	mCTime.index = 2;
	mCTime.DoModal();
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select the server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			if(net_session::instance2()->continueTime)
			{
				NET_C2GMS_SetDoublePolicy cmd;
				cmd.eType = EGMDT_Practice;
				cmd.dwValue = exp*100;
				_tcscpy(cmd.szServerName, name.GetBuffer());
				tagDWORDTime time = GetCurrentDWORDTime();
				cmd.dwStartTime = (DWORD)time;
				cmd.dwPersistSeconds = net_session::instance2()->continueTime;
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
	}
}

void CServerToolDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	mEXP.GetWindowText(str);
	int exp = _wtoi(str.GetBuffer());
	if(!exp||exp<0)
	{
		::MessageBox(0 , _T("input number is invalid") , _T("error") , 0);
		return;
	}
	POSITION i7 = mServerList.GetFirstSelectedItemPosition();
	if(i7 == NULL)
	{
		::MessageBox(0 , _T("please select the server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i7)
		{
			int item = mServerList.GetNextSelectedItem(i7);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mCTime.servernamelist.push_back(name.GetBuffer());
			sDoubleInfo& xxx = net_session::instance2()->mDoublePolicy[name.GetBuffer()];
			xxx.bei[0] = exp;
		}
	}
	mCTime.index = 0;
	mCTime.DoModal();
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select the server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			if(net_session::instance2()->continueTime)
			{
				NET_C2GMS_SetDoublePolicy cmd;
				cmd.eType = EGMDT_EXP;
				cmd.dwValue = exp*100;
				_tcscpy(cmd.szServerName, name.GetBuffer());
				tagDWORDTime time = GetCurrentDWORDTime();
				cmd.dwStartTime = (DWORD)time;
				cmd.dwPersistSeconds = net_session::instance2()->continueTime;
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
	}
}

void CServerToolDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	mITEM.GetWindowText(str);
	int exp = _wtoi(str.GetBuffer());
	if(!exp||exp<0)
	{
		mItemCheck = false;
		::MessageBox(0 , _T("input number is invalid") , _T("error") , 0);
		return;
	}
	POSITION i7 = mServerList.GetFirstSelectedItemPosition();
	if(i7 == NULL)
	{
		::MessageBox(0 , _T("please select the server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i7)
		{
			int item = mServerList.GetNextSelectedItem(i7);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			mCTime.servernamelist.push_back(name.GetBuffer());
			sDoubleInfo& xxx = net_session::instance2()->mDoublePolicy[name.GetBuffer()];
			xxx.bei[1] = exp;
		}
	}
	mCTime.index = 1;
	mCTime.DoModal();
	POSITION i = mServerList.GetFirstSelectedItemPosition();
	if(i == NULL)
	{
		::MessageBox(0 , _T("please select the server you want to apply") , _T("error") , 0);
		return;
	}
	else
	{
		while(i)
		{
			int item = mServerList.GetNextSelectedItem(i);
			CString name = mServerList.GetItemText(item , 1);
			if(name.IsEmpty())
				continue;
			if(net_session::instance2()->continueTime)
			{
				NET_C2GMS_SetDoublePolicy cmd;
				cmd.eType = EGMDT_ITEM;
				cmd.dwValue = exp*100;
				_tcscpy(cmd.szServerName, name.GetBuffer());
				tagDWORDTime time = GetCurrentDWORDTime();
				cmd.dwStartTime = (DWORD)time;
				cmd.dwPersistSeconds = net_session::instance2()->continueTime;
				net_session::instance()->send_msg(&cmd , cmd.dw_size);
			}
		}
	}
}
