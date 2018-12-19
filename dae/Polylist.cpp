#include <dae/Polylist.h>
#include <unify/String.h>

using namespace dae;

Polylist::Polylist( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_name( node->GetAttributeElse( "name", std::string() ) )
, m_count( node->GetAttribute< int >( "count" ) )
, m_material( node->GetAttributeElse( "material", std::string() ) )
{
	std::vector< char > splitDelimitors;
	splitDelimitors.push_back( ' ' );
	splitDelimitors.push_back( '\n' );
	splitDelimitors.push_back( '\t' );

	if ( node->IsTagName( "polylist" ) )
	{
		m_type = PolylistType;
	}
	else if ( node->IsTagName( "triangles" ) )
	{
		m_type = TrianglesType;
	}
	else if ( node->IsTagName( "lines" ) )
	{
		m_type = LinesType;
	}
	else
	{
		throw unify::Exception( "\"" + node->GetName() + "\" is not a supported primitive type for Collada documents!" );
	}

	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "input" ) )
		{
			m_input.push_back( std::shared_ptr< Input_Shared >( new Input_Shared( childNode ) ) );
		}
		else if ( childNode->IsTagName( "vcount" ) )
		{
			m_vcount = unify::string::SplitOnWhitespace< int >( childNode->GetText() );
		}
		else if ( childNode->IsTagName( "p" ) )
		{
			m_p = unify::string::SplitOnWhitespace< int >( childNode->GetText() );
		}
	}
}

std::string Polylist::GetName() const
{
	return m_name;
}

int Polylist::GetCount() const
{
	return m_count;
}

std::string Polylist::GetMaterial() const
{
	return m_material;
}

const std::vector< std::shared_ptr< Input_Shared > > & Polylist::GetInput() const
{
	return m_input;
}

const std::vector< int > & Polylist::GetVCount() const
{
	return m_vcount;
}

const std::vector< int > & Polylist::GetP() const
{
	return m_p;
}

Polylist::Type Polylist::GetType() const
{
	return m_type;
}
