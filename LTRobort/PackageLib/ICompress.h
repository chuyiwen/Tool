#pragma once
#include "IPackage.h"

namespace Package
{
namespace Compress
{

// 处理结果
// first  [bool]     操作是否成功
// second [uint32_t] 压缩/解压缩后数据大小
typedef std::pair<bool,uint32_t> ProcessResult;

class ICompress
{
public:
	virtual ProcessResult Compress(uint8_t* out_buf, uint32_t out_buf_len, uint8_t* in_buf, uint32_t in_buf_len) = 0;
	virtual ProcessResult Uncompress(uint8_t* out_buf, uint32_t out_buf_len, uint8_t* in_buf, uint32_t in_buf_len) = 0;

	virtual uint32_t GetBufferSize( uint32_t size ) = 0;
};

enum ECompressType
{
	ECT_ZLIB,
};

typedef boost::shared_ptr<ICompress> CompressPtr;
CompressPtr GetCompressInterface(ECompressType type);
}; // namespace Compress {
}; // namespace Package {