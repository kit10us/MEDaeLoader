// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <qxml/QXML.h>
#include <unify/Optional.h>
#include <string>

namespace dae
{
	/// <summary>
	/// DAE node: COLLADA->library_geometries->geometry (1 or more)
	/// </summary>
	class Input_Shared
	{
	public:
		typedef std::shared_ptr< Input_Shared > ptr;

		Input_Shared( const qxml::Element * node );

		const int GetOffset() const;
		std::string GetSemantic() const;
		std::string GetSource() const;
		const unify::Optional< int > & GetSet() const;
		size_t GetStride() const;
			
	private:
		int m_offset;
		std::string m_semantic;
		std::string m_source;
		unify::Optional< int > m_set;
		std::string m_type;
		size_t m_stride;
	};
}