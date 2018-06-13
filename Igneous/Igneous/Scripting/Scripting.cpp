#include "Scripting.h"

#include <iostream>

bool Scripting::Init()
{
	mono_set_dirs("mono\\lib", "mono\\etc");
	domain = mono_jit_init("Igneous");
	mono_add_internal_call("Igneous.Test::Run", Run);
	assembly = mono_domain_assembly_open(domain, "Game.dll");
	if (!assembly)
	{
		std::cerr << "Failed to open the assembly!" << std::endl;
		return false;
	}
	image = mono_assembly_get_image(assembly);
	MonoClass* gameClass = mono_class_from_name(image, "Game", "Game");
	MonoMethod* mainMethod = mono_class_get_method_from_name(gameClass, "Main", 0);
	mono_runtime_invoke(mainMethod, NULL, NULL, NULL);

	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os, sol::lib::io, sol::lib::jit, sol::lib::coroutine, sol::lib::count, sol::lib::table, sol::lib::string, sol::lib::debug, sol::lib::bit32);

	sol::table igneousTable = lua.create_named_table("igneous");
	igneousTable.set("version", "v0.0.2");
	igneousTable.set("major", 0);
	igneousTable.set("minor", 0);
	igneousTable.set("patch", 2);

	sol::table entitiesTable = lua.create_named_table("entities");

	sol::table componentsTable = lua.create_named_table("components");

	sol::table audioTable = lua.create_named_table("audio");

	sol::table physicsTable = lua.create_named_table("physics");

	sol::table savesTable = lua.create_named_table("saves");

	sol::table uiTable = lua.create_named_table("ui");

	sol::table displayTable = lua.create_named_table("display");

	return true;
}

std::string Scripting::GetMonoVersion()
{
	return mono_get_runtime_build_info();
}

std::string Scripting::GetLuaVersion()
{
	return lua.get<std::string>("_VERSION");
}

std::string Scripting::GetLuaJITVersion()
{
	sol::table jitTable = lua.get<sol::table>("jit");
	return jitTable.get<std::string>("version");
}

bool Scripting::RunLua(const char* fileName)
{
	auto result = lua.script_file(fileName);
	if (!result.valid())
	{
		sol::error err = result;
		std::cerr << "Script failed!" << std::endl << "ERROR: " << err.what() << std::endl;
		return false;
	}
	return true;
}

void Scripting::Terminate()
{
	mono_jit_cleanup(domain);
}

void Scripting::Run()
{
	std::clog << "C# Ran!" << std::endl;
}

MonoDomain *Scripting::domain;
MonoAssembly* Scripting::assembly;
MonoImage* Scripting::image;
sol::state Scripting::lua;