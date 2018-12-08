#include <dae/Profile_Technique.h>

using namespace dae;

Profile_Technique::Profile_Technique( const qxml::Element * node )
: m_id( node->GetAttributeElse( "id", std::string() ) )
, m_sid( node->GetAttribute< std::string >( "sid" ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "blinn" ) )
		{
			// TODO:
			//technique._shadingType = Blinn;
		}
		else if ( childNode->IsTagName( "constant" ) )
		{
			// TODO:
		}
		else if ( childNode->IsTagName( "lambert" ) )
		{
			m_shading.reset( new Shading( childNode ) );
		}
		else if ( childNode->IsTagName( "phong" ) )
		{
			m_shading.reset( new Shading( childNode ) );
		}
	}
}

std::string Profile_Technique::GetID() const
{
	return m_id;
}

std::string Profile_Technique::GetSID() const
{
	return m_sid;
}

const Shading & Profile_Technique::GetShading() const
{
	return *m_shading.get();
}
