// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_visual_scenes/VisualScene.h>
#include <dae/library_visual_scenes/InstanceGeometry.h>
#include <dae/library_visual_scenes/InstanceController.h>
#include <unify/String.h>

using namespace dae;

Node::Node( IDocument & document, const dae::Node * parent, const qxml::Element * node )
: DocumentNode( document, node )
, m_parent( parent )
, m_id( node->GetAttributeElse( "id", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
, m_sid( node->GetAttributeElse( "sid", std::string() ) )
, m_matrix( unify::MatrixIdentity() )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "matrix" ) )
		{
			std::vector< float > components;
			components = unify::string::SplitOnWhitespace< float >( childNode->GetText() );
			unify::Matrix transform;
			transform.Set( 0, 0, components.at( 0 ) );
			transform.Set( 1, 0, components.at( 1 ) );
			transform.Set( 2, 0, components.at( 2 ) );
			transform.Set( 3, 0, components.at( 3 ) );

			transform.Set( 0, 1, components.at( 4 ) );
			transform.Set( 1, 1, components.at( 5 ) );
			transform.Set( 2, 1, components.at( 6 ) );
			transform.Set( 3, 1, components.at( 7 ) );

			transform.Set( 0, 2, components.at( 8 ) );
			transform.Set( 1, 2, components.at( 9 ) );
			transform.Set( 2, 2, components.at( 10 ) );
			transform.Set( 3, 2, components.at( 11 ) );

			transform.Set( 0, 3, components.at( 12 ) );
			transform.Set( 1, 3, components.at( 13 ) );
			transform.Set( 2, 3, components.at( 14 ) );
			transform.Set( 3, 3, components.at( 15 ) );
			m_matrix *= transform;
		}
		else if ( childNode->IsTagName( "translate" ) )
		{
			std::vector< float > components;
			components = unify::string::SplitOnWhitespace< float >( childNode->GetText() );
			unify::V3< float > translation( components[ 0 ], components[ 1 ], components[ 2 ] );
			m_matrix.Translate( translation );
		}
		else if ( childNode->IsTagName( "rotate" ) )
		{
			std::vector< float > components = unify::string::SplitOnWhitespace< float >( childNode->GetText() );
			unify::V3< float > axis( components[ 0 ], components[ 1 ], components[ 2 ] );
			unify::Angle angle( unify::AngleInDegrees( components[ 3 ] ) );
			m_matrix *= unify::MatrixRotationAboutAxis( axis, angle );
		}
		else if ( childNode->IsTagName( "instance_camera" ) )
		{
			// TODO: 
		}
		else if ( childNode->IsTagName( "instance_controller" ) )
		{
			m_instances.push_back( std::shared_ptr< InstanceController >( new InstanceController( childNode ) ) );
		}
		else if ( childNode->IsTagName( "instance_geometry" ) )
		{
			m_instances.push_back( std::shared_ptr< InstanceGeometry >( new InstanceGeometry( childNode ) ) );
		}
		else if ( childNode->IsTagName( "instance_light" ) )
		{
			// TODO:
		}
		else if ( childNode->IsTagName( "instance_node" ) )
		{
			m_instances.push_back( std::shared_ptr< InstanceSet >( new InstanceSet( childNode, InstanceSet::InstanceTypeNode ) ) );
		}
		else if ( childNode->IsTagName( "node" ) )
		{
			if ( ! m_firstChild )
			{
				m_firstChild = std::shared_ptr< Node >( new Node( document, this, childNode ) );
			}
			else
			{
				m_firstChild->Append( std::shared_ptr< Node >( new Node( document, this, childNode ) ) );
			}
		}
	}
}

Node::Node( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_parent( 0 )
, m_id( node->GetAttributeElse( "id", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
, m_sid( node->GetAttributeElse( "sid", std::string() ) )
, m_matrix( unify::MatrixIdentity() )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "matrix" ) )
		{
			std::vector< float > components;
			components = unify::string::SplitOnWhitespace< float >( childNode->GetText() );
			unify::Matrix transform;
			transform.Set( 0, 0, components.at( 0 ) );
			transform.Set( 1, 0, components.at( 1 ) );
			transform.Set( 2, 0, components.at( 2 ) );
			transform.Set( 3, 0, components.at( 3 ) );

			transform.Set( 0, 1, components.at( 4 ) );
			transform.Set( 1, 1, components.at( 5 ) );
			transform.Set( 2, 1, components.at( 6 ) );
			transform.Set( 3, 1, components.at( 7 ) );

			transform.Set( 0, 2, components.at( 8 ) );
			transform.Set( 1, 2, components.at( 9 ) );
			transform.Set( 2, 2, components.at( 10 ) );
			transform.Set( 3, 2, components.at( 11 ) );

			transform.Set( 0, 3, components.at( 12 ) );
			transform.Set( 1, 3, components.at( 13 ) );
			transform.Set( 2, 3, components.at( 14 ) );
			transform.Set( 3, 3, components.at( 15 ) );
			m_matrix *= transform;
		}
		else if ( childNode->IsTagName( "translate" ) )
		{
			std::vector< float > components;
			components = unify::string::SplitOnWhitespace< float >( childNode->GetText() );
			unify::V3< float > translation( components[ 0 ], components[ 1 ], components[ 2 ] );
			m_matrix.Translate( translation );
		}
		else if ( childNode->IsTagName( "rotate" ) )
		{
			std::vector< float > components = unify::string::SplitOnWhitespace< float >( childNode->GetText() );
			unify::V3< float > axis( components[ 0 ], components[ 1 ], components[ 2 ] );
			unify::Angle angle( unify::AngleInDegrees( components[ 3 ] ) );
			m_matrix *= unify::MatrixRotationAboutAxis( axis, angle );
		}
		else if ( childNode->IsTagName( "instance_camera" ) )
		{
			// TODO: 
		}
		else if ( childNode->IsTagName( "instance_controller" ) )
		{
			m_instances.push_back( std::shared_ptr< InstanceController >( new InstanceController( childNode ) ) );
		}
		else if ( childNode->IsTagName( "instance_geometry" ) )
		{
			m_instances.push_back( std::shared_ptr< InstanceGeometry >( new InstanceGeometry( childNode ) ) );
		}
		else if ( childNode->IsTagName( "instance_light" ) )
		{
			// TODO:
		}
		else if ( childNode->IsTagName( "instance_node" ) )
		{
			m_instances.push_back( std::shared_ptr< InstanceSet >( new InstanceSet( childNode, InstanceSet::InstanceTypeNode ) ) );
		}
		else if ( childNode->IsTagName( "node" ) )
		{
			if ( ! m_firstChild )
			{
				m_firstChild = std::shared_ptr< Node >( new Node( document, this, childNode ) );
			}
			else
			{
				m_firstChild->Append( std::shared_ptr< Node >( new Node( document, this, childNode ) ) );
			}
		}
	}
}

void Node::Append( std::shared_ptr< Node > node )
{
	if ( ! m_next )
	{
		m_next = node;
	}
	else
	{
		m_next->Append( node );
	}
}

std::string Node::GetID() const
{
	return m_id;
}

std::string Node::GetName() const
{
	return m_name;
}

std::string Node::GetSID() const
{
	return m_sid;
}

const unify::Matrix & Node::GetMatrix() const
{
	return m_matrix;
}

unify::Matrix Node::GetFinalMatrix() const
{
	return m_parent ? ( m_parent->GetFinalMatrix() * GetMatrix() ) : GetMatrix();
}

const std::vector< std::shared_ptr< InstanceSet > > & Node::GetInstances() const
{
	return m_instances;
}

const Node * Node::GetParent() const
{
	return m_parent;
}

const Node * Node::GetFirstChild() const
{
	return m_firstChild.get();
}

const Node * Node::GetNext() const
{
	return m_next.get();
}
