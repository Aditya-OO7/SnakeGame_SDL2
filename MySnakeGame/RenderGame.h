#pragma once
#include"Game.h"

class RenderGame
{
public :
	void renderPlayer(SDL_Renderer* _renderer, SDL_Rect player, int x, int y, int wscale, vector<int> tailX, vector<int> tailY, int tailLength);
	void renderFood(SDL_Renderer* _renderer, SDL_Rect food);
	void renderScore(SDL_Renderer* _renderer, int tailLength, int wscale, int hscale);
};

