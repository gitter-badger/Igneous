#pragma once

#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace Renderer
{
	bool Init();
	std::string GetGLFWVersion();
	const GLubyte* GetOpenGLVersion();
	const GLubyte* GetVendor();
	const GLubyte* GetRenderer();
	const GLubyte* GetShaderLanguageVersion();
	std::string GetExtensions();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	bool ShouldClose();
	void Update();
	void ProcessInput();
	void Prepare();
	void Terminate();

	extern GLFWwindow* window;
	extern double lastSecondTime;
	extern double lastFrameTime;
	extern double currentFrameTime;
	extern double delta;
	extern int frames;
}