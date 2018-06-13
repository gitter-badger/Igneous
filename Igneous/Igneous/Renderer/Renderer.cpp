#include "Renderer.h"

#include <iostream>

#include "Display\Display.h"

bool Renderer::Init()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize!" << std::endl;
		return false;
	}

	if (!Display::Init())
	{
		std::cerr << "Display failed to initialize!" << std::endl;
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD failed to initialize!" << std::endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	return true;
}

std::string Renderer::GetGLADVersion() { return "0.1.16a0"; }
std::string Renderer::GetGLFWVersion() { return glfwGetVersionString(); }
const GLubyte* Renderer::GetOpenGLVersion() { return glGetString(GL_VERSION); }
const GLubyte* Renderer::GetVendor() { return glGetString(GL_VENDOR); }
const GLubyte* Renderer::GetRenderer() { return glGetString(GL_RENDERER); }
const GLubyte* Renderer::GetShaderLanguageVersion() { return glGetString(GL_SHADING_LANGUAGE_VERSION); }

std::string Renderer::GetExtensions()
{
	std::string extensions;
	GLint n;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	if (n > 0)
	{
		GLint i;
		for (i = 0; i < n; i++)
		{
			extensions += " ";
			extensions += (char*)glGetStringi(GL_EXTENSIONS, i);
		}
	}
	return extensions;
}

void Renderer::Terminate()
{
	Display::Terminate();
	glfwTerminate();
}