#pragma once

#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Shader\Shader.h"
#include "Model\Model.h"
#include "Texture\Texture.h"

namespace Renderer
{
	bool Init();
	std::string GetGLADVersion();
	std::string GetGLFWVersion();
	std::string GetGLMVersion();
	const GLubyte* GetOpenGLVersion();
	const GLubyte* GetVendor();
	const GLubyte* GetRenderer();
	const GLubyte* GetShaderLanguageVersion();
	std::string GetExtensions();
	bool UseShader(Shader shader);
	void BindTexture(unsigned int unit, Texture::Texture texture);
	void Render(Model model);
	void Terminate();
}