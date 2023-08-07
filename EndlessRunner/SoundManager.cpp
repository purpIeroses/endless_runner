#include "SoundManager.h"

SoundManager::SoundManager() : sfx_volume(0), music_volume(0)
{ 
	lib.Initialize(); 
}

SoundManager::SoundManager(int p_sfxvolume)
{
	sfx_volume = p_sfxvolume;
}

SoundManager::~SoundManager() {}

void SoundManager::LoadSettings(Config& config)
{
	m_config = &config;
	music_volume = m_config->MusicVolume;
}
void SoundManager::PlaySound(int index, Mix_Chunk* chunk, int loops)
{
	Mix_PlayChannel(1, chunk, loops);
}

void SoundManager::SetSoundVolume(int volume)
{
	sfx_volume = volume;
	Mix_Volume(1, sfx_volume);
}

void SoundManager::PlayMusic(Mix_Music* song)
{
	Mix_PlayMusic(song, -1);
}

void SoundManager::MusicPlaying(bool playing)
{
	if (playing)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

void SoundManager::Update()
{
	SetMusicVolume(music_volume);
}

void SoundManager::SetMusicVolume(int volume)
{
	music_volume = volume;
	Mix_VolumeMusic(music_volume);
}
void SoundManager::OnQuit()
{
	m_config->MusicVolume = music_volume;
}