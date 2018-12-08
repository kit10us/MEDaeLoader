// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/Accessor.h>

using namespace dae;

Accessor::Accessor( const qxml::Element * node )
: m_count( node->GetAttribute< int >( "count" ) )
, m_offset( node->GetAttributeElse< int >( "offset", 0 ) )
, m_source( node->GetAttribute< std::string >( "source" ) )
, m_stride( node->GetAttributeElse< int >( "stride", 1 ) )
{
}

int Accessor::GetCount() const
{
	return m_count;
}

int Accessor::GetOffset() const
{
	return m_offset;
}

std::string Accessor::GetSource()
{
	return m_source;
}

int Accessor::GetStride() const
{
	return m_stride;
}
