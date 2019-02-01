// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once
#include <dae/Node.h>
#include <dae/BindMaterial.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_visual_scenes->visual_scene->node->instance_controller ()
	/// </summary>
	class InstanceController : public InstanceSet
	{
	public:
		InstanceController( const qxml::Element * node );

		std::string GetURL() const;

		const BindMaterial * GetBindMaterial() const;

		std::string GetSkeleton() const;

	private:
		std::string m_url;
		std::shared_ptr< BindMaterial > m_bind_material;
		std::string m_skeleton;
	};
}