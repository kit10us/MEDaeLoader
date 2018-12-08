#include <dae/Input_Unshared.h>
#include <unify/String.h>

using namespace dae;

Input_Unshared::Input_Unshared( const qxml::Element * node )
: m_semantic( node->GetAttribute< std::string >( "semantic" ) )
, m_source( node->GetAttribute< std::string >( "source" ) )
{
}

std::string Input_Unshared::GetSemantic() const
{
	return m_semantic;
}

std::string Input_Unshared::GetSource() const
{
	return m_source;
}
