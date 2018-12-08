#include <qxml/QXML.h>
#include <dae/Library.h>
#include <dae/library_effects/Effect.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_effects (0 or more)
	/// </summary>
	class LibraryEffects : public Library< Effect >
	{
	public:
		LibraryEffects( IDocument & document, const qxml::Element * node );
	};
}