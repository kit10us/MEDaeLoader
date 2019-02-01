// Copyright (c) 2002 - 2018, Kit10 Studios LLC
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
	/// DAE node: COLLADA->library_geometries->geometry->mesh->polylist (0 or more) {type = PolylistType}
	/// DAE node: COLLADA->library_geometries->geometry->mesh->triangles (0 or more) {type = TrianglesType}
	/// DAE node: COLLADA->library_geometries->geometry->mesh->lines (0 or more) {type = LinesType}
	/// </summary>
	class Polylist : public DocumentNode
	{
	public:
		typedef std::shared_ptr< Polylist > ptr;

		enum Type
		{
			PolylistType,
			TrianglesType,
			LinesType
		};

		Polylist( IDocument & document, const qxml::Element * node );

		std::string GetName() const;
		int GetCount() const;
		std::string GetMaterial() const;
		const std::vector< std::shared_ptr< Input_Shared > > & GetInput() const;
		const std::vector< int > & GetVCount() const;
		const std::vector< int > & GetP() const;
		Type GetType() const;

	private:
		std::string m_name;
		int m_count;
		std::string m_material;
		std::vector< std::shared_ptr< Input_Shared > > m_input;
		std::vector< int > m_vcount;
		std::vector< int > m_p;
		//dxi::VertexDeclaration m_vertexFormat;
		Type m_type;
	};
}