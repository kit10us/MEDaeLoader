#include <dae/ProfileCommon.h>

using namespace dae;

ProfileCOMMON::ProfileCOMMON( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_id( node->GetAttributeElse( "id", std::string() ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "newparam" ) )
		{
			std::shared_ptr< NewParam > newParam( new NewParam( document, childNode ) );
			m_newParams.push_back( newParam );
			m_newParamsMap[ childNode->GetAttribute< std::string >( "sid" ) ] = newParam;
		}
		else if ( childNode->IsTagName( "technique" ) )
		{
			m_technique.reset( new Profile_Technique( childNode ) );
		}
	}
}

std::string ProfileCOMMON::GetID() const
{
	return m_id;
}

const Profile_Technique & ProfileCOMMON::GetTechnique() const
{
	return *m_technique;
}

const std::vector< std::shared_ptr< NewParam > > & ProfileCOMMON::GetNewParams() const
{
	return m_newParams;
}

const NewParam * ProfileCOMMON::FindNewParam( std::string sid ) const
{
	std::map< std::string, std::shared_ptr< NewParam > >::const_iterator itr = m_newParamsMap.find( sid );
	if ( itr == m_newParamsMap.end() )
	{
		return 0;
	}
	return itr->second.get();
}
