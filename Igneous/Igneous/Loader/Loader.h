#pragma once

#include <string>
#include <iostream>

#include "../Renderer/Model/Model.h"
#include "../Renderer/Texture/Texture.h"

namespace Loader
{
	std::string GetAssimpVersion();
	Model* LoadModel(const std::string& filename);
	Texture::Texture* LoadTexture(const char* filename, unsigned int type, bool hasTransparency);
}