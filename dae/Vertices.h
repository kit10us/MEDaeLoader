// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/Input_Shared.h>
#include <dae/DocumentNode.h>
#include <qxml/QXML.h>
#include <vector>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry->{mesh, convex_mesh, brep}->vertices (1 or more)
	/// </summary>
	class Vertices : public DocumentNode
	{
	public:
		Vertices( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		std::string GetName() const;
		const std::vector< std::shared_ptr< Input_Shared > > & GetInput() const;

	private:
		std::string m_id;
		std::string m_name;
		std::vector< std::shared_ptr< Input_Shared > > m_input;
	};
}