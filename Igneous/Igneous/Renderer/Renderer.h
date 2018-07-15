#pragma once

#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <bgfx/bgfx.h>

#include "Shader\Shader.h"
#include "Model\Model.h"
#include "Texture\Texture.h"

namespace Renderer
{
	bool Init();
	std::string GetGLFWVersion();
	std::string GetGLMVersion();
	std::string GetbgfxVersion();
	std::string GetRenderer();
	std::string GetSupportedRenderers();
	std::string GetVendor(uint16_t vendorId);
	std::string GetGpuInfo();
	void BindTexture(unsigned int unit, Texture::Texture texture);
	void Render(Model* model);
	void Update();
	void Terminate();

	extern int width;
	extern int height;
	const extern bgfx::Caps* caps;
}