// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/Library.h>
#include <dae/library_visual_scenes/VisualScene.h>
#include <qxml/QXML.h>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_visual_scenes (0 or more)
	/// </summary>
	class LibraryVisualScenes : public Library< VisualScene >
	{
	public:
		LibraryVisualScenes( IDocument & document, const qxml::Element * node );
	};
}