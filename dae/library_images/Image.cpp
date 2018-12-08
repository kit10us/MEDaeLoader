// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/library_images/Image.h>

using namespace dae;

Image::Image( IDocument & document, const qxml::Element * node )
: DocumentNode( document, node )
, m_id( node->GetAttributeElse( "id", std::string() ) )
, m_sid( node->GetAttributeElse( "sid", std::string() ) )
, m_name( node->GetAttributeElse( "name", std::string() ) )
{
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "init_from" ) )
		{
			std::string filename = childNode->GetText();
			size_t p = filename.find( "file:///" );
			if ( p == 0 )
			{
				filename = filename.erase( 0, strlen( "file:///" ) );
			}
																	 			
			unify::Path source = unify::Path( childNode->GetDocument()->GetPath().DirectoryOnly(), unify::Path( filename ) ).Normalize();
			m_texture = document.GetRenderer()->ProduceT( {source} );
		}
	}
}

std::string Image::GetID() const
{
	return m_id;
}

std::string Image::GetSID() const
{
	return m_sid;
}

std::string Image::GetName() const
{
	return m_name;
}

me::render::ITexture::ptr Image::GetTexture() const
{
	return m_texture;
}