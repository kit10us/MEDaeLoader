#include <dae/Input_Shared.h>
#include <unify/String.h>

using namespace dae;

Input_Shared::Input_Shared( const qxml::Element * node )
: m_offset( node->GetAttributeElse< int >( "offset", 0 ) )
, m_semantic( node->GetAttribute< std::string >( "semantic" ) )
, m_source( node->GetAttribute< std::string >( "source" ) )
{
	if ( node->HasAttributes( "set" ) )
	{
		m_set = node->GetAttribute< int >( "set" );
	}

	if( unify::string::StringIs( m_semantic, "VERTEX" ) )
	{
		m_stride = 3;
	}
	else if( unify::string::StringIs( m_semantic, "POSITION" ) )
	{
		m_stride = 3;
	}
	else if( unify::string::StringIs( m_semantic, "NORMAL" ) )
	{
		m_stride = 3;
	}
	else if( unify::string::StringIs( m_semantic, "COLOR" ) )
	{
		m_stride = 1;
	}
	else if( unify::string::StringIs( m_semantic, "TEXCOORD" ) )
	{
		m_stride = 2;
	}
}

const int Input_Shared::GetOffset() const
{
	return m_offset;
}

std::string Input_Shared::GetSemantic() const
{
	return m_semantic;
}

std::string Input_Shared::GetSource() const
{
	return m_source;
}

const unify::Optional< int > & Input_Shared::GetSet() const
{
	return m_set;
}

size_t Input_Shared::GetStride() const
{
	return m_stride;
}
