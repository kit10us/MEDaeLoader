// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <dae/Profile_Technique.h>
#include <dae/NewParam.h>
#include <qxml/QXML.h>
#include <vector>
#include <map>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_effects->effect->profile_COMMON (0 or more)
	/// </summary>
	class ProfileCOMMON : public DocumentNode
	{
	public:
		ProfileCOMMON( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		const Profile_Technique & GetTechnique() const;
		const std::vector< std::shared_ptr< NewParam > > & GetNewParams() const;
		const NewParam * FindNewParam( std::string sid ) const;

	private:
		std::string m_id;
		std::vector< std::shared_ptr< NewParam > > m_newParams;
		std::map< std::string, std::shared_ptr< NewParam > > m_newParamsMap;
		std::shared_ptr< Profile_Technique > m_technique;
	};
}