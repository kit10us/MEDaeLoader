#include <dae/library_geometries/LibraryGeometries.h>

using namespace dae;

LibraryGeometries::LibraryGeometries( IDocument & document, const qxml::Element * node )
: Library< Geometry >( document, node, "geometry" )
{
}