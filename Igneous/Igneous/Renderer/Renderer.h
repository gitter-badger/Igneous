#pragma once

#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace Renderer
{
	bool Init();
	std::string GetGLADVersion();
	std::string GetGLFWVersion();
	const GLubyte* GetOpenGLVersion();
	const GLubyte* GetVendor();
	const GLubyte* GetRenderer();
	const GLubyte* GetShaderLanguageVersion();
	std::string GetExtensions();
	void Terminate();
}