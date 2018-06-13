#pragma once
#include <string>

namespace Networking
{
	bool Init();
	std::string GetRakNetVersion();
	void Terminate();
}