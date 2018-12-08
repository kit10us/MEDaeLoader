// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/library_materials/Material.h>

using namespace dae;

Material::Material( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_id( node->GetAttribute< std::string >( "id" ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	for( const qxml::Element * childNode = node->GetFirstChild(); childNode != 0; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "instance_effect" ) )
		{
			m_instance_effect.reset( new InstanceEffect( childNode ) );
		}
	}
}

std::string Material::GetID() const
{
	return m_id;
}

std::string Material::GetName() const
{
	return m_name;
}

const InstanceEffect & Material::GetInstanceEffect() const
{
	return *m_instance_effect;
}


