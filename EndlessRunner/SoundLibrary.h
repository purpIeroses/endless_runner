#ifndef SOUNDLIBRARY_H_DEFINED
#define SOUNDLIBRARY_H_DEFINED

#include "SDL_mixer.h"
#include <vector>

struct SoundLibrary
{
	static std::vector<Mix_Chunk*> sounds;
	static std::vector<Mix_Music*> songs;
	static bool Initialize();
	Mix_Chunk* getSound(int index);
	Mix_Music* getSong(int index);
};

#endif