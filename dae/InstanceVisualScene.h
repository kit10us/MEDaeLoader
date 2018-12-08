// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once
#include <qxml/QXML.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->scene->instance_visual_scene (0 or 1)
	/// </summary>
	class InstanceVisualScene
	{
	public:
		InstanceVisualScene( const qxml::Element * node );

		std::string GetSID() const;
		std::string GetName() const;
		std::string GetURL() const;

	private:
		std::string m_sid;
		std::string m_name;
		std::string m_url;
	};
}