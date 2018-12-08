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
	/// DAE node: COLLADA->library_geometries->geometry->mesh->triangles (0 or more)
	/// </summary>
	class Triangles : public DocumentNode
	{
	public:
		Triangles( IDocument & document, const qxml::Element * node );

		std::string GetName() const;
		int GetCount() const;
		std::string GetMaterial() const;
		const std::vector< std::shared_ptr< Input_Shared > > & GetInput() const;
		const std::vector< int > & GetP() const;
		me::render::VertexDeclaration::ptr GetVertexFormat() const;

	private:
		std::string m_name;
		int m_count;
		std::string m_material;
		std::vector< std::shared_ptr< Input_Shared > > m_input;
		std::vector< int > m_p;
		me::render::VertexDeclaration::ptr m_vertexFormat;
	};
}