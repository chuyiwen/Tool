#pragma once
#include "ICompress.h"

namespace Package
{
namespace Compress
{
class ZlibCompress : public ICompress
{
public:
	virtual ProcessResult Compress(uint8_t* out_buf, uint32_t out_buf_len, uint8_t* in_buf, uint32_t in_buf_len);
	virtual ProcessResult Uncompress(uint8_t* out_buf, uint32_t out_buf_len, uint8_t* in_buf, uint32_t in_buf_len);

	virtual uint32_t GetBufferSize( uint32_t size );
};

}; // namespace Compress {
}; // namespace Package {