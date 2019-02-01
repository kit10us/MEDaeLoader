// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_effects/Effect.h>

using namespace dae;

dae::Effect::Effect( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_id( node->GetAttribute< std::string >( "id" ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "profile_COMMON" ) )
		{
			m_profileCOMMON.reset( new ProfileCOMMON( document, childNode ) );
		}
	}
}

std::string dae::Effect::GetID() const
{
	return m_id;
}

std::string dae::Effect::GetName() const
{
	return m_name;
}

const ProfileCOMMON * dae::Effect::GetProfileCOMMON() const
{
	return m_profileCOMMON.get();
}
