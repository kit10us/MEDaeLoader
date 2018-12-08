// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/library_visual_scenes/InstanceMaterial.h>

using namespace dae;

InstanceMaterial::InstanceMaterial( const qxml::Element * node )
: m_sid( node->GetAttributeElse( "sid", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
, m_target( node->GetAttribute< std::string >( "target" ) )
, m_symbol( node->GetAttribute< std::string >( "symbol" ) )
{
}

std::string InstanceMaterial::GetSID() const
{
	return m_sid;
}

std::string InstanceMaterial::GetName() const
{
	return m_name;
}

std::string InstanceMaterial::GetTarget() const
{
	return m_target;
}

std::string InstanceMaterial::GetSymbol() const
{
	return m_symbol;
}
