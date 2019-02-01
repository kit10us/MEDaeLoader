// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <dae/Technique_Core.h>
#include <qxml/QXML.h>
#include <vector>

namespace dae
{
	// TODO: Add to all possible parent elements (currently just adding as immediately usefull).
	/// <summary>
	/// DAE node: COLLADA->*extra (*)
	/// </summary>
	class Extra
	{
	public:
		Extra( const qxml::Element * node );

		const std::vector< std::shared_ptr< Technique_Core > > & GetTechniques() const;

	private:
		std::vector< std::shared_ptr< Technique_Core > > m_techniques;
	};
}