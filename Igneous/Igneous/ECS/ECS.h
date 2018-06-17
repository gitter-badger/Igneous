#pragma once

#include <string>

#include <entt\entt.hpp>

namespace ECS
{
	bool Init();
	std::string GetEnTTVersion();
	void Terminate();
}