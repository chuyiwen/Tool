#pragma once
#include <tchar.h>
#include <string>

#include <boost\shared_ptr.hpp>

namespace Package
{
typedef unsigned __int64 uint64_t;
typedef __int64          int64_t;
typedef unsigned int	uint32_t;
typedef int				int32_t;
typedef unsigned short  uint16_t;
typedef short			int16_t;
typedef unsigned char	uint8_t;
typedef char			int8_t;

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string  tstring;
#endif

enum EPackageType
{
	EPT_TPK,
};

// �ļ���С��ѯ���
// first  [bool]     �ļ��Ƿ����
// second [uint32_t] �ļ���С
typedef std::pair<bool,uint32_t> FileSizeResult;

const uint32_t DEFAULT_MAX_FILE_NUM = 10000;

enum EPackageErrorCode
{
    EPEC_IOCreateFileFailed,
    EPEC_IOOpenFileNotExist,
    EPEC_IOOpenFileFailed,
    EPEC_IOReadFileFailed,
    EPEC_IOWriteFileFailed,

    EPEC_OpenMagicInvalid,
    EPEC_OpenVersionInvalid,
    EPEC_OpenFileNumInvalid,

    EPEC_PackageFull,
    EPEC_HashConflict,
    EPEC_HashNotExist,

    EPEC_BuffTooSmall,
    EPEC_UncompressFailed,
};

class IPackage
{
public:	
	virtual ~IPackage() { }

	virtual bool Create		(tstring const& strPackage, uint32_t maxFileNum =DEFAULT_MAX_FILE_NUM )		= 0;
	virtual bool Open		(tstring const& strPackage)		= 0;
	virtual bool Close		()								= 0;
	virtual bool Flush		()								= 0;
    virtual bool Rebuild    ()                              = 0;
    virtual float GetFragmentPercent()                      = 0;
	
	virtual bool AddFile    (tstring const& strFile, void const* pData, size_t len) = 0;
	virtual bool AddFile	(tstring const& strFile)		= 0;
	virtual bool DelFile	(tstring const& strFile)		= 0;
		
	virtual FileSizeResult	GetFileSize(tstring const& strFile) = 0;
	virtual bool			GetFileData(tstring const& strFile, void* pData, size_t len) = 0;

    virtual EPackageErrorCode GetErrorCode() = 0;
    virtual tstring const&    GetErrorMsg() = 0;
};

typedef boost::shared_ptr<IPackage> PackagePtr;
PackagePtr GetPackageInterface(EPackageType type); 

}; // namespace Package