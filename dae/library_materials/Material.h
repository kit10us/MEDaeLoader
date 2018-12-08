// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <dae/library_visual_scenes/InstanceEffect.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_materials->material (1 or more)
	/// </summary>
	class Material : public DocumentNode
	{
	public:
		Material( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		std::string GetName() const;
		const InstanceEffect & GetInstanceEffect() const;

	private:
		std::string m_id;
		std::string m_name;
		std::shared_ptr< InstanceEffect > m_instance_effect; // (1)
	};
}