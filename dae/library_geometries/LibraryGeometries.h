// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/Library.h>
#include <dae/library_geometries/Geometry.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries (0 or more)
	/// </summary>
	class LibraryGeometries : public Library< Geometry >
	{
	public:
		LibraryGeometries( IDocument & document, const qxml::Element * node );
	};
}