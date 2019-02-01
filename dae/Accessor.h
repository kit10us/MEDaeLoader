// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry->mesh->source->technique_common->accessor ()
	/// </summary>
	class Accessor
	{
	public:
		Accessor( const qxml::Element * node );

		int GetCount() const;
		int GetOffset() const;
		std::string GetSource();
		int GetStride() const;

	private:
		int m_count;
		int m_offset;
		std::string m_source;
		int m_stride;
		//std::vector< std::string > param
	};
}
