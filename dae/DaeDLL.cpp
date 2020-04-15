// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/GeometrySourceFactory.h>
#include <me/factory/GeometryFactory.h>
#include <memory.h>
#include <me/render/IRenderer.h>
#include <me/game/IGame.h>
#include <me/debug/ErrorLevel.h>

void Deleter( dae::GeometrySourceFactory * factory )
{
	delete factory;
}

extern "C" __declspec(dllexport) bool MELoader( me::game::IGame * gameInstance, const qxml::Element * element );

__declspec(dllexport) bool MELoader( me::game::IGame * gameBase, const qxml::Element * element )
{
	using namespace me;
	using namespace render;

	auto gameInstance = dynamic_cast<game::Game *>( gameBase );

	// Setup DAE factory.
	class MyEffectSolver : public dae::util::IEffectSolver
	{
		game::Game * m_game;
		Effect::ptr m_default_color;
		Effect::ptr m_default_texture;
	public:

		MyEffectSolver( Effect::ptr default_color, Effect::ptr default_texture )
			: m_default_color{ default_color }
			, m_default_texture{ default_texture }
		{
		}

		Effect::ptr GetEffect( const dae::Effect * effect ) const
		{
			// Assume default color texture if effect is null...
			if( effect == nullptr )
			{
				return m_default_color;
			}

			auto & shading = effect->GetProfileCOMMON()->GetTechnique().GetShading();
			if( shading.GetDiffuse().GetType() == dae::Shading::Property::ColorType )
			{
				return m_default_color;
			}
			else
			{
				return m_default_texture;
			}
		}
	};


	Effect::ptr color;
	{
		IPixelShader::ptr ps;
		{
			const auto node = element->FindFirstElement( "colorps" );
			std::string name = node->GetAttributeElse< std::string >( "name", std::string() );
			unify::Path path( node->GetAttributeElse< std::string >( "source", std::string() ) );

			if( !name.empty() && path.Empty() )
			{
				ps = gameInstance->GetManager< IPixelShader >()->Find( name );
			}
			else if( name.empty() && ! path.Empty() )
			{
				ps = gameInstance->GetManager< IPixelShader >()->Add( path.ToString(), path );
			}
			else if( !name.empty() && !path.Empty() )
			{
				ps = gameInstance->GetManager< IPixelShader >()->Add( name, path );
			}
		}

		IVertexShader::ptr vs;
		{
			const auto node = element->FindFirstElement( "colorvs" );
			std::string name = node->GetAttributeElse< std::string >( "name", std::string() );
			unify::Path path( node->GetAttributeElse< std::string >( "source", std::string() ) );

			if( !name.empty() && path.Empty() )
			{
				vs = gameInstance->GetManager< IVertexShader >()->Find( name );
			}
			else if( name.empty() && !path.Empty() )
			{
				vs = gameInstance->GetManager< IVertexShader >()->Add( path.ToString(), path );
			}
			else if( !name.empty() && !path.Empty() )
			{
				vs = gameInstance->GetManager< IVertexShader >()->Add( name, path );
			}
		}
		color.reset( new Effect( vs, ps ) );
	}
	
	Effect::ptr texture;
	{
		IPixelShader::ptr ps;
		{
			std::string shaderElementName( "textureps" );
			const auto node = element->FindFirstElement( shaderElementName );
			if ( ! node )
			{
				gameInstance->Debug()->ReportError( me::debug::ErrorLevel::Failure, "Cannot find \"" + shaderElementName + "\" node in \"" + element->GetDocument()->GetPath().ToString() + "\".", false, false );
			}

			std::string name = node->GetAttributeElse< std::string >( "name", std::string() );
			unify::Path path( node->GetAttributeElse< std::string >( "source", std::string() ) );

			if( !name.empty() && path.Empty() )
			{
				ps = gameInstance->GetManager< IPixelShader >()->Find( name );
			}
			else if( name.empty() && !path.Empty() )
			{
				ps = gameInstance->GetManager< IPixelShader >()->Add( path.ToString(), path );
			}
			else if( !name.empty() && !path.Empty() )
			{
				ps = gameInstance->GetManager< IPixelShader >()->Add( name, path );
			}
		}

		IVertexShader::ptr vs;
		{
			const auto node = element->FindFirstElement( "texturevs" );
			if( !node )
			{
				gameInstance->Debug()->ReportError( me::debug::ErrorLevel::Failure, "Cannot find \"texturevs\" node in \"" + element->GetDocument()->GetPath().ToString() + "\".", true, true );
			}

			std::string name = node->GetAttributeElse< std::string >( "name", std::string() );
			unify::Path path( node->GetAttributeElse< std::string >( "source", std::string() ) );

			if( !name.empty() && path.Empty() )
			{
				vs = gameInstance->GetManager< IVertexShader >()->Find( name );
			}
			else if( name.empty() && !path.Empty() )
			{
				vs = gameInstance->GetManager< IVertexShader >()->Add( path.ToString(), path );
			}
			else if( !name.empty() && !path.Empty() )
			{
				vs = gameInstance->GetManager< IVertexShader >()->Add( name, path );
			}
		}
		texture.reset( new Effect( vs, ps ) );
	}

	auto effectSolver = new MyEffectSolver( color, texture );

	dae::GeometrySourceFactory * daeFactory = new dae::GeometrySourceFactory( gameInstance, effectSolver );
	gameInstance->GetManager< Geometry >()->AddFactory( ".dae", GeometryFactory::ptr( daeFactory ) );

	return true;
}

