// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <dae/Source.h>
#include <dae/library_controllers/Joints.h>
#include <dae/library_controllers/VertexWeights.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_controllers->controller->skin (1 or morph)
	/// </summary>
	class Skin : public DocumentNode
	{
	public:
		Skin( IDocument & document, const qxml::Element * node );

	public: // Attributes...
		std::string GetSource() const;

	public: // Children...
		const unify::Matrix & GetBindShapeMatrix() const;
		const Source * GetSource( std::string id ) const;
		const Joints & GetJoints() const;
		const VertexWeights & GetVertexWeights() const;

	private:
		std::string m_source_attribute;
		std::vector< std::shared_ptr< Source > > m_source;
		std::map< std::string, size_t, unify::string::CaseInsensitiveLessThanEqualTest > m_source_map;
		Joints::ptr m_joints;
		unify::Matrix m_bind_shape_matrix;
		VertexWeights::ptr m_vertex_weights;
	};
}
