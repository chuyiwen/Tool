// SvrConfig.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define BUFFSIZE 0x10000


VOID LoadIniFromDir(LPCTSTR szDir, std::vector<tstring>& iniFiles, BOOL bFirst=FALSE)
{
	if( bFirst )
	{
		// ����ǵ�һ�ν���ú�������Ѱ��ȫ�ֽű�Ŀ¼
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
		// �����Ŀ¼����ݹ����
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
	
	// ���ó���Ĭ��·��
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

	std::cout << "��ȡini�ļ�����:" << iniFiles.size() << std::endl;
	
	//std::cout << "\n���������ʼ�����ļ�..." << std::endl;
	
	std::cout << "\n������ɺ��Ƿ�ɾ��ԭʼ�ļ�?(Y/N)" << std::endl;

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

	// ���ܸ����ļ�
	for(std::vector<tstring>::iterator itr = iniFiles.begin(); itr != iniFiles.end(); ++itr)
	{
		tstring strFileName = *itr;

		_sntprintf(szFileName, MAX_PATH, _T("%s"), strFileName.c_str());
		
		//_tprintf(_T("�����ļ�:%s"), strFileName.c_str());

		std::wcout << _T("�����ļ�:") << strFileName.c_str() << std::endl;

		FILE *pf = _tfopen(itr->c_str(),_T("rb+"));
		if (!pf)
		{
			std::cout << "�����ļ�ʧ��" << std::endl;
			continue;
		}
		fseek(pf,0,SEEK_END);
		int FileLen  =ftell(pf);
		if(FileLen>BUFFSIZE)
		{
			fclose(pf);
			printf("�ļ�����64k,��ʧ��\n");
			continue;
		}
		
		// ��ȡ���ݵ��ڴ���
		fseek(pf,0,SEEK_SET);
		fread(FileBuff,FileLen,1,pf);
		fclose(pf); 
		
		// ��������
		INT len = (FileLen / 8 + 1) * 8;
		INT	nIndex = 2;
		get_tool()->encrypt(FileBuff, FileTempBuffer, len, nIndex, 1);
		
		// ���ɼ����ļ�
		size_t pos = strFileName.find(_T(".ini"));
		tstring strNewFile = strFileName;
		strNewFile.replace(pos, 4, _T(".inc"));
		
		pf = _tfopen(strNewFile.c_str() ,_T("wb+"));
		fwrite(&nIndex, sizeof(nIndex), 1, pf);
		fwrite(FileTempBuffer,len,1,pf);
		fclose(pf);
		
		std::wcout << _T("���ɼ����ļ�:") << strNewFile.c_str() << std::endl;

	
		if (bDelete)
		{
			::DeleteFile(strFileName.c_str());
			std::wcout << _T("ԭʼ�ļ���ɾ��!")<< std::endl;
		}
		
		std::wcout << _T("\n") << std::endl;
	}

	std::cout << "\n�����������..." << std::endl;

	while(!_kbhit()){}


	return 0;
}

