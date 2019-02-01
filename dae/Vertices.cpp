// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/Vertices.h>

using namespace dae;

Vertices::Vertices( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_id( node->GetAttribute< std::string >( "id" ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "input" ) )
		{
			m_input.push_back( std::shared_ptr< Input_Shared >( new Input_Shared( childNode ) ) );
		}
	}
}

std::string Vertices::GetID() const
{
	return m_id;
}

std::string Vertices::GetName() const
{
	return m_name;
}

const std::vector< std::shared_ptr< Input_Shared > > & Vertices::GetInput() const
{
	return m_input;
}
