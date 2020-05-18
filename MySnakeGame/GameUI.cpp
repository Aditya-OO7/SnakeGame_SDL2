#include "GameUI.h"
#include<process.h>

int GameUI::StartUI(SDL_Renderer* _renderer,SDL_Event evnt, int wscale)
{
	while (true)
	{
		
		SDL_Color RED = { 0, 255, 0, 255 };
		SDL_Color YELLOW = { 255,255,255 };

		TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 100);
		if (font == NULL) {
			cout << "Font loading error" << endl;
			break;
		}

		Title(_renderer, font, RED, wscale);
		StartGame(_renderer, font, YELLOW, wscale);
		Options(_renderer, font, YELLOW, wscale);
		Quit(_renderer, font, YELLOW, wscale);

		TTF_CloseFont(font);

		SDL_RenderPresent(_renderer);

		SDL_SetRenderDrawColor(_renderer, 105, 105, 105, 255);

		SDL_RenderClear(_renderer);


		if (SDL_PollEvent(&evnt))
		{
			cout << evnt.motion.x << " " << evnt.motion.y << endl;
			switch (evnt.type)
			{
			case SDL_QUIT :
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN :
				//start game :
				if ((evnt.button.x >= 160 && evnt.button.x <= 385) && (evnt.button.y >= 205 && evnt.button.y <= 235))
				{
					return 75;
				}
				//options :
				else if ((evnt.button.x >= 190 && evnt.button.x <= 350) && (evnt.button.y >= 280 && evnt.button.y <= 310))
				{
					cout << "Button Clicked....";
					int speedT = SpeedOptions(_renderer, evnt, font, YELLOW, wscale);
					return speedT;
				}
				//quit :
				else if ((evnt.button.x >= 227 && evnt.button.x <= 312) && (evnt.button.y >= 360 && evnt.button.y <= 390))
				{
					exit(0);
				}
				break;
			default:
				break;
			}
		}
	}
}

void GameUI::Title(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color RED, int wscale)
{
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "- SNAKE GAME -", RED);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(_renderer, gameover);

	SDL_Rect gameoverRect;

	gameoverRect.w = 344;
	gameoverRect.h = 40;
	gameoverRect.x = 115;
	gameoverRect.y = 90;

	SDL_RenderCopy(_renderer, gameoverMessage, NULL, &gameoverRect);
}

void GameUI::StartGame(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color YELLOW, int wscale)
{
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "START GAME", YELLOW);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(_renderer, gameover);

	SDL_Rect gameoverRect;

	gameoverRect.w = 225;
	gameoverRect.h = 30;
	gameoverRect.x = 160;
	gameoverRect.y = 205;

	SDL_RenderCopy(_renderer, gameoverMessage, NULL, &gameoverRect);
}

void GameUI::Options(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color YELLOW, int wscale)
{
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "OPTIONS", YELLOW);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(_renderer, gameover);

	SDL_Rect gameoverRect;

	gameoverRect.w = 160;
	gameoverRect.h = 30;
	gameoverRect.x = 190;
	gameoverRect.y = 280;

	SDL_RenderCopy(_renderer, gameoverMessage, NULL, &gameoverRect);
}

void GameUI::Quit(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color YELLOW, int wscale)
{
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "QUIT", YELLOW);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(_renderer, gameover);

	SDL_Rect gameoverRect;

	gameoverRect.w = 85;
	gameoverRect.h = 30;
	gameoverRect.x = 227;
	gameoverRect.y = 360;

	SDL_RenderCopy(_renderer, gameoverMessage, NULL, &gameoverRect);
}

int GameUI::SpeedOptions(SDL_Renderer* _renderer, SDL_Event evnt, TTF_Font* font, SDL_Color YELLOW, int wscale)
{
	while (true)
	{
		TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 100);
		if (font == NULL) {
			cout << "Font loading error" << endl;
			break;
		}

		SDL_Surface* options = TTF_RenderText_Solid(font, "- OPTIONS -", YELLOW);
		SDL_Texture* optionsMessage = SDL_CreateTextureFromSurface(_renderer, options);

		SDL_Rect optionsRect;

		optionsRect.w = 344;
		optionsRect.h = 40;
		optionsRect.x = 115;
		optionsRect.y = 90;

		SDL_RenderCopy(_renderer, optionsMessage, NULL, &optionsRect);

		SDL_Surface* speed = TTF_RenderText_Solid(font, "SPEED", YELLOW);
		SDL_Texture* speedMessage = SDL_CreateTextureFromSurface(_renderer, speed);

		SDL_Rect speedRect;

		speedRect.w = 120;
		speedRect.h = 30;
		speedRect.x = 230;
		speedRect.y = 185;

		SDL_RenderCopy(_renderer, speedMessage, NULL, &speedRect);

		SDL_Surface* slow = TTF_RenderText_Solid(font, "SLOW", YELLOW);
		SDL_Texture* slowMessage = SDL_CreateTextureFromSurface(_renderer, slow);

		SDL_Rect slowRect;

		slowRect.w = 80;
		slowRect.h = 20;
		slowRect.x = 75;
		slowRect.y = 300;

		SDL_RenderCopy(_renderer, slowMessage, NULL, &slowRect);

		SDL_Surface* medium = TTF_RenderText_Solid(font, "MEDIUM", YELLOW);
		SDL_Texture* mediumMessage = SDL_CreateTextureFromSurface(_renderer, medium);

		SDL_Rect mediumRect;

		mediumRect.w = 110;
		mediumRect.h = 20;
		mediumRect.x = 235;
		mediumRect.y = 300;

		SDL_RenderCopy(_renderer, mediumMessage, NULL, &mediumRect);

		SDL_Surface* high = TTF_RenderText_Solid(font, "HIGH", YELLOW);
		SDL_Texture* highMessage = SDL_CreateTextureFromSurface(_renderer, high);

		SDL_Rect highRect;

		highRect.w = 67;
		highRect.h = 20;
		highRect.x = 430;
		highRect.y = 300;

		SDL_RenderCopy(_renderer, highMessage, NULL, &highRect);
		TTF_CloseFont(font);

		SDL_RenderPresent(_renderer);

		SDL_RenderClear(_renderer);

		////--------------Input for speed from here below


		if (SDL_PollEvent(&evnt))
		{
			cout << evnt.motion.x << " " << evnt.motion.y << endl;

			switch (evnt.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				//slow :
				if ((evnt.button.x >= 75 && evnt.button.x <= 155) && (evnt.button.y >= 300 && evnt.button.y <= 320))
				{
					cout << "SLOW.......";
					return 100;
					
				}
				else if ((evnt.button.x >= 235 && evnt.button.x <= 345) && (evnt.button.y >= 300 && evnt.button.y <= 320))
				{
					cout << "MEDIUM ........";
					return 75;
				}
				else if ((evnt.button.x >= 430 && evnt.button.x <= 497) && (evnt.button.y >= 300 && evnt.button.y <= 320))
				{
					cout << "HIGH ............";
					return 25;
				}
			default:
				break;
			}
		}

	}
}
