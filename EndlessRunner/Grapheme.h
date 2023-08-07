#ifndef GRAPHEME_H_DEFINED
#define GRAPHEME_H_DEFINED

#include "Transform.h"
#include "Sprite.h"
#include "RenderManager.h"
#include "ImageLibrary.h"
#include <string>

struct Digit
{
	int m_value;

	Transform m_trans;
	Sprite m_sprite;

	Digit();
	Digit(const int value, const int x, const int y, const ImageLibrary& imageLibrary);
	void Update(const ImageLibrary& imageLibrary);
	void Render(RenderManager& renderManager);
	void Increment(ImageLibrary& imageLibrary);
	void Decrement(ImageLibrary& imageLibrary);
	void Add(const int value, ImageLibrary& imageLibrary);
};

struct Letter
{
	Sprite sprites[26];
	Sprite m_sprite;
	Transform m_trans;
	char m_value;
	Letter();
	Letter(const char c, const int x, const int y, ImageLibrary& imageLibrary);
	void Update();
	void Render(RenderManager& renderManager);
};

struct Word
{
	std::string word;
	std::vector<Letter> letters;
	Word();
	Word(const std::string word, ImageLibrary& imageLibrary);
	Word(const std::string word, const int x, const int y, ImageLibrary& imageLibrary);
	void Move(Vector2 newPosition);
	void Render(RenderManager& renderManager);
	void Reset();
};

struct Number
{
	std::vector<Digit> digits;
	int m_value;

	Number();
	Number(const int x, const int y, const float scale, const int integers, ImageLibrary& imageLibrary);
	Number(const int value, const int x, const int y, const float scale, const int integers, ImageLibrary& imageLibrary);
	~Number();

	void Increment(ImageLibrary& imageLibrary); void OnIncrement(int i, ImageLibrary& imageLibrary);
	void Add(const int value, ImageLibrary& imageLibrary); void OnAdd(const int value, const int modifier, const int totalValue, const int limit, const int i, ImageLibrary& imageLibrary);

	void Decrement();
	void Subtract(int value);
	void Multiply(int value);
	void Divide(int value);
	void Exponentiate(int value);
	void Reset(ImageLibrary& imageLibrary);
	void Render(RenderManager& renderManager);
};
#endif