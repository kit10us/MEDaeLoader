#include <dae/Scene.h>

using namespace dae;

Scene::Scene( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
{
	// Child elements...
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "instance_physics_scene" ) )
		{
			// TODO: m_instance_physics_scenes.push_back( InstanceSet( childNode ));
		}
		else if ( childNode->IsTagName( "instance_visual_scene" ) )
		{
			m_instance_visual_scene.reset( new InstanceVisualScene( childNode ) );
		}
		else if ( childNode->IsTagName( "instance_kinematics_scene" ) )
		{
			// TODO: m_instance_kinematics_scene = InstanceSet( childNode );
		}
	}
}

const std::vector< InstanceSet > & Scene::GetInstancePhysicsScenes() const
{
	return m_instance_physics_scenes;
}

const InstanceVisualScene * Scene::GetInstanceVisualScene() const
{
	return m_instance_visual_scene.get();
}

const unify::Optional< InstanceSet > & Scene::GetInstanceKinematicsScene() const
{
	return m_instance_kinematics_scene;
}
