#include "Display.h"

#include <iostream>

#include <stb\image.h>

bool Display::Init(const int width, const int height, const char* title)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to init GLFW!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, title, NULL, NULL);//Create the window 4th param glfwGetPrimaryMonitor() for fullscreen

	GLFWimage images[3];
	images[0].pixels = stbi_load("Resources/icons/icon16.png", &images[0].width, &images[0].height, 0, 4);
	images[1].pixels = stbi_load("Resources/icons/icon32.png", &images[1].width, &images[1].height, 0, 4);
	images[2].pixels = stbi_load("Resources/icons/icon48.png", &images[2].width, &images[2].height, 0, 4);
	glfwSetWindowIcon(window, 3, images);
	stbi_image_free(images[0].pixels);
	stbi_image_free(images[1].pixels);
	stbi_image_free(images[2].pixels);

	//Set callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindow();

	//Setup delta time and fps counter
	currentFrameTime = glfwGetTime();
	lastSecondTime = currentFrameTime;
	lastFrameTime = currentFrameTime;
	frames = 0;
	return true;
}

int Display::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Display::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Display::Prepare()
{
	
}

void Display::Update()
{
	glfwPollEvents();//Poll for and process events

	currentFrameTime = glfwGetTime();//Set the current time

									 //Update delta time
	delta = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	//Update fps
	frames++;
	if ((currentFrameTime - lastSecondTime) >= 1)
	{
		fps = frames;
		std::cout << fps << std::endl;
		lastSecondTime = currentFrameTime;
		frames = 0;
	}
}

void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
}

void Display::Terminate()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

static void* Display::glfwNativeWindowHandle()
{
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	return (void*)(uintptr_t)glfwGetX11Window(window);
#	elif BX_PLATFORM_OSX
	return glfwGetCocoaWindow(window);
#	elif BX_PLATFORM_WINDOWS
	return glfwGetWin32Window(window);
#	endif // BX_PLATFORM_
}

static void Display::glfwSetWindow()
{
	bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	pd.ndt = glfwGetX11Display();
#	elif BX_PLATFORM_OSX
	pd.ndt = NULL;
#	elif BX_PLATFORM_WINDOWS
	pd.ndt = NULL;
#	endif // BX_PLATFORM_WINDOWS
	pd.nwh = glfwNativeWindowHandle();
	pd.context = NULL;
	pd.backBuffer = NULL;
	pd.backBufferDS = NULL;
	bgfx::setPlatformData(pd);
}

GLFWwindow* Display::window;
double Display::lastSecondTime;
double Display::lastFrameTime;
double Display::currentFrameTime;
double Display::delta;
int Display::frames;
int Display::fps;