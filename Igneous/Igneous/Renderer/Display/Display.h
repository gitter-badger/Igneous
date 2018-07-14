#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <bgfx/platform.h>

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX
#elif BX_PLATFORM_OSX
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif //

#include <GLFW/glfw3native.h>

namespace Display
{
	bool Init(const int width, const int height, const char* title);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	int ShouldClose();
	void Update();
	void ProcessInput();
	void Prepare();
	void Terminate();
	static void * glfwNativeWindowHandle();
	static void glfwSetWindow();

	extern GLFWwindow* window;
	extern double lastSecondTime;
	extern double lastFrameTime;
	extern double currentFrameTime;
	extern double delta;
	extern int frames;
	extern int fps;
}