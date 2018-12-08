// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/Source_TechniqueCommon.h>

using namespace dae;

Source_TechniqueCommon::Source_TechniqueCommon( const qxml::Element * node )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "accessor" ) )
		{
			m_accessor.reset( new Accessor( childNode ) );
		}
	}
}

const std::shared_ptr< Accessor > & Source_TechniqueCommon::GetAccessor() const
{
	return m_accessor;
}
