// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/library_visual_scenes/InstanceMaterial.h>
#include <qxml/QXML.h>
#include <map>
#include <string>

namespace dae
{
	/// <summary>
	/// </summary>
	class BindMaterial_TechniqueCommon
	{
	public:
		BindMaterial_TechniqueCommon( const qxml::Element * node );
		const std::vector< std::shared_ptr< InstanceMaterial > > & GetInstanceMaterial() const;
		const InstanceMaterial & GetInstanceMaterial( std::string name ) const;

	private:
		std::vector< std::shared_ptr< InstanceMaterial > > m_instance_material;
		std::map< std::string, std::shared_ptr< InstanceMaterial > > m_instance_material_map;
	};
}
