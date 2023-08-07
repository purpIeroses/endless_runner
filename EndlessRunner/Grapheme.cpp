#include "Grapheme.h"

Digit::Digit() :m_value(0) {};
Digit::Digit(const int value, const int x, const int y, const ImageLibrary& imageLibrary)
{
	m_value = value;
	m_trans.SetPosition((float)x, (float)y);
	m_sprite = imageLibrary.digitSprites[m_value];
	m_sprite.SetDestination((int)m_trans.m_position.x, (int)m_trans.m_position.y, 8, 8);
}
void Digit::Update(const ImageLibrary& imageLibrary)
{
	m_sprite = imageLibrary.digitSprites[m_value];
	m_sprite.SetDestination((int)m_trans.m_position.x, (int)m_trans.m_position.y, 8, 8);
}
void Digit::Render(RenderManager& renderManager)
{
	renderManager.AddToHUDRenderObjects(&m_sprite, &m_trans);
}
void Digit::Increment(ImageLibrary& imageLibrary)
{
	m_value++;
	m_value %= 10;
	Update(imageLibrary);
}
void Digit::Decrement(ImageLibrary& imageLibrary)
{
	m_value--;
	if (m_value < 0)
	{
		m_value = 9;
	}
	Update(imageLibrary);
}
void Digit::Add(const int value, ImageLibrary& imageLibrary)
{
	m_value += value;
	m_value %= 10;
	Update(imageLibrary);
}
Letter::Letter() : m_value('A') {}
Letter::Letter(const char c, const int x, const int y, ImageLibrary& imageLibrary)
{
	for (unsigned int i = 0; i <= 25; i++)
	{
		sprites[i] = imageLibrary.letterSprites[i];
	}
	m_value = c;
	m_trans.SetPosition((float)x, (float)y);
	Update();
}
void Letter::Update()
{
	switch (m_value)
	{
	case 'A': m_sprite = sprites[0]; break;
	case 'B': m_sprite = sprites[1]; break;
	case 'C': m_sprite = sprites[2]; break;
	case 'D': m_sprite = sprites[3]; break;
	case 'E': m_sprite = sprites[4]; break;
	case 'F': m_sprite = sprites[5]; break;
	case 'G': m_sprite = sprites[6]; break;
	case 'H': m_sprite = sprites[7]; break;
	case 'I': m_sprite = sprites[8]; break;
	case 'J': m_sprite = sprites[9]; break;
	case 'K': m_sprite = sprites[10]; break;
	case 'L': m_sprite = sprites[11]; break;
	case 'M': m_sprite = sprites[12]; break;
	case 'N': m_sprite = sprites[13]; break;
	case 'O': m_sprite = sprites[14]; break;
	case 'P': m_sprite = sprites[15]; break;
	case 'Q': m_sprite = sprites[16]; break;
	case 'R': m_sprite = sprites[17]; break;
	case 'S': m_sprite = sprites[18]; break;
	case 'T': m_sprite = sprites[19]; break;
	case 'U': m_sprite = sprites[20]; break;
	case 'V': m_sprite = sprites[21]; break;
	case 'W': m_sprite = sprites[22]; break;
	case 'X': m_sprite = sprites[23]; break;
	case 'Y': m_sprite = sprites[24]; break;
	case 'Z': m_sprite = sprites[25]; break;
	default: m_sprite = sprites[0]; break;
	}
}
void Letter::Render(RenderManager& renderManager)
{
	renderManager.AddToHUDRenderObjects(&m_sprite, &m_trans);
}

Number::Number()
{
}

Number::Number(const int x, const int y, const float scale, const int integers, ImageLibrary& imageLibrary) :
	m_value(0)
{
	for (int i = 0; i < integers; i++)
	{
		digits.push_back(Digit(0, x + (8 * i) * (int)scale + 48, y, imageLibrary));
		digits[i].m_trans.SetScale(scale, scale);
	}
}
Number::Number(const int value, const int x, const int y, const float scale, const int integers, ImageLibrary& imageLibrary) :
	m_value(0)
{
	for (int i = 0; i < integers; i++)
	{
		digits.push_back(Digit(0, x + (8 * i) * (int)scale + 48, y, imageLibrary));
		digits[i].m_trans.SetScale(scale, scale);
	}
	Add(value, imageLibrary);
}
Number::~Number()
{

}
void Number::Increment(ImageLibrary& imageLibrary)
{
	OnIncrement(digits.size() - 1, imageLibrary);
	m_value++;
}
void Number::OnIncrement(const int i, ImageLibrary& imageLibrary)
{
	if (digits[i].m_value == 9 && i != 0)
	{
		OnIncrement(i - 1, imageLibrary);
	}
	digits[i].Increment(imageLibrary);
}
void Number::Add(const int value, ImageLibrary& imageLibrary)
{
	if (digits[digits.size() - 1].m_value + value > 9 && digits.size() - 1 != 0)
	{
		OnAdd(value, 10, value + digits[digits.size() - 1].m_value, 99, digits.size() - 2, imageLibrary);
		digits[digits.size() - 1].Add(value % 10, imageLibrary);
	}
	else
	{
		digits[digits.size() - 1].Add(value, imageLibrary);
	}
	m_value += value;
}
void Number::OnAdd(const int value, const int modifier, const int totalValue, const int limit, const int i, ImageLibrary& imageLibrary)
{
	if (digits[i].m_value * modifier + totalValue > limit
		&&
		i != 0)
	{
		OnAdd(value, modifier * 10, totalValue + digits[i].m_value * modifier, limit * 10 + 9, i - 1, imageLibrary);
	}
	digits[i].Add((totalValue / modifier) % 10, imageLibrary);
}
void Number::Decrement()
{

}
void Number::Subtract(int value)
{

}
void Number::Multiply(int value)
{

}
void Number::Divide(int value)
{

}
void Number::Exponentiate(int value)
{

}
void Number::Reset(ImageLibrary& imageLibrary)
{
	for (unsigned int i = 0; i < digits.size(); i++)
	{
		digits[i].m_value = 0; digits[i].Update(imageLibrary);
	}
	m_value = 0;
}
void Number::Render(RenderManager& renderManager)
{
	for (unsigned int i = 0; i < digits.size(); i++)
	{
		digits[i].Render(renderManager);
	}
}
Word::Word()
{

}
Word::Word(const std::string word, ImageLibrary& imageLibrary)
{
	for (int i = 0; i < word.size(); i++)
	{
		letters.push_back(Letter(word[i], 0,0, imageLibrary));
	}
}
Word::Word(const std::string word, const int x,const int y, ImageLibrary& imageLibrary)
{
	for (int i = 0; i < word.size(); i++)
	{
		letters.push_back(Letter(word[i], x + (i * 8), y, imageLibrary));
	}
}
void Word::Move(Vector2 newPosition)
{
	for (int i = 0; i < letters.size(); i++)
	{
		letters[i].m_trans.SetPosition(newPosition.x + (i * 8), newPosition.y);
	}
}
void Word::Render(RenderManager& rM)
{
	for (int i = 0; i < letters.size(); i++)
	{
		letters[i].Render(rM);
	}
}
void Word::Reset()
{
	for (int i = letters.size()-1; i >= 0; i--)
	{
		letters.pop_back();
	}
}