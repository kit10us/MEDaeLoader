// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_effects->effect->profile_COMMON->extra->technique (0 or 1)
	/// </summary>
	class Technique_Core
	{
	public:
		Technique_Core( const qxml::Element * node );
		std::string GetProfile() const;

		/// <summary>
		/// Since the contents are dynamic, use GetXML to retrieve the actual XML node that represents this Technique.
		/// </summary>
		const qxml::Element & GetXML() const;

	private:
		std::string m_profile; // Required attribute.
		const qxml::Element * m_xmlNode;
	};
}