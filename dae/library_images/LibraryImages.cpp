#include <dae/library_images/LibraryImages.h>

using namespace dae;

LibraryImages::LibraryImages( IDocument & document, const qxml::Element * node )
: Library< Image >( document, node, "image" ) 
{
}