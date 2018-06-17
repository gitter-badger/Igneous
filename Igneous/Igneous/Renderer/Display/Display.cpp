#include "Display.h"

#include <iostream>

#include <stb\image.h>

bool Display::Init(const int width, const int height, const char* title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(width, height, title, NULL, NULL);//Create the window
	glfwMakeContextCurrent(window);

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

	//Setup delta time and fps counter
	currentFrameTime = glfwGetTime();
	lastSecondTime = currentFrameTime;
	lastFrameTime = currentFrameTime;
	frames = 0;
	return true;
}

bool Display::ShouldClose()
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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the buffers
}

void Display::Update()
{
	glfwSwapBuffers(window);//Swap front and back buffer
	glfwPollEvents();//Poll for and process events

	currentFrameTime = glfwGetTime();//Set the current time

									 //Update delta time
	delta = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	//Update fps
	frames++;
	if ((currentFrameTime - lastSecondTime) >= 1)
	{
		std::cout << frames << std::endl;
		lastSecondTime = currentFrameTime;
		frames = 0;
	}
}

void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Display::Terminate()
{
	glfwDestroyWindow(window);
}

GLFWwindow* Display::window;
double Display::lastSecondTime;
double Display::lastFrameTime;
double Display::currentFrameTime;
double Display::delta;
int Display::frames;