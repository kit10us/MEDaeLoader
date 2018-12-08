// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <dae/DocumentNode.h>
#include <qxml/QXML.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_images->image (1 or more)
	/// </summary>
	class Image : public DocumentNode
	{
	public:
		Image( IDocument & document, const qxml::Element * node );

		std::string GetID() const;
		std::string GetSID() const;
		std::string GetName() const;
		me::render::ITexture::ptr GetTexture() const;

	private:
		std::string m_id;
		std::string m_sid;
		std::string m_name;
		me::render::ITexture::ptr m_texture;
	};
}