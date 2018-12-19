#include <dae/FloatArray.h>
#include <unify/String.h>

using namespace dae;

FloatArray::FloatArray( const qxml::Element * node )
: m_count( node->GetAttribute< int >( "count" ) )
, m_id( node->GetAttributeElse( "id", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
, m_digits( node->GetAttributeElse< int >( "digits", 6 ) )
, m_magnitude( node->GetAttributeElse< int >( "magnitude", 38 ) )
{
	m_stringContents = node->GetText();
	m_arrayContents = unify::string::SplitOnWhitespace< float >( m_stringContents );
}

int FloatArray::GetCount() const
{
	return m_count;
}

std::string FloatArray::GetID() const
{
	return m_id;
}

std::string FloatArray::GetName() const
{
	return m_name;
}

int FloatArray::GetDigits() const
{
	return m_digits;
}

int FloatArray::GetMagnitude() const
{
	return m_magnitude;
}

std::string FloatArray::GetStringContents() const
{
	return m_stringContents;
}

const std::vector< float > & FloatArray::GetArrayContents() const
{
	return m_arrayContents;
}
