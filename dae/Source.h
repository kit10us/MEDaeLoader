// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/FloatArray.h>
#include <dae/NameArray.h>
#include <dae/Source_TechniqueCommon.h>
#include <dae/Exceptions.h>
#include <dae/DocumentNode.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry->mesh->source (1 or more)
	/// DAE node: COLLADA->library_controllers->controller->skin->source (1 or more)
	/// </summary>
	class Source : public DocumentNode
	{
	public:
		typedef std::shared_ptr< Source > ptr;

		Source( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		std::string GetName() const;
		const FloatArray & GetFloatArray() const;
		const NameArray & GetNameArray() const;
		const Source_TechniqueCommon & GetTechniqueCommon() const;

	private:
		std::string m_id;
		std::string m_name;
		std::shared_ptr< FloatArray > m_float_array;
		std::shared_ptr< NameArray > m_name_array;
		std::shared_ptr< Source_TechniqueCommon > m_technique_common;
	};
}