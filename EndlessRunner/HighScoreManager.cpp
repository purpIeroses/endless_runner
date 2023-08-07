#include "Highscore.h"

char Highscore::fileData[nameBytes + scoreBytes]{};

Highscore::Highscore()
{
	LoadHighScore();
}

Highscore::~Highscore()
{

}

void Highscore::LoadHighScore()
{
	FILE* file;
	fopen_s(&file, "HighScore.txt", "rb");
	if (!file) return;
	uint8_t fileData[nameBytes + scoreBytes];
	fread(fileData, 1, nameBytes + scoreBytes, file);

	uint8_t* fileDataHead = fileData;

	memcpy(&score1, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(&score2, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(&score3, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(&score4, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(&score5, fileDataHead, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	memcpy(name1, fileDataHead, strlen((const char*)fileDataHead));
	fileDataHead += strlen(name1) + 1;
	memcpy(name2, fileDataHead, strlen((const char*)fileDataHead));
	fileDataHead += strlen(name2) + 1;
	memcpy(name3, fileDataHead, strlen((const char*)fileDataHead));
	fileDataHead += strlen(name3) + 1;
	memcpy(name4, fileDataHead, strlen((const char*)fileDataHead));
	fileDataHead += strlen(name4) + 1;
	memcpy(name5, fileDataHead, strlen((const char*)fileDataHead));
	fileDataHead += strlen(name5) + 1;
	fclose(file);
}
void Highscore::PrintHighScore()
{
	/*std::cout << "Score 1: " << score1 << " by: " << name1 << std::endl;
	std::cout << "Score 2: " << score2 << " by: " << name2 << std::endl;
	std::cout << "Score 3: " << score3 << " by: " << name3 << std::endl;
	std::cout << "Score 4: " << score4 << " by: " << name4 << std::endl;
	std::cout << "Score 5: " << score5 << " by: " << name5 << std::endl;*/
}
void Highscore::UpdateHighScore(unsigned int newScore, std::string newName)
{
	if (newScore <= score1)
	{
		if (newScore <= score2)
		{
			if (newScore <= score3)
			{
				if (newScore <= score4)
				{
					if (newScore < score5)
					{
						return;
					}
					score5 = newScore;
					SaveName(newName, name5);
					return;
				}
				score5 = score4;
				score4 = newScore;
				SaveName(name4, name5);
				SaveName(newName, name4);
				return;
			}
			score5 = score4;
			score4 = score3;
			score3 = newScore;
			SaveName(name4, name5);
			SaveName(name3, name4);
			SaveName(newName, name3);
			return;
		}
		score5 = score4;
		score4 = score3;
		score3 = score2;
		score2 = newScore;
		SaveName(name4, name5);
		SaveName(name3, name4);
		SaveName(name2, name3);
		SaveName(newName, name2);
		return;
	}
	score5 = score4;
	score4 = score3;
	score3 = score2;
	score2 = score1;
	score1 = newScore;
	SaveName(name4, name5);
	SaveName(name3, name4);
	SaveName(name2, name3);
	SaveName(name1, name2);
	SaveName(newName, name1);
	return;
}
void Highscore::SaveName(std::string newName, char* scoreHolder)
{
	int temp = (int)newName.length();
	if (temp > 10) { temp = 10; };
	for (int i = 0; i <= 10; i++)
	{
		if (i < temp)
		{
			scoreHolder[i] = newName[i];
		}
		else
		{
			scoreHolder[i] = '\0';
		}
	}
}
bool Highscore::SaveHighScore()
{
	FILE* file;
	fopen_s(&file, "HighScore.txt", "wb");
	if (!file) return false;
	uint8_t fileData[nameBytes + scoreBytes] = { };
	uint8_t* fileDataHead = fileData;

	memcpy(fileDataHead, &score1, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(fileDataHead, &score2, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(fileDataHead, &score3, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(fileDataHead, &score4, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);
	memcpy(fileDataHead, &score5, sizeof(unsigned int));
	fileDataHead += sizeof(unsigned int);

	memcpy(fileDataHead, name1, strlen(name1));
	fileDataHead += strlen(name1) + 1;
	memcpy(fileDataHead, name2, strlen(name2));
	fileDataHead += strlen(name2) + 1;
	memcpy(fileDataHead, name3, strlen(name3));
	fileDataHead += strlen(name3) + 1;
	memcpy(fileDataHead, name4, strlen(name4));
	fileDataHead += strlen(name4) + 1;
	memcpy(fileDataHead, name5, strlen(name5));
	fileDataHead += strlen(name5) + 1;

	__analysis_assume(_Old_3 > 70)fwrite(fileData, 1, nameBytes + scoreBytes, file);
	fclose(file);
	return true;
}