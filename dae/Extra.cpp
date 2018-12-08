// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved
#include <dae/Extra.h>

using namespace dae;

Extra::Extra( const qxml::Element * node )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "technique" ) )
		{
			std::shared_ptr< Technique_Core > technique( new Technique_Core( childNode ) );
			m_techniques.push_back( technique );
		}
	}

}

const std::vector< std::shared_ptr< Technique_Core > > & Extra::GetTechniques() const
{
	return m_techniques;
}
