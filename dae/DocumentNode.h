// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/IDocument.h>
#include <dae/Extra.h>

namespace dae
{
	/// <summary>
	/// Adding "extra" support as most nodes support this sub node.
	/// </summary>
	class DocumentNode
	{
		IDocument & m_document;
		std::shared_ptr< Extra > m_extra;
	public:
		DocumentNode( IDocument & document, const qxml::Element * node );
		virtual ~DocumentNode();

		IDocument & GetDocument();
		const IDocument & GetDocument() const;
		const Extra * GetExtra() const;
	};
}
