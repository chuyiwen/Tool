// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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
