// Igneous.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assimp\version.h>
#include <bullet3\btBulletDynamicsCommon.h>
#include <raknet\RakNetVersion.h>
#include <AL\alc.h>
#include <glm\glm.hpp>

#include "Audio\Audio.h"
#include "Renderer\Renderer.h"

int main()
{
	std::clog << "Igneous Version: 0.0.2" << std::endl;

	if (!Renderer::Init())
	{
		std::cerr << "Failed to initialize the renderer!" << std::endl;
		return -1;
	}

	if (!Audio::Init())
	{
		std::cerr << "Failed to initialize the audio!" << std::endl;
		return -1;
	}

	std::clog << "GLAD Version: 0.1.16a0" << std::endl;

	std::clog << "GLFW Version: " << Renderer::GetGLFWVersion() << std::endl;

	std::clog << "OpenGL Version: " << Renderer::GetOpenGLVersion() << std::endl;
	std::clog << "OpenGL Vendor: " << Renderer::GetVendor() << std::endl;
	std::clog << "OpenGL Renderer: " << Renderer::GetRenderer() << std::endl;
	std::clog << "OpenGL Shading Language Version: " << Renderer::GetShaderLanguageVersion() << std::endl;
	std::clog << "OpenGL Extensions:" << Renderer::GetExtensions() << std::endl;

	std::clog << "OpenAL Version: " << Audio::GetVersion() << std::endl;
	std::clog << "OpenAL Vendor: " << Audio::GetVendor() << std::endl;
	std::clog << "OpenAL Renderer: " << Audio::GetRenderer() << std::endl;
	std::clog << "OpenAL Extensions: " << Audio::GetExtensions() << std::endl;
	std::clog << "OpenAL Devices: " << Audio::GetDevices() << std::endl;

	std::clog << "GLM Version: " << GLM_VERSION << std::endl;

	std::clog << "Bullet Physics Version: " << BT_BULLET_VERSION << std::endl;

	std::clog << "Assimp Version: " << aiGetVersionMajor() << "." << aiGetVersionMinor() << "." << aiGetVersionRevision() << std::endl;

	std::clog << "RakNet Version: " << RAKNET_VERSION << std::endl;

	while (!Renderer::ShouldClose())
	{
		Renderer::ProcessInput();
		Renderer::Prepare();
		Renderer::Update();
	}

	Audio::Terminate();
	Renderer::Terminate();

	return 0;
}

