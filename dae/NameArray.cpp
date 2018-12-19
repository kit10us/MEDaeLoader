#include <dae/NameArray.h>
#include <unify/String.h>

using namespace dae;

NameArray::NameArray( const qxml::Element * node )
: m_count( node->GetAttribute< int >( "count" ) )
, m_id( node->GetAttributeElse( "id", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	m_stringContents = node->GetText();
	m_arrayContents = unify::string::SplitOnWhitespace< std::string >( m_stringContents );
}

int NameArray::GetCount() const
{
	return m_count;
}

std::string NameArray::GetID() const
{
	return m_id;
}

std::string NameArray::GetName() const
{
	return m_name;
}

std::string NameArray::GetStringContents() const
{
	return m_stringContents;
}

const std::vector< std::string > & NameArray::GetArrayContents() const
{
	return m_arrayContents;
}
