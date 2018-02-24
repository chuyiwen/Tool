// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>


// TODO: 在此处引用程序需要的其他头文件
#include "..\server\common\serverbase\serverbase.h"
#include "..\server\common\filesystem\file_define.h"
using namespace filesystem;
using namespace serverbase;

#ifdef _DEBUG
#define X_STRING_RUN_TIME "Debug"
#pragma comment(lib,"..\\vsout\\serverbase\\debug\\serverbase.lib")
#else
#define X_STRING_RUN_TIME "Release"
#pragma comment(lib,"..\\vsout\\serverbase\\release\\serverbase.lib")
#endif


#ifdef _DEBUG
#define X_STRING_RUN_TIME "Debug"
#pragma comment(lib,"..\\vsout\\filesystem\\debug\\filesystem.lib")
#else
#define X_STRING_RUN_TIME "Release"
#pragma comment(lib,"..\\vsout\\filesystem\\release\\filesystem.lib")
#endif
