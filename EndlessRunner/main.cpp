#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SDL.h"
#include "SdlManager.h"
#include "Game.h"
#include "Keycode.h"
#include "SceneManager.h"

#pragma region EnumTranslations

KeyCode TranslateKeyCode(SDL_Keycode code)
{
	switch (code)
	{
	case SDLK_ESCAPE: return KeyCode::ESCAPE; break;
	case SDLK_SPACE: return KeyCode::SPACE; break;
	case SDLK_RETURN: return KeyCode::ENTER; break;
	case SDLK_RETURN2: return KeyCode::ENTER; break;
	case SDLK_a: return KeyCode::A; break;
	case SDLK_b: return KeyCode::B; break;
	case SDLK_c: return KeyCode::C; break;
	case SDLK_d: return KeyCode::D; break;
	case SDLK_e: return KeyCode::E; break;
	case SDLK_f: return KeyCode::F; break;
	case SDLK_g: return KeyCode::G; break;
	case SDLK_h: return KeyCode::H; break;
	case SDLK_i: return KeyCode::I; break;
	case SDLK_j: return KeyCode::J; break;
	case SDLK_k: return KeyCode::K; break;
	case SDLK_l: return KeyCode::L; break;
	case SDLK_m: return KeyCode::M; break;
	case SDLK_n: return KeyCode::N; break;
	case SDLK_o: return KeyCode::O; break;
	case SDLK_p: return KeyCode::P; break;
	case SDLK_q: return KeyCode::Q; break;
	case SDLK_r: return KeyCode::R; break;
	case SDLK_s: return KeyCode::S; break;
	case SDLK_t: return KeyCode::T; break;
	case SDLK_u: return KeyCode::U; break;
	case SDLK_v: return KeyCode::V; break;
	case SDLK_w: return KeyCode::W; break;
	case SDLK_x: return KeyCode::X; break;
	case SDLK_y: return KeyCode::Y; break;
	case SDLK_z: return KeyCode::Z; break;
	case SDLK_LEFT: return KeyCode::LEFT_ARROW; break;
	case SDLK_RIGHT: return KeyCode::RIGHT_ARROW; break;
	case SDLK_UP: return KeyCode::UP_ARROW; break;
	case SDLK_DOWN: return KeyCode::DOWN_ARROW; break;
	case SDLK_BACKSPACE: return KeyCode::BACKSPACE; break;
	case SDLK_F1  : return KeyCode::F1; break;
	case SDLK_F2: return KeyCode::F2; break;
	case SDLK_F3: return KeyCode::F3; break;
	default: return KeyCode::INVALID; break;
	}
}

#pragma endregion

int main(int argc, char* args[])
{
	SdlManager sdlManager;
	sdlManager.Init();

	Game game;

	ImageLibrary imageLibrary;
	imageLibrary.Initialize(&game.screen);

	game.Init(imageLibrary);

	SceneManager sceneManager = SceneManager(game.managers.rM, game.managers.gM, game.managers.sdM, imageLibrary, game.managers.hM);
	sceneManager.ChangeScreen(game.managers.gM, game.managers.rM, game.managers.sdM, imageLibrary);

	bool quit = false;
	SDL_Event event;

	const int framesPerSecond = 24;
	const int frameLength = 1000 / framesPerSecond;

	while (!quit)
	{
		auto time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
			case SDL_QUIT: quit = true; break;
			case SDL_KEYDOWN: game.OnKeyDown(TranslateKeyCode(event.key.keysym.sym), sceneManager, imageLibrary); break;
			case SDL_KEYUP: game.OnKeyUp(TranslateKeyCode(event.key.keysym.sym)); break;
			}
		}
		quit = !game.Run(time, sceneManager, imageLibrary);
		sceneManager.Update(game.managers.rM, game.managers.gM, game.managers.sdM, imageLibrary);

		game.Render(imageLibrary);

		int timeElapsed = SDL_GetTicks() - time;
		int timeToWait = frameLength - timeElapsed;

		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}
		if (event.type == SDL_QUIT) {
			quit = true;
		}
	}

	sceneManager.OnQuitGame();
	game.QuitGame();

	imageLibrary.DeleteSprites();
	imageLibrary.FreeSurfaces();

	_CrtDumpMemoryLeaks();
	
	return 0;
}
