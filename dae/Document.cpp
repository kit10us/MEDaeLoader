// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <dae/Document.h>
#include <me/game/Game.h>

using namespace dae;

Document::Document( me::game::Game * gameInstance, unify::Path filePath, dae::util::IEffectSolver * effectSolver )
	: m_game{ gameInstance }
	, m_effectSolver( effectSolver )
{
	qxml::Document doc( filePath );
	qxml::Element * node = doc.GetRoot();

	// Validity check...
	if ( ! node->IsTagName( "COLLADA" ) )
	{
		throw Exception_MissingCOLLADA( node->GetDocument()->GetPath().ToString() );
	}

	// Attributes...
	m_version = node->GetAttribute< std::string >( "version" );

	// Child elements...
	for ( const qxml::Element * childNode = node->GetFirstChild(); childNode; childNode = childNode->GetNext() )
	{
		if ( childNode->IsTagName( "asset" ) )
		{
			// TODO:
		}
		else if ( childNode->IsTagName( "library_cameras" ) )
		{
			// TODO:
		}
		else if ( childNode->IsTagName( "library_lights" ) )
		{
			// TODO:
		}
		else if ( childNode->IsTagName( "library_nodes" ) )
		{
			m_library_nodes.reset( new LibraryNodes( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "library_images" ) )
		{
			m_library_images.reset( new LibraryImages( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "library_materials" ) )
		{
			m_library_materials.reset( new LibraryMaterials( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "library_effects" ) )
		{
			m_library_effects.reset( new LibraryEffects( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "library_geometries" ) )
		{
			m_library_geometries.reset( new LibraryGeometries( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "library_controllers" ) )
		{
			m_library_controllers.reset( new LibraryControllers( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "library_visual_scenes" ) )
		{
			m_library_visual_scenes.reset( new LibraryVisualScenes( *this, childNode ) );
		}
		else if ( childNode->IsTagName( "scene" ) )
		{
			m_scene.reset( new Scene( *this, childNode ) );
		}
	}

	// Load effects...
	unify::Path effectPath = unify::Path( filePath ).ChangeExtension( "effect" );
	if( effectPath.Exists() )
	{
		qxml::Document * effectDoc( new qxml::Document( effectPath ) );
		for( auto && effectNode : effectDoc->GetRoot()->Children( "effect" ) )
		{
			me::render::IVertexShader::ptr vs;
			me::render::IPixelShader::ptr ps;

			const qxml::Element* vsNode = effectNode.GetElement( "vertexshader" );
			const qxml::Element* psNode = effectNode.GetElement( "pixelshader" );

			if( vsNode )
			{
				std::string name = vsNode->GetAttributeElse( "name", std::string() );
				unify::Path source = vsNode->GetAttributeElse( "source", unify::Path() );

				try
				{
					if( !name.empty() && !source.Empty() )
					{
						vs = gameInstance->GetManager< me::render::IVertexShader >()->Add( name, source );
					}
					else if( !name.empty() && source.Empty() )
					{
						vs = gameInstance->GetManager< me::render::IVertexShader >()->Find( name );
					}
					else if( name.empty() && !source.Empty() )
					{
						vs = gameInstance->GetManager< me::render::IVertexShader >()->Add( source );
					}
					else
					{
						gameInstance->Debug()->ReportError( me::ErrorLevel::Failure, "DAE Loader", "VertexShader must have name and/or path!" );
					}
				}
				catch( std::exception ex )
				{
					gameInstance->Debug()->ReportError( me::ErrorLevel::Failure, "DAE Loader", "failed in loading effect file \"" + effectPath.ToString() + "\"! " + ex.what() );
				}
				catch( ... )
				{
					gameInstance->Debug()->ReportError( me::ErrorLevel::Failure, "DAE Loader", "failed in loading effect file \"" + effectPath.ToString() + "\"!" );
				}
			}

			if( psNode )
			{
				std::string name = psNode->GetAttributeElse( "name", std::string() );
				unify::Path source = psNode->GetAttributeElse( "source", unify::Path() );

				if( !name.empty() && !source.Empty() )
				{
					ps = gameInstance->GetManager< me::render::IPixelShader >()->Add( name, source );
				}
				else if( !name.empty() && source.Empty() )
				{
					ps = gameInstance->GetManager< me::render::IPixelShader >()->Find( name );
				}
				else if( name.empty() && !source.Empty() )
				{
					ps = gameInstance->GetManager< me::render::IPixelShader >()->Add( source );
				}
				else
				{
					gameInstance->Debug()->ReportError( me::ErrorLevel::Failure, "DAE Loader", "Failed in loading effect file \"" + effectPath.ToString() + "\"! PixelShader must have name and/or path!" );
				}
			}

			std::string effectName = effectNode.GetAttribute<std::string >( "name" );

			m_effects[effectName] = me::render::Effect::ptr( new me::render::Effect{ vs, ps } );
		}
	}
}

std::string Document::GetVersion() const
{
	return m_version;
}

me::render::Effect::ptr Document::GetEffect( const Effect * effect ) const
{
	if( effect == nullptr )
	{
		return m_effectSolver->GetEffect( nullptr );
	}

	// Search for the effect in our document's effect map...
	auto itr = m_effects.find( effect->GetName() );
	if( itr != m_effects.end() )
	{
		return itr->second;
	}
	else
	{
		// Return an appropriate default effect...
		return m_effectSolver->GetEffect( effect );
	}
}

const LibraryNodes & Document::GetLibraryNodes() const
{
	return *m_library_nodes;
}

const LibraryMaterials & Document::GetLibraryMaterials() const
{
	return *m_library_materials;
}

const LibraryImages & Document::GetLibraryImages() const
{
	return *m_library_images;
}

const LibraryEffects & Document::GetLibraryEffects() const
{
	return *m_library_effects;
}

const LibraryGeometries & Document::GetLibraryGeometries() const
{
	return *m_library_geometries;
}

const LibraryControllers & Document::GetLibraryControllers() const
{
	return *m_library_controllers;
}

const LibraryVisualScenes & Document::GetLibraryVisualScenes() const
{
	return *m_library_visual_scenes;
}

const Scene & Document::GetScene() const
{
	return *m_scene;
}

void Document::Add( std::string name, DocumentNode * node )
{
	std::map< const std::string, DocumentNode * >::const_iterator itr = m_nodes.find( name );
	if ( itr != m_nodes.end() )
	{
		throw unify::Exception( "DAE Document Add: Node \"" + name + "\" already exists!" );
	}
	else
	{
		m_nodes[ name ] = node;
	}
}

const DocumentNode * Document::Find( std::string name ) const
{
	std::string fixedName;
	if ( name.at( 0 ) == '#' )
	{
		fixedName = name.substr( 1 );
	}
	else
	{
		fixedName = name;
	}
	std::map< const std::string, DocumentNode * >::const_iterator itr = m_nodes.find( fixedName );
	if ( itr != m_nodes.end() )
	{
		return itr->second;
	}
	else
	{
		return 0;
	}
}

me::render::IRenderer * Document::GetRenderer()
{
	return m_game->GetOS()->GetRenderer(0);
}
