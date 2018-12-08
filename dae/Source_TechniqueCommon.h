// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/Accessor.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry->mesh->source->technique_common (0 or 1)
	/// </summary>
	class Source_TechniqueCommon
	{
	public:
		Source_TechniqueCommon( const qxml::Element * node );

		const std::shared_ptr< Accessor > & GetAccessor() const;

	private:
		std::shared_ptr< Accessor > m_accessor;
	};
}