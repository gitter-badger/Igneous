#pragma once
#include <GLFW\glfw3.h>

namespace Display
{
	bool Init(const int width, const int height, const char* title);
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