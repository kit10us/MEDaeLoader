// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_controllers->controller->morph (1 or skin)
	/// </summary>
	class Morph : public DocumentNode
	{
	public:
		Morph( IDocument & document, const qxml::Element * node );
		std::string GetSource() const;

		// TOOD: Implement

	private:
		std::string m_source;
	};
}
