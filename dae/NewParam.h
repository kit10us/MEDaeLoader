// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once
#include <qxml/QXML.h>
#include <dae/DocumentNode.h>
#include <string>

namespace dae
{
	class NewParam : public DocumentNode
	{
	public:
		enum Type
		{
			SurfaceType,
			Sampler2DType
		};

		struct Surface
		{
			std::string type;
			std::string init_from;
			std::string format;
		};

		struct Sampler2D
		{
			std::string source;
			std::string minfilter;
			std::string magfilter;
		};

		NewParam( IDocument & document, const qxml::Element * node );

		std::string GetSID() const; // Required.
		Type GetType() const; // Meta (not in the file explicitly).
		const Surface & GetSurface() const;
		const Sampler2D & GetSampler2D() const;

	private:
		std::string m_sid;
		Type m_type;
		Surface m_surface;
		Sampler2D m_sampler2D;
	};
}