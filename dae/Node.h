// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/InstanceSet.h>
#include <dae/DocumentNode.h>
#include <qxml/QXML.h>
#include <unify/Matrix.h>
#include <string>
#include <memory>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_visual_scene->visual_scene->node (1 or more)
	/// </summary>
	class Node : public DocumentNode
	{
	public:
		typedef std::shared_ptr< Node > ptr;

		/// <summary>
		/// For hierarchical tree structure.
		/// </summary>
		Node( IDocument & document, const Node * parent, const qxml::Element * node );
			
		/// <summary>
		/// Specifically for LibraryNodes, as there isn't a hierarchy.
		/// </summary>
		Node( IDocument & document, const qxml::Element * node );

		void Append( std::shared_ptr< Node > node );

		std::string GetID() const;
		std::string GetName() const;
		std::string GetSID() const;
		const unify::Matrix & GetMatrix() const;
		unify::Matrix GetFinalMatrix() const;
		const std::vector< std::shared_ptr< InstanceSet > > & GetInstances() const;
		const Node * GetParent() const;
		const Node * GetFirstChild() const;
		const Node * GetNext() const;

	private:
		const Node * m_parent;
		std::string m_id;
		std::string m_name;
		std::string m_sid;
		// type;
		// layer;

		unify::Matrix m_matrix; // Combination of all transformation_elements.
		std::vector< std::shared_ptr< InstanceSet > > m_instances;
		std::shared_ptr< Node > m_firstChild;
		std::shared_ptr< Node > m_next;
	};
}