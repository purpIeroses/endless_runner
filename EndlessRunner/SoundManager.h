#ifndef SOUNDMANAGER_H_DEFINED
#define SOUNDMANAGER_H_DEFINED

#include <vector>
#include "SoundLibrary.h"
#include "Config.h"

//sound effects are all played in channel 1

struct SoundManager
{
	Config* m_config;
	int sfx_volume;
	float music_volume;
	SoundLibrary lib;
	SoundManager();
	SoundManager(int p_sfxvolume);
	~SoundManager();
	void LoadSettings(Config& config);
	void PlaySound(int index, Mix_Chunk* chunk, int loops);
	void SetSoundVolume(int volume);
	void PlayMusic(Mix_Music* song);
	void MusicPlaying(bool playing);
	void SetMusicVolume(int volume);
	void Update();
	void OnQuit();
};

#endif