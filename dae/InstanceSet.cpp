// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/InstanceSet.h>

using namespace dae;

InstanceSet::InstanceSet( const qxml::Element * node, InstanceSet::InstanceType type )
: m_sid( node->GetAttributeElse< std::string >( "sid", "" ) )
, m_name( node->GetAttributeElse< std::string >( "name", "" ) )
, m_url( node->GetAttribute< std::string >( "url" ) )
, m_type( type )
{
}

InstanceSet::~InstanceSet()
{
}

std::string InstanceSet::GetSID() const
{
	return m_sid;
}

std::string InstanceSet::GetName() const
{
	return m_name;
}

std::string InstanceSet::GetURL() const
{
	return m_url;
}

InstanceSet::InstanceType InstanceSet::GetType() const
{
	return m_type;
}