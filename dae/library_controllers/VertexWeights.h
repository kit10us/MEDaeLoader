// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <dae/Input_Shared.h>
#include <dae/library_controllers/VertexWeights.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_controllers->controller->skin->vertex_weights (1)
	/// </summary>
	class VertexWeights : public DocumentNode
	{
	public:
		typedef std::shared_ptr< VertexWeights > ptr;

		struct JointWeight
		{
			int joint;
			int weight;
		};

		VertexWeights( IDocument & document, const qxml::Element * node );

	public: // Attributes...
		int GetCount() const;

	public: // Children...
		const std::vector< Input_Shared::ptr > & GetInputs() const;
		const std::vector< int > GetVCount() const;
		const std::vector< int > GetV() const;
		const std::vector< std::vector< JointWeight > > & GetVExpanded() const;
	
	private:
		int m_count_attribute;
		std::vector< Input_Shared::ptr > m_inputs;
		std::vector< int > m_vcount;
		std::vector< int > m_v;
		std::vector< std::vector< JointWeight > > m_v_expanded;
	};
}
