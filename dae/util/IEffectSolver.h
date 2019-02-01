// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <me/render/Effect.h>
#include <dae/library_effects/Shading.h>
#include <unify/unify.h>

namespace dae
{
	namespace util
	{
		class IEffectSolver
		{
		public:
			virtual ~IEffectSolver() {}
			virtual me::render::Effect::ptr GetEffect( const dae::Effect * effect ) const = 0;
		};
	}
}