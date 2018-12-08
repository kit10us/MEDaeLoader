#include <dae/library_controllers/Controller.h>

using namespace dae;

Controller::Controller( IDocument & document, const qxml::Element * node )
	: DocumentNode( document, node )
	, m_id( node->GetAttributeElse( "id", std::string() ) )
	, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "skin" ) )
		{
			m_skin = std::shared_ptr< Skin >( new Skin( document, childNode ) );
		}
		else if ( childNode->IsTagName( "morph" ) )
		{
			m_morph = std::shared_ptr< Morph >( new Morph( document, childNode ) );
		}
	}
}

std::string Controller::GetID() const
{
	return m_id;
}

std::string Controller::GetName() const
{
	return m_name;
}

std::shared_ptr< Skin > Controller::GetSkin() const
{
	return m_skin;
}

std::shared_ptr< Morph > Controller::GetMorph() const
{
	return m_morph;
}
