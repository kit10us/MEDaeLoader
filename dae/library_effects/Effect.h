// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once
#include <dae/ProfileCommon.h>
#include <dae/DocumentNode.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_effects->effect (1 or more)
	/// </summary>
	class Effect : public DocumentNode
	{
	public:
		Effect( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		std::string GetName() const;
		const ProfileCOMMON * GetProfileCOMMON() const;

	private:
		std::string m_id;
		std::string m_name;

		std::shared_ptr< ProfileCOMMON > m_profileCOMMON;
	};
}