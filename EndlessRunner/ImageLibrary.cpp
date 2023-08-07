#include "ImageLibrary.h"

bool ImageLibrary::Initialize(Screen* screen)
{
	surfaces.push_back(IMG_Load("assets/Gummy_Rat_Run.png")); //0
	surfaces.push_back(IMG_Load("assets/Chocolate_Square.png")); //1
	surfaces.push_back(IMG_Load("assets/Lollipop.png")); //2 
	surfaces.push_back(IMG_Load("assets/Gummy_Rat_Crouch.png"));
	surfaces.push_back(IMG_Load("assets/Death.png")); //4
	letters = IMG_Load("assets/letters.png");
	numbers = IMG_Load("assets/numbers.png");
	PushSprite(IMG_Load("assets/Button_Selected.png"), screen); //0
	PushSprite(IMG_Load("assets/Button_NotSelected.png"), screen); //1
	PushSprite(IMG_Load("assets/Background_1.png"), screen); //2
	PushSprite(IMG_Load("assets/Background_2.png"), screen); //3
	PushSprite(IMG_Load("assets/Background_3.png"), screen); //4
	PushSprite(IMG_Load("assets/Background_4.png"), screen); //5
	PushSprite(IMG_Load("assets/Background_5.png"), screen); //6
	PushSprite(IMG_Load("assets/Selection_Arrow.png"), screen); //7
	PushSprite(IMG_Load("assets/Slider.png"), screen); //8
	PushSprite(IMG_Load("assets/Slider_Button.png"), screen); //9
	PushSprite(IMG_Load("assets/Ground.png"), screen); // 10
	PushSprite(IMG_Load("assets/InputUnderline.png"), screen); // 11
	for (unsigned int i = 0; i <= 9; i++)
	{
		digitSprites[i].SetSource(i * 8, 0, 8, 8);
		digitSprites[i].m_surface = numbers;
		digitSprites[i].m_texture = SDL_CreateTextureFromSurface(screen->renderer, numbers);
		digitSprites[i].SetDestination(0, 0, 8, 8);
	}
	for (unsigned int i = 0; i < 26; i++)
	{
		Sprite s;
		s.m_surface = letters;
		s.m_texture = SDL_CreateTextureFromSurface(screen->renderer, s.m_surface);
		s.SetDestination(0, 0, s.m_surface->w, s.m_surface->h);
		s.SetSource(i*8, 64, 8, 8);
		letterSprites.push_back(s);
	}
	for (unsigned int i = 0; i < surfaces.size(); i++)
	{
		if (surfaces[i] == NULL)
		{
			printf("Could not load files");
			return false;
		}
	}
	return true;
}
void ImageLibrary::FreeSurfaces()
{
	for (unsigned int i = 0; i < surfaces.size(); i++)
	{
		SDL_FreeSurface(ImageLibrary::surfaces[i]);
	}
}

void ImageLibrary::PushSprite(SDL_Surface* surface, Screen* screen)
{
	Sprite* s = new Sprite();
	s->m_surface = surface;
	s->m_texture = SDL_CreateTextureFromSurface(screen->renderer, s->m_surface);
	s->SetDestination(0, 0, s->m_surface->w, s->m_surface->h);
	s->SetSource(0, 0, s->m_surface->w, s->m_surface->h);
	sprites.push_back(s);
}
void ImageLibrary::DeleteSprites()
{
	for (unsigned int i = 0; i < sprites.size(); i++)
	{
		SDL_DestroyTexture(sprites[i]->m_texture);
		sprites[i]->m_texture = nullptr;
		SDL_FreeSurface(sprites[i]->m_surface);
		sprites[i]->m_surface = nullptr;
		delete sprites[i];
		sprites[i] = nullptr;
	}
}