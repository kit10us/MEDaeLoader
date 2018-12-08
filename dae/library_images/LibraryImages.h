#include <qxml/QXML.h>
#include <dae/Library.h>
#include <dae/library_images/Image.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_images (0 or more)
	/// </summary>
	class LibraryImages : public Library< Image >
	{
	public:
		LibraryImages( IDocument & document, const qxml::Element * node );
	};
}