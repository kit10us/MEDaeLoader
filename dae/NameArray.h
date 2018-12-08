// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <qxml/QXML.h>
#include <unify/String.h>
#include <vector>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry->mesh->source->name_array (0 or 1)
	/// DAE node: COLLADA->library_controllers->controller->skin->source->name_array (0 or 1)
	/// </summary>
	class NameArray
	{
	public:
		NameArray( const qxml::Element * node );

		int GetCount() const;
		std::string GetID() const;
		std::string GetName() const;
		std::string GetStringContents() const;
		const std::vector< std::string > & GetArrayContents() const;

	private:
		int m_count;
		std::string m_id;
		std::string m_name;
		std::string m_stringContents;
		std::vector< std::string > m_arrayContents;
	};
}