// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once
#include <me/render/Effect.h>
#include <me/render/IRenderer.h>

namespace dae
{
	class DocumentNode;
	class Effect;

	/// <summary>
	/// </summary>
	class IDocument
	{
	public:
		virtual ~IDocument(){}
		virtual std::string GetVersion() const = 0;

		/// <summary>
		/// Returns an effect which can best represent the shading's intention.
		/// </summary>
		virtual me::render::Effect::ptr GetEffect( const Effect * effect ) const = 0;

		virtual const class LibraryNodes & GetLibraryNodes() const = 0;
		virtual const class LibraryMaterials & GetLibraryMaterials() const = 0;
		virtual const class LibraryImages & GetLibraryImages() const = 0;
		virtual const class LibraryEffects & GetLibraryEffects() const = 0;
		virtual const class LibraryGeometries & GetLibraryGeometries() const = 0;
		virtual const class LibraryControllers & GetLibraryControllers() const = 0;
		virtual const class LibraryVisualScenes & GetLibraryVisualScenes() const = 0;
		virtual const class Scene & GetScene() const = 0;
		virtual void Add( std::string name, DocumentNode * node ) = 0;
		virtual const DocumentNode * Find( std::string name ) const = 0;
		virtual me::render::IRenderer * GetRenderer() = 0;
	};
}