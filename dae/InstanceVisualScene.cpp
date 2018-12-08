// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/InstanceVisualScene.h>

using namespace dae;

InstanceVisualScene::InstanceVisualScene( const qxml::Element * node )
: m_sid( node->GetAttributeElse< std::string >( "sid", "" ) )
, m_name( node->GetAttributeElse< std::string >( "name", "" ) )
, m_url( node->GetAttribute< std::string >( "url" ) )
{
}

std::string InstanceVisualScene::GetSID() const
{
	return m_sid;
}

std::string InstanceVisualScene::GetName() const
{
	return m_name;
}

std::string InstanceVisualScene::GetURL() const
{
	return m_url;
}
