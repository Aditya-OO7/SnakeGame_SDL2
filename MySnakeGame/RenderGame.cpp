#include "RenderGame.h"

void RenderGame::renderPlayer(SDL_Renderer* _renderer, SDL_Rect player, int x, int y, int wscale, vector<int> tailX, vector<int> tailY, int tailLength)
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	player.w = wscale;
	player.h = wscale;

	// Gets x and y of all tail blocks and renders them
	for (int i = 0; i < tailLength; i++) {
		player.x = tailX[i];
		player.y = tailY[i];
		SDL_RenderFillRect(_renderer, &player);
	}

	player.x = x;
	player.y = y;

	SDL_RenderFillRect(_renderer, &player);
}

void RenderGame::renderFood(SDL_Renderer* _renderer, SDL_Rect food)
{
	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(_renderer, &food);
}

void RenderGame::renderScore(SDL_Renderer* _renderer, int tailLength, int wscale, int hscale)
{
	SDL_Color Black = { 0, 0, 0 };

	// Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(_renderer, score);
	SDL_Rect scoreRect;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((hscale * wscale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(_renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);
}
