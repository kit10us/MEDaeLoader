// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/library_controllers/Joints.h>

using namespace dae;
Joints::Joints( IDocument & document, const qxml::Element * node )
	: DocumentNode( document, node )
{
	for ( const auto & childNode : node->Children() )
	{ 
		if ( childNode.IsTagName( "input" ) )
		{
			m_inputs.push_back( Input_Unshared::ptr( new dae::Input_Unshared( &childNode ) ) );
		}
	}
}

const std::vector< Input_Unshared::ptr > & Joints::GetInputs() const
{
	return m_inputs;
}

