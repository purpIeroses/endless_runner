#ifndef HIGHSCORE_H_DEFINED
#define HIGHSCORE_H_DEFINED

#include <fstream>
#include <string>
class Highscore
{
	static constexpr int maxNameLetters{ 11 };
	static constexpr int scoreBytes{ sizeof(unsigned int) * 5 };
	static constexpr int nameBytes{ sizeof(char) * maxNameLetters * 5 };
	static char fileData[nameBytes + scoreBytes];
public:
	unsigned int score1;
	unsigned int score2;
	unsigned int score3;
	unsigned int score4;
	unsigned int score5;
	char name1[11];
	char name2[11];
	char name3[11];
	char name4[11];
	char name5[11];

	int currentScore;

	Highscore();
	~Highscore();

	void LoadHighScore();
	void PrintHighScore();
	void UpdateHighScore(unsigned int newScore, std::string newName);
	void SaveName(std::string newName, char* scoreHolder);
	bool SaveHighScore();
};

#endif