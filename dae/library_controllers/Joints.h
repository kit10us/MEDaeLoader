// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <dae/Input_Unshared.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_controllers->controller->skin (1 or morph)
	/// </summary>
	class Joints : public DocumentNode
	{
	public:
		typedef std::shared_ptr< Joints > ptr;

		Joints( IDocument & document, const qxml::Element * node );

	public: // Attributes...

	public: // Children...
		const std::vector< Input_Unshared::ptr > & GetInputs() const;
	
	private:
		std::vector< Input_Unshared::ptr > m_inputs;
	};
}
