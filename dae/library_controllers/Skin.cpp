// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/library_controllers/Skin.h>
#include <dae/Source.h>

using namespace dae;

Skin::Skin( IDocument & document, const qxml::Element * node )
	: DocumentNode( document, node )
	, m_source_attribute( node->GetAttributeElse( "source", std::string() ) )
{
	for ( const auto & childNode : node->Children() )
	{ 
		if ( childNode.IsTagName( "bind_shape_matrix" ) )
		{
			m_bind_shape_matrix = unify::Matrix( childNode.GetText() );
		}
		else if( childNode.IsTagName( "source" ) )
		{
			std::shared_ptr< Source > source( new Source( document, &childNode ) );
			m_source.push_back( source );
			m_source_map[source->GetID()] = m_source.size() - 1;
		}
		else if( childNode.IsTagName( "joints" ) )
		{
			m_joints = Joints::ptr( new Joints( document, &childNode ) );
		}
		else if( childNode.IsTagName( "vertex_weights" ) )
		{
			m_vertex_weights = VertexWeights::ptr( new dae::VertexWeights( document, &childNode ) );
		}
	}
}

std::string Skin::GetSource() const
{
	return m_source_attribute;
}

const Source * Skin::GetSource( std::string id ) const
{
	auto itr = m_source_map.find( id );
	if( itr == m_source_map.end() )
	{
		return nullptr;
	}
	
	return m_source[itr->second].get();
}

const Joints & Skin::GetJoints() const
{
	return *m_joints;
}

const unify::Matrix & Skin::GetBindShapeMatrix() const
{
	return m_bind_shape_matrix;
}

const VertexWeights & Skin::GetVertexWeights() const
{
	return *m_vertex_weights;
}


