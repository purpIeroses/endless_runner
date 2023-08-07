#include "SoundLibrary.h"

std::vector<Mix_Chunk*> SoundLibrary::sounds{};
std::vector<Mix_Music*> SoundLibrary::songs{};

bool SoundLibrary::Initialize()
{
	sounds.push_back(Mix_LoadWAV("assets/8bitjump.wav"));
	songs.push_back(Mix_LoadMUS("assets/music.ogg"));
	songs.push_back(Mix_LoadMUS("assets/mainmenu.ogg"));
	for (unsigned int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i] == NULL)
		{
			printf("Could not load files");
			return false;
		}
	}
	for (unsigned int i = 0; i < songs.size(); i++)
	{
		if (songs[i] == NULL)
		{
			printf("Could not load files");
			return false;
		}
	}
	return true;
}

Mix_Chunk* SoundLibrary::getSound(int index)
{
	return sounds[index];
}

Mix_Music* SoundLibrary::getSong(int index)
{
	return songs[index];
}
