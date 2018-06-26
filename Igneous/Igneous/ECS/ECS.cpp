#include "ECS.h"

bool ECS::Init()
{
	return true;
}

std::string ECS::GetEnTTVersion()
{
	return "2.6.1";
}

void ECS::Terminate()
{

}

entt::DefaultRegistry registry;