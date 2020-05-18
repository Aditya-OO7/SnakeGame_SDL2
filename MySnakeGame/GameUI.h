#pragma once
#include"Game.h"

class GameUI
{
public :
	int StartUI(SDL_Renderer* _renderer, SDL_Event evnt, int wscale);
	void Title(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color RED, int wscale);
	void StartGame(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color YELLOW, int wscale);
	void Options(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color YELLOW, int wscale);
	void Quit(SDL_Renderer* _renderer, TTF_Font* font, SDL_Color YELLOW, int wscale);
	int SpeedOptions(SDL_Renderer* _renderer, SDL_Event evnt, TTF_Font* font, SDL_Color YELLOW, int wscale);
};

