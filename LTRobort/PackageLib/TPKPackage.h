#pragma once
#include <fstream>
#include <vector>
#include <map>

#include "IPackage.h"
#include "TPKDefine.h"

namespace Package
{
class CPKUpdate : public IPackage
{
public:	
	CPKUpdate();
	virtual ~CPKUpdate();

	virtual bool Create(tstring const& strPackage, uint32_t maxFileNum);
	virtual bool Open(tstring const& strPackage);
	virtual bool Close();
	virtual bool Flush();
    virtual bool Rebuild();
    virtual float GetFragmentPercent();
	
	virtual bool AddFile(tstring const& strFile, void const* pData, size_t len);
	virtual bool AddFile(tstring const& strFile);    
	virtual bool DelFile(tstring const& strFile);

	virtual FileSizeResult GetFileSize(tstring const& strFile);
	virtual bool GetFileData(tstring const& strFile, void* pData, size_t len);

    virtual EPackageErrorCode GetErrorCode();
    virtual tstring const&    GetErrorMsg();
private:
    bool            _AddFile(uint32_t hash, void const* pData, size_t len);
    bool            _DelFile(uint32_t hash);
    FileSizeResult  _GetFileSize(uint32_t hash);
	bool            _GetFileData(uint32_t hash, void* pData, size_t len);

	void			SortTable();
	uint32_t		CalcHash(tstring const& strFile);
    tagCPKTable*	GetTable(uint32_t hash);
    tagCPKTable*	NewTable(uint32_t hash, uint32_t len);
    bool            FreeTable(uint32_t hash);
	bool            RebuildHashMap();

    void            CheckBackupHeader();
    void            BackupHeader();
    void            DeleteBackupHeader();
    tstring         GetBackupPath(tstring const& strPath);
    tstring         GetRebuildPath(tstring const& strPath);
    tstring         GetRebuildBackupPath(tstring const& strPath);
    void            SetError(EPackageErrorCode code, tstring const& msg = _T(""));

    bool            ReadHeaderAndTable(std::fstream& fs, tagCPKHeader& header, std::vector<tagCPKTable>& table);
    bool            WriteHeaderAndTable(std::fstream& fs, tagCPKHeader const& header, std::vector<tagCPKTable> const& table);
private:
    tstring                             m_path;         //!< 包文件路径
	std::fstream						m_file;			//!< 包文件流
	tagCPKHeader						m_Header;		//!< CPK文件头
	std::vector<tagCPKTable>			m_vTable;		//!< CPK文件表	
	std::map<uint32_t,tagCPKTable*>		m_hash2table;   //!< hash映射表
    EPackageErrorCode                   m_errCode;
    tstring                             m_errMsg;
	
	bool                                m_bDirty;       //!< 已进行写入操作 无法再进行正常的读取操作
};

}; // namespace Package