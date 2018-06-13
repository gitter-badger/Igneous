#include "Audio.h"

#include <iostream>

#include <stb\vorbis.h>

bool Audio::Init()
{
	ALCenum error;
	// Initialize Open AL quit with error if it fails
	const ALCchar* deviceName = alcGetString(0, ALC_DEVICE_SPECIFIER);
	device = alcOpenDevice(deviceName);
	if (device)
	{
		context = alcCreateContext(device, NULL); // create context
		if (context)
		{
			if (!alcMakeContextCurrent(context))
			{
				std::cerr << "OpenAL failed to make context current!" << std::endl;
				error = alGetError();
				std::clog << ALErrorToString(error) << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "OpenAL failed to create a context!" << std::endl;
			error = alGetError();
			std::clog << ALErrorToString(error) << std::endl;
			return false;
		}
	}
	else
	{
		std::cerr << "OpenAL failed to open a device!" << std::endl;
		error = alGetError();
		std::clog << ALErrorToString(error) << std::endl;
		return false;
	}
	return true;
}

std::string Audio::GetVersion() { return alGetString(AL_VERSION); }
std::string Audio::GetVendor() { return alGetString(AL_VENDOR); }
std::string Audio::GetRenderer() { return alGetString(AL_RENDERER); }
std::string Audio::GetExtensions() { return alGetString(AL_EXTENSIONS); }
std::string Audio::GetDevices() { return alcGetString(NULL, ALC_DEVICE_SPECIFIER); }

void Audio::setListenerData(float x, float y, float z) {
	alListener3f(AL_POSITION, x, y, z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
}

int Audio::loadSound(const char* fileName) {
	ALuint buffer;
	alGenBuffers(1, &buffer);
	buffers.push_back(buffer);
	int error;
	stb_vorbis_alloc vorbisBuffer;
	stb_vorbis* vorbis = stb_vorbis_open_filename(fileName, &error, &vorbisBuffer);
	int channels;
	int sampleRate;
	ALshort* output;
	ALsizei frequency;
	stb_vorbis_decode_filename(fileName, &channels, &sampleRate, &output);
	ALenum format = 0;
	if (channels == 1)
		format = AL_FORMAT_MONO16;
	else if (channels == 2)
		format = AL_FORMAT_STEREO16;
	frequency = stb_vorbis_stream_length_in_samples(vorbis) * channels * sizeof(ALshort);
	alBufferData(buffer, format, output, frequency, sampleRate);
	stb_vorbis_close(vorbis);
	return buffer;
}

const char * Audio::ALErrorToString(ALCenum error)
{
	switch (error)
	{
	case ALC_NO_ERROR: return "ALC_NO_ERROR";
	case ALC_INVALID_DEVICE: return "ALC_INVALID_DEVICE";
	case ALC_INVALID_CONTEXT: return "ALC_INVALID_CONTEXT";
	case ALC_INVALID_ENUM: return "ALC_INVALID_ENUM";
	case ALC_INVALID_VALUE: return "ALC_INVALID_VALUE";
	case ALC_OUT_OF_MEMORY: return "ALC_OUT_OF_MEMORY";
	default: break;
	}
	return "Failed to find error";
}

void Audio::Terminate()
{
	for (const ALuint buffer : buffers) {
		alDeleteBuffers(1, &buffer);
		buffers.pop_front();
	}

	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

std::deque<ALint> Audio::buffers;
ALCdevice* Audio::device;
ALCcontext* Audio::context;