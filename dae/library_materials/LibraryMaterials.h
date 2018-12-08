#include <qxml/QXML.h>
#include <dae/Library.h>
#include <dae/library_materials/Material.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_materials (0 or more)
	/// </summary>
	class LibraryMaterials : public Library< Material >
	{
	public:
		LibraryMaterials( IDocument & document, const qxml::Element * node );
	};
}