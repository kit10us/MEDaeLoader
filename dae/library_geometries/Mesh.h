// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/Source.h>
#include <dae/Polylist.h>
#include <dae/Vertices.h>
#include <dae/Triangles.h>
#include <dae/DocumentNode.h>
#include <dae/BindMaterial_TechniqueCommon.h>
#include <dae/library_controllers/Skin.h>
#include <me/render/Mesh.h>
#include <qxml/QXML.h>
#include <map>
#include <vector>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry->mesh (1 or more)
	/// </summary>
	class Mesh : public DocumentNode
	{
	public:
		Mesh( IDocument & document, const qxml::Element * node );

		/// <summary>
		/// Build a primitive list using a given/optional material.
		/// </summary>
		void Build( me::render::Mesh & mesh, const unify::Matrix & matrix, const BindMaterial_TechniqueCommon * technique, const dae::Skin * skin, const me::render::Skeleton * skeleton ) const;
			
	private:
		struct ContributingInput
		{
			const Input_Shared * input;
			const Source * source;
			int offset;
		};

		void GetSources( std::list< ContributingInput > & sources, const Input_Shared * input, int offset, size_t & pStride ) const;

		std::vector< Source::ptr > m_source;
		std::map< std::string, size_t > m_source_map;

		std::shared_ptr< Vertices > m_vertices; // 1
		std::vector< Polylist::ptr > m_polylist;
	};
}