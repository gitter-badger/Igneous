#include "Networking.h"

#include <raknet\RakNetVersion.h>

bool Networking::Init()
{
	return true;
}

std::string Networking::GetRakNetVersion()
{
	return RAKNET_VERSION;
}

void Networking::Terminate()
{

}