// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <dae/GeometrySourceFactory.h>
#include <me/exception/FailedToCreate.h>
#include <me/game/Game.h>
#include <me/render/Mesh.h>

using namespace dae;

GeometrySourceFactory::GeometrySourceFactory( me::game::Game * renderer, util::IEffectSolver * effectSolver )
	: m_game( renderer )
	, m_effectSolver( effectSolver )
{
}

unify::Result<me::render::Geometry::ptr> GeometrySourceFactory::Produce( unify::Path path, unify::Parameters parameters )
{
	dae::Document::ptr doc = std::make_shared<dae::Document>();
	auto result = doc->Create(m_game, path, m_effectSolver.get());
	if (!result)
	{
		return unify::Failure{result.Message()};
	}

	me::render::Mesh * mesh = new me::render::Mesh( "file: " + path.ToString(), m_game->GetOS()->GetRenderer(0) );
	const dae::VisualScene & visualScene = *dynamic_cast< const dae::VisualScene* >(doc->Find( doc->GetScene().GetInstanceVisualScene()->GetURL() ));
	visualScene.Build( *mesh );
	mesh->ComputeBounds();
	return me::render::Geometry::ptr( mesh );
}

unify::Result<me::render::Geometry::ptr> GeometrySourceFactory::Produce( unify::Parameters parameters )
{
	return unify::Failure{ "Failed to create geometry from paramters." };
}