// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT





#ifndef INVALID_VALUE
#define INVALID_VALUE				(-1)
#endif
#ifndef VALID_VALUE
#define VALID_VALUE(n)				(((INT)(n)) != INVALID_VALUE)
#endif
#ifndef VALID_POINT
#define VALID_POINT(n)				( (((INT)(n)) != INVALID_VALUE) && ((n) != NULL) )
#endif

#ifndef INVALID
#define INVALID						(-1)
#endif
#ifndef IS_VALID
#define IS_VALID(n)					(((INT)(n)) != INVALID)
#endif
#ifndef IS_VALID_PTR
#define IS_VALID_PTR(n)				( (((INT)(n)) != INVALID) && ((n) != NULL) )
#endif

#ifndef SAFE_DEL
#define SAFE_DEL(p)				{ if(p) { delete(p);		(p) = NULL; } }
#endif

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <list>
#include <map>
#include <process.h>

using namespace std;
#include "..\..\..\common\WorldDefine\time.h"
#include "base_define.h"
#include "..\..\..\siEngineSDK\Include\siCore\siCore.h"
using namespace si;
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\..\\siEngineSDK\\Lib\\debug\\siCore.lib")
#else
#pragma comment(lib,"..\\..\\..\\siEngineSDK\\Lib\\Release\\siCore.lib")
#endif

#include "FastDelegate.h"
#include "Singleton.h"
#include "net_define.h"
#include "SList.h"
#include "SMap.h"
#include "f_util.h"
#include "f_md5.h"
#include "f_data_set.h"
#include "NetCmdMgr.h"
#include "Console.h"
#include "ClientVFS.h"
//#include "..\vEngine\vEngine.h"
//using namespace vEngine;
//#ifdef _DEBUG
//#pragma comment(lib,"..\\vsout\\vEngine\\debug\\vEngine.lib")
//#else
//#define X_STRING_RUN_TIME "Release"
//#pragma comment(lib,"..\\vsout\\vEngine\\release\\vEngine.lib")
//#endif
