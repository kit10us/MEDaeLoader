#include <qxml/QXML.h>
#include <dae/Library.h>
#include <dae/Node.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_nodes (0 or more)
	/// </summary>
	class LibraryNodes : public Library< Node >
	{
	public:
		LibraryNodes( IDocument & document, const qxml::Element * node );
	};
}