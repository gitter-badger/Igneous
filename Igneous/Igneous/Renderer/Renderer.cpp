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

	if (!Display::Init(800, 600, "Igneous"))
	{
		std::cerr << "Display failed to initialize!" << std::endl;
		glfwTerminate();
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

std::string Renderer::GetGLADVersion() {return "0.1.16a0"; }
std::string Renderer::GetGLFWVersion() { return glfwGetVersionString(); }
std::string Renderer::GetGLMVersion() { return std::to_string(GLM_VERSION_MAJOR) + "." + std::to_string(GLM_VERSION_MINOR) + "." + std::to_string(GLM_VERSION_PATCH); }
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

void Renderer::BindTexture(unsigned int unit, Texture::Texture texture)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture.id);
}

void Renderer::Render(Model* model)
{
	glBindVertexArray(model->mesh->vao);
	glDrawElements(GL_TRIANGLES, model->mesh->num_verticies, GL_UNSIGNED_INT, 0);
}

void Renderer::Terminate()
{
	Display::Terminate();
	glfwTerminate();
}