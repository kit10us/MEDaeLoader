// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <qxml/QXML.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_visual_scenes->visual_scene->node->instance_geometry->bind_material->instance_material (1 or more)
	/// </summary>
	class InstanceMaterial
	{
	public:
		InstanceMaterial( const qxml::Element * node );

		std::string GetSID() const;
		std::string GetName() const;
		std::string GetTarget() const;
		std::string GetSymbol() const;
			
	private:
		std::string m_sid;
		std::string m_name;
		std::string m_target;
		std::string m_symbol;
	};
}