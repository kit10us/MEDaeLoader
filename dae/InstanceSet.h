// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <qxml/QXML.h>

namespace dae
{
	// instance
	class InstanceSet
	{
	public:
		enum InstanceType
		{
			InstanceTypeNone,
			InstanceTypeCamera,
			InstanceTypeController,
			InstanceTypeGeometry,
			InstanceTypeLight,
			InstanceTypeNode
		};

		InstanceSet( const qxml::Element * node, InstanceType type );
		virtual ~InstanceSet();

		std::string GetSID() const;
		std::string GetName() const;
		std::string GetURL() const;
		InstanceType GetType() const;

	private:
		std::string m_sid;
		std::string m_name;
		std::string m_url;
		InstanceType m_type;
	};
}