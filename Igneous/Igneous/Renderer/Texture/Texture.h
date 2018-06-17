#pragma once

#include <glad\glad.h>

namespace Texture
{
	struct Texture
	{
		GLuint id;
		unsigned int type;
	};
	
	enum type
	{
		DIFFUSE,
		NUM_TYPES
	};
}