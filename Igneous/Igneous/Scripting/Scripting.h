#pragma once
#include <string>

#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>
#include <sol\sol.hpp>

namespace Scripting
{
	bool Init();
	std::string GetMonoVersion();
	std::string GetLuaVersion();
	std::string GetLuaJITVersion();
	bool RunLua(const char* fileName);
	void Terminate();

	void Run();

	extern MonoDomain *domain;
	extern MonoAssembly* assembly;
	extern MonoImage* image;
	extern sol::state lua;
}