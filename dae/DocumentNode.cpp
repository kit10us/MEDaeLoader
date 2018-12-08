// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/DocumentNode.h>

using namespace dae;

DocumentNode::DocumentNode( IDocument & document, const qxml::Element * node )
: m_document( document )
{
}

DocumentNode::~DocumentNode()
{
}

IDocument & DocumentNode::GetDocument()
{
	return m_document;
}

const IDocument & DocumentNode::GetDocument() const
{
	return m_document;
}

const Extra * DocumentNode::GetExtra() const
{
	return m_extra ? m_extra.get() : 0;
}