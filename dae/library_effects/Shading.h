// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/Exceptions.h>
#include <qxml/QXML.h>
#include <unify/ColorUnit.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_effects->effect->profile_COMMON->technique->[phong, lambert] (0 or more)
	/// </summary>
	class Shading // TODO: Assessing using renaming this to something generic that also supports the other types, as they are so similar.
	{
	public:
		enum Type
		{
			PhongType,
			LambertType
		};

		/// <summary>
		/// Represents a property of shading.
		class Property
		{
		public:
			enum Type
			{
				UnknownType,
				FloatType,
				ColorType,
				TextureType
			};

			Property();
			Property( const qxml::Element * node );
			Type GetType() const;
			float GetFloat() const;
			const unify::ColorUnit & GetColor() const;
			std::string GetTexture() const;
			std::string GetTexCoord() const;
				
		private:
			Type m_type;
			float m_float;
			unify::ColorUnit m_color;
			std::string m_texture;
			std::string m_texCoord;
		};

		Shading( const qxml::Element * node );

		Type GetType() const;

		const Property & GetEmission() const;
		const Property & GetAmbient() const;
		const Property & GetDiffuse() const;
		const Property & GetSpecular() const;
		float GetShininess() const;
		const Property & GetReflective() const;
		float GetReflectivity() const;
		const Property & GetTransparent() const;
		float GetTransparency() const;
		float GetIndexOfRefraction() const;

	public:
		Type m_type;
		Property m_emission;
		Property m_ambient;
		Property m_diffuse;
		Property m_specular;
		float m_shininess;
		Property m_reflective;
		float m_reflectivity;
		Property m_transparent;
		float m_transparency;
		float m_index_of_refraction;

	};
}