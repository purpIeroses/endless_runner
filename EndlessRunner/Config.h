#ifndef CONFIG_H_DEFINED
#define CONFIG_H_DEFINED

#include <string>

struct Config
{
	unsigned int HUDRenderDimensions;
	unsigned int RenderDimensions;
	unsigned int MusicVolume;

	char optionIdentifier[6];
	static constexpr int identifierBytes{ sizeof(char) * 6 };
	bool WriteOptions();
	void LoadOptions();
};

#endif