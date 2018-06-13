#include "Renderer.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb\image.h>

bool Renderer::Init()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(800, 600, "Igneous", NULL, NULL);//Create the window
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

bool Renderer::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Renderer::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Renderer::Prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the buffers
}

void Renderer::Update()
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

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Renderer::Terminate()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Renderer::window;
double Renderer::lastSecondTime;
double Renderer::lastFrameTime;
double Renderer::currentFrameTime;
double Renderer::delta;
int Renderer::frames;