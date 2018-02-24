#include "ICompress.h"
#include "ZlibCompress.h"

namespace Package
{
namespace Compress
{

CompressPtr GetCompressInterface(ECompressType type)
{
	if ( type == ECT_ZLIB )
		return CompressPtr( new ZlibCompress );

	return CompressPtr();
}

}; // namespace Compress {
}; // namespace Package {