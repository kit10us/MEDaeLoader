// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_visual_scenes/InstanceController.h>

using namespace dae;

InstanceController::InstanceController( const qxml::Element * node )
	: InstanceSet( node, InstanceSet::InstanceTypeController )
	, m_url( node->GetAttribute< std::string >( "url" ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "bind_material" ) )
		{
			m_bind_material.reset( new BindMaterial( childNode ) );
		}
		else if ( childNode->IsTagName( "skeleton" ) )
		{
			m_skeleton = childNode->GetText();
		}
	}
}

std::string InstanceController::GetURL() const
{
	return m_url;
}

const BindMaterial * InstanceController::GetBindMaterial() const
{
	return m_bind_material.get();
}

std::string InstanceController::GetSkeleton() const
{
	return m_skeleton;
}
