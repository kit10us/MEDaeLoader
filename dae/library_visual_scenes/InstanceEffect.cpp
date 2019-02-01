// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_visual_scenes/InstanceEffect.h>

using namespace dae;

InstanceEffect::InstanceEffect( const qxml::Element * node )
: m_sid( node->GetAttributeElse( "sid", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
, m_url( node->GetAttribute< std::string >( "url" ) )
{
}

std::string InstanceEffect::GetSID() const
{
	return m_sid;
}

std::string InstanceEffect::GetName() const
{
	return m_name;
}

std::string InstanceEffect::GetURL() const
{
	return m_url;
}
