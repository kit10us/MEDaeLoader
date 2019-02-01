// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/Library.h>
#include <dae/library_controllers/Controller.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_controllers (0 or more)
	/// </summary>
	class LibraryControllers : public Library< Controller >
	{
	public:
		LibraryControllers( IDocument & document, const qxml::Element * node );
	};
}