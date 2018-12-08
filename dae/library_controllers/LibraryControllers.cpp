#include <dae/library_controllers/LibraryControllers.h>

using namespace dae;

LibraryControllers::LibraryControllers( IDocument & document, const qxml::Element * node )
: Library< Controller >( document, node, "controller" )
{
}