#pragma once

#include <string>
#include <deque>

#include <AL\al.h>
#include <AL\alc.h>

namespace Audio
{
	bool Init();
	std::string GetVersion();
	std::string GetVendor();
	std::string GetRenderer();
	std::string GetExtensions();
	std::string GetDevices();
	void setListenerData(float x, float y, float z);
	int loadSound(const char * fileName);
	void Terminate();

	const char* ALErrorToString(ALCenum error);

	extern std::deque<ALint> buffers;

	extern ALCdevice* device;
	extern ALCcontext* context;
}