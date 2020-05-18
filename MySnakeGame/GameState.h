#pragma once
#include"Game.h"

class GameState
{
public :
	static void YouWin(SDL_Renderer* renderer,SDL_Event event,int wscale,int hscale,int tailLength);
	static void GameOver(SDL_Renderer* renderer, SDL_Event event, int wscale, int hscale, int tailLength);
};

