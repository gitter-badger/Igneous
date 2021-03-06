// Igneous.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Loader\Loader.h"
#include "Audio\Audio.h"
#include "Renderer\Display\Display.h"
#include "Renderer\Renderer.h"
#include "Scripting\Scripting.h"
#include "Input\Input.h"
#include "Physics\Physics.h"
#include "Networking\Networking.h"
#include "ECS\ECS.h"

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

	if (!Scripting::Init())
	{
		std::cerr << "Failed to initialize scripting!" << std::endl;
		return -1;
	}

	if (!ECS::Init())
	{
		std::cerr << "Failed to initialize ECS!" << std::endl;
		return -1;
	}

	std::clog << "GLFW Version: " << Renderer::GetGLFWVersion() << std::endl;

	std::clog << "GLM Version: " << Renderer::GetGLMVersion() << std::endl;

	std::clog << "bgfx Version: " << Renderer::GetbgfxVersion() << std::endl;
	std::clog << "Graphics Renderer: " << Renderer::GetRenderer() << std::endl;
	std::clog << "Supported Graphics Renderers: " << Renderer::GetSupportedRenderers() << std::endl;
	std::clog << Renderer::GetGpuInfo();

	std::clog << "OpenAL Version: " << Audio::GetVersion() << std::endl;
	std::clog << "OpenAL Vendor: " << Audio::GetVendor() << std::endl;
	std::clog << "OpenAL Renderer: " << Audio::GetRenderer() << std::endl;
	std::clog << "OpenAL Extensions: " << Audio::GetExtensions() << std::endl;
	std::clog << "OpenAL Devices: " << Audio::GetDevices() << std::endl;

	std::clog << "EnTT Version:" << ECS::GetEnTTVersion() << std::endl;

	std::clog << "Bullet Physics Version: " << Physics::GetBulletVersion() << std::endl;

	std::clog << "Assimp Version: " << Loader::GetAssimpVersion() << std::endl;

	std::clog << "RakNet Version: " << Networking::GetRakNetVersion() << std::endl;

	std::clog << "Mono Version: " << Scripting::GetMonoVersion() << std::endl;
	std::clog << "Lua Version: " << Scripting::GetLuaVersion() << std::endl;
	std::clog << "LuaJIT Version: " << Scripting::GetLuaJITVersion() << std::endl;

	while (!Display::ShouldClose())
	{
		Display::Prepare();
		Display::ProcessInput();
		Renderer::Update();
		Display::Update();
	}

	Scripting::Terminate();
	Audio::Terminate();
	Renderer::Terminate();

	return 0;
}