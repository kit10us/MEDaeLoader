// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/BindMaterial.h>

using namespace dae;

BindMaterial::BindMaterial( const qxml::Element * node )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "technique_common" ) )
		{
			m_technique_common.reset( new BindMaterial_TechniqueCommon( childNode ) );
		}
		else if ( childNode->IsTagName( "instance_material" ) )
		{
			m_instance_material.push_back( InstanceMaterial( childNode ) );
		}
	}
}

const BindMaterial_TechniqueCommon & BindMaterial::GetTechniqueCommon() const
{
	return *m_technique_common.get();
}

const std::vector< InstanceMaterial > & BindMaterial::GetInstanceMaterials() const
{
	return m_instance_material;
}
