#include "IPackage.h"
#include "TPKPackage.h"

namespace Package 
{
PackagePtr GetPackageInterface(EPackageType type)
{
	if ( type == EPT_TPK )
		return PackagePtr( new CPKUpdate );

	return PackagePtr();
}

}; // namespace Package {