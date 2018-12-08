#include <dae/Exceptions.h>

using namespace dae;
					
Exception_MissingCOLLADA::Exception_MissingCOLLADA( std::string filename )
: unify::Exception( "COLLADA DAE file \"" + filename + "\" must have the root element \"COLLADA\"!" )
{
}
					
Exception_NotSupported::Exception_NotSupported( std::string feature )
: unify::Exception( "DAE feature \"" + feature + "\" not supported!" )
{
}

Exception_MissingChildElement::Exception_MissingChildElement( std::string parent, std::string child )
: unify::Exception( "DAE element " + parent + " is mising '" + child + "' child element!" )
{
}
