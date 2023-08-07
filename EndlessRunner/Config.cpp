#include "Config.h"

bool Config::WriteOptions()
{
	FILE* file;
	fopen_s(&file, "Config.txt", "wb");
	if (!file) return false;
	uint8_t fileData[identifierBytes * 3 + sizeof(unsigned int) * 3] = { };
	uint8_t* fileDataHead = fileData;

	memcpy(fileDataHead, "RNsz:", strlen("RNsz:")); //Rendersize
	fileDataHead += strlen("RNsz:") + 1;

	memcpy(fileDataHead, &RenderDimensions, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	memcpy(fileDataHead, "UIsz:", strlen("UIsz:")); //UISize
	fileDataHead += strlen("UIsz:") + 1;

	memcpy(fileDataHead, &HUDRenderDimensions, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	memcpy(fileDataHead, "MusV:", strlen("MusV:")); //UISize
	fileDataHead += strlen("MusV:") + 1;

	memcpy(fileDataHead, &MusicVolume, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	fwrite(fileData, 1, sizeof(unsigned int) * 3 + identifierBytes * 3, file);
	fclose(file);
	return true;
}

void Config::LoadOptions()
{
	FILE* file;
	fopen_s(&file, "Config.txt", "rb"); 
	if (!file) return;
	uint8_t fileData[sizeof(unsigned int) * 3 + identifierBytes * 3];
	fread(fileData, 1, sizeof(unsigned int) * 3 + identifierBytes * 3, file);

	uint8_t* fileDataHead = fileData;

	fileDataHead += strlen((const char*)fileDataHead) + 1; //Skips the identifier name
	//unsigned int number = 0;
	memcpy(&RenderDimensions, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	fileDataHead += strlen((const char*)fileDataHead) + 1; //Skips the identifier name
	memcpy(&HUDRenderDimensions, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	fileDataHead += strlen((const char*)fileDataHead) + 1; //Skips the identifier name
	memcpy(&MusicVolume, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	fclose(file);
}