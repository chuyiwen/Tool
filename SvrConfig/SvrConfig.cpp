// SvrConfig.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define BUFFSIZE 0x10000


VOID LoadIniFromDir(LPCTSTR szDir, std::vector<tstring>& iniFiles, BOOL bFirst=FALSE)
{
	if( bFirst )
	{
		// 如果是第一次进入该函数，则寻找全局脚本目录
		TCHAR szGlobalDir[MAX_PATH];
		_tcscpy(szGlobalDir, szDir);
		_tcscat(szGlobalDir, _T("\\"));
		_tcscat(szGlobalDir, _T("gloable"));
		LoadIniFromDir(szGlobalDir, iniFiles);
	}

	HANDLE hFile;
	WIN32_FIND_DATA fd;
	memset(&fd, 0, sizeof(fd));

	TCHAR szSearchName[MAX_PATH];

	_tcscpy(szSearchName, szDir);
	_tcscat(szSearchName, _T("\\*.*"));

	hFile = FindFirstFile(szSearchName, &fd);
	FindNextFile(hFile, &fd);

	while( FindNextFile(hFile, &fd) )
	{
		// 如果是目录，则递归调用
		if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			if( !bFirst || 0 != _tcscmp(fd.cFileName, _T("gloable")) )
			{
				_tcscpy(szSearchName, szDir);
				_tcscat(szSearchName, _T("\\"));
				_tcscat(szSearchName, fd.cFileName);
				LoadIniFromDir(szSearchName, iniFiles);
			}
		}
		else
		{
			TCHAR* ext = _tcsrchr(fd.cFileName, _T('.'));

			if(VALID_POINT(ext) && !_tcsicmp(ext, _T(".ini")) )
			{
				tstring fname = szDir;
				fname += _T("\\");
				fname += fd.cFileName;

				iniFiles.push_back(fname);
			}
		}
	}
	FindClose(hFile);
}

int _tmain(int argc, _TCHAR* argv[])
{
	serverbase::init_serverbase();
	
	// 设置程序默认路径
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	TCHAR *pResult = _tcsrchr(szPath, _T('\\'));	
	if(pResult)
		*pResult = 0;

	SetCurrentDirectory(szPath);


	TCHAR FileBuff[BUFFSIZE];
	TCHAR FileTempBuffer[BUFFSIZE];
	memset(FileBuff,0,sizeof(FileBuff));
	memset(FileTempBuffer, 0, sizeof(FileTempBuffer));
	
	std::vector<tstring> iniFiles;
	LoadIniFromDir(_T("..\\server_config"), iniFiles, TRUE);
	
	std::wcout.imbue(std::locale("chs"));

	std::cout << "读取ini文件个数:" << iniFiles.size() << std::endl;
	
	//std::cout << "\n按任意键开始加密文件..." << std::endl;
	
	std::cout << "\n加密完成后是否删除原始文件?(Y/N)" << std::endl;

	char c;
	std::cin >> c;

	BOOL bDelete = FALSE;
	if (c == 'Y' || c== 'y')
	{
		bDelete = TRUE;
	}

	//while(!_kbhit()){}

	TCHAR szFileName[MAX_PATH];
	TCHAR szNewFileName[MAX_PATH];

	// 加密各个文件
	for(std::vector<tstring>::iterator itr = iniFiles.begin(); itr != iniFiles.end(); ++itr)
	{
		tstring strFileName = *itr;

		_sntprintf(szFileName, MAX_PATH, _T("%s"), strFileName.c_str());
		
		//_tprintf(_T("加载文件:%s"), strFileName.c_str());

		std::wcout << _T("加载文件:") << strFileName.c_str() << std::endl;

		FILE *pf = _tfopen(itr->c_str(),_T("rb+"));
		if (!pf)
		{
			std::cout << "加载文件失败" << std::endl;
			continue;
		}
		fseek(pf,0,SEEK_END);
		int FileLen  =ftell(pf);
		if(FileLen>BUFFSIZE)
		{
			fclose(pf);
			printf("文件超过64k,打开失败\n");
			continue;
		}
		
		// 读取数据到内存中
		fseek(pf,0,SEEK_SET);
		fread(FileBuff,FileLen,1,pf);
		fclose(pf); 
		
		// 加密数据
		INT len = (FileLen / 8 + 1) * 8;
		INT	nIndex = 2;
		get_tool()->encrypt(FileBuff, FileTempBuffer, len, nIndex, 1);
		
		// 生成加密文件
		size_t pos = strFileName.find(_T(".ini"));
		tstring strNewFile = strFileName;
		strNewFile.replace(pos, 4, _T(".inc"));
		
		pf = _tfopen(strNewFile.c_str() ,_T("wb+"));
		fwrite(&nIndex, sizeof(nIndex), 1, pf);
		fwrite(FileTempBuffer,len,1,pf);
		fclose(pf);
		
		std::wcout << _T("生成加密文件:") << strNewFile.c_str() << std::endl;

	
		if (bDelete)
		{
			::DeleteFile(strFileName.c_str());
			std::wcout << _T("原始文件被删除!")<< std::endl;
		}
		
		std::wcout << _T("\n") << std::endl;
	}

	std::cout << "\n按任意键继续..." << std::endl;

	while(!_kbhit()){}


	return 0;
}

