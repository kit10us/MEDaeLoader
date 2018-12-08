// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <me/render/Geometry.h>
#include <rm/ResourceManagerSimple.h>
#include <dae/Document.h>

namespace dae
{
	class GeometrySourceFactory : public rm::ISourceFactory< me::render::Geometry >
	{
	public:
		GeometrySourceFactory( me::game::Game * renderer, util::IEffectSolver * effectSolver );

		me::render::Geometry::ptr Produce( unify::Path path, void * data ) override;

	private:
	me::game::Game *m_game;
		std::shared_ptr< util::IEffectSolver > m_effectSolver;
	};
}