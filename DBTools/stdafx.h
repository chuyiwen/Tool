// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT









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

//-----------------------------------------------------------------------------
// 引用数据库引擎
//-----------------------------------------------------------------------------
#include "../../common/serverbase/serverbase.h"
#include "../../common/memory/memory_define.h"
#include "../../common/ODBC/ODBC.h"
#include "../../common/network/network_define.h"
#include "..\..\common\dump\dump_define.h"
using namespace serverbase;

using namespace odbc;

using namespace memorysystem;

using namespace networkbase;

using namespace serverdump;

#ifdef _DEBUG
#define X_STRING_RUN_TIME "Debug"
#pragma comment(lib, "../vsout/ODBC/debug/ODBC.lib")
#pragma comment(lib, "../vsout/ServerDefine/debug/ServerDefine.lib")
#pragma comment(lib, "../vsout/network/debug/network.lib")
#pragma comment(lib,"..\\vsout\\dump\\debug\\dump.lib")
#pragma comment(lib, "../vsout/WorldDefine/debug/WorldDefine.lib")
#else
#define X_STRING_RUN_TIME "Release"
#pragma comment(lib, "../../../vsout/serverbase/release/serverbase.lib")
#pragma comment(lib, "../../../vsout/memory/release/memory.lib")
#pragma comment(lib, "../../../vsout/ODBC/release/ODBC.lib")
#pragma comment(lib, "../../../vsout/ServerDefine/release/ServerDefine.lib")
#pragma comment(lib, "../../../vsout/network/release/network.lib")
#pragma comment(lib,"..\\..\\..\\vsout\\dump\\release\\dump.lib")
#pragma comment(lib, "../../../vsout/WorldDefine/release/WorldDefine.lib")
#endif

#include "..\..\common\filesystem\file_define.h"
using namespace filesystem;

#ifdef _DEBUG
#define X_STRING_RUN_TIME "Debug"
#pragma comment(lib,"..\\vsout\\filesystem\\debug\\filesystem.lib")
#else
#define X_STRING_RUN_TIME "Release"
#pragma comment(lib,"..\\..\\..\\vsout\\filesystem\\release\\filesystem.lib")
#endif

#include "..\..\common\serverframe\frame_define.h"
using namespace serverframe;

#ifdef _DEBUG
#define X_STRING_RUN_TIME "Debug"
#pragma comment(lib,"..\\vsout\\serverframe\\debug\\serverframe.lib")
#else
#define X_STRING_RUN_TIME "Release"
#pragma comment(lib,"..\\..\\..\\vsout\\serverframe\\release\\serverframe.lib")
#endif



//------------------------------------------------------------------------------

#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"winmm.lib")

#include "WorldDefine\base_define.h"
#include "WorldDefine\time.h"
#include "WorldDefine\ItemDefine.h"
#include "ServerDefine\role_data_server_define.h"
#include "ServerDefine\guild_server_define.h"
#include "..\siLogin\si_login_server_define.h"
#include "ServerDefine\mail_server_define.h"
#include "ServerDefine\master_apprentice_server_define.h"
#include "WorldDefine\paimai_protocol.h"
#include "ServerDefine\pet_server_define.h"
#include "ServerDefine\title_server_define.h"
#include "WorldDefine\bank_protocol.h"
#include "ServerDefine\base_server_define.h"
#include "ServerDefine\achievement_server_define.h"
#include "WorldDefine\guerdon_quest_define.h"
#include "Data_define.h"
#include "WorldDefine\reward_define.h"
#include "WorldDefine\vcard_define.h"

