#include <dae/library_nodes/LibraryNodes.h>

using namespace dae;

LibraryNodes::LibraryNodes( IDocument & document, const qxml::Element * node )
: Library< Node >( document, node, "node" ) 
{
}