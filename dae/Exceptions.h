// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Exception.h>
#include <string>

namespace dae
{
	class Exception_MissingCOLLADA : public unify::Exception
	{
	public:
		Exception_MissingCOLLADA( std::string filename );
	};

	class Exception_NotSupported : public unify::Exception
	{
	public:
		Exception_NotSupported( std::string feature );
	};

	class Exception_MissingChildElement : public unify::Exception
	{
	public:
		Exception_MissingChildElement( std::string parent, std::string child );
	};
}
