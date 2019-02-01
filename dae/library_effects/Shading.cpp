// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/library_effects/Shading.h>
#include <unify/Cast.h>

using namespace dae;

Shading::Property::Property()
: m_type( UnknownType )
, m_float( 0 )
, m_color( unify::ColorUnitWhite() )
{
}

Shading::Property::Property( const qxml::Element * node )
{
	if ( node->HasElements( "float" ) )
	{
		m_type = FloatType;
		m_float = unify::Cast< float >( node->GetElement( "float" )->GetText() );
	}
	else if ( node->HasElements( "color" ) )
	{
		m_type = ColorType;
		m_color = unify::ColorUnit( node->GetElement( "color" )->GetText(), unify::ColorUnit::RGBA );
	}
	else if ( node->HasElements( "texture" ) )
	{
		m_type = TextureType;
		m_texture = node->GetElement( "texture" )->GetAttribute< std::string >( "texture" );
		m_texCoord = node->GetElement( "texture" )->GetAttributeElse< std::string >( "texcoord", std::string() );
	}
	else
	{
		int x(0);x;
		// TODO: Solve other options.
	}
}

Shading::Property::Type Shading::Property::GetType() const
{
	return m_type;
}

float Shading::Property::GetFloat() const
{
	return m_float;
}

const unify::ColorUnit & Shading::Property::GetColor() const
{
	return m_color;
}

std::string Shading::Property::GetTexture() const
{
	return m_texture;
}

std::string Shading::Property::GetTexCoord() const
{
	return m_texCoord;
}





Shading::Shading( const qxml::Element * node )
{
	if ( node->IsTagName( "phong" ) )
	{
		m_type = PhongType;
	}
	else if ( node->IsTagName( "lambert" ) )
	{
		m_type = LambertType;
	}

	for( const qxml::Element * childNode = node->GetFirstChild(); childNode != 0; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "emission" ) )
		{
			m_emission = Property( childNode );
		}
		else if ( childNode->IsTagName( "ambient" ) )
		{
			m_ambient = Property( childNode );
		}
		else if ( childNode->IsTagName( "diffuse" ) )
		{
			m_diffuse = Property( childNode );
		}
		else if ( childNode->IsTagName( "specular" ) )
		{
			m_specular = Property( childNode );
		}
		else if ( childNode->IsTagName( "shininess" ) )
		{
			m_shininess = unify::Cast< float >( childNode->GetElement( "float" )->GetText() );
		}
		else if ( childNode->IsTagName( "reflective" ) )
		{
			m_reflective = Property( childNode );
		}
		else if ( childNode->IsTagName( "reflectivity" ) )
		{
			m_reflectivity = unify::Cast< float >( childNode->GetElement( "float" )->GetText() );
		}
		else if ( childNode->IsTagName( "transparent" ) )
		{
			m_transparent = Property( childNode );
		}
		else if ( childNode->IsTagName( "transparency" ) )
		{
			m_transparency = unify::Cast< float >( childNode->GetElement( "float" )->GetText() );
		}
		else if ( childNode->IsTagName( "index_of_refraction" ) )
		{
			m_index_of_refraction = unify::Cast< float >( childNode->GetElement( "float" )->GetText() );
		}
	}
}

dae::Shading::Type Shading::GetType() const
{
	return m_type;
}

const Shading::Property & Shading::GetEmission() const
{
	return m_emission;
}

const Shading::Property & Shading::GetAmbient() const
{
	return m_ambient;
}

const Shading::Property & Shading::GetDiffuse() const
{
	return m_diffuse;
}

const Shading::Property & Shading::GetSpecular() const
{
	return m_specular;
}

float Shading::GetShininess() const
{
	return m_shininess;
}

const Shading::Property & Shading::GetReflective() const
{
	return m_reflective;
}

float Shading::GetReflectivity() const
{
	return m_reflectivity;
}

const Shading::Property & Shading::GetTransparent() const
{
	return m_transparent;
}

float Shading::GetTransparency() const
{
	return m_transparency;
}

float Shading::GetIndexOfRefraction() const
{
	return m_index_of_refraction;
}
