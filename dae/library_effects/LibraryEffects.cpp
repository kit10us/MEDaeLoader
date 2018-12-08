#include <dae/library_effects/LibraryEffects.h>

using namespace dae;

LibraryEffects::LibraryEffects( IDocument & document, const qxml::Element * node )
: Library< Effect >( document, node, "effect" ) 
{
}