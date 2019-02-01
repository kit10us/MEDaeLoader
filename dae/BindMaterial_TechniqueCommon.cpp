// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/BindMaterial_TechniqueCommon.h>

using namespace dae;

BindMaterial_TechniqueCommon::BindMaterial_TechniqueCommon( const qxml::Element * node )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "instance_material" ) )
		{
			std::shared_ptr< InstanceMaterial > instanceMaterial( new InstanceMaterial( childNode ) );
			m_instance_material.push_back( instanceMaterial );
			m_instance_material_map[ instanceMaterial->GetSymbol() ] = instanceMaterial;
		}
	}
}

const std::vector< std::shared_ptr< InstanceMaterial > > & BindMaterial_TechniqueCommon::GetInstanceMaterial() const
{
	return m_instance_material;
}

const InstanceMaterial & BindMaterial_TechniqueCommon::GetInstanceMaterial( std::string name ) const
{
	std::map< std::string, std::shared_ptr< InstanceMaterial > >::const_iterator itr = m_instance_material_map.find( name );
	return *itr->second;
}

