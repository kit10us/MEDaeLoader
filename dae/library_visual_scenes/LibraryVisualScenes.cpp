#include <dae/library_visual_scenes/LibraryVisualScenes.h>

using namespace dae;

LibraryVisualScenes::LibraryVisualScenes( IDocument & document, const qxml::Element * node )
: Library< VisualScene >( document, node, "visual_scene" )
{
}
