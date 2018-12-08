// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/library_visual_scenes/InstanceGeometry.h>

using namespace dae;

InstanceGeometry::InstanceGeometry( const qxml::Element * node )
: InstanceSet( node, InstanceSet::InstanceTypeGeometry )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "bind_material" ) )
		{
			m_bind_material.reset( new BindMaterial( childNode ) );
		}
	}
}

const BindMaterial * InstanceGeometry::GetBindMaterial() const
{
	return m_bind_material.get();
}
