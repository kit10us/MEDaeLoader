// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/library_nodes/LibraryNodes.h>
#include <dae/library_images/LibraryImages.h>
#include <dae/library_materials/LibraryMaterials.h>
#include <dae/library_effects/LibraryEffects.h>
#include <dae/library_geometries/LibraryGeometries.h>
#include <dae/library_controllers/LibraryControllers.h>
#include <dae/library_visual_scenes/LibraryVisualScenes.h>
#include <dae/Scene.h>
#include <dae/util/IEffectSolver.h>
#include <dae/Exceptions.h>
#include <me/render/IRenderer.h>
#include <me/render/Effect.h>
#include <qxml/QXML.h>
#include <unify/Path.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA
	/// The root element for a COLLADA DAE. To find the area of code where work is needed, identify the DAE node, then drill down from here.
	/// See the "DAE node" appended to every DAE class.
	/// </summary>
	class Document : public IDocument
	{
	public:
		Document( me::game::Game * gameInstance, unify::Path filePath, util::IEffectSolver * effectSolver );

		/// <summary>
		/// DAE attribute: version
		/// </summary>
		std::string GetVersion() const;

		me::render::Effect::ptr GetEffect( const Effect * effect ) const;

		const LibraryNodes & GetLibraryNodes() const;
		const LibraryMaterials & GetLibraryMaterials() const;
		const LibraryImages & GetLibraryImages() const;
		const LibraryEffects & GetLibraryEffects() const;
		const LibraryGeometries & GetLibraryGeometries() const;
		const LibraryControllers & GetLibraryControllers() const;
		const LibraryVisualScenes & GetLibraryVisualScenes() const;
		const Scene & GetScene() const;

		void Add( std::string name, DocumentNode * node );
		const DocumentNode * Find( std::string name ) const;

		me::render::IRenderer * GetRenderer() override;

	private:
	me::game::Game *m_game;
		std::string m_version;
		std::shared_ptr< LibraryNodes > m_library_nodes;
		std::shared_ptr< LibraryMaterials > m_library_materials;
		std::shared_ptr< LibraryEffects > m_library_effects;
		std::shared_ptr< LibraryGeometries > m_library_geometries;
		std::shared_ptr< LibraryControllers > m_library_controllers;
		std::shared_ptr< LibraryVisualScenes > m_library_visual_scenes;
		std::shared_ptr< LibraryImages > m_library_images;
		std::shared_ptr< Scene > m_scene;
		util::IEffectSolver * m_effectSolver;
		std::map< const std::string, DocumentNode * > m_nodes;
		std::map< std::string, me::render::Effect::ptr > m_effects;
		me::render::Effect::ptr m_defaultEffect;
	};
}