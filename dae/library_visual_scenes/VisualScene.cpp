// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_visual_scenes/VisualScene.h>
#include <dae/library_geometries/LibraryGeometries.h>
#include <dae/library_controllers/LibraryControllers.h>
#include <dae/library_nodes/LibraryNodes.h>
#include <dae/library_visual_scenes/InstanceGeometry.h>
#include <dae/library_visual_scenes/InstanceController.h>
#include <dae/library_materials/Material.h>

using namespace dae;

VisualScene::VisualScene( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_id( node->GetAttributeElse( "id", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "node" ) )
		{
			if ( ! m_firstNode )
			{
				m_firstNode = std::shared_ptr< Node >( new Node( document, 0, childNode ) );
			}
			else
			{
				m_firstNode->Append( std::shared_ptr< Node >( new Node( document, 0, childNode ) ) );
			}
		}
	}
}

std::string VisualScene::GetID() const
{
	return m_id;
}

std::string VisualScene::GetName() const
{
	return m_name;
}

const Node * VisualScene::GetFirstNode() const
{
	return m_firstNode.get();
}



const Node* FindNode( const Node* node, std::string id )
{
	if( !node ) return nullptr;

	if( unify::string::StringIs( node->GetID(), id ) )
	{
		return node;
	}

	// Search children...
	{
		auto result = FindNode( node->GetFirstChild(), id );
		if( result )
		{
			return result;
		}
	}

	// Search siblings...
	return FindNode( node->GetNext(), id );
}

const Node * VisualScene::FindNode( std::string id ) const
{
	// Remove prepended "#" from name if it exists...
	if( id.at( 0 ) == '#' )
	{
		id = id.substr( 1 );
	}

	const Node* node = ::FindNode( m_firstNode.get(), id );
	return node;
}

void VisualScene::Build( me::render::Mesh & mesh ) const
{
	Build( mesh, unify::MatrixIdentity(), GetFirstNode() );
}

void BuildSkeleton( me::render::Skeleton & skeleton, const dae::Node * node )
{
	if( node == nullptr )
	{
		return;
	}

	skeleton.AddJoint( node->GetName(), node->GetMatrix(), node->GetParent() ? node->GetParent()->GetName() : std::string() );
	BuildSkeleton( skeleton, node->GetFirstChild() );
	BuildSkeleton( skeleton, node->GetNext() );
}

void VisualScene::Build( me::render::Mesh & mesh, const unify::Matrix & matrix, const dae::Node * node ) const
{
	// Iterate this nodes instances...
	for ( const auto instance : node->GetInstances() )
	{
		switch( instance->GetType() )
		{
		case InstanceSet::InstanceTypeGeometry:
			{
				const InstanceGeometry * instanceGeometry = dynamic_cast< const InstanceGeometry * >( instance.get() );
				const dae::Geometry & geo = *GetDocument().GetLibraryGeometries().Find( instance->GetURL() );
				const BindMaterial * bindMaterial = instanceGeometry->GetBindMaterial();
				const BindMaterial_TechniqueCommon * techniqueCommon = ( bindMaterial ) ? (&bindMaterial->GetTechniqueCommon()) : nullptr;
				geo.Build( mesh, matrix * node->GetFinalMatrix(), techniqueCommon, nullptr, nullptr );
			}
			break;
		case InstanceSet::InstanceTypeController:
			{
				const InstanceController * instanceController = dynamic_cast< const InstanceController * >(instance.get());
				const dae::Controller & controller = *GetDocument().GetLibraryControllers().Find( instanceController->GetURL() );
				const dae::Geometry & geo = *GetDocument().GetLibraryGeometries().Find( controller.GetSkin()->GetSource() );
				const dae::Node * skeleton = FindNode( instanceController->GetSkeleton() );
				BuildSkeleton( *mesh.GetSkeleton(), skeleton );
				const dae::Skin * skin = controller.GetSkin().get();
				geo.Build( mesh, matrix * node->GetFinalMatrix(), &instanceController->GetBindMaterial()->GetTechniqueCommon(), skin, mesh.GetSkeleton() );
			}
			break;
		case InstanceSet::InstanceTypeNode:
			{
				const dae::Node * referencedNode = GetDocument().GetLibraryNodes().Find( instance->GetURL() );
				Build( mesh, matrix * node->GetFinalMatrix(), referencedNode );
			}
			break;
		}
	}

	// Iterate children nodes...
	if ( node->GetFirstChild() )
	{
		Build( mesh, matrix, node->GetFirstChild() );
	}

	// Iterate next sibling...
	if ( node->GetNext() )
	{
		Build( mesh, matrix, node->GetNext() );
	}
}

