// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <dae/library_controllers/Skin.h>
#include <dae/library_controllers/Morph.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_controllers->controller (1 or more)
	/// </summary>
	class Controller : public DocumentNode
	{
	public:
		Controller( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		std::string GetName() const;

		std::shared_ptr< Skin > GetSkin() const;
		std::shared_ptr< Morph > GetMorph() const;

	private:
		std::string m_id;
		std::string m_name;

		std::shared_ptr< Skin > m_skin;
		std::shared_ptr< Morph > m_morph;
	};
}
