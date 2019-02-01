// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once
#include <qxml/QXML.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_visual_scenes->visual_scene->node->instance_geometry->bind_material->instance_material (1 or more)
	/// </summary>
	class InstanceEffect
	{
	public:
		InstanceEffect( const qxml::Element * node );

		std::string GetSID() const;
		std::string GetName() const;
		std::string GetURL() const;
			
	private:
		std::string m_sid;
		std::string m_name;
		std::string m_url;
	};
}