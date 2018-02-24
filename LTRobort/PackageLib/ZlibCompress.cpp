#include "ZlibCompress.h"
#include "zlib\zlib.h"

namespace Package
{
namespace Compress
{
ProcessResult ZlibCompress::Compress(uint8_t* out_buf, uint32_t out_buf_len, uint8_t* in_buf, uint32_t in_buf_len)
{	
	ProcessResult ret;
	ret.first  = false;
	ret.second = 0;

	if ( Z_OK == ::compress( out_buf, (uLongf*)&out_buf_len, in_buf, in_buf_len ) )
	{
		ret.second = out_buf_len;
		ret.first = true;
	}

	return ret;
}

ProcessResult ZlibCompress::Uncompress(uint8_t* out_buf, uint32_t out_buf_len, uint8_t* in_buf, uint32_t in_buf_len)
{
	ProcessResult ret;
	ret.first  = false;
	ret.second = 0;

	if ( Z_OK == ::uncompress( out_buf, (uLongf*)&out_buf_len, in_buf, in_buf_len ) )
	{
		ret.second = out_buf_len;
		ret.first = true;
	}

	return ret;
}

uint32_t ZlibCompress::GetBufferSize( uint32_t size )
{
	// 0.1% larger than sourcelen plus 12 bytes
	return size + size / 1000 + 12;
}

}; // namespace Compress {
}; // namespace Package {