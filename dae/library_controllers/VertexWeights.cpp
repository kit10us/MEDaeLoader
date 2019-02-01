// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_controllers/VertexWeights.h>

using namespace dae;
VertexWeights::VertexWeights( IDocument & document, const qxml::Element * node )
	: DocumentNode( document, node )
	, m_count_attribute{ node->GetAttribute< int >( "count" ) }
{
	for ( const auto & childNode : node->Children() )
	{ 
		if ( childNode.IsTagName( "input" ) )
		{
			m_inputs.push_back( Input_Shared::ptr( new dae::Input_Shared( &childNode ) ) );
		}
		else if( childNode.IsTagName( "vcount" ) )
		{
			std::string text = childNode.GetText();
			size_t index = 0;
			size_t left = 0;
			size_t right = 0;

			char sep = ' ';
			do
			{
				right = text.find( sep, left );
				std::string value = text.substr( left, right - left );
				m_vcount.push_back( unify::Cast< int >( value ) );
				left = right + 1;
			} while( right != std::string::npos );
		}
		else if( childNode.IsTagName( "v" ) )
		{
			std::string text = childNode.GetText();
			size_t index = 0;
			size_t left = 0;
			size_t right = 0;

			char sep = ' ';
			do
			{
				right = text.find( sep, left );
				std::string value = text.substr( left, right - left );
				m_v.push_back( unify::Cast< int >( value ) );
				left = right + 1;
			} while( right != std::string::npos );
		}
	}

	// Expand V...
	int v_consumed = 0;
	for( int i = 0; i < m_count_attribute; i++ )
	{
		std::vector< JointWeight > v_expanded;

		int bone_count = GetVCount()[i];
		for( int b = 0; b < bone_count; b++ )
		{			
			v_expanded.push_back( 
				JointWeight{
				GetV()[v_consumed++],
				GetV()[v_consumed++]
				}
			);
		}
		m_v_expanded.push_back( v_expanded );
	}
}

int VertexWeights::GetCount() const
{
	return m_count_attribute;
}

const std::vector< Input_Shared::ptr > & VertexWeights::GetInputs() const
{
	return m_inputs;
}

const std::vector< int > VertexWeights::GetVCount() const
{
	return m_vcount;
}

const std::vector< int > VertexWeights::GetV() const
{
	return m_v;
}

const std::vector< std::vector< VertexWeights::JointWeight > > & VertexWeights::GetVExpanded() const
{
	return m_v_expanded;
}