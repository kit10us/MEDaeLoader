// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once
#include <dae/BindMaterial_TechniqueCommon.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_visual_scenes->visual_scene->node->instance_geometry->bind_material (0 or 1)
	/// </summary>
	class BindMaterial
	{
	public:
		BindMaterial( const qxml::Element * node );
		const BindMaterial_TechniqueCommon & GetTechniqueCommon() const;
		const std::vector< InstanceMaterial > & GetInstanceMaterials() const;

	private:
		std::shared_ptr< BindMaterial_TechniqueCommon > m_technique_common; // (1)
		std::vector< InstanceMaterial > m_instance_material; // (1 or more)

	};
}
